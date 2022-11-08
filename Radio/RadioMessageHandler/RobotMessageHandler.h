#pragma once

#include "RadioMessageHandler.h"

class Robot;

class RobotMessageHandler final : public RadioMessageHandler {
private:
    Robot *robot;

public:
    explicit RobotMessageHandler(Robot *robot);

    ~RobotMessageHandler() override = default;

    void handle_message(RadioMessage *message) override;
};
