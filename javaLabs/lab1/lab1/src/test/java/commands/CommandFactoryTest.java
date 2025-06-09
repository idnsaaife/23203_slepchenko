package commands;

import nsu.slepchenko.commands.*;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class CommandFactoryTest {
    @Test
    void testIncrement() {
        CommandFactory testFactory = new CommandFactory();
        Command command = testFactory.createCommandByName('+');
        assertInstanceOf(Increment.class, command);
    }

    @Test
    void testDecrement() {
        CommandFactory testFactory = new CommandFactory();
        Command command = testFactory.createCommandByName('-');
        assertInstanceOf(Decrement.class, command);
    }

    @Test
    void testMoveLeft() {
        CommandFactory testFactory = new CommandFactory();
        Command command = testFactory.createCommandByName('<');
        assertInstanceOf(MoveLeft.class, command);
    }

    @Test
    void testMoveRight() {
        CommandFactory testFactory = new CommandFactory();
        Command command = testFactory.createCommandByName('>');
        assertInstanceOf(MoveRight.class, command);
    }

    @Test
    void testLoopStart() {
        CommandFactory testFactory = new CommandFactory();
        Command command = testFactory.createCommandByName('[');
        assertInstanceOf(LoopStart.class, command);
    }

    @Test
    void testLoopEnd() {
        CommandFactory testFactory = new CommandFactory();
        Command command = testFactory.createCommandByName(']');
        assertInstanceOf(LoopEnd.class, command);
    }

    @Test
    void testInput() {
        CommandFactory testFactory = new CommandFactory();
        Command command = testFactory.createCommandByName(',');
        assertInstanceOf(Input.class, command);
    }

    @Test
    void testOutput() {
        CommandFactory testFactory = new CommandFactory();
        Command command = testFactory.createCommandByName('.');
        assertInstanceOf(Output.class, command);
    }

    @Test
    void testCreatingCommandForUnknownName() {
        String message = new String();
        CommandFactory testFactory = new CommandFactory();
        try {
            Command command = testFactory.createCommandByName(')');
        } catch (Exception e) {
            message = e.getMessage();
        }
        assertEquals("Unknown command symbol: )", message);

        try {
            Command command = testFactory.createCommandByName(')');
        } catch (Exception e) {
            message = e.getMessage();
        }
        assertEquals("Unknown command symbol: )", message);

        try {
            Command command = testFactory.createCommandByName('?');
        } catch (Exception e) {
            message = e.getMessage();
        }
        assertEquals("Unknown command symbol: ?", message);
    }

}