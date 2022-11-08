#pragma once

#include "SimulationCommand.h"

class EndCommand final : public SimulationCommand {
private:
public:
    EndCommand(Simulation *simulation, const std::vector<std::string> &arguments);

    ~EndCommand() override = default;

    void execute() override;
};
