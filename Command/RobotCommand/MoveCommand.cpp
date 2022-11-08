#include "MoveCommand.h"
#include "../../Exception/CommandException.h"

MoveCommand::MoveCommand(Robot *robot, const std::vector<std::string> &arguments)
        : RobotCommand(robot, arguments) {
}

void MoveCommand::execute() {
    const std::vector<std::string> &arguments = this->get_arguments();
    if (arguments.size() != 1) {
        throw CommandException("Bad number of arguments");
    } else {
        Robot *robot = this->get_robot();
        Terrain &terrain = robot->get_terrain();
        if (arguments[0] == "U") {
            robot->move(Direction::UP);
            terrain.move_robot(robot, Direction::UP);
        } else if (arguments[0] == "D") {
            robot->move(Direction::DOWN);
            terrain.move_robot(robot, Direction::DOWN);
        } else if (arguments[0] == "L") {
            robot->move(Direction::LEFT);
            terrain.move_robot(robot, Direction::LEFT);
        } else if (arguments[0] == "R") {
            robot->move(Direction::RIGHT);
            terrain.move_robot(robot, Direction::RIGHT);
        } else {
            throw CommandException("Invalid arguments");
        }
    }
}
