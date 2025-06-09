package nsu.slepchenko.commands;
import java.io.InputStream;
import java.util.HashMap;
import java.util.Properties;

public class CommandFactory {
    private HashMap<Character, Command> commandMap = new HashMap<>();
    private Properties commandConfig = new Properties();

    public CommandFactory() {
        try (InputStream input = CommandFactory.class.getResourceAsStream("/command.properties")) {
            if (input == null) {
                throw new RuntimeException("configFile not found");
            }
            commandConfig.load(input);
        } catch (Exception e) {
            throw new IllegalArgumentException("Config file can't load");
        }
    }

    public void registCommand(char commandName, String commandClassName) {
        if (commandClassName == null) {
            throw new RuntimeException("Unknown command symbol: " + commandName);
        }
        try {
            Command command = (Command) Class.forName(commandClassName).getConstructor().newInstance();
            commandMap.put(commandName, command);
        } catch (Exception e) {
            throw new RuntimeException("error creating command for symbol: " + commandName);
        }
    }

    public Command createCommandByName(char commandName) {
        if (commandMap.containsKey(commandName)) {
            return commandMap.get(commandName);
        }

        String commandClassName = commandConfig.getProperty(String.valueOf(commandName));
        registCommand(commandName, commandClassName);

        return commandMap.get(commandName);
    }
}
