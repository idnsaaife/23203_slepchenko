package commands;

import nsu.slepchenko.commands.Command;
import nsu.slepchenko.commands.Decrement;
import nsu.slepchenko.context.*;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class DecrementTest {
    private Context context = new Context();
    private LoopContext loopContext = new LoopContext();
    private Command cmd = new Decrement();

    @Test
    void testSimpleDecrement() {
        for (byte i = 0; i > -127; i--) {
            cmd.execute(context, loopContext);
            assertEquals(context.getValue(), i - 1);
        }
    }

}
