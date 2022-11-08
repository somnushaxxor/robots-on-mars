#pragma once

#include "AutoMode.h"

class AutoDefuseMode : public AutoMode {
private:
public:
    explicit AutoDefuseMode(Robot *robot);

    ~AutoDefuseMode() override = default;

    bool find_path(std::deque<Command *> &new_commands_deque) override;

    void execute_next_command() override;
};
