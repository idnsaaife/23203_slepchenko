#pragma once

#include <map>
#include "headers/simulation.h"

template <class Key, class Product>
class SimulationFactory
{
public:
    static SimulationFactory *getInstance()
    {
        static SimulationFactory sf;
        return &sf;
    }

    void registSimulation(const Key &simulationName, std::function<Product *()> creator)
    {
        creators_[simulationName] = creator;
    }

    std::unique_ptr<Simulation> createSimulation(const Key &simulationName)
    {
        if (!creators_.contains(simulationName))
        {
            throw std::runtime_error("Simulation not found: " + simulationName);
        }
        auto &creator = creators_.at(simulationName);
        return std::unique_ptr<Simulation>(creator());
    }

private:
    SimulationFactory() = default;
    ~SimulationFactory() = default;
    SimulationFactory(const SimulationFactory &) = delete;
    SimulationFactory &operator=(const SimulationFactory &) = delete;
    SimulationFactory(SimulationFactory &&) = delete;
    SimulationFactory &operator=(SimulationFactory &&) = delete;
    std::unordered_map<Key, std::function<Product *()>> creators_;
};
