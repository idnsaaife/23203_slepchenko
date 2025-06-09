package nsu.slepchenko.context;
import java.util.ArrayList;
import java.util.Stack;

import nsu.slepchenko.commands.Command;



public class CommandContext {
    private ArrayList<Command> commandArrayList = new ArrayList<>();
    private Stack<Integer> loopStack = new Stack<>();
    private int commandPointer = 0;


    public void pushLoopStart(int commandPointer) {
        loopStack.add(commandPointer);
    }

    public int size() {
        return commandArrayList.size();
    }

    public void popLoopStart() {
        loopStack.pop();
    }

    public int getLastLoopStart() {
        return loopStack.peek();
    }

    public void addCommand(Command command) {
        commandArrayList.add(command);
    }

    public Command getCommand(int idx) {
        if (idx >= (commandArrayList.size())) {
            throw new IndexOutOfBoundsException("CommandArrayList index out of range");
        }
        return commandArrayList.get(idx);
    }

    public Command removeCommand(int idx) {
        return commandArrayList.remove(idx);
    }

    public void incrementPointer() {
        commandPointer++;
    }

    public void decrementPointer() {
        commandPointer--;
    }

    public void setPointer(int newPointer) {
        commandPointer = newPointer;
    }

    public int getPointer() {
        return commandPointer;
    }

    public boolean isEmpty() {
        return loopStack.empty();
    }

}
