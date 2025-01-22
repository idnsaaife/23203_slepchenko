#include "headers/tournamentsimulation.h"

std::map<std::pair<size_t, size_t>, size_t> TournamentSimulation::run(std::vector<Player> &players_, Deck &deck_)
{
    std::map<std::pair<size_t, size_t>, size_t> results;
    for (size_t i = 0; i < players_.size(); i++)
        for (size_t j = i + 1; j < players_.size(); j++)
        {
            size_t winNum = playMatch(players_, i, j, deck_);
            results[{i, j}] = winNum;
        }
    return results;
}

namespace
{
    SimulationRegistrar<TournamentSimulation> TournamentSimulationRegistrar("tournament");
}
