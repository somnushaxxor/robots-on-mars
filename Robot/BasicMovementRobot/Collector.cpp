#include <cstddef>
#include "Collector.h"

Collector::Collector(Terrain &terrain, RadioChannel *radio_channel, const size_t &id)
        : BasicMovementRobot(terrain, radio_channel, id, RobotWeight::LIGHT, false,
                             {"MANUAL", "AUTO_SCAN", "AUTO_GRAB"}), apples_grabbed(0), last_apples_grabbed(0) {
    this->scan();
}

void Collector::scan() {
    const Terrain &terrain = this->get_terrain();
    TerrainMap &map = this->get_terrain_map();
    const std::pair<int, int> real_current_position = terrain.get_robot_real_position(this);
    const std::pair<int, int> real_upper_cell_position = std::make_pair(real_current_position.first,
                                                                        real_current_position.second - 1);
    const std::pair<int, int> real_bottom_cell_position = std::make_pair(real_current_position.first,
                                                                         real_current_position.second + 1);
    const std::pair<int, int> real_left_cell_position = std::make_pair(real_current_position.first - 1,
                                                                       real_current_position.second);
    const std::pair<int, int> real_right_cell_position = std::make_pair(real_current_position.first + 1,
                                                                        real_current_position.second);
    const std::pair<int, int> relative_current_position = this->get_position();
    const std::pair<int, int> relative_upper_cell_position = std::make_pair(relative_current_position.first,
                                                                            relative_current_position.second - 1);
    const std::pair<int, int> relative_bottom_cell_position = std::make_pair(relative_current_position.first,
                                                                             relative_current_position.second + 1);
    const std::pair<int, int> relative_left_cell_position = std::make_pair(relative_current_position.first - 1,
                                                                           relative_current_position.second);
    const std::pair<int, int> relative_right_cell_position = std::make_pair(relative_current_position.first + 1,
                                                                            relative_current_position.second);
    map.set_cell_type(relative_upper_cell_position, terrain.get_cell_type(real_upper_cell_position));
    map.set_cell_type(relative_bottom_cell_position, terrain.get_cell_type(real_bottom_cell_position));
    map.set_cell_type(relative_left_cell_position, terrain.get_cell_type(real_left_cell_position));
    map.set_cell_type(relative_right_cell_position, terrain.get_cell_type(real_right_cell_position));
}

void Collector::grab() {
    Terrain &terrain = this->get_terrain();
    TerrainMap &map = this->get_terrain_map();
    const std::pair<int, int> relative_current_position = this->get_position();
    if (map.get_cell_type(relative_current_position) == TerrainCellType::APPLE) {
        map.set_cell_type(relative_current_position, TerrainCellType::EMPTY);
        apples_grabbed++;
        last_apples_grabbed++;
    }
    terrain.on_apple_grabbed(this);
}
