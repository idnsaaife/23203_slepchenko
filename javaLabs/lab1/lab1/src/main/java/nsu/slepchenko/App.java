package nsu.slepchenko;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import java.io.IOException;
import nsu.slepchenko.interpreter.BrainfuckInterpreter;
import nsu.slepchenko.util.InputManager;

public class App {
    private static final Logger logger = LogManager.getLogger(App.class);

    public static void main(String[] args) {
        logger.info("Brainfuck interpreter is starting to work");

        BrainfuckInterpreter interpreter = new BrainfuckInterpreter();
        try {
            String program = InputManager.getCode(args);
            if (!program.isEmpty()) {
                try {
                    interpreter.execute(program);
                } catch (Exception e) {
                    System.err.println("Error executing Brainfuck code: " + e.getMessage());
                    logger.trace("Execution error", e);
                }
            }
        } catch (IOException e) {
            System.err.println("Error while reading code");
            logger.trace("Execution error", e);
        }
        logger.info("Brainfuck interpreter finished working");
    }
}

