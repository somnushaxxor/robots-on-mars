#include "DispatcherException.h"
#include <string>

DispatcherException::DispatcherException(const char *message)
        : message(message) {
}

const char *DispatcherException::what() const noexcept {
    std::string exception_name = "DispatcherException: ";
    std::string what_text = exception_name + this->message;
    return what_text.c_str();
}
