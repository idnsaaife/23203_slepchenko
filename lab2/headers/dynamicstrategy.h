#include "headers/strategy.h"

#include <vector>
#include <string>
#include <random>
#include <nlohmann/json.hpp>

#include "headers/card.h"

class DynamicStrategy : public Strategy
{
private:
    std::string strategyName;
    unsigned int maxScore;
    unsigned int expectedOpponentScore;
    double riskTolerance;
    double opponentHighCardImpact;

    void applyConfig(const nlohmann::json &config);

public:
    DynamicStrategy(const std::string &name, const nlohmann::json &config);
    bool decideTakeCard(unsigned int score, const Card &opponentCard) override;
};