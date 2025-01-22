#include "headers/simplestrategy.h"
#include "headers/strategyregistrar.h"

bool SimpleStrategy::decideTakeCard(unsigned int score, const Card &oppositeCard)
{
    return score < 17;
}

namespace
{
    StrategyRegistrar<SimpleStrategy> simpleStrategyRegistrar("simple");
}
