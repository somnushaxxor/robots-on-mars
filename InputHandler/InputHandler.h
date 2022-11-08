#pragma once

#include <string>

class InputHandler {
private:
public:
    InputHandler() = default;

    virtual ~InputHandler() = default;

    virtual std::string get_input() = 0;
};
