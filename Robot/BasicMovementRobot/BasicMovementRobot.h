#pragma once

#include "../Robot.h"

class BasicMovementRobot : public Robot {
private:
public:
    BasicMovementRobot(Terrain &terrain, RadioChannel *radio_channel, const size_t &id, const RobotWeight &weight,
                       const bool &is_armoured, const std::list<std::string> &preinstalled_modes_names);

    ~BasicMovementRobot() override = default;

    void move(const Direction &direction) override;
};
