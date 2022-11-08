#pragma once

#include <string>
#include <vector>

class Command {
private:
    const std::vector<std::string> arguments;

protected:
    const std::vector<std::string> &get_arguments() const;

public:
    explicit Command(std::vector<std::string> arguments);

    virtual ~Command() = default;

    virtual void execute() = 0;
};

inline const std::vector<std::string> &Command::get_arguments() const {
    return arguments;
}
