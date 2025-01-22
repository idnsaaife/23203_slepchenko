#include "headers/detailedsimulation.h"

std::map<std::pair<size_t, size_t>, size_t> DetailedSimulation::run(std::vector<Player> &players_, Deck &deck_)
{
    std::map<std::pair<size_t, size_t>, size_t> results;
    Console console;

    players_[0].takeCard(deck_.giveCard());
    console.printFirstCard(players_[0]);
    console.printScore(players_[0]);

    players_[1].takeCard(deck_.giveCard());
    console.printFirstCard(players_[1]);
    console.printScore(players_[1]);

    while (1)
    {
        if (!console.waitQuit())
        {
            results.clear();
            return results;
        }

        if (!players_[0].hitOrStand(players_[1].getFirstCard()))
        {
            console.printStand(players_[0]);
            if (!players_[1].hitOrStand(players_[0].getFirstCard()))
                break;
        }

        else
        {
            console.printHit(players_[0]);
            players_[0].takeCard(deck_.giveCard());
            console.printHand(players_[0]);
            console.printScore(players_[0]);
        }

        if (players_[0].countScore() > BLACKJACK_NUM)
        {
            break;
        }

        if (!players_[1].hitOrStand(players_[0].getFirstCard()))
        {
            console.printStand(players_[1]);
            if (!players_[0].hitOrStand(players_[1].getFirstCard()))
                break;
        }

        else
        {
            console.printHit(players_[1]);
            players_[1].takeCard(deck_.giveCard());
            console.printHand(players_[1]);
            console.printScore(players_[1]);
        }

        if (players_[1].countScore() > BLACKJACK_NUM)
        {
            break;
        }
    }
    size_t winNum = determineWinner(players_, 0, 1);
    results[{0, 1}] = winNum;
    return results;
}

namespace
{
    SimulationRegistrar<DetailedSimulation> DetailedSimulationRegistrar("detailed");
}
