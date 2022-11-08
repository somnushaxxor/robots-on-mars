#include "Terrain.h"
#include "../Robot/Robot.h"
#include <random>
#include <ctime>

Terrain::Terrain(const size_t &width, const size_t &height, std::vector<TerrainCellType> &cells)
        : width(width), height(height), cells(cells), radiobeacon_position(0, 0) {
}

Terrain::~Terrain() {
    for (auto &iterator: robots) {
        Robot *robot = iterator.first;
        delete robot;
        robot = nullptr;
    }
}

void Terrain::add_robot(Robot *robot, const std::pair<int, int> &robot_relative_position) {
    robots[robot] = this->convert_relative_to_absolute_position(robot_relative_position);
}

void Terrain::move_robot(Robot *robot, const Direction &direction) {
    std::pair<size_t, size_t> &robot_real_position = robots.at(robot);
    if (cells[robot_real_position.second * width + robot_real_position.first] != TerrainCellType::ROCK) {
        if (direction == Direction::UP) {
            Robot *another_robot = nullptr;
            for (auto iterator = robots.begin(); iterator != robots.end(); iterator++) {
                Robot *current_robot = iterator->first;
                std::pair<size_t, size_t> current_robot_real_position = robots.at(current_robot);
                if (current_robot_real_position.second == robot_real_position.second - 1) {
                    if (current_robot_real_position.first == robot_real_position.first) {
                        another_robot = current_robot;
                        break;
                    }
                }
            }
            if (another_robot) {
                if (robot->get_weight() > another_robot->get_weight()) {
                    std::pair<size_t, size_t> &another_robot_real_position = robots.at(another_robot);
                    robot_real_position.second -= 1;
                    another_robot_real_position.second -= 1;
                    if (this->is_bomb_triggered(another_robot)) {
                        robots.erase(another_robot);
                        this->on_bomb_triggered(another_robot);
                    }
                }
            } else {
                robot_real_position.second -= 1;
            }

        } else if (direction == Direction::DOWN) {
            Robot *another_robot = nullptr;
            for (auto iterator = robots.begin(); iterator != robots.end(); iterator++) {
                Robot *current_robot = iterator->first;
                std::pair<size_t, size_t> current_robot_real_position = robots.at(current_robot);
                if (current_robot_real_position.second == robot_real_position.second + 1) {
                    if (current_robot_real_position.first == robot_real_position.first) {
                        another_robot = current_robot;
                        break;
                    }
                }
            }
            if (another_robot) {
                if (robot->get_weight() > another_robot->get_weight()) {
                    std::pair<size_t, size_t> &another_robot_real_position = robots.at(another_robot);
                    robot_real_position.second += 1;
                    another_robot_real_position.second += 1;
                    if (this->is_bomb_triggered(another_robot)) {
                        robots.erase(another_robot);
                        this->on_bomb_triggered(another_robot);
                    }
                }
            } else {
                robot_real_position.second += 1;
            }

        } else if (direction == Direction::LEFT) {
            Robot *another_robot = nullptr;
            for (auto iterator = robots.begin(); iterator != robots.end(); iterator++) {
                Robot *current_robot = iterator->first;
                std::pair<size_t, size_t> current_robot_real_position = robots.at(current_robot);
                if (current_robot_real_position.first == robot_real_position.first - 1) {
                    if (current_robot_real_position.second == robot_real_position.second) {
                        another_robot = current_robot;
                        break;
                    }
                }
            }
            if (another_robot) {
                if (robot->get_weight() > another_robot->get_weight()) {
                    std::pair<size_t, size_t> &another_robot_real_position = robots.at(another_robot);
                    robot_real_position.first -= 1;
                    another_robot_real_position.first -= 1;
                    if (this->is_bomb_triggered(another_robot)) {
                        robots.erase(another_robot);
                        this->on_bomb_triggered(another_robot);
                    }
                }
            } else {
                robot_real_position.first -= 1;
            }

        } else if (direction == Direction::RIGHT) {
            Robot *another_robot = nullptr;
            for (auto iterator = robots.begin(); iterator != robots.end(); iterator++) {
                Robot *current_robot = iterator->first;
                std::pair<size_t, size_t> current_robot_real_position = robots.at(current_robot);
                if (current_robot_real_position.first == robot_real_position.first + 1) {
                    if (current_robot_real_position.second == robot_real_position.second) {
                        another_robot = current_robot;
                        break;
                    }
                }
            }
            if (another_robot) {
                if (robot->get_weight() > another_robot->get_weight()) {
                    std::pair<size_t, size_t> &another_robot_real_position = robots.at(another_robot);
                    robot_real_position.first += 1;
                    another_robot_real_position.first += 1;
                    if (this->is_bomb_triggered(another_robot)) {
                        robots.erase(another_robot);
                        this->on_bomb_triggered(another_robot);
                    }
                }
            } else {
                robot_real_position.first += 1;
            }
        }
    }
}

void Terrain::on_apple_grabbed(Robot *robot) {
    std::pair<size_t, size_t> robot_real_position = robots.at(robot);
    if (cells[robot_real_position.second * width + robot_real_position.first] == TerrainCellType::APPLE) {
        cells[robot_real_position.second * width + robot_real_position.first] = TerrainCellType::EMPTY;
    }
}

bool Terrain::is_bomb_triggered(Robot *robot) {
    std::pair<size_t, size_t> robot_real_position = robots.at(robot);
    if (cells[robot_real_position.second * width + robot_real_position.first] == TerrainCellType::BOMB) {
        return true;
    } else {
        return false;
    }
}

void Terrain::on_bomb_triggered(Robot *robot) {
    std::pair<size_t, size_t> robot_real_position = robots.at(robot);
    cells[robot_real_position.second * width + robot_real_position.first] = TerrainCellType::EMPTY;
}

bool Terrain::is_robot_exploded(Robot *robot) {
    if (!robot->get_armoured_state()) {
        delete robot;
        robot = nullptr;
        return true;
    } else {
        return false;
    }
}

std::pair<int, int>
Terrain::convert_absolute_to_relative_position(const std::pair<size_t, size_t> &absolute_position) const {
    std::pair<int, int> relative_position;
    relative_position.first = absolute_position.first - radiobeacon_position.first;
    relative_position.second = absolute_position.second - radiobeacon_position.second;
    return relative_position;
}

std::pair<size_t, size_t>
Terrain::convert_relative_to_absolute_position(const std::pair<int, int> &relative_position) const {
    std::pair<size_t, size_t> absolute_position;
    absolute_position.first = relative_position.first + radiobeacon_position.first;
    absolute_position.second = relative_position.second + radiobeacon_position.second;
    return absolute_position;
}

std::pair<size_t, size_t> Terrain::get_random_cell_position() const {
    srand(time(nullptr));
    std::pair<size_t, size_t> random_position(rand() % width, rand() % height);
    return random_position;
}

std::pair<int, int> Terrain::get_new_robot_position() const {
    bool is_new_robot_position_found = false;
    std::pair<size_t, size_t> new_robot_position;
    while (!is_new_robot_position_found) {
        is_new_robot_position_found = true;
        new_robot_position = this->get_random_cell_position();
        if (cells[new_robot_position.second * width + new_robot_position.first] == TerrainCellType::EMPTY) {
            for (const auto &iterator: robots) {
                Robot *robot = iterator.first;
                if (this->convert_relative_to_absolute_position(robot->get_position()) == new_robot_position) {
                    is_new_robot_position_found = false;
                    break;
                }
            }
        } else {
            is_new_robot_position_found = false;
        }
    }
    return this->convert_absolute_to_relative_position(new_robot_position);
}
