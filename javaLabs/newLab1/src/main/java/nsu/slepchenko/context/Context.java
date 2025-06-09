package nsu.slepchenko.context;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import nsu.slepchenko.commands.LoopEnd;

public class Context {
    private static final Logger logger = LogManager.getLogger(LoopEnd.class);

    private final int ARR_SIZE = 30000;
    private byte[] arr = new byte[ARR_SIZE];
    private int pointer = 0;

    public void incrementPointer() {
        pointer++;
        if (pointer >= ARR_SIZE) {
            logger.error("Pointer is greater or equal to the size of value array");
            throw new ArrayIndexOutOfBoundsException("Index" + pointer + "out of bounds");
        }
    }

    public void decrementPointer() {
        pointer--;
        if (pointer < 0) {
            logger.error("Pointer is less than zero");
            throw new ArrayIndexOutOfBoundsException("Index" +  "out of bounds");
        }
    }

    public int getPointer() {
        return pointer;
    }

    public void incrementValue() {
        arr[pointer]++;
    }

    public void decrementValue() {
        arr[pointer]--;
    }

    public void setValue(byte newValue) {
        arr[pointer] = newValue;
    }

    public byte getValue() {
        return arr[pointer];
    }
}
