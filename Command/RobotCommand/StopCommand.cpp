#include "StopCommand.h"
#include "../../Exception/CommandException.h"

StopCommand::StopCommand(Robot *robot, const std::vector<std::string> &arguments)
        : RobotCommand(robot, arguments) {
}

void StopCommand::execute() {
    const std::vector<std::string> &arguments = this->get_arguments();
    if (!arguments.empty()) {
        throw CommandException("Bad number of arguments");
    } else {
        Robot *robot = this->get_robot();
        Mode *mode = robot->get_mode();
        mode->stop();
    }
}
