#include "TerrainLoader.h"
#include "../../Exception/TerrainLoaderException.h"
#include "../Terrain.h"
#include <fstream>
#include <sstream>

Terrain TerrainLoader::load_from_file(std::string map_file_name) const {
    std::ifstream map_file(TERRAIN_EXAMPLES_PATH + map_file_name);
    if (map_file.fail()) {
        throw TerrainLoaderException("Failed while opening terrain file");
    }

    std::string current_line;
    if (!getline(map_file, current_line)) {
        throw TerrainLoaderException("Terrain file is empty");
    }

    std::stringstream current_line_stringstream;
    current_line_stringstream << current_line;
    size_t width;
    current_line_stringstream >> width;
    size_t height;
    current_line_stringstream >> height;
    if (current_line_stringstream.good()) {
        throw TerrainLoaderException("Invalid terrain file");
    }

    std::vector<TerrainCellType> cells;
    cells.resize(width * height);
    size_t y = 0;
    while (getline(map_file, current_line)) {
        size_t x = 0;
        while (x < current_line.size()) {
            if (current_line[x] == '.') {
                cells[y * width + x] = TerrainCellType::EMPTY;
            } else if (current_line[x] == '#') {
                cells[y * width + x] = TerrainCellType::ROCK;
            } else if (current_line[x] == 'X') {
                cells[y * width + x] = TerrainCellType::BOMB;
            } else if (current_line[x] == '$') {
                cells[y * width + x] = TerrainCellType::APPLE;
            } else {
                throw TerrainLoaderException("Invalid terrain file");
            }
            ++x;
        }
        if (x != width) {
            throw TerrainLoaderException("Invalid terrain file");
        }
        ++y;
    }
    if (y != height) {
        throw TerrainLoaderException("Invalid terrain file");
    }

    return Terrain(width, height, cells);
}
