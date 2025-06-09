package ru.nsu.slepchenko.lab.torrent;

import java.io.IOException;
import java.io.InputStream;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.*;
import java.nio.file.*;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.*;
import java.util.concurrent.*;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class TorrentClient {
    private final Selector selector;
    private final String downloadDir;
    private final String currentFileName;
    private final long currentFileSize;
    private final long pieceLength;
    private final Map<ServerAddress, ServerInfo> serverInfoMap = new ConcurrentHashMap<>();
    private final BitSet clientBitfield;
    private final FileManager fileManager;
    private final DownloadProgress downloadProgress;
    private final ScheduledExecutorService scheduler;
    private final ExecutorService taskExecutor;
    private final ChunkStatus[] chunkStatuses;
    private final int totalChunks;
    private final Set<Integer> missingChunks;
    private final Map<Integer, Integer> failedAttempts = new ConcurrentHashMap<>();
    private final List<byte[]> pieces;
    private static final int MAX_FAILED_ATTEMPTS = 10;
    private static final int RECONNECT_INTERVAL = 5;
    private static final int STATUS_PRINT_INTERVAL = 5;
    private static final int CONNECTION_TIMEOUT = 1000;
    private static final int MAX_RETRY_DELAY = 60;
    private static final int REQUEST_TIMEOUT_SECONDS = 30;
    private volatile boolean isRunning = true;
    private static final int READ_TIMEOUT = 10000;
    private static final int WRITE_TIMEOUT = 10000;

    public TorrentClient(String downloadDir, String torrentPath) throws Exception {
        System.out.println("Initialized Torrent Client");
        this.downloadDir = downloadDir;
        this.selector = Selector.open();

        TorrentParser parser = new TorrentParser(torrentPath, downloadDir);
        System.out.println("Parsing TorrentFile " + torrentPath);
        TorrentMetadata torrentInfo = parser.parse();

        this.currentFileName = torrentInfo.getFileName();
        this.currentFileSize = torrentInfo.getFileSize();
        this.totalChunks = torrentInfo.getPieces().size();
        this.pieces = torrentInfo.getPieces();
        this.pieceLength = torrentInfo.getPieceLength();

        this.fileManager = new FileManager(downloadDir, torrentInfo.getPieceLength());

        DownloadProgress loadedProgress = DownloadProgress.load(downloadDir, currentFileName);
        this.downloadProgress = (loadedProgress != null) ? loadedProgress : new DownloadProgress(currentFileName, totalChunks);

        Path filePath = Paths.get(downloadDir, currentFileName);
        if (!Files.exists(filePath)) {
            fileManager.createEmptyFile(currentFileName, currentFileSize);
        }

        this.clientBitfield = TorrentParser.buildPieceMap(filePath.toString(), torrentInfo);

        this.chunkStatuses = new ChunkStatus[totalChunks];
        this.missingChunks = ConcurrentHashMap.newKeySet();

        IntStream.range(0, totalChunks).forEach(i -> {
            if (downloadProgress.isPartDownloaded(i)) {
                chunkStatuses[i] = ChunkStatus.AVAILABLE;
                clientBitfield.set(i);
            } else {
                chunkStatuses[i] = ChunkStatus.MISSING;
                missingChunks.add(i);
            }
        });

        scheduler = Executors.newScheduledThreadPool(4);
        taskExecutor = Executors.newFixedThreadPool(Runtime.getRuntime().availableProcessors());
    }

    public void startClient(List<ServerAddress> servers) throws IOException {
        for (ServerAddress server : servers) {
            serverInfoMap.put(server, new ServerInfo(server));
        }

        scheduler.scheduleAtFixedRate(this::reconnectToServers, 0, RECONNECT_INTERVAL, TimeUnit.SECONDS);
        scheduler.scheduleAtFixedRate(this::printDownloadStatus, 0, STATUS_PRINT_INTERVAL, TimeUnit.SECONDS);
        scheduler.scheduleAtFixedRate(this::resetFailedAttempts, 60, 60, TimeUnit.SECONDS);
        scheduler.scheduleAtFixedRate(this::retryMissingChunks, 10, 10, TimeUnit.SECONDS);
        scheduler.scheduleAtFixedRate(this::checkRequestTimeouts, 10, 10, TimeUnit.SECONDS);

        CompletableFuture.runAsync(this::processEvents, taskExecutor);

        while (isRunning) {
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                stop();
                break;
            }
        }

        System.out.println("Client stopped. Closing connections.");
        closeAllConnections();
        scheduler.shutdown();
        taskExecutor.shutdown();
    }

    private void processEvents() {
        while (isRunning) {
            try {
                if (selector.select(CONNECTION_TIMEOUT) == 0) {
                    continue;
                }

                Set<SelectionKey> selectedKeys = selector.selectedKeys();
                Iterator<SelectionKey> iterator = selectedKeys.iterator();

                while (iterator.hasNext()) {
                    SelectionKey key = iterator.next();
                    iterator.remove();

                    if (!key.isValid()) continue;

                    try {
                        if (key.isConnectable()) {
                            handleConnect(key);
                        } else if (key.isReadable()) {
                            handleRead(key);
                        } else if (key.isWritable()) {
                            handleWrite(key);
                        }
                    } catch (IOException e) {
                        System.out.println("Error processing key: " + e.getMessage());
                        handleDisconnect((SocketChannel) key.channel());
                        key.cancel();
                    }
                }
            } catch (IOException e) {
                System.out.println("Error in processEvents: " + e.getMessage());
                e.printStackTrace();
            } catch (Exception e) {
                System.out.println("Unexpected error in processEvents: " + e.getMessage());
                e.printStackTrace();
                isRunning = false;
            }
        }
    }

    private void connectToServer(ServerAddress server) {
        CompletableFuture.runAsync(() -> {
            try {
                SocketChannel socketChannel = SocketChannel.open();
                socketChannel.configureBlocking(false);
                socketChannel.connect(new InetSocketAddress(server.getAddress(), server.getPort()));
                socketChannel.register(selector, SelectionKey.OP_CONNECT, server);
                ServerInfo serverInfo = serverInfoMap.get(server);
                serverInfo.channel = socketChannel;
                serverInfo.consecutiveFailures = 0;
                System.out.println("Attempting to connect to server: " + server.getAddress() + ":" + server.getPort());
            } catch (IOException e) {
                System.out.println("Failed to connect to server: " + server.getAddress() + ":" + server.getPort());
                ServerInfo serverInfo = serverInfoMap.get(server);
                serverInfo.consecutiveFailures++;
                if (serverInfo.consecutiveFailures > 10) {
                    System.out.println("Server " + server.getAddress() + ":" + server.getPort() + " seems to be offline. Will keep retrying.");
                }
                scheduleReconnect(server);
            }
        }, taskExecutor);
    }

    private void reconnectToServers() {
        serverInfoMap.entrySet().stream()
                .filter(entry -> !entry.getValue().isConnected)
                .forEach(entry -> {
                    ServerAddress server = entry.getKey();
                    System.out.println("Attempting to reconnect to server: " + server.getAddress() + ":" + server.getPort());
                    connectToServer(server);
                });
    }

    private synchronized void handleDisconnect(SocketChannel channel) {
        serverInfoMap.values().stream()
                .filter(serverInfo -> serverInfo.channel == channel)
                .findFirst()
                .ifPresent(serverInfo -> {
                    serverInfo.isConnected = false;
                    serverInfo.channel = null;
                    if (serverInfo.partNumber != -1) {
                        updateChunkStatus(serverInfo.partNumber, ChunkStatus.MISSING);
                        missingChunks.add(serverInfo.partNumber);
                        serverInfo.requestStartTime = 0; // Reset request time
                        serverInfo.partNumber = -1;
                    }
                    System.out.println("Disconnected from server: " + serverInfo.serverAddress);
                    scheduleReconnect(serverInfo.serverAddress);
                });
    }

    private void scheduleReconnect(ServerAddress server) {
        long delay = Math.min(serverInfoMap.get(server).consecutiveFailures * 5, MAX_RETRY_DELAY);
        scheduler.schedule(() -> connectToServer(server), delay, TimeUnit.SECONDS);
    }

    private void handleConnect(SelectionKey key) throws IOException {
        SocketChannel channel = (SocketChannel) key.channel();
        ServerAddress server = (ServerAddress) key.attachment();

        if (channel.finishConnect()) {
            System.out.println("Connected to " + channel.getRemoteAddress());
            channel.register(selector, SelectionKey.OP_WRITE, server);
            ServerInfo serverInfo = serverInfoMap.get(server);
            if (serverInfo != null) {
                serverInfo.isConnected = true;
                serverInfo.channel = channel;
                serverInfo.consecutiveFailures = 0;
            }
        }
    }

    private void handleRead(SelectionKey key) throws IOException {
        SocketChannel channel = (SocketChannel) key.channel();
        ServerAddress server = (ServerAddress) key.attachment();
        ServerInfo serverInfo = serverInfoMap.get(server);

        if (serverInfo == null) {
            System.out.println("ServerInfo is null for " + server);
            return;
        }

        ByteBuffer buffer = ByteBuffer.allocate(16 * 1024 * 1024);
        int bytesRead;

        try {
            channel.configureBlocking(false);
            channel.socket().setSoTimeout(READ_TIMEOUT);
            bytesRead = channel.read(buffer);
        } catch (IOException e) {
            System.out.println("Error reading from server " + server + ": " + e.getMessage());
            handleDisconnect(channel);
            markServerAsOffline(server);
            key.cancel();
            channel.close();
            return;
        }

        if (bytesRead == -1) {
            handleDisconnect(channel);
            markServerAsOffline(server);
            key.cancel();
            channel.close();
            return;
        }

        buffer.flip();
        byte[] data = new byte[bytesRead];
        buffer.get(data);

        CompletableFuture.runAsync(() -> {
            try {
                processReceivedData(key, serverInfo, data);
            } catch (Exception e) {
                System.out.println("Error processing received data: " + e.getMessage());
                e.printStackTrace();
            }
        }, taskExecutor);
    }

    private void markServerAsOffline(ServerAddress server) {
        ServerInfo serverInfo = serverInfoMap.get(server);
        if (serverInfo != null) {
            serverInfo.isConnected = false;
            System.out.println("Marked server " + server + " as offline.");
        }
    }

    private void processReceivedData(SelectionKey key, ServerInfo serverInfo, byte[] data) throws NoSuchAlgorithmException, IOException {
        if (!serverInfo.receivingFileList) {
            serverInfo.serverBitfield = BitSet.valueOf(data);
            serverInfo.receivingFileList = true;
            requestNextMissingPart(key);
        } else {
            if (serverInfo.partNumber < 0 || serverInfo.partNumber >= totalChunks) {
                System.out.println("Invalid part number: " + serverInfo.partNumber);
                serverInfo.partNumber = -1;
                serverInfo.requestStartTime = 0;
                requestNextMissingPart(key);
                return;
            }
            synchronized (serverInfo) {
                if (verifyPartHash(data, serverInfo.partNumber) && serverInfo.partNumber >= 0) {
                    fileManager.writeFilePart(data, currentFileName, serverInfo.partNumber);
                    clientBitfield.set(serverInfo.partNumber);
                    downloadProgress.markPartAsDownloaded(serverInfo.partNumber);
                    downloadProgress.save(downloadDir);
                    updateChunkStatus(serverInfo.partNumber, ChunkStatus.AVAILABLE);

                    synchronized (missingChunks) {
                        missingChunks.remove(serverInfo.partNumber);
                    }
                    failedAttempts.remove(serverInfo.partNumber);
                    System.out.println("Received and verified file part " + serverInfo.partNumber + " from " + serverInfo.serverAddress);
                } else {
                    System.out.println("Hash mismatch for part number " + serverInfo.partNumber);
                    updateChunkStatus(serverInfo.partNumber, ChunkStatus.MISSING);
                    synchronized (missingChunks) {
                        missingChunks.add(serverInfo.partNumber);
                    }
                    failedAttempts.merge(serverInfo.partNumber, 1, Integer::sum);
                    if (failedAttempts.get(serverInfo.partNumber) != null && failedAttempts.get(serverInfo.partNumber) > MAX_FAILED_ATTEMPTS) {
                        System.out.println("Too many failed attempts for part " + serverInfo.partNumber + ". Marking as skipped.");
                        updateChunkStatus(serverInfo.partNumber, ChunkStatus.SKIPPED);
                    }
                }
            }
            serverInfo.partNumber = -1;
            serverInfo.requestStartTime = 0;
            requestNextMissingPart(key);
        }

        if (Arrays.stream(chunkStatuses).allMatch(status -> status == ChunkStatus.AVAILABLE)) {
            if (!verifyEntireFile()) {
                System.out.println("File integrity check failed after receiving all chunks. Resuming download for missing pieces.");
            } else {
                System.out.println("Download complete. Continuing to seed.");
            }
        }
    }

    private void handleWrite(SelectionKey key) throws IOException {
        SocketChannel channel = (SocketChannel) key.channel();
        ServerAddress server = (ServerAddress) key.attachment();
        ServerInfo serverInfo = serverInfoMap.get(server);

        if (serverInfo == null) {
            System.out.println("ServerInfo is null for " + server);
            return;
        }

        if (serverInfo.partNumber == -1) {
            findNextMissingPart(serverInfo);
        }

        if (serverInfo.partNumber == -1) {
            key.interestOps(SelectionKey.OP_READ);
            return;
        }

        String request = "REQUEST:" + currentFileName + ":" + serverInfo.partNumber;
        ByteBuffer buffer = ByteBuffer.wrap(request.getBytes());

        try {
            channel.configureBlocking(false);
            channel.socket().setSoTimeout(WRITE_TIMEOUT);
            channel.write(buffer);
            serverInfo.requestStartTime = System.currentTimeMillis();
        } catch (IOException e) {
            System.out.println("Error writing to server " + server + ": " + e.getMessage());
            handleDisconnect(channel);
            return;
        }

        key.interestOps(SelectionKey.OP_READ);
    }

    private synchronized void findNextMissingPart(ServerInfo serverInfo) {
        if (serverInfo.serverBitfield == null) {
            System.out.println("Server bitfield is null for " + serverInfo);
            serverInfo.partNumber = -1;
            return;
        }
        System.out.println("Server bitfield size: " + serverInfo.serverBitfield.size() + ", cardinality: " + serverInfo.serverBitfield.cardinality());
        List<Integer> availableParts = missingChunks.stream()
                .filter(i -> {
                    if (i < 0) {
                        return false;
                    }
                    boolean hasPiece = serverInfo.serverBitfield.get(i);
                    boolean notSkipped = chunkStatuses[i] != ChunkStatus.SKIPPED;
                    return hasPiece && notSkipped;
                })
                .sorted()
                .collect(Collectors.toList());
        if (!availableParts.isEmpty()) {
            serverInfo.partNumber = availableParts.get(0);
            System.out.println("Selected part: " + serverInfo.partNumber);
            updateChunkStatus(serverInfo.partNumber, ChunkStatus.REQUESTED);
        } else {
            System.out.println("No available parts for " + serverInfo);
            serverInfo.partNumber = -1;
        }
    }

    private void requestNextMissingPart(SelectionKey key) {
        if (key.isValid()) {
            key.interestOps(SelectionKey.OP_WRITE);
            selector.wakeup();
        }
    }

    private boolean verifyPartHash(byte[] data, int partNumber) throws NoSuchAlgorithmException {
        if (partNumber < 0 || partNumber >= pieces.size()) {
            return false;
        }
        MessageDigest md = MessageDigest.getInstance("SHA-1");
        byte[] calculatedHash = md.digest(data);
        byte[] expectedHash = pieces.get(partNumber);
        return Arrays.equals(calculatedHash, expectedHash);
    }

    private void closeAllConnections() throws IOException {
        for (ServerInfo serverInfo : serverInfoMap.values()) {
            if (serverInfo.channel != null && serverInfo.channel.isOpen()) {
                try {
                    if (serverInfo.channel.isConnected()) {
                        ByteBuffer buffer = ByteBuffer.wrap("DOWNLOAD_COMPLETE".getBytes());
                        serverInfo.channel.write(buffer);
                    }
                    serverInfo.channel.close();
                } catch (IOException e) {
                    System.out.println("Error closing connection: " + e.getMessage());
                } catch (NotYetConnectedException e) {
                    System.out.println("Channel not yet connected: " + e.getMessage());
                }
            }
        }
        try {
            selector.close();
        } catch (IOException e) {
            System.out.println("Error closing selector: " + e.getMessage());
        }
        downloadProgress.save(downloadDir);
    }

    private void printDownloadStatus() {
        long availableChunks = Arrays.stream(chunkStatuses).filter(status -> status == ChunkStatus.AVAILABLE).count();
        long requestedChunks = Arrays.stream(chunkStatuses).filter(status -> status == ChunkStatus.REQUESTED).count();
        long missingChunksCount = missingChunks.size();
        long skippedChunks = Arrays.stream(chunkStatuses).filter(status -> status == ChunkStatus.SKIPPED).count();

        System.out.printf("Download status: %d/%d  - Available: %d, Requested: %d, Missing: %d, Skipped: %d%n",
                availableChunks, totalChunks, availableChunks, requestedChunks, missingChunksCount, skippedChunks);
    }

    private synchronized void resetFailedAttempts() {
        IntStream.range(0, chunkStatuses.length)
                .filter(i -> chunkStatuses[i] == ChunkStatus.SKIPPED)
                .forEach(i -> {
                    updateChunkStatus(i, ChunkStatus.MISSING);
                    missingChunks.add(i);
                });
        failedAttempts.clear();
        System.out.println("Reset failed attempts and skipped chunks.");
    }

    private synchronized void retryMissingChunks() {
        missingChunks.stream()
                .filter(chunk -> chunkStatuses[chunk] != ChunkStatus.REQUESTED && chunkStatuses[chunk] != ChunkStatus.SKIPPED)
                .forEach(chunk -> {
                    serverInfoMap.values().stream()
                            .filter(serverInfo -> serverInfo.isConnected && serverInfo.serverBitfield != null && serverInfo.serverBitfield.get(chunk))
                            .findFirst()
                            .ifPresent(serverInfo -> {
                                System.out.println("Retrying chunk " + chunk + " from server " + serverInfo.serverAddress);
                                serverInfo.partNumber = chunk;
                                serverInfo.requestStartTime = System.currentTimeMillis();
                                updateChunkStatus(chunk, ChunkStatus.REQUESTED);
                                requestNextMissingPart(serverInfo.channel.keyFor(selector));
                            });
                });
    }

    private synchronized void checkRequestTimeouts() {
        long currentTime = System.currentTimeMillis();
        serverInfoMap.values().stream()
                .filter(serverInfo -> serverInfo.partNumber != -1 && serverInfo.requestStartTime > 0)
                .forEach(serverInfo -> {
                    if (currentTime - serverInfo.requestStartTime > REQUEST_TIMEOUT_SECONDS * 1000) {
                        System.out.println("Request for chunk " + serverInfo.partNumber + " timed out from server " + serverInfo.serverAddress);
                        updateChunkStatus(serverInfo.partNumber, ChunkStatus.MISSING);
                        missingChunks.add(serverInfo.partNumber);
                        serverInfo.partNumber = -1;
                        serverInfo.requestStartTime = 0;
                        if (serverInfo.channel != null && serverInfo.channel.isOpen()) {
                            requestNextMissingPart(serverInfo.channel.keyFor(selector));
                        }
                    }
                });
    }

    public void stop() {
        isRunning = false;
        try {
            downloadProgress.save(downloadDir);
        } catch (IOException e) {
            System.out.println("Error saving download progress: " + e.getMessage());
        }
        selector.wakeup();
    }

    private synchronized void updateChunkStatus(int chunkIndex, ChunkStatus status) {
        if (chunkIndex < 0 || chunkIndex >= chunkStatuses.length) {
            return;
        }
        chunkStatuses[chunkIndex] = status;
    }

    private boolean verifyEntireFile() throws IOException, NoSuchAlgorithmException {
        Path filePath = Paths.get(downloadDir, currentFileName);
        MessageDigest md = MessageDigest.getInstance("SHA-1");
        byte[] buffer = new byte[(int) pieceLength];

        try (InputStream is = Files.newInputStream(filePath)) {
            int pieceIndex = 0;
            int bytesRead;

            while ((bytesRead = is.read(buffer)) != -1) {
                if (pieceIndex >= pieces.size()) {
                    System.out.println("File has more data than expected pieces");
                    return false;
                }
                md.update(buffer, 0, bytesRead);
                byte[] calculatedHash = md.digest();

                if (!Arrays.equals(calculatedHash, pieces.get(pieceIndex))) {
                    System.out.println("Hash mismatch for piece " + pieceIndex);
                    updateChunkStatus(pieceIndex, ChunkStatus.MISSING);
                    missingChunks.add(pieceIndex);
                    return false;
                }

                pieceIndex++;
                md.reset();
            }

            if (pieceIndex != pieces.size()) {
                System.out.println("File has fewer pieces than expected: " + pieceIndex + " vs " + pieces.size());
                for (int i = pieceIndex; i < pieces.size(); i++) {
                    updateChunkStatus(i, ChunkStatus.MISSING);
                    missingChunks.add(i);
                }
                return false;
            }
        }

        return true;
    }

    private enum ChunkStatus {
        MISSING,
        REQUESTED,
        AVAILABLE,
        SKIPPED
    }

    private static class ServerInfo {
        BitSet serverBitfield;
        boolean receivingFileList = false;
        int partNumber = -1;
        long requestStartTime = 0;
        boolean isConnected = false;
        SocketChannel channel;
        ServerAddress serverAddress;
        int consecutiveFailures = 0;

        ServerInfo(ServerAddress serverAddress) {
            this.serverBitfield = new BitSet();
            this.serverAddress = serverAddress;
        }

        @Override
        public String toString() {
            return serverAddress.getAddress() + ":" + serverAddress.getPort();
        }
    }
}
