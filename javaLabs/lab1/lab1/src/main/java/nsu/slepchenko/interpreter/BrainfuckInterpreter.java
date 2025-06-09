package nsu.slepchenko.interpreter;


import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import nsu.slepchenko.commands.Command;
import nsu.slepchenko.context.CommandContext;
import nsu.slepchenko.context.Context;
import nsu.slepchenko.context.LoopContext;

public class BrainfuckInterpreter {
    private static final Logger logger = LogManager.getLogger(BrainfuckInterpreter.class);
    private final long MAX_EXECUTION_TIME_NS = 30_000_000_000L;
    private Context context = new Context();
    private CommandContext commandContext;

    private LoopContext loopContext;


    public void execute(String program) {
        try {
            commandContext = new CommandContext(program);
            loopContext = new LoopContext(commandContext);
        } catch (IllegalArgumentException e) {
            logger.trace(e);
            System.out.println(e.getMessage());
            return;
        }
        long startTime = System.nanoTime();
        try {
            while (commandContext.size() > commandContext.getPointer()) {
                Command command = commandContext.getCommand(commandContext.getPointer());
                command.execute(context, loopContext);
                loopContext.incrementPointer();
                
                if ((System.nanoTime() - startTime) > MAX_EXECUTION_TIME_NS) {
                    logger.info("Execution time exceeded limit");
                    System.out.println("Execution time exceeded limit");
                    return;
                }
            }
        } catch (RuntimeException e) {
            logger.trace(e);
            System.out.println(e.getMessage());
        }

    }
}
