package nsu.slepchenko.interpreter;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import nsu.slepchenko.commands.Command;
import nsu.slepchenko.commands.CommandFactory;
import nsu.slepchenko.context.CommandContext;
import nsu.slepchenko.context.Context;

public class BrainfuckInterpreter {
    private static final Logger logger = LogManager.getLogger(BrainfuckInterpreter.class);

    private CommandFactory commandFactory = new CommandFactory();
    private Context context = new Context();
    private CommandContext commandContext = new CommandContext();


    public void execute(String program) {
        for (char commandSymbol : program.toCharArray()) {
            Command command = commandFactory.createCommandByName(commandSymbol);
            commandContext.addCommand(command);
        }

        try {
            while (commandContext.size() > commandContext.getPointer()) {

                Command command = commandContext.getCommand(commandContext.getPointer());
                if (command != null) {
                    command.execute(context, commandContext);
                }
                commandContext.incrementPointer();
            }
        } catch (Exception e) {
            logger.trace(e);
        }

        if (!commandContext.isEmpty()) {
            logger.error("Not enough ]");
            System.out.println("Incorrect loop, not enough ]");
        }
    }
}
