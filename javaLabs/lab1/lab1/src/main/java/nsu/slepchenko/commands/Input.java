package nsu.slepchenko.commands;

import nsu.slepchenko.context.CommandContext;
import nsu.slepchenko.context.Context;
import nsu.slepchenko.context.LoopContext;

import java.io.IOException;


public class Input implements Command {
    @Override
    public void execute(Context context, LoopContext loopContext) {
        try {
            context.setValue((byte)( System.in.read()));
        } catch(IOException e) {
            throw new RuntimeException("Error while reading", e);
        }
    }
}
