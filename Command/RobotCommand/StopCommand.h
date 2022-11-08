#pragma once

#include "RobotCommand.h"

class StopCommand final : public RobotCommand {
private:
public:
    StopCommand(Robot *robot, const std::vector<std::string> &arguments);

    ~StopCommand() override = default;

    void execute() override;
};
