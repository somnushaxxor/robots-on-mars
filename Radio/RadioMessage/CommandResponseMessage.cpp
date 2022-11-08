#include "CommandResponseMessage.h"

#include <utility>

CommandResponseMessage::CommandResponseMessage(std::string command_string)
        : command_string(std::move(command_string)) {
}
