#pragma once

#include "CommandParser.h"

class Robot;

class RobotCommandParser : public CommandParser {
private:
    Robot *robot;

protected:
    Robot *get_robot();

public:
    explicit RobotCommandParser(Robot *robot);

    ~RobotCommandParser() override = default;
};

inline Robot *RobotCommandParser::get_robot() {
    return robot;
}
