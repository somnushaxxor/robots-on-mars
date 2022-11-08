#pragma once

#include <string>

class Command;

class CommandParser {
private:
public:
    CommandParser() = default;

    virtual ~CommandParser() = default;

    virtual Command *parse_command_string(const std::string &command_string) = 0;
};
