#pragma once

#include "SimulationCommand.h"

class SetModeCommand final : public SimulationCommand {
private:
public:
    SetModeCommand(Simulation *simulation, const std::vector<std::string> &arguments);

    ~SetModeCommand() override = default;

    void execute() override;
};
