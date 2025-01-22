#include <iostream>
#include <fstream>
#include "headers/factory.h"
#include "headers/blackjack.h"
#include "headers/player.h"
#include "headers/loader.h"
#include "headers/console.h"
#include "headers/dynamicstrategy.h"

void registerDynamicStrategy(const std::string &strategyName, const nlohmann::json &config)
{
    Factory<std::string, Strategy>::getInstance()->registConfigStrategy(strategyName, [strategyName, config](const nlohmann::json &)
                                                                       { return new DynamicStrategy(strategyName, config); });
}

int main(int argc, char *argv[])
{
    Console console;
    std::cout << "BlackJack Game loading..." << std::endl;
    if (argc < 3)
    {
        std::cout << "Incorrect number of arguments" << std::endl;
        console.printHelp();
        return 0;
    }

    std::string deckType = "simple";
    std::string mode = "detailed";
    std::vector<std::string> strategiesNames;
    std::string configDir = "configs/";
    std::string strategiesConfigFile = configDir + "strategies.config";
    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];
        if (arg.find("--") == 0)
        {
            if (arg.find("--mode=") == 0)
            {
                mode = arg.substr(7);
                std::cout << "Mode set to: " << mode << std::endl;
            }
            else if (arg.find("--configs=") == 0)
            {
                configDir = arg.substr(10);
            }

            else if (arg.find("--deck=") == 0)
            {
                deckType = arg.substr(7);
                std::cout << "Deck type set to: " << deckType << std::endl;
            }
            else if (arg.find("--strategies=") == 0)
            {
                std::string strategiesList = arg.substr(13);
                size_t pos = 0;
                while ((pos = strategiesList.find(',')) != std::string::npos)
                {
                    strategiesNames.push_back(strategiesList.substr(0, pos));
                    strategiesList.erase(0, pos + 1);
                }
                strategiesNames.push_back(strategiesList);
                std::cout << "Strategies set to: ";
                for (const auto &strategy : strategiesNames)
                {
                    std::cout << strategy << " ";
                }
                std::cout << std::endl;
            }
        }
        else
        {
            std::cerr << "Unknown argument: " << arg << std::endl;
        }
    }

    std::vector<Player> players;
    auto strategiesFactory = Factory<std::string, Strategy>::getInstance();
    try
    {
        for (const auto &name : strategiesNames)
        {
            std::string dynamicConfigFile = configDir + "/" + name + ".json";
            Loader loader;
            if(!loader.loadDynamicStrategyConfig(dynamicConfigFile))
            {
                players.emplace_back(strategiesFactory->createStrategyByName(name), name);
                continue;
            }
            registerDynamicStrategy(name, loader.getConfig());
            players.emplace_back(strategiesFactory->createStrategyByConfig(name, loader.getConfig()), name);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }

    std::cout << "Starting Blackjack game with mode: " << mode << ", and deck type: " << deckType << std::endl;
    BlackJackGame game(mode, std::move(players), deckType);
    game.run();
    std::cout << "Blackjack game ended." << std::endl;

    return 0;
}
