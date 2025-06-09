package nsu.slepchenko.commands;

import nsu.slepchenko.context.CommandContext;
import nsu.slepchenko.context.Context;

public class Output implements Command {
    @Override
    public void execute(Context context, CommandContext commandContext) {
        System.out.print((char) context.getValue());//???
    }
}
