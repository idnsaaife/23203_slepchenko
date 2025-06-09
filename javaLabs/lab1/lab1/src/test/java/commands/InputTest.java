package commands;

import nsu.slepchenko.commands.Command;
import nsu.slepchenko.commands.Input;
import nsu.slepchenko.context.*;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Test;
import java.io.ByteArrayInputStream;
import java.io.InputStream;
import static org.junit.jupiter.api.Assertions.*;

class InputTest {
    private Context context;
    private LoopContext loopContext;
    private Command cmd = new Input();
    private final InputStream originalSystemIn = System.in;

    @BeforeEach
    void setUp() {
        context = new Context();
        loopContext = new LoopContext();
    }

    @AfterEach
    void setOriginalIn() {
        System.setIn(originalSystemIn);
    }

    @Test
    public void testSingleCharacterInput() {

        System.setIn(new ByteArrayInputStream("B".getBytes()));
        cmd.execute(context, loopContext);
        assertEquals('B', context.getValue());
    }

    @Test
    void testMultipleCharactersInput() {
        System.setIn(new ByteArrayInputStream("V".getBytes()));
        cmd.execute(context, loopContext);
        assertEquals('V', context.getValue());
        System.setIn(new ByteArrayInputStream("Z".getBytes()));
        cmd.execute(context, loopContext);
        assertEquals('Z', context.getValue());
    }
}
