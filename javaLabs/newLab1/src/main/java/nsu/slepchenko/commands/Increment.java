package nsu.slepchenko.commands;

import nsu.slepchenko.context.CommandContext;
import nsu.slepchenko.context.Context;


public class Increment implements Command{
    @Override
    public void execute(Context context, CommandContext commandContext) {
        context.incrementValue();
    }
}
