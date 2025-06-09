package ru.nsu.slepchenko.lab.torrent;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;
import java.util.concurrent.CountDownLatch;

public class TorrentServer {
    private final String fileName;
    private final BitSet serverBitfield;
    private Selector selector;
    private String downloadPath;
    private ArrayList<SocketChannel> clientInfoMap = new ArrayList<>();
    private final int partSize;
    private CountDownLatch latch;
    private final FileManager fileManager;
    private volatile boolean isRunning = true;

    public TorrentServer(String downloadDir, String torrentFilePath, CountDownLatch latch) throws Exception {
        System.out.println("Initialized Torrent Server");
        this.downloadPath = downloadDir;
        this.latch = latch;

        TorrentParser parser = new TorrentParser(torrentFilePath, downloadDir);
        System.out.println("Parsing TorrentFile " + torrentFilePath);
        TorrentMetadata torrentInfo = parser.parse();

        this.fileName = torrentInfo.getFileName();
        this.partSize = torrentInfo.getPieceLength();
        this.fileManager = new FileManager(downloadDir, partSize);

        Path fullPath = Paths.get(downloadDir, fileName);
        long currentFileSize = torrentInfo.getFileSize();
        String currentFileName = this.fileName;
        Path filePath = Paths.get(downloadDir, currentFileName);

        if (!Files.exists(filePath)) {
            fileManager.createEmptyFile(currentFileName, currentFileSize);
        }

        this.serverBitfield = TorrentParser.buildPieceMap(fullPath.toString(), torrentInfo);
        createDownloadProgress();
    }

    public void startServer(int port) throws IOException {
        selector = Selector.open();
        ServerSocketChannel serverChannel = ServerSocketChannel.open();
        serverChannel.bind(new InetSocketAddress(port));
        serverChannel.configureBlocking(false);
        serverChannel.register(selector, SelectionKey.OP_ACCEPT);

        System.out.println("Server started on port " + port);
        latch.countDown();

        while (isRunning) {
            try {
                selector.select(1000);
                Set<SelectionKey> selectedKeys = selector.selectedKeys();
                Iterator<SelectionKey> iterator = selectedKeys.iterator();

                while (iterator.hasNext()) {
                    SelectionKey key = iterator.next();
                    iterator.remove();

                    if (!key.isValid()) continue;

                    if (key.isAcceptable()) {
                        handleAccept(serverChannel);
                    } else if (key.isReadable()) {
                        handleRead(key);
                    } else if (key.isWritable()) {
                        handleWrite(key);
                    }
                }
            } catch (IOException e) {
                System.out.println("Error in server loop: " + e.getMessage());
                e.printStackTrace();
            }
        }

        closeAllConnections();
    }

    private void handleAccept(ServerSocketChannel serverChannel) throws IOException {
        SocketChannel clientChannel = serverChannel.accept();
        clientChannel.configureBlocking(false);
        clientChannel.register(selector, SelectionKey.OP_READ);
        clientInfoMap.add(clientChannel);

        System.out.println("Accepted connection from " + clientChannel.getRemoteAddress());

        ByteBuffer buffer = ByteBuffer.wrap(serverBitfield.toByteArray());
        clientChannel.write(buffer);
    }

    private void handleRead(SelectionKey key) throws IOException {
        SocketChannel channel = (SocketChannel) key.channel();
        ByteBuffer buffer = ByteBuffer.allocate(256);
        int bytesRead;

        try {
            bytesRead = channel.read(buffer);
        } catch (IOException e) {
            System.out.println("Connection reset by client: " + channel.getRemoteAddress());
            clientInfoMap.remove(channel);
            channel.close();
            key.cancel();
            return;
        }

        if (bytesRead == -1) {
            System.out.println("Client disconnected: " + channel.getRemoteAddress());
            clientInfoMap.remove(channel);
            channel.close();
            key.cancel();
            return;
        }

        buffer.flip();
        String request = new String(buffer.array(), 0, bytesRead).trim();
        System.out.println("Received: " + request);

        if (request.equals("DOWNLOAD_COMPLETE")) {
            System.out.println("Client completed download: " + channel.getRemoteAddress());
            return;
        }

        String[] parts = request.split(":");
        if (parts.length == 3 && parts[0].equals("REQUEST")) {
            String fileName = parts[1];
            int partNumber;
            try {
                partNumber = Integer.parseInt(parts[2]);
            } catch (NumberFormatException e) {
                System.out.println("Invalid part number in request: " + request);
                return;
            }
            if (serverBitfield.get(partNumber)) {
                byte[] filePart = fileManager.readFilePart(fileName, partNumber);
                key.interestOps(SelectionKey.OP_WRITE);
                key.attach(ByteBuffer.wrap(filePart));
            } else {
                System.out.println("Requested part " + partNumber + " not available on server");
            }
        }
    }

    private void handleWrite(SelectionKey key) throws IOException {
        SocketChannel channel = (SocketChannel) key.channel();
        ByteBuffer buffer = (ByteBuffer) key.attachment();

        if (buffer != null && buffer.hasRemaining()) {
            channel.write(buffer);
        } else {
            key.interestOps(SelectionKey.OP_READ);
            key.attach(null); // Clear attachment after writing
        }
    }

    private void createDownloadProgress() throws IOException {
        DownloadProgress downloadProgress = new DownloadProgress(fileName, serverBitfield.size());
        for (int i = 0; i < serverBitfield.size(); i++) {
            if (serverBitfield.get(i)) {
                downloadProgress.markPartAsDownloaded(i);
            }
        }
        downloadProgress.save(downloadPath);
    }

    public void stop() {
        isRunning = false;
        selector.wakeup();
    }

    private void closeAllConnections() {
        for (SocketChannel channel : clientInfoMap) {
            try {
                if (channel.isOpen()) {
                    channel.close();
                }
            } catch (IOException e) {
                System.out.println("Error closing client connection: " + e.getMessage());
            }
        }
        try {
            if (selector != null && selector.isOpen()) {
                selector.close();
            }
        } catch (IOException e) {
            System.out.println("Error closing selector: " + e.getMessage());
        }
        clientInfoMap.clear();
    }

    private static class ClientInfo {
        public String currentFileName;
        public int partNumber;
        public long currentFileSize;
    }
}
