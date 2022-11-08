#pragma once

#include <cstddef>
#include "AutoMode.h"

class AutoScanMode : public AutoMode {
private:
    size_t iterations_number;

public:
    AutoScanMode(Robot *robot, const size_t &iterations_number);

    ~AutoScanMode() override = default;

    bool find_path(std::deque<Command *> &new_commands_deque) override;

    void execute_next_command() override;
};
