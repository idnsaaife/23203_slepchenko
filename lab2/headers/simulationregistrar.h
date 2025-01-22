#pragma once
#include "headers/simulationfactory.h"
#include "headers/simulation.h"

template <typename SimulationType>
class SimulationRegistrar
{
public:
    SimulationRegistrar(const std::string &name)
    {
        SimulationFactory<std::string, Simulation>::getInstance()->registSimulation(name, createSimulationInstance);
    }

private:
    static Simulation *createSimulationInstance()
    {
        return new SimulationType();
    }
};
