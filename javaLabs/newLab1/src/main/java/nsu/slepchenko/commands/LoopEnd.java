package nsu.slepchenko.commands;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import nsu.slepchenko.context.CommandContext;
import nsu.slepchenko.context.Context;

public class LoopEnd implements Command {

    private static final Logger logger = LogManager.getLogger(LoopEnd.class);

    @Override
    public void execute(Context context, CommandContext commandContext) {
        if (context.getValue() != 0) {
            commandContext.setPointer(commandContext.getLastLoopStart());
        } else {
            logger.info("Value is zero, loop ended");
            try {
            commandContext.popLoopStart();
        } catch (Exception e) {
            logger.error("Not enough [");
            }
        }
    }
}
