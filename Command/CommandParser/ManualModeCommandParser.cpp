#include "ManualModeCommandParser.h"
#include "../../Exception/CommandParserException.h"
#include "../RobotCommand/GrabCommand.h"
#include "../RobotCommand/MoveCommand.h"
#include "../RobotCommand/ScanCommand.h"
#include "../RobotCommand/StopCommand.h"
#include <sstream>

ManualModeCommandParser::ManualModeCommandParser(Robot *robot)
        : RobotCommandParser(robot) {
}

Command *ManualModeCommandParser::parse_command_string(const std::string &command_string) {
    std::stringstream command_stringstream;
    command_stringstream << command_string;
    std::string command_name;
    command_stringstream >> command_name;
    std::vector<std::string> arguments;
    while (command_stringstream.good()) {
        std::string argument;
        command_stringstream >> argument;
        arguments.push_back(argument);
    }
    Robot *robot = this->get_robot();
    if (command_name == "MOVE") {
        Command *command = new MoveCommand(robot, arguments);
        return command;
    } else if (command_name == "SCAN") {
        Command *command = new ScanCommand(robot, arguments);
        return command;
    } else if (command_name == "GRAB") {
        Command *command = new GrabCommand(robot, arguments);
        return command;
    } else if (command_name == "STOP") {
        Command *command = new StopCommand(robot, arguments);
        return command;
    } else {
        throw CommandParserException("Unavailable or unknown command");
    }
}
