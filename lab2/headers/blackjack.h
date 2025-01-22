#pragma once
#include "headers/strategy.h"
#include "headers/deck.h"
#include "headers/player.h"
#include "headers/factory.h"
#include "headers/simulationfactory.h"
#include "headers/simulation.h"
#include "headers/console.h"

class BlackJackGame
{
public:
    BlackJackGame(const std::string &mode, std::vector<Player> players, const std::string &deckType)
        : players_(std::move(players)), numOfVictories(players_.size()), mode_(mode), deck(deckType) {};
    void run();


private:
    std::vector<Player> players_;
    std::vector<size_t> numOfVictories;
    std::string mode_; 
    Deck deck;
};
