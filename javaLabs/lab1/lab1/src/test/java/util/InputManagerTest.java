package util;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
import java.io.IOException;
import org.junit.jupiter.api.Test;
import nsu.slepchenko.util.InputManager;

public class InputManagerTest {
    @Test
    public void testInputManagerCodeArg() throws Exception {
        String[] args = { "-code=+++." };
        String code = InputManager.getCode(args);
        assertEquals("+++.", code);
    }

    @Test
    public void testInputManagerFileArg() throws Exception {
        String[] args = { "-file=test.bf" };
        assertThrows(IOException.class, () -> InputManager.getCode(args)); 
    }

    @Test
    public void testInputManagerInvalidArg() {
        String[] args = { "invalid" };
        assertThrows(IllegalArgumentException.class, () -> InputManager.getCode(args));
    }

    @Test
    public void testInputManagerEmptyArgs() {
        String[] args = {};
        assertThrows(IllegalArgumentException.class, () -> InputManager.getCode(args));
    }
}
