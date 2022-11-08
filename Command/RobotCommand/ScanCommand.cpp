#include "ScanCommand.h"
#include "../../Exception/CommandException.h"
#include "../../Robot/BasicMovementRobot/Collector.h"

ScanCommand::ScanCommand(Robot *robot, const std::vector<std::string> &arguments)
        : RobotCommand(robot, arguments) {
}

void ScanCommand::execute() {
    const std::vector<std::string> &arguments = this->get_arguments();
    if (!arguments.empty()) {
        throw CommandException("Bad number of arguments");
    } else {
        auto *collector = dynamic_cast<Collector *>(this->get_robot());
        collector->scan();
    }
}
