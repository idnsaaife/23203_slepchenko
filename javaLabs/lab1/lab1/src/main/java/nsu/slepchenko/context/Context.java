package nsu.slepchenko.context;

public class Context {
    private final int ARR_SIZE = 30000;
    private byte[] arr = new byte[ARR_SIZE];
    private int pointer = 0;

    public void incrementPointer() {
        pointer++;
        if (pointer >= ARR_SIZE) {
            pointer = 0;
        }
    }

    public void decrementPointer() {
        pointer--;
        if (pointer < 0) {
            pointer = ARR_SIZE - 1;
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
