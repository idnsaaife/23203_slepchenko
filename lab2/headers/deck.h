#pragma once
#include "headers/card.h"

#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <string>
#include <algorithm>

class Deck
{
public:
    Deck(const std::string &type);
    void shuffleDeck();
    const Card &giveCard();
    size_t size() const;

private:
    std::mt19937 rng{std::random_device{}()};
    std::vector<Card> cards;
};
