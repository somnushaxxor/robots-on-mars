#pragma once

#include <string>

class Terrain;

const std::string TERRAIN_EXAMPLES_PATH("../terrain_examples/");
const size_t TERRAIN_MIN_WIDTH = 1000;
const size_t TERRAIN_MIN_HEIGHT = 1000;

class TerrainLoader final {
private:
public:
    TerrainLoader() = default;

    ~TerrainLoader() = default;

    Terrain load_from_file(std::string map_file_name) const;
};
