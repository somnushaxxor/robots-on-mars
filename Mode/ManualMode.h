#pragma once

#include "Mode.h"

class ManualMode final : public Mode {
private:
public:
    explicit ManualMode(Robot *robot);

    ~ManualMode() override = default;

    void execute_next_command() override;
};
