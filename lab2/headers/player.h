#pragma once
#include "headers/deck.h"
#include "headers/strategy.h"
#include "headers/card.h"

class Player
{
public:
    Player(std::unique_ptr<Strategy> strategy, std::string name_)
        : myStrategy(std::move(strategy)), name(name_) {};
    Player() = delete;
    Player(const Player &other) = delete;
    Player(Player &&other) noexcept = default;
    Player &operator=(Player &&other) = default;
    Player &operator=(const Player &other) = delete;
    unsigned int countScore() const;
    const std::string &getName() const;
    void takeCard(const Card &card);
    bool hitOrStand(const Card &oppositeCard);
    Card getFirstCard() const;
    std::vector<Card> getHand() const;

private:
    std::unique_ptr<Strategy> myStrategy;
    std::vector<Card> myCards;
    std::string name;
};