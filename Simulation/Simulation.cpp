#include "Simulation.h"
#include "../Command/Command.h"
#include "../Exception/CommandException.h"
#include "../Exception/CommandParserException.h"
#include "../Robot/Robot.h"
#include <iostream>

Simulation::Simulation(Dispatcher &dispatcher, Terrain &terrain, View &view, InputHandler &input_handler)
        : dispatcher(dispatcher), terrain(terrain), view(view), input_handler(input_handler),
          command_parser(SimulationCommandParser(this)), focused_robot(nullptr), is_running(false),
          is_command_awaited(false) {
}

void Simulation::run() {
    is_running = true;
    std::map<Robot *, std::pair<size_t, size_t>> &robots = terrain.get_robots();
    Robot *first_robot = robots.begin()->first;
    focused_robot = first_robot;
    TerrainMap &map = dispatcher.get_terrain_map();

    while (is_running) {
        for (auto iterator = robots.begin(); iterator != robots.end(); iterator) {
            Robot *robot = iterator->first;
            robot->do_step();
            if (terrain.is_bomb_triggered(robot)) {
                terrain.on_bomb_triggered(robot);
                if (terrain.is_robot_exploded(robot)) {
                    iterator = robots.erase(iterator);
                } else {
                    ++iterator;
                }
            } else {
                ++iterator;
            }
        }
        dispatcher.do_step();
        if (focused_robot) {
            view.set_camera_position(focused_robot->get_position());
        } else {
            if (!robots.empty()) {
                focused_robot = robots.begin()->first;
                view.set_camera_position(focused_robot->get_position());
            }
        }
        view.draw_frame(map, robots, dispatcher.get_total_apples_grabbed());
        if (dispatcher.get_exploration_suspended_state()) {
            is_command_awaited = true;
            std::cout << "Waiting for simulation command" << std::endl;
            Command *command = nullptr;
            while (is_command_awaited) {
                std::string simulation_command_string = input_handler.get_input();
                std::cout << simulation_command_string << std::endl;
                try {
                    command = command_parser.parse_command_string(simulation_command_string);
                    command->execute();
                } catch (CommandParserException &exception) {
                    std::cerr << exception.what() << std::endl;
                } catch (CommandException &exception) {
                    std::cerr << exception.what() << std::endl;
                }
                delete command;
                command = nullptr;
            }
        }
    }

    std::cout << "Simulation ended!" << std::endl;
}
