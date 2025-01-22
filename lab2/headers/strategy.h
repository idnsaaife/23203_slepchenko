#pragma once
#include "headers/card.h"
#include "nlohmann/json.hpp"

class Strategy
{
public:
    Strategy() = default;
    Strategy(const std::string &name, const nlohmann::json &config) {};
    Strategy(Strategy &&other) = default;
    Strategy(const Strategy &other) = default;
    virtual ~Strategy() = default;
    virtual bool decideTakeCard(unsigned int score, const Card &oppositeCard) = 0;
};