#pragma once

#include "CommandParser.h"

class Simulation;

class SimulationCommandParser final : public CommandParser {
private:
    Simulation *simulation;

public:
    explicit SimulationCommandParser(Simulation *simulation);

    ~SimulationCommandParser() override = default;

    Command *parse_command_string(const std::string &command_string) override;
};
