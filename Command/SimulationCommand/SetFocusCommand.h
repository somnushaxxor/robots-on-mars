#pragma once

#include "SimulationCommand.h"

class SetFocusCommand final : public SimulationCommand {
private:
public:
    SetFocusCommand(Simulation *simulation, const std::vector<std::string> &arguments);

    ~SetFocusCommand() override = default;

    void execute() override;
};
