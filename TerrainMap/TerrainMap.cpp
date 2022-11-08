#include "TerrainMap.h"

TerrainMap::TerrainMap()
        : top_left_corner_position(0, 0), bottom_right_corner_position(0, 0), is_initialized(false) {
}

void TerrainMap::update_corners_positions(const std::pair<int, int> &cell_position) {
    if (!is_initialized) {
        top_left_corner_position.first = cell_position.first;
        top_left_corner_position.second = cell_position.second;
        bottom_right_corner_position.first = cell_position.first;
        bottom_right_corner_position.second = cell_position.second;
        is_initialized = true;
    } else {
        if (cell_position.first < top_left_corner_position.first) {
            top_left_corner_position.first = cell_position.first;
        }
        if (cell_position.first > bottom_right_corner_position.first) {
            bottom_right_corner_position.first = cell_position.first;
        }
        if (cell_position.second < top_left_corner_position.second) {
            top_left_corner_position.second = cell_position.second;
        }
        if (cell_position.second > bottom_right_corner_position.second) {
            bottom_right_corner_position.second = cell_position.second;
        }
    }
}

void TerrainMap::set_cell_type(const std::pair<int, int> &cell_position, const TerrainCellType &type) {
    cells[cell_position] = type;
    last_set_cells[cell_position] = type;
    this->update_corners_positions(cell_position);
}

bool TerrainMap::check_cell_existence(const std::pair<int, int> &cell_position) const {
    if (cells.find(cell_position) != cells.end()) {
        return true;
    } else {
        return false;
    }
}
