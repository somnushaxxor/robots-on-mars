#include "AutoDefuseMode.h"
#include "../Command/RobotCommand/MoveCommand.h"
#include "../Exception/CommandException.h"
#include "../Radio/RadioMessage/MapUpdateMessage.h"
#include "../Radio/RadioMessage/StepDoneMessage.h"
#include <iostream>

AutoDefuseMode::AutoDefuseMode(Robot *robot)
        : AutoMode(robot) {
}

bool AutoDefuseMode::find_path(std::deque<Command *> &new_commands_deque) {
    std::deque<std::pair<int, int>> cells_deque;
    std::map<std::pair<int, int>, bool> is_visited;
    std::map<std::pair<int, int>, Direction> cells_directions;

    Robot *robot = this->get_robot();
    TerrainMap &map = robot->get_terrain_map();
    std::pair<int, int> robot_position = robot->get_position();
    is_visited[robot_position] = true;
    cells_deque.push_back(robot_position);

    std::vector<Direction> directions = {Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT};

    bool is_bomb_found = false;
    std::pair<int, int> bomb_position;
    while (!cells_deque.empty()) {
        std::pair<int, int> current_cell = cells_deque.front();
        cells_deque.pop_front();
        for (auto current_direction: directions) {
            std::pair<int, int> next_cell = current_cell;
            if (current_direction == Direction::UP) {
                next_cell.second--;
            } else if (current_direction == Direction::DOWN) {
                next_cell.second++;
            } else if (current_direction == Direction::LEFT) {
                next_cell.first--;
            } else if (current_direction == Direction::RIGHT) {
                next_cell.first++;
            }
            if (map.check_cell_existence(next_cell)) {
                if (is_visited.find(next_cell) == is_visited.end()) {
                    if (map.get_cell_type(next_cell) != TerrainCellType::ROCK) {
                        is_visited[next_cell] = true;
                        cells_deque.push_back(next_cell);
                        cells_directions[next_cell] = current_direction;
                        if (map.get_cell_type(next_cell) == TerrainCellType::BOMB) {
                            is_bomb_found = true;
                            bomb_position = next_cell;
                            break;
                        }
                    }
                }
            }
        }
        if (is_bomb_found) {
            break;
        }
    }
    if (is_bomb_found) {
        std::pair<int, int> current_cell = bomb_position;
        while (current_cell != robot_position) {
            Command *command = nullptr;
            if (cells_directions[current_cell] == Direction::UP) {
                command = new MoveCommand(robot, {"U"});
                current_cell.second++;
            } else if (cells_directions[current_cell] == Direction::DOWN) {
                command = new MoveCommand(robot, {"D"});
                current_cell.second--;
            } else if (cells_directions[current_cell] == Direction::LEFT) {
                command = new MoveCommand(robot, {"L"});
                current_cell.first++;
            } else if (cells_directions[current_cell] == Direction::RIGHT) {
                command = new MoveCommand(robot, {"R"});
                current_cell.first--;
            }
            new_commands_deque.push_front(command);
        }
        return true;
    } else {
        return false;
    }
}

void AutoDefuseMode::execute_next_command() {
    Robot *robot = this->get_robot();
    Command *next_command = this->pop_next_command();
    if (!next_command) {
        if (!this->set_new_aim()) {
            this->stop();
        }
        RadioMessage *message = new StepDoneMessage();
        robot->send_message_to_dispatcher(message);
    } else {
        try {
            next_command->execute();
        } catch (CommandException &exception) {
            std::cerr << exception.what() << std::endl;
        }
        delete next_command;
        next_command = nullptr;
        TerrainMap &map = robot->get_terrain_map();
        if (map.get_cell_type(robot->get_position()) == TerrainCellType::BOMB) {
            map.set_cell_type(robot->get_position(), TerrainCellType::EMPTY);
        }
        if (map.check_last_set_cells_availability()) {
            RadioMessage *map_update_message = new MapUpdateMessage(map.get_last_set_cells_copy());
            robot->send_message_to_dispatcher(map_update_message);
            map.clear_last_set_cells();
        }
        RadioMessage *message = new StepDoneMessage();
        robot->send_message_to_dispatcher(message);
    }
}
