package ru.nsu.slepchenko.lab.torrent;

import java.util.List;

public class TorrentMetadata {
    private final String fileName;
    private final long fileSize;
    private final int pieceLength;
    private final List<byte[]> pieces;
    public TorrentMetadata(String fileName, long totalSize, int pieceLength, List<byte[]> pieces) {
        this.fileName = fileName;
        this.fileSize = totalSize;
        this.pieceLength = pieceLength;
        this.pieces = pieces;
    }

    public String getFileName() {
        return fileName;
    }

    public long getFileSize() {
        return fileSize;
    }

    public int getPieceLength() {
        return pieceLength;
    }

    public List<byte[]> getPieces() {
        return pieces;
    }
}
