package commands;

import nsu.slepchenko.commands.Command;
import nsu.slepchenko.commands.Increment;
import nsu.slepchenko.context.*;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class IncrementTest {
    private Context context = new Context();
    private LoopContext loopContext = new LoopContext();
    private Command cmd = new Increment();

    @Test
    void testSimpleIncrement() {
        for (byte i = 1; i < 127; i++) {
            cmd.execute(context, loopContext);
            assertEquals(context.getValue(), i);
        }
    }
}
