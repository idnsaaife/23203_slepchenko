#include "headers/player.h"

unsigned int Player::countScore() const
{
    unsigned int sum = 0;
    for (size_t i = 0; i < myCards.size(); i++)
    {
        Card current = myCards[i];
        if (current.getRank() == Rank::Ace)
        {
            if ((sum + static_cast<unsigned int>(current.getRank())) > 21)
            {
                sum += 1;
                return sum;
            }
        }
        sum += static_cast<unsigned int>(current.getRank());
    }
    return sum;
}

const std::string &Player::getName() const
{
    return name;
}

void Player::takeCard(const Card &card)
{
    myCards.push_back(card);
}

bool Player::hitOrStand(const Card &oppositeCard)
{
    bool decision = myStrategy->decideTakeCard(countScore(), oppositeCard);
    return decision;
}

Card Player::getFirstCard() const
{
    return myCards[0];
}

std::vector<Card> Player::getHand() const
{
    return myCards;
}
