#pragma once

#include "Mode.h"

class AutoMode : public Mode {
private:
public:
    explicit AutoMode(Robot *robot);

    ~AutoMode() override = default;

    bool set_new_aim();

    virtual bool find_path(std::deque<Command *> &new_commands_deque) = 0;
};
