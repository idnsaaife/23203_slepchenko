package interpreter;

import nsu.slepchenko.commands.*;
import nsu.slepchenko.context.CommandContext;
import nsu.slepchenko.context.Context;
import nsu.slepchenko.interpreter.BrainfuckInterpreter;
import nsu.slepchenko.util.InputManager;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.parallel.Execution;

import java.io.IOException;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.PrintStream;

import static org.junit.jupiter.api.Assertions.*;

public class BrainfuckTests {
    private BrainfuckInterpreter interpreter;
    private ByteArrayOutputStream outputStream;
    private final PrintStream originalOut = System.out;
    
    @BeforeEach
    public void setUp() {
        interpreter = new BrainfuckInterpreter();
        outputStream = new ByteArrayOutputStream();
        System.setOut(new PrintStream(outputStream));
    }

    @AfterEach
    void setOriginalOut() {
        System.setOut(originalOut);
    }

    @Test
    public void testHelloWorld() {
        String helloWorld = "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.";
        interpreter.execute(helloWorld);
        assertEquals("Hello World!\n", outputStream.toString());
    }

    @Test
    void testLoop() {
        String program = "+++++[->++<]>.";
        interpreter.execute(program);
        assertEquals("\n", outputStream.toString());
    }

    @Test
    public void testNestedLoops() {
        String program = "++++++++[>++++[>++<-]<-]>>.";
        interpreter.execute(program);
        assertEquals("@", outputStream.toString());
    }

    @Test
    public void testInfiniteLoop() {
        
        String program = "++++[.]";
        interpreter.execute(program);
        assertTrue(outputStream.toString().contains("Execution time exceeded limit"));
    }


    @Test
    public void testECalculation() {
        String[] args = { "-file=/Users/sofya/javaLabs/lab1/lab1/programms/e.b" };
        try {
            String eProgram = InputManager.getCode(args);
            interpreter.execute(eProgram);
            assertTrue(outputStream.toString().contains("2.7182818284"));
        } catch (Exception e) {}
    }

    @Test
    public void testInvalidProgram() {
        interpreter.execute("+++[");
        assertTrue(outputStream.toString().contains("Unmatched brackets"));
    }
}
