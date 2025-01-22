#pragma once
#include "headers/strategy.h"
#include "headers/card.h"
#include "headers/player.h"

class Console
{
public:
    std::string getInput();
    void printHelp();
    bool waitQuit();
    void printWinner(const Player &player);
    void printFirstCard(const Player &player);
    void printHand(const Player &player);
    void printScore(const Player &player);
    void printStand(const Player &player);
    void printHit(const Player &player);
    void printMatchPlayers(std::vector<Player> &players, size_t num1, size_t num2);
    void printWinnerMatch(std::vector<Player> &players, size_t winNum);
    void printNotEnoughPlayers();
};