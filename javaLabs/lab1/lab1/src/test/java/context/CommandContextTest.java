package context;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import nsu.slepchenko.commands.LoopEnd;
import nsu.slepchenko.commands.LoopStart;
import nsu.slepchenko.context.CommandContext;

public class CommandContextTest {
    private CommandContext commandContext;

    @BeforeEach
    public void setUp() {
        // commandContext = new CommandContext();
    }

    @Test
    public void testLoadValidProgram() {
        commandContext = new CommandContext("+++[>++<-]");
        // commandContext.loadContext("+++[>++<-]");
        assertEquals(10, commandContext.size());
        assertEquals(LoopStart.class, commandContext.getCommand(3).getClass());
        assertEquals(LoopEnd.class, commandContext.getCommand(9).getClass());
    }

    @Test
    public void testLoadUnmatchedBrackets() {
        IllegalArgumentException exception1 = assertThrows(IllegalArgumentException.class,
                () -> new CommandContext("+++[>++<"));
        assertEquals("Unmatched brackets. Not enough ]", exception1.getMessage());

        IllegalArgumentException exception2 = assertThrows(IllegalArgumentException.class,
                () -> new CommandContext("+++]>++<"));
        assertTrue(exception2.getMessage().startsWith("Unmatched brackets. Not enough ["));
    }
}
