package nsu.slepchenko.util;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.io.BufferedReader;
import java.io.FileDescriptor;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Scanner;

public class InputManager {
    public static String getCode(String[] args) throws IOException {
        if (args.length == 0) {
            throw new IllegalArgumentException("No arguments provided. Use -code= or -file=");
        }
        StringBuilder codeBuilder = new StringBuilder();
        for (String arg : args) {
            if (arg.startsWith("-code=")) {
                for (char symbol : arg.substring(6).toCharArray()) {
                    if (!Character.isWhitespace(symbol)) {
                        codeBuilder.append(symbol);
                    }
                }
            } else if (arg.startsWith("-file=")) {
                try (FileInputStream fileProgram = new FileInputStream(arg.substring(6))) {
                    int byteData;
                    while ((byteData = fileProgram.read()) != -1) {
                        if (!Character.isWhitespace((char) byteData)) {
                            codeBuilder.append((char) byteData);
                        }
                    }
                } catch (IOException e) {
                    throw new IOException("Error reading file " + arg.substring(6) + ": " + e.getMessage());
                }
            } else {
                throw new IllegalArgumentException("Invalid argument: " + arg + ". Use -code= or -file=");
            }
        }
        String program = codeBuilder.toString();
        return program;
    }
}
