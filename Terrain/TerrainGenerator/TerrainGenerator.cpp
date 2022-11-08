#include "TerrainGenerator.h"
#include <fstream>
#include <random>
#include <ctime>

void TerrainGenerator::generate() const {
    std::ofstream generated_file(TERRAIN_EXAMPLES_PATH + "generated.ter");
    srand(time(nullptr));
    const size_t WIDTH = 1000 + rand() % 9000;
    const size_t HEIGHT = 1000 + rand() % 9000;
    generated_file << WIDTH << " " << HEIGHT << std::endl;
    for (size_t i = 0; i < WIDTH; i++) {
        generated_file << "#";
    }
    generated_file << std::endl;
    for (size_t i = 0; i < WIDTH; i++) {
        generated_file << "#";
    }
    generated_file << std::endl;
    std::random_device random_device;
    std::mt19937 gen(random_device());
    std::uniform_int_distribution<> distribution(0, 12);
    for (size_t i = 0; i < HEIGHT - 4; i++) {
        generated_file << "##";
        for (size_t j = 0; j < WIDTH - 4; j++) {
            int random_int = distribution(gen);
            if (random_int == 10) {
                generated_file << "#";
            } else if (random_int == 11) {
                generated_file << "X";
            } else if (random_int == 12) {
                generated_file << "$";
            } else {
                generated_file << ".";
            }
        }
        generated_file << "##" << std::endl;
    }
    for (size_t i = 0; i < WIDTH; i++) {
        generated_file << "#";
    }
    generated_file << std::endl;
    for (size_t i = 0; i < WIDTH; i++) {
        generated_file << "#";
    }
}
