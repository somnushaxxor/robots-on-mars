#include "RobotCommand.h"

RobotCommand::RobotCommand(Robot *robot, const std::vector<std::string> &arguments)
        : Command(arguments), robot(robot) {
}
