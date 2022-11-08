#pragma once

#include "SimulationCommand.h"

class AddCommand final : public SimulationCommand {
private:
public:
    AddCommand(Simulation *simulation, const std::vector<std::string> &arguments);

    ~AddCommand() override = default;

    void execute() override;
};
