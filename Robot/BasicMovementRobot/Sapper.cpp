#include <cstddef>
#include "Sapper.h"

Sapper::Sapper(Terrain &terrain, RadioChannel *radio_channel, const size_t &id)
        : BasicMovementRobot(terrain, radio_channel, id, RobotWeight::HEAVY, true, {"AUTO_DEFUSE"}) {
}
