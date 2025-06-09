package ru.nsu.slepchenko.lab.torrent;

import com.dampcake.bencode.BencodeInputStream;
import com.dampcake.bencode.BencodeOutputStream;
import java.io.*;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.nio.charset.StandardCharsets;
import java.nio.file.NoSuchFileException;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.*;

public class TorrentParser {
    private final File torrentFile;
    private final String downloadDir;

    public TorrentParser(String torrentPath, String downloadDir) {
        this.torrentFile = new File(torrentPath);
        this.downloadDir = downloadDir;
    }

    public TorrentMetadata parse() throws Exception {
        if (!torrentFile.exists()) {
            throw new FileNotFoundException("Torrent file not found: " + torrentFile.getPath());
        }

        try (FileInputStream fileInputStream = new FileInputStream(torrentFile)) {
            BencodeInputStream bencodeInputStream = new BencodeInputStream(fileInputStream, StandardCharsets.UTF_8, true);
            Map<String, Object> root = bencodeInputStream.readDictionary();
            Map<String, Object> infoMap = (Map<String, Object>) root.get("info");
            if (infoMap == null) {
                throw new IOException("Invalid torrent file: missing info dictionary");
            }

            String fileName = createFileName(infoMap);
            ByteBuffer piecesBuffer = (ByteBuffer) infoMap.get("pieces");
            if (piecesBuffer == null) {
                throw new IOException("Invalid torrent file: missing pieces");
            }

            long fileSize = (Long) infoMap.getOrDefault("length", 0L);
            if (fileSize <= 0) {
                throw new IOException("Invalid torrent file: invalid file size");
            }

            int pieceSize = ((Long) infoMap.getOrDefault("piece length", 0L)).intValue();
            if (pieceSize <= 0) {
                throw new IOException("Invalid torrent file: invalid piece length");
            }

            byte[] piecesBytes = new byte[piecesBuffer.remaining()];
            piecesBuffer.get(piecesBytes);
            List<byte[]> pieces = new ArrayList<>();
//            ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
//            new BencodeOutputStream(outputStream, StandardCharsets.UTF_8).writeDictionary(infoMap);
//            byte[] infoHash = MessageDigest.getInstance("SHA-1").digest(outputStream.toByteArray());
            for (int i = 0; i < piecesBytes.length; i += 20) {
                if (i + 20 > piecesBytes.length) {
                    throw new IOException("Invalid torrent file: incomplete piece hash");
                }
                byte[] hash = new byte[20];
                System.arraycopy(piecesBytes, i, hash, 0, 20);
                pieces.add(hash);
            }
            System.out.println("Piece count " + pieces.size());
            return new TorrentMetadata(fileName, fileSize, pieceSize, pieces);
        } catch (IOException e) {
            throw new IOException("Failed to parse torrent file: " + e.getMessage(), e);
        }
    }

    private String createFileName(Map<String, Object> info) {
        Object nameObj = info.get("name");
        if (nameObj instanceof String) {
            return (String) nameObj;
        } else if (nameObj instanceof ByteBuffer) {
            ByteBuffer nameBuffer = (ByteBuffer) nameObj;
            byte[] nameBytes = new byte[nameBuffer.remaining()];
            nameBuffer.get(nameBytes);
            return new String(nameBytes, StandardCharsets.UTF_8);
        }
        return "file-" + UUID.randomUUID();
    }

    static public BitSet buildPieceMap(String fullPath, TorrentMetadata torrentInfo) throws IOException {
        List<byte[]> pieceList = torrentInfo.getPieces();
        int pieceCount = pieceList.size();
        BitSet bitSet = new BitSet(torrentInfo.getPieces().size());
        long pieceSize = torrentInfo.getPieceLength();
        int retryCount = 0;
        int maxRetries = 5;
        boolean success = false;

        System.out.println("Try to find file " + fullPath);
        File file = new File(fullPath);
        if (!file.exists()) {
            System.err.println("File does not exist: " + fullPath);
            return bitSet;
        }

        while (retryCount < maxRetries && !success) {
            try (RandomAccessFile raf = new RandomAccessFile(fullPath, "r")) {
                for (int i = 0; i < pieceCount; i++) {
                    long from = (long) i * torrentInfo.getPieceLength();
                    long size = Math.min(torrentInfo.getPieceLength(), raf.length() - from);
                    if (size > 0) {
                        byte[] piece = new byte[(int) size];
                        raf.seek(from);
                        raf.readFully(piece);
                        byte[] pieceHash = MessageDigest.getInstance("SHA-1").digest(piece);
                        if (MessageDigest.isEqual(pieceHash, torrentInfo.getPieces().get(i))) {
                            bitSet.set(i);
                        }
                    }
                }
                success = true;
            } catch (NoSuchFileException e) {
                retryCount++;
                if (retryCount >= maxRetries) {
                    throw new IOException("File not found after multiple retries: " + fullPath, e);
                }
                System.err.println("File not found: " + fullPath + ". Retrying in 3 seconds...");
                try {
                    Thread.sleep(3000);
                } catch (InterruptedException ie) {
                    Thread.currentThread().interrupt();
                    throw new IOException("Thread interrupted during retry delay", ie);
                }
            } catch (NoSuchAlgorithmException e) {
                throw new RuntimeException(e);
            }
        }
        return bitSet;
    }
}
