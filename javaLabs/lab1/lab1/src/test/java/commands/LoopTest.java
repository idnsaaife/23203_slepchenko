package commands;

import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.api.Test;

import nsu.slepchenko.context.*;
import nsu.slepchenko.commands.Command;
import nsu.slepchenko.commands.LoopStart;
import nsu.slepchenko.commands.LoopEnd;

public class LoopTest {
    private Context context = new Context();
    private LoopContext loopContext;

    @Test
    public void testLoopStartAndEnd() {
        loopContext = new LoopContext(new CommandContext("+++[-]"));
        Command loopStart = loopContext.getCommand(3);
        Command loopEnd = loopContext.getCommand(5);
        assertEquals(LoopStart.class, loopStart.getClass());
        assertEquals(LoopEnd.class, loopEnd.getClass());
        context.setValue((byte) 3);
        loopContext.setPointer(3);
        loopStart.execute(context, loopContext);
        assertEquals(3, loopContext.getPointer());
        loopContext.setPointer(5);
        loopEnd.execute(context, loopContext);
        assertEquals(3, loopContext.getPointer());
        context.setValue((byte) 0);
        loopContext.setPointer(3);
        loopStart.execute(context, loopContext);
        assertEquals(5, loopContext.getPointer());
    }
}
