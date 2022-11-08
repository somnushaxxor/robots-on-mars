#pragma once

#include <string>

class Terrain;

const std::string TERRAIN_EXAMPLES_PATH("../terrain_examples/");

class TerrainGenerator final {
private:
public:
    TerrainGenerator() = default;

    ~TerrainGenerator() = default;

    void generate() const;
};
