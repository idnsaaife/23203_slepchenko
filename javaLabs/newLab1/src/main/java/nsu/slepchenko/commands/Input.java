package nsu.slepchenko.commands;

import nsu.slepchenko.context.CommandContext;
import nsu.slepchenko.context.Context;


public class Input implements Command {
    @Override
    public void execute(Context context, CommandContext commandContext) {
        try {
            context.setValue((byte)( System.in.read()));//????????
        } catch(Exception e) {
            e.getStackTrace();//?????
        }
    }
}
