#include "TerrainLoaderException.h"
#include <string>

TerrainLoaderException::TerrainLoaderException(const char *message)
        : message(message) {
}

const char *TerrainLoaderException::what() const noexcept {
    std::string exception_name = "TerrainLoaderException: ";
    std::string what_text = exception_name + this->message;
    return what_text.c_str();
}
