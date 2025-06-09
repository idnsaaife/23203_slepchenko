package commands;

import nsu.slepchenko.commands.Command;
import nsu.slepchenko.commands.MoveRight;
import nsu.slepchenko.context.*;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class MoveRightTest {
    private Context context;
    private LoopContext loopContext = new LoopContext();
    private final int ARR_SIZE = 30000;
    private Command cmd = new MoveRight();

    @BeforeEach
    public void setUpNewContext() {
        context = new Context();
        loopContext = new LoopContext();
    }
   
    @Test
    public void testSimpleMoveRight() {
        for (int i = 0; i < ARR_SIZE - 1; i++) {
            assertEquals(context.getPointer(), i);
            cmd.execute(context, loopContext);

        }
        assertEquals(context.getPointer(), ARR_SIZE - 1);
    }

    @Test
    public void testPointerOutOfBounds() {
        for (int i = 0; i < ARR_SIZE - 1; i++) {
            cmd.execute(context, loopContext);
        }
        cmd.execute(context, loopContext);
        assertEquals(0, context.getPointer());
    }
}