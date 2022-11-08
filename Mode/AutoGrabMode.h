#pragma once

#include "AutoMode.h"

class AutoGrabMode : public AutoMode {
private:
public:
    explicit AutoGrabMode(Robot *robot);

    ~AutoGrabMode() override = default;

    bool find_path(std::deque<Command *> &new_commands_deque) override;

    void execute_next_command() override;
};
