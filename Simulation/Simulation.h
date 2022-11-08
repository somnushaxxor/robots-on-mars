#pragma once

#include "../Command/CommandParser/SimulationCommandParser.h"
#include "../Dispatcher/Dispatcher.h"
#include "../InputHandler/InputHandler.h"
#include "../Terrain/Terrain.h"
#include "../View/View.h"

class Robot;

class Simulation final {
private:
    Dispatcher &dispatcher;
    Terrain &terrain;
    View &view;
    InputHandler &input_handler;
    SimulationCommandParser command_parser;
    Robot *focused_robot;
    bool is_running;
    bool is_command_awaited;

public:
    Simulation(Dispatcher &dispatcher, Terrain &terrain, View &view, InputHandler &input_handler);

    ~Simulation() = default;

    Dispatcher &get_dispatcher();

    Terrain &get_terrain();

    void set_focused_robot(Robot *new_focused_robot);

    void stop_command_awaiting();

    void run();

    void end();
};

inline Dispatcher &Simulation::get_dispatcher() {
    return dispatcher;
}

inline Terrain &Simulation::get_terrain() {
    return terrain;
}

inline void Simulation::set_focused_robot(Robot *new_focused_robot) {
    this->focused_robot = new_focused_robot;
}

inline void Simulation::stop_command_awaiting() {
    is_command_awaited = false;
}

inline void Simulation::end() {
    is_running = false;
}
