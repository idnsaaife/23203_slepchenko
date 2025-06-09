package nsu.slepchenko.commands;

import nsu.slepchenko.App;
import nsu.slepchenko.context.Context;
import nsu.slepchenko.context.LoopContext;


public class LoopStart implements Command {

    @Override
    public void execute(Context context, LoopContext loopContext) {
        loopContext.unsetLoopFlag();
        if (context.getValue() == 0) {
            int pairPosition = loopContext.getBracketPair(loopContext.getPointer());
            if (pairPosition == -1) {
                throw new IllegalStateException("No matching ] found for [ at " + loopContext.getPointer());
            }
            loopContext.setPointer(pairPosition);
        }
    }
}
