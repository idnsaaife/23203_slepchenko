#pragma once
#include "headers/factory.h"
#include "headers/strategy.h"

template <typename StrategyType>
class StrategyRegistrar
{
public:
    StrategyRegistrar(const std::string &name)
    {
        Factory<std::string, Strategy>::getInstance()->registStrategy(name, createStrategyInstance);
    }    

private:
    static Strategy *createStrategyInstance()
    {
        return new StrategyType();
    }
    
};
