#include "headers/smartstrategy.h"

bool SmartStrategy::decideTakeCard(unsigned int score, const Card &oppositeCard)
{
    if (score > 17)
        return false;
    if (static_cast<unsigned int>(oppositeCard.getRank()) > 7)
        return score < 16;
    return score < 18;
}

namespace
{
    static StrategyRegistrar<SmartStrategy> smartStrategyRegistrar("smart");
}