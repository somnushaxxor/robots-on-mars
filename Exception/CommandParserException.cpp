#include "CommandParserException.h"
#include <string>

CommandParserException::CommandParserException(const char *message)
        : message(message) {
}

const char *CommandParserException::what() const noexcept {
    std::string exception_name = "CommandParserException: ";
    std::string what_text = exception_name + this->message;
    return what_text.c_str();
}
