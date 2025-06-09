package context;

import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import nsu.slepchenko.context.Context;

public class ContextTest {
    private Context context;
    private final int ARR_SIZE = 30000;

    @BeforeEach
    void setUp() {
        context = new Context();
    }

    @Test
    void testIncrementPointerWithinBounds() {
        context.incrementPointer();
        assertEquals(1, context.getPointer());
    }

    @Test
    void testDecrementPointerWithinBounds() {
        context.incrementPointer();
        context.decrementPointer();
        assertEquals(0, context.getPointer());
    }

    @Test
    void testIncrementPointerOutOfBounds() {
        for (int i = 0; i < 29999; i++) {
            context.incrementPointer();
        }
        context.incrementPointer();
        assertEquals(0, context.getPointer());
        context.incrementPointer();
        assertEquals(1, context.getPointer());

    }

    @Test
    void testDecrementPointerOutOfBounds() {
        context.decrementPointer();
        assertEquals(ARR_SIZE - 1, context.getPointer());
        context.decrementPointer();
        assertEquals(ARR_SIZE - 2, context.getPointer());
        context.decrementPointer();
        assertEquals(ARR_SIZE - 3, context.getPointer());

    }

    @Test
    void testIncrementValue() {
        context.incrementValue();
        assertEquals(1, context.getValue());
    }

    @Test
    void testDecrementValue() {
        context.incrementValue();
        context.incrementValue();
        context.decrementValue();
        assertEquals(1, context.getValue());
    }

    @Test
    void testSetValue() {
        context.setValue((byte) 100);
        assertEquals(100, context.getValue());
    }

    @Test
    void testModifyValueAtDifferentPositions() {
        context.setValue((byte) 22);
        context.incrementPointer();
        context.setValue((byte) 52);

        context.decrementPointer();
        assertEquals(22, context.getValue());

        context.incrementPointer();
        assertEquals(52, context.getValue());
    }
}

