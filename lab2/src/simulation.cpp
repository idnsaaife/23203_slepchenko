#include "headers/simulation.h"

size_t Simulation::determineWinner(const std::vector<Player> &players_, size_t num0, size_t num1) const
{
    if (players_[num0].countScore() <= BLACKJACK_NUM && players_[num1].countScore() <= BLACKJACK_NUM)
    {
        if (players_[num0].countScore() <= players_[num1].countScore())
        {
            return num1;
        }
        return num0;
    }
    if (players_[num0].countScore() <= BLACKJACK_NUM && players_[num1].countScore() > BLACKJACK_NUM)
        return num0;

    return num1;
}

size_t Simulation::playMatch(std::vector<Player> &players_, size_t num0, size_t num1, Deck &deck_)
{
    players_[num0].takeCard(deck_.giveCard());
    players_[num1].takeCard(deck_.giveCard());
    while ((!players_[num0].hitOrStand(players_[num1].getFirstCard())) && (!players_[num1].hitOrStand(players_[num0].getFirstCard())))
    {
        if (players_[num0].hitOrStand(players_[num1].getFirstCard()))
        {
            players_[num0].takeCard(deck_.giveCard());
        }

        if (players_[num0].countScore() > BLACKJACK_NUM)
        {
            break;
        }

        if (players_[num1].hitOrStand(players_[num0].getFirstCard()))
        {
            players_[num1].takeCard(deck_.giveCard());
        }

        if (players_[num1].countScore() > BLACKJACK_NUM)
        {
            break;
        }
    }
    return determineWinner(players_, num0, num1);
}