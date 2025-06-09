package nsu.slepchenko.context;

import nsu.slepchenko.commands.Command;

public class LoopContext {
    private final CommandContext commandContext;
    
    public LoopContext() {
        commandContext = new CommandContext("");
    }

    public LoopContext(String program) {
        commandContext = new CommandContext(program);
    }

    public LoopContext(CommandContext commandContext) {
        this.commandContext = commandContext;
    }

    public int getBracketPair(int position) {
        return commandContext.getBracketPair(position);
    }

    public int size() {
        return commandContext.size();
    }

    public Command getCommand(int idx) {
        return commandContext.getCommand(idx);
    }

    public Command removeCommand(int idx) {
        return commandContext.removeCommand(idx);
    }

    public void incrementPointer() {
        commandContext.incrementPointer();
    }

    public void decrementPointer() {
        commandContext.decrementPointer();
    }

    public void setPointer(int newPointer) {
        commandContext.setPointer(newPointer);
    }

    public int getPointer() {
        return commandContext.getPointer();
    }
}