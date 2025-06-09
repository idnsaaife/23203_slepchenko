package nsu.slepchenko.commands;

import nsu.slepchenko.context.CommandContext;
import nsu.slepchenko.context.Context;
import nsu.slepchenko.context.LoopContext;


public class Decrement implements Command {
    @Override
    public void execute(Context context, LoopContext loopContext) {
        context.decrementValue();
    }
}
