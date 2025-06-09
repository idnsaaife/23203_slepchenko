package nsu.slepchenko.commands;

import nsu.slepchenko.context.CommandContext;
import nsu.slepchenko.context.Context;

public interface Command {
    void execute(Context context, CommandContext commandContext);
}
