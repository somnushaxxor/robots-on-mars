#pragma once

#include "RobotCommand.h"

class GrabCommand final : public RobotCommand {
private:
public:
    GrabCommand(Robot *robot, const std::vector<std::string> &arguments);

    ~GrabCommand() override = default;

    void execute() override;
};
