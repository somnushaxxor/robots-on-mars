#include <cstddef>
#include <string>
#include "BasicMovementRobot.h"

BasicMovementRobot::BasicMovementRobot(Terrain &terrain, RadioChannel *radio_channel, const size_t &id,
                                       const RobotWeight &weight, const bool &is_armoured,
                                       const std::list<std::string> &preinstalled_modes_names)
        : Robot(terrain, radio_channel, id, weight, is_armoured, preinstalled_modes_names) {
}

void BasicMovementRobot::move(const Direction &direction) {
    const std::pair<int, int> &current_position = this->get_position();
    if (direction == Direction::UP) {
        this->set_position(std::make_pair(current_position.first, current_position.second - 1));
    } else if (direction == Direction::DOWN) {
        this->set_position(std::make_pair(current_position.first, current_position.second + 1));
    } else if (direction == Direction::LEFT) {
        this->set_position(std::make_pair(current_position.first - 1, current_position.second));
    } else if (direction == Direction::RIGHT) {
        this->set_position(std::make_pair(current_position.first + 1, current_position.second));
    }
}
