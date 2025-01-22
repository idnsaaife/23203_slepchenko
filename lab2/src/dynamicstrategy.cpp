#include "headers/dynamicstrategy.h"
#include <vector>
#include <string>
#include <random>
#include <nlohmann/json.hpp>

void DynamicStrategy::applyConfig(const nlohmann::json &config)
{
    maxScore = config.value("maxScore", 17);
    riskTolerance = config.value("riskTolerance", 0.5);
    opponentHighCardImpact = config.value("opponentHighCardImpact", 0.0);
    expectedOpponentScore = config.value("expectedOpponentScore", 8);
}

DynamicStrategy::DynamicStrategy(const std::string &name, const nlohmann::json &config)
    : strategyName(name), maxScore(17), riskTolerance(0.5), opponentHighCardImpact(0.0)
{
    applyConfig(config);
}

bool DynamicStrategy::decideTakeCard(unsigned int score, const Card &opponentCard)
{
    if (score >= maxScore)
    {
        return false;
    }
    double effectiveRiskTolerance = 1.0;
    if (static_cast<unsigned int>(opponentCard.getRank()) >= expectedOpponentScore)
    {
        effectiveRiskTolerance -= opponentHighCardImpact;
    }

    return effectiveRiskTolerance > riskTolerance;
}
