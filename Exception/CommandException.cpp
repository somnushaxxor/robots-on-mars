#include "CommandException.h"
#include <string>

CommandException::CommandException(const char *message)
        : message(message) {
}

const char *CommandException::what() const noexcept {
    std::string exception_name = "CommandException: ";
    std::string what_text = exception_name + this->message;
    return what_text.c_str();
}
