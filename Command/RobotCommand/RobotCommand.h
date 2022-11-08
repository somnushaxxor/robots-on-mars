#pragma once

#include "../../Robot/Robot.h"
#include "../Command.h"

class RobotCommand : public Command {
private:
    Robot *robot;

protected:
    Robot *get_robot();

public:
    RobotCommand(Robot *robot, const std::vector<std::string> &arguments);

    ~RobotCommand() override = default;
};

inline Robot *RobotCommand::get_robot() {
    return robot;
}
