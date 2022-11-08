#include "Command.h"

#include <utility>

Command::Command(std::vector<std::string> arguments)
        : arguments(std::move(arguments)) {
}
