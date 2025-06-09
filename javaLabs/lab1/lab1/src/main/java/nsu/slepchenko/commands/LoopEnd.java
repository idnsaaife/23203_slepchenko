package nsu.slepchenko.commands;

import java.security.InvalidParameterException;
import java.util.EmptyStackException;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import nsu.slepchenko.context.Context;
import nsu.slepchenko.context.LoopContext;

public class LoopEnd implements Command {
    private static final long MAX_EXECUTION_TIME_NS = 20_000_000_000L;
    private long startTime = -1;
    @Override
    public void execute(Context context, LoopContext loopContext) {
        if (context.getValue() != 0) {
            if (startTime == -1) {
                startTime = System.nanoTime();
            }
            int pairPosition = loopContext.getBracketPair(loopContext.getPointer());
            if (pairPosition == -1) {
                throw new IllegalStateException("No matching [ found for ] at " + loopContext.getPointer());
            }
            if (System.nanoTime() - startTime > MAX_EXECUTION_TIME_NS) {
                throw new RuntimeException("Execution time exceeded limit at position " + loopContext.getPointer());
            }
            loopContext.setPointer(pairPosition);
            loopContext.setLoopFlag();
        }
        else {
            loopContext.unsetLoopFlag();
            startTime = -1;
        }
    }
}
