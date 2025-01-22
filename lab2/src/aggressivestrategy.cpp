#include "headers/aggressivestrategy.h"

bool AggressiveStrategy::decideTakeCard(unsigned int score, const Card &oppositeCard)
{
    return score < 19;
}

namespace
{
    StrategyRegistrar<AggressiveStrategy> aggressiveStrategyRegistrar("aggressive");
}
