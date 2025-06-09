package nsu.slepchenko.commands;

import nsu.slepchenko.context.*;

public interface Command {
    void execute(Context context, LoopContext loopContext);
}
