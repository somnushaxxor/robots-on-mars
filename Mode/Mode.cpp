#include "Mode.h"
#include "../Command/Command.h"
#include "../Command/CommandParser/RobotCommandParser.h"

Mode::Mode(Robot *robot, RobotCommandParser *command_parser)
        : robot(robot), command_parser(command_parser), is_stopped(false) {
}

Mode::~Mode() {
    delete command_parser;
    command_parser = nullptr;
    while (!commands_deque.empty()) {
        Command *command = commands_deque.front();
        delete command;
        command = nullptr;
        commands_deque.pop_front();
    }
}

Command *Mode::pop_next_command() {
    Command *next_command = nullptr;
    if (!commands_deque.empty()) {
        next_command = commands_deque.front();
        commands_deque.pop_front();
    }
    return next_command;
}
