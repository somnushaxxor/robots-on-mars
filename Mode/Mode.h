#pragma once

#include <deque>

class Command;

class Robot;

class RobotCommandParser;

class Mode {
private:
    Robot *robot;
    RobotCommandParser *command_parser;
    std::deque<Command *> commands_deque;
    bool is_stopped;

protected:
    Robot *get_robot();

    Command *pop_next_command();

public:
    Mode(Robot *robot, RobotCommandParser *command_parser);

    virtual ~Mode();

    RobotCommandParser *get_command_parser();

    std::deque<Command *> &get_commands_deque();

    bool get_stopped_state() const;

    void stop();

    void push_command_to_deque(Command *command);

    virtual void execute_next_command() = 0;
};

inline Robot *Mode::get_robot() {
    return robot;
}

inline RobotCommandParser *Mode::get_command_parser() {
    return command_parser;
}

inline std::deque<Command *> &Mode::get_commands_deque() {
    return commands_deque;
}

inline void Mode::push_command_to_deque(Command *command) {
    commands_deque.push_back(command);
}

inline bool Mode::get_stopped_state() const {
    return is_stopped;
}

inline void Mode::stop() {
    is_stopped = true;
}
