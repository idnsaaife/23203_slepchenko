package ru.nsu.slepchenko.lab.torrent;

import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.file.*;
import java.util.ArrayList;
import java.util.List;

public class FileManager {

    public String getDirectoryPath() {
        return directoryPath;
    }

    private final String directoryPath;
    private final int partSize;

    public FileManager(String directoryPath, int partSize) {
        this.directoryPath = directoryPath;
        this.partSize = partSize;
    }

    public List<String> listFiles() {
        List<String> fileNames = new ArrayList<>();
        try (DirectoryStream<Path> stream = Files.newDirectoryStream(Paths.get(directoryPath))) {
            for (Path entry : stream) {
                fileNames.add(entry.getFileName().toString());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return fileNames;
    }

    public byte[] readFilePart(String fileName, int partNumber) throws IOException {
        Path path = Paths.get(directoryPath, fileName);
        long fileSize = Files.size(path);
        long offset = (long) partNumber * partSize;

        if (offset >= fileSize) {
            return new byte[0]; // No more parts
        }

        int size = (int) Math.min(partSize, fileSize - offset);
        byte[] data = new byte[size];

        try (RandomAccessFile file = new RandomAccessFile(path.toFile(), "r")) {
            file.seek(offset);
            file.readFully(data);
        }

        System.out.println("Reading file part " + partNumber + " with size " + size);
        return data;
    }

    public void createEmptyFile(String fileName, long size) throws IOException {
        Files.createDirectories(Paths.get(directoryPath));
        Path path = Paths.get(directoryPath, fileName);
        try (RandomAccessFile file = new RandomAccessFile(path.toFile(), "rw")) {
            file.setLength(size);
        }
    }

    public void writeFilePart(byte[] data, String fileName, int partNumber) throws IOException {
        Path path = Paths.get(directoryPath, fileName);

        long offset = (long) partNumber * partSize;

        try (RandomAccessFile file = new RandomAccessFile(path.toFile(), "rw")) {
            file.seek(offset);
            file.write(data);
            System.out.println("Writing file part " + partNumber + " with size " + data.length);
        }
    }
}