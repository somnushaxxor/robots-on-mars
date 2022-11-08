#include "RadioMessageHandlerException.h"
#include <string>

RadioMessageHandlerException::RadioMessageHandlerException(const char *message)
        : message(message) {
}

const char *RadioMessageHandlerException::what() const noexcept {
    std::string exception_name = "RadioMessageHandlerException: ";
    std::string what_text = exception_name + this->message;
    return what_text.c_str();
}
