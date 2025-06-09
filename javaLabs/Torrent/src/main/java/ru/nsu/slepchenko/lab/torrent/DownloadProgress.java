package ru.nsu.slepchenko.lab.torrent;

import java.io.*;
import java.util.BitSet;

public class DownloadProgress implements Serializable {
    private BitSet downloadedParts;
    private String fileName;

    public DownloadProgress(String fileName, int totalParts) {
        this.fileName = fileName;
        this.downloadedParts = new BitSet(totalParts);
    }

    public void markPartAsDownloaded(int partNumber) {
        downloadedParts.set(partNumber);
    }

    public boolean isPartDownloaded(int partNumber) {
        return downloadedParts.get(partNumber);
    }

    public void save(String directoryPath) throws IOException {
        File file = new File(directoryPath, fileName + ".progress");
        try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(file))) {
            oos.writeObject(this);
        }
    }

    public static DownloadProgress load(String directoryPath, String fileName) throws IOException, ClassNotFoundException {
        File file = new File(directoryPath, fileName + ".progress");
        if (file.exists()) {
            try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(file))) {
                return (DownloadProgress) ois.readObject();
            } catch (EOFException e) {
                System.err.println("The file is corrupted or incomplete: " + file.getAbsolutePath());
            }
        } else {
            System.err.println("File not found: " + file.getAbsolutePath());
        }
        return null;
    }

    public BitSet getDownloadedParts() {
        return downloadedParts;
    }
}
