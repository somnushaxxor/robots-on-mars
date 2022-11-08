#pragma once

#include "SimulationCommand.h"

class ContinueCommand final : public SimulationCommand {
private:
public:
    ContinueCommand(Simulation *simulation, const std::vector<std::string> &arguments);

    ~ContinueCommand() override = default;

    void execute() override;
};
