#include "headers/strategy.h"
#include "headers/strategyregistrar.h"

class SimpleStrategy : public Strategy
{
public:
    bool decideTakeCard(unsigned int score, const Card &oppositeCard) override;
};