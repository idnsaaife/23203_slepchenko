package nsu.slepchenko.util;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.nio.file.Files;
import java.nio.file.Paths;


public class InputManager {
    public static String getCode(String[] args) throws Exception {
        for (String arg : args) {
            if (arg.startsWith("-code=")) {
                return arg.substring(6);
            } 
        }
        throw new RuntimeException("Wrong arguments");
    }
}
