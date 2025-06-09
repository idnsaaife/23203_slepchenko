package nsu.slepchenko.commands;

import nsu.slepchenko.context.CommandContext;
import nsu.slepchenko.context.Context;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

public class LoopStart implements Command {
    private static final Logger logger = LogManager.getLogger(LoopStart.class);

    @Override
    public void execute(Context context, CommandContext commandContext) {
        logger.info("Loop at programm is starting");
        if (context.getValue() == 0) {
            
            int depth = 1;
            while (depth > 0) {
                try {
                    commandContext.incrementPointer();
                    Command command = commandContext.getCommand(commandContext.getPointer());
                    if (command.getClass() == LoopStart.class)
                        depth++;
                    if (command.getClass() == LoopEnd.class)
                        depth--;
                } catch (Exception e) {
                    logger.error("Not enough ]");
                    System.err.println("Error! Not enough ]");
                    break;
                }
            }
            if (depth < 0) {
                logger.error("Not enough [");
                System.err.println("Error! Not enough [");
            }
        } else {
            commandContext.pushLoopStart(commandContext.getPointer());
        }
    }
}
