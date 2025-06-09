package nsu.slepchenko.context;

import java.util.ArrayList;
import java.util.Stack;
import java.util.HashMap;

import nsu.slepchenko.commands.Command;
import nsu.slepchenko.commands.CommandFactory;
import nsu.slepchenko.commands.LoopEnd;
import nsu.slepchenko.commands.LoopStart;

public class CommandContext {
    private ArrayList<Command> commandArrayList = new ArrayList<>();
    private HashMap<Integer,Integer> bracketPairs = new HashMap<>();
    private int commandPointer = 0;
    private CommandFactory commandFactory = new CommandFactory();

    public CommandContext(String program) {
        int checkBraces = 0;
        Stack<Integer> tempStack = new Stack<>();
        final int programLength = program.length();
        for (int i = 0; i < programLength; i++) {
            Command command = commandFactory.createCommandByName(program.charAt(i));
            commandArrayList.add(command);
            if (command.getClass() == LoopStart.class) {
                checkBraces++;
                tempStack.push(i);
            }
            if (command.getClass() == LoopEnd.class) {
                checkBraces--;
                if (tempStack.isEmpty()) {
                    throw new IllegalArgumentException("Unmatched brackets. Not enough [ for ] at position " + i);
                }
                int startPos = tempStack.pop();
                bracketPairs.put(startPos, i); 
                bracketPairs.put(i, startPos);
            }
        }
        if (checkBraces > 0) {
            throw new IllegalArgumentException("Unmatched brackets. Not enough ]");
        }

        if (checkBraces < 0) {
            throw new IllegalArgumentException("Unmatched brackets. Not enough [");
        }
    }

    public int getBracketPair(int position) {
        return bracketPairs.getOrDefault(position, -1);
    }

    public int size() {
        return commandArrayList.size();
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

}
