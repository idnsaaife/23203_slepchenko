package commands;

import nsu.slepchenko.commands.Command;
import nsu.slepchenko.commands.MoveLeft;
import nsu.slepchenko.commands.MoveRight;
import nsu.slepchenko.context.*;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class MoveLeftTest {
    private Context context;
    private LoopContext loopContext;
    private final int ARR_SIZE = 30000;
    private Command cmdLeft = new MoveLeft();
    private Command cmdRight = new MoveRight();
    
    @BeforeEach
    public void setUpNewContext() {
        context = new Context();
        loopContext = new LoopContext();
    }

    @Test
    public void testPointerOutOfBounds() {
        assertEquals(context.getPointer(), 0);
        cmdLeft.execute(context, loopContext);
        assertEquals(ARR_SIZE - 1, context.getPointer());
        cmdLeft.execute(context, loopContext);
        assertEquals(ARR_SIZE - 2, context.getPointer());
    }

    @Test
    public void testSimpleMoveLeft() {
        for (int i = 0; i < ARR_SIZE - 1; i++) {
            cmdRight.execute(context, loopContext);
        }
        for (int i = ARR_SIZE - 1; i > 0; i--) {
            assertEquals(context.getPointer(), i);
            cmdLeft.execute(context, loopContext);
        }
    }
}
