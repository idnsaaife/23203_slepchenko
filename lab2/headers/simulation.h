#pragma once

#include "headers/deck.h"
#include "headers/strategy.h"
#include "headers/player.h"
#include "headers/blackjacknum.h"

class Simulation
{
public:
    virtual std::map<std::pair<size_t, size_t>, size_t> run(std::vector<Player> &players_, Deck &deck_) = 0;
    virtual ~Simulation() = default;
    size_t determineWinner(const std::vector<Player> &players_, size_t num0, size_t num1) const;
    size_t playMatch(std::vector<Player> &players_, size_t num0, size_t num1, Deck &deck_);
};
