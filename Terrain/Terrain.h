#pragma once

#include "../Robot/Direction.h"
#include "TerrainCellType.h"
#include <map>
#include <vector>
#include <cstddef>

class Robot;

class Terrain final {
private:
    size_t width;
    size_t height;
    std::vector<TerrainCellType> cells;
    std::map<Robot *, std::pair<size_t, size_t>> robots;
    std::pair<size_t, size_t> radiobeacon_position;

    std::pair<size_t, size_t> get_random_cell_position() const;

    std::pair<int, int> convert_absolute_to_relative_position(const std::pair<size_t, size_t> &absolute_position) const;

    std::pair<size_t, size_t> convert_relative_to_absolute_position(const std::pair<int, int> &relative_position) const;

public:
    Terrain(const size_t &width, const size_t &height, std::vector<TerrainCellType> &cells);

    ~Terrain();

    void place_radiobeacon();

    void add_robot(Robot *robot, const std::pair<int, int> &robot_relative_position);

    void move_robot(Robot *robot, const Direction &direction);

    void on_apple_grabbed(Robot *robot);

    bool is_bomb_triggered(Robot *robot);

    void on_bomb_triggered(Robot *robot);

    bool is_robot_exploded(Robot *robot);

    std::map<Robot *, std::pair<size_t, size_t>> &get_robots();

    std::pair<int, int> get_robot_real_position(Robot *robot) const;

    TerrainCellType get_cell_type(const std::pair<int, int> &cell_relative_position) const;

    std::pair<int, int> get_new_robot_position() const;
};

inline TerrainCellType Terrain::get_cell_type(const std::pair<int, int> &cell_relative_position) const {
    std::pair<size_t, size_t> cell_absolute_position = this->convert_relative_to_absolute_position(
            cell_relative_position);
    return cells[cell_absolute_position.second * width + cell_absolute_position.first];
}

inline std::map<Robot *, std::pair<size_t, size_t>> &Terrain::get_robots() {
    return robots;
}

inline void Terrain::place_radiobeacon() {
    radiobeacon_position = this->get_random_cell_position();
}

inline std::pair<int, int> Terrain::get_robot_real_position(Robot *robot) const {
    return this->convert_absolute_to_relative_position(robots.at(robot));
}
