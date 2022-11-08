#pragma once

#include "RobotCommand.h"

class MoveCommand final : public RobotCommand {
private:
public:
    MoveCommand(Robot *robot, const std::vector<std::string> &arguments);

    ~MoveCommand() override = default;

    void execute() override;
};
