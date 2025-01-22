#include "headers/fastsimulation.h"

std::map<std::pair<size_t, size_t>, size_t> FastSimulation::run(std::vector<Player> &players_, Deck &deck_) 
{
    std::map<std::pair<size_t, size_t>, size_t> results;
    Console console;
    size_t winNum = playMatch(players_, 0, 1, deck_);
    console.printFirstCard(players_[0]);
    console.printFirstCard(players_[1]);
    results[{0, 1}] = winNum;
    return results;
}

namespace
{
    SimulationRegistrar<FastSimulation> FastSimulationRegistrar("fast");
}