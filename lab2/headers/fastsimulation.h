#pragma once
#include "headers/simulation.h"
#include "headers/simulationregistrar.h"
#include "headers/simulationfactory.h"
#include "headers/console.h"

class FastSimulation : public Simulation
{
public:
    std::map<std::pair<size_t, size_t>, size_t> run(std::vector<Player> &players_, Deck &deck_) override;
};
