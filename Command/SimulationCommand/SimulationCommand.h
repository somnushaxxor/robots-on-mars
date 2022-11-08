#pragma once

#include "../../Simulation/Simulation.h"
#include "../Command.h"

class SimulationCommand : public Command {
private:
    Simulation *simulation;

protected:
    Simulation *get_simulation();

public:
    SimulationCommand(Simulation *simulation, const std::vector<std::string> &arguments);

    ~SimulationCommand() override = default;
};

inline Simulation *SimulationCommand::get_simulation() {
    return simulation;
}
