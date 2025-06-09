package ru.nsu.slepchenko.lab.torrent;

import java.io.IOException;
import java.security.NoSuchAlgorithmException;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main {
    private static TorrentClient client;
    private static TorrentServer server;
    private static ExecutorService executor;

    public static void main(String[] args) {
        if (args.length < 3) {
            System.out.println("Usage: java Main <torrentFilePath> <downloadDir> <ownPort> <peer1> [<peer2> ...]");
            System.out.println("Example: java Main /Users/sofya/largefile.torrent /Users/sofya/downloads 6883 localhost:6884");
            return;
        }

        String torrentFilePath = args[0];
        String downloadDir = args[1] + "/";
        int ownPort;
        try {
            ownPort = Integer.parseInt(args[2]);
        } catch (NumberFormatException e) {
            System.err.println("Invalid port number: " + args[2]);
            return;
        }
        List<ServerAddress> peers = new ArrayList<>();
        for (int i = 3; i < args.length; i++) {
            String[] parts = args[i].split(":");
            if (parts.length != 2) {
                System.err.println("Invalid peer format: " + args[i] + ". Expected host:port");
                continue;
            }
            try {
                peers.add(new ServerAddress(parts[0], Integer.parseInt(parts[1])));
            } catch (NumberFormatException e) {
                System.err.println("Invalid port in peer: " + args[i]);
            }
        }

        startNode(torrentFilePath, downloadDir, ownPort, peers);
    }

    private static void startNode(String torrentFilePath, String downloadDir, int ownPort, List<ServerAddress> peers) {
        executor = Executors.newFixedThreadPool(2);
        CountDownLatch latch = new CountDownLatch(1);

        executor.submit(() -> {
            try {
                server = new TorrentServer(downloadDir, torrentFilePath, latch);
                server.startServer(ownPort);
            } catch (IOException | NoSuchAlgorithmException e) {
                System.err.println("Error starting Torrent server on port " + ownPort + ": " + e.getMessage());
                e.printStackTrace();
                latch.countDown();
            } catch (Exception e) {
                throw new RuntimeException(e);
            }
        });

        executor.submit(() -> {
            try {
                latch.await();
                client = new TorrentClient(downloadDir, torrentFilePath);
                client.startClient(peers);
            } catch (IOException | NoSuchAlgorithmException | InterruptedException | ClassNotFoundException e) {
                System.err.println("Error starting Torrent client: " + e.getMessage());
            } catch (Exception e) {
                throw new RuntimeException(e);
            }
        });

        Runtime.getRuntime().addShutdownHook(new Thread(() -> {
            System.out.println("Shutting down Torrent node...");
            if (client != null) {
                client.stop();
            }
            if (server != null) {
                server.stop();
            }
            if (executor != null) {
                executor.shutdownNow();
            }
            System.out.println("Shutdown complete.");
        }));
    }
}
