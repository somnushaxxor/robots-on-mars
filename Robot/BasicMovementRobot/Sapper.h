#pragma once

#include "BasicMovementRobot.h"

class Sapper final : public BasicMovementRobot {
private:
public:
    Sapper(Terrain &terrain, RadioChannel *radio_channel, const size_t &id);

    ~Sapper() override = default;
};
