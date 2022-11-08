#pragma once

#include "../Terrain/TerrainCellType.h"
#include <map>

class TerrainMap final {
private:
    std::pair<int, int> top_left_corner_position;
    std::pair<int, int> bottom_right_corner_position;
    std::map<std::pair<int, int>, TerrainCellType> cells;
    std::map<std::pair<int, int>, TerrainCellType> last_set_cells;
    bool is_initialized;

    void update_corners_positions(const std::pair<int, int> &cell_position);

public:
    TerrainMap();

    ~TerrainMap() = default;

    std::pair<int, int> get_top_left_corner_position() const;

    std::pair<int, int> get_bottom_right_corner_position() const;

    TerrainCellType get_cell_type(const std::pair<int, int> &cell_position) const;

    std::map<std::pair<int, int>, TerrainCellType> &get_cells();

    std::map<std::pair<int, int>, TerrainCellType> get_cells_copy() const;

    std::map<std::pair<int, int>, TerrainCellType> get_last_set_cells_copy() const;

    void clear_last_set_cells();

    void set_cell_type(const std::pair<int, int> &cell_position, const TerrainCellType &type);

    bool check_cell_existence(const std::pair<int, int> &cell_position) const;

    bool check_last_set_cells_availability() const;
};

inline std::pair<int, int> TerrainMap::get_top_left_corner_position() const {
    return top_left_corner_position;
}

inline std::pair<int, int> TerrainMap::get_bottom_right_corner_position() const {
    return bottom_right_corner_position;
}

inline TerrainCellType TerrainMap::get_cell_type(const std::pair<int, int> &cell_position) const {
    return cells.at(cell_position);
}

inline bool TerrainMap::check_last_set_cells_availability() const {
    if (last_set_cells.empty()) {
        return false;
    } else {
        return true;
    }
}

inline std::map<std::pair<int, int>, TerrainCellType> &TerrainMap::get_cells() {
    return cells;
}

inline std::map<std::pair<int, int>, TerrainCellType> TerrainMap::get_cells_copy() const {
    return cells;
}

inline std::map<std::pair<int, int>, TerrainCellType> TerrainMap::get_last_set_cells_copy() const {
    return last_set_cells;
}

inline void TerrainMap::clear_last_set_cells() {
    last_set_cells.clear();
}
