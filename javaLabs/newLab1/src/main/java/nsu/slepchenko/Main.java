package nsu.slepchenko;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import nsu.slepchenko.util.InputManager;
import nsu.slepchenko.interpreter.BrainfuckInterpreter;

public class Main {
    private static final Logger logger = LogManager.getLogger(Main.class);

    public static void main(String[] args) {
        logger.info("Brainfuck interpreter is starting to work");
        try {
            String program = InputManager.getCode(args);
            BrainfuckInterpreter interpreter = new BrainfuckInterpreter();
            interpreter.execute(program);

        } catch (Exception e) {
            System.err.println("Enter the code with -code=");
            logger.error("Wrong arguments");
        }
        logger.info("Brainfuck interpreter finished working");
        // String program =
        // "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.";
    }
}