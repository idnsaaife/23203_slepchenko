#include "headers/blackjack.h"

void BlackJackGame::run()
{
    Console console;

    if (players_.size() < 2)
    {
        console.printNotEnoughPlayers();
        return;
    }

    auto simulationFactory = SimulationFactory<std::string, Simulation>::getInstance();
    auto simulation = simulationFactory->createSimulation(mode_);

    std::map<std::pair<size_t, size_t>, size_t> results = simulation->run(players_, deck);

    for (const auto &pair : results)
    {
        console.printMatchPlayers(players_, pair.first.first, pair.first.second);
        console.printWinnerMatch(players_, results[{pair.first.first, pair.first.second}]);
        numOfVictories[results[{pair.first.first, pair.first.second}]] += 1;
    }

    size_t maxVictories = 0;
    size_t winNum = 0;
    for (size_t i = 0; i < players_.size(); i++)
    {
        if (maxVictories < numOfVictories[i]) {
            maxVictories = numOfVictories[i];
            winNum = i;
        }
    }
    if (maxVictories > 0) console.printWinner(players_[winNum]);
}
