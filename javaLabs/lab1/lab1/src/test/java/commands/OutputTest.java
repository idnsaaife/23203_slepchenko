package commands;


import nsu.slepchenko.context.*;

import nsu.slepchenko.commands.*;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;

import static org.junit.jupiter.api.Assertions.*;

class OutputTest {
    private Context context;
    private LoopContext loopContext = new LoopContext();
    private Command cmd = new Output();
    private ByteArrayOutputStream outputStream;
    private final PrintStream originalOut = System.out;

    @BeforeEach
    void setNewOut() {
        context = new Context();
        loopContext = new LoopContext();
        outputStream = new ByteArrayOutputStream();
        System.setOut(new PrintStream(outputStream));
    }

    @AfterEach
    void setOriginalOut() {
        System.setOut(originalOut);
    }

    @Test
    void testSingleCharacterOutput() {
        context.setValue((byte) 'A');
        cmd.execute(context, loopContext);
        assertEquals("A", outputStream.toString());
    }

    @Test
    void testMultipleCharactersOutput() {
        context.setValue((byte) 'X');
        cmd.execute(context, loopContext);
        assertEquals("X", outputStream.toString());
        outputStream.reset();
        context.setValue((byte) 'Y');
        cmd.execute(context, loopContext);
        assertEquals("Y", outputStream.toString());
    }

    @Test
    void testContextUnchangedAfterExecution() {
        byte originalValue = (byte) 'C';
        context.setValue(originalValue);
        cmd.execute(context, loopContext);
        assertEquals(originalValue, context.getValue());
    }

}
