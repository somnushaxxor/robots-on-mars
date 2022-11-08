#pragma once

#include "RobotCommand.h"

class ScanCommand final : public RobotCommand {
private:
public:
    ScanCommand(Robot *robot, const std::vector<std::string> &arguments);

    ~ScanCommand() override = default;

    void execute() override;
};
