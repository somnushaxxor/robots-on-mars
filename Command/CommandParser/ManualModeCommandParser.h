#pragma once

#include "RobotCommandParser.h"

class ManualModeCommandParser final : public RobotCommandParser {
private:
public:
    explicit ManualModeCommandParser(Robot *robot);

    ~ManualModeCommandParser() override = default;

    Command *parse_command_string(const std::string &command_string) override;
};
