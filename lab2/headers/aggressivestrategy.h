#include "headers/strategy.h"
#include "headers/strategyregistrar.h"
#include "headers/factory.h"

class AggressiveStrategy : public Strategy
{
public:
    bool decideTakeCard(unsigned int score, const Card &oppositeCard) override;
};
