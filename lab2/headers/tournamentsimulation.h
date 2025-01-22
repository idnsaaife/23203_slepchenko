#pragma once
#include "headers/simulation.h"
#include "headers/deck.h"
#include "headers/player.h"
#include "headers/strategy.h"
#include "headers/simulationregistrar.h"
#include "headers/console.h"

class TournamentSimulation : public Simulation
{
public:
    std::map<std::pair<size_t, size_t>, size_t> run(std::vector<Player> &players_, Deck &deck_) override;
};


