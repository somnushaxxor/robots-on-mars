#pragma once

#include "../InputHandler/InputHandler.h"
#include "../Radio/RadioMessageHandler/DispatcherMessageHandler.h"
#include "../Radio/RadioModule.h"
#include "../Robot/RobotType.h"
#include "../Terrain/Terrain.h"
#include "../TerrainMap/TerrainMap.h"

#include <map>

class RadioChannel;

class RadioMessage;

class Dispatcher final {
private:
    Terrain &terrain;
    TerrainMap map;
    std::map<size_t, RadioChannel *> robots_radio_channels;
    InputHandler &input_handler;
    RadioModule radio_module;
    DispatcherMessageHandler message_handler;
    bool is_exploration_suspended;
    size_t last_robot_id;
    size_t total_apples_grabbed;

    void send_radiobeacon();

public:
    Dispatcher(Terrain &terrain, InputHandler &input_handler);

    ~Dispatcher();

    TerrainMap &get_terrain_map();

    InputHandler &get_input_handler();

    void send_message_to_current_robot(RadioMessage *message);

    void send_message_to_robot_by_id(const size_t &robot_id, RadioMessage *message);

    void add_apples_grabbed(const size_t &apples_grabbed);

    size_t get_total_apples_grabbed() const;

    void deploy_robot(const RobotType &type);

    void do_step();

    bool get_exploration_suspended_state() const;
};

inline TerrainMap &Dispatcher::get_terrain_map() {
    return map;
}

inline InputHandler &Dispatcher::get_input_handler() {
    return input_handler;
}

inline bool Dispatcher::get_exploration_suspended_state() const {
    return is_exploration_suspended;
}

inline void Dispatcher::add_apples_grabbed(const size_t &apples_grabbed) {
    total_apples_grabbed += apples_grabbed;
}

inline size_t Dispatcher::get_total_apples_grabbed() const {
    return total_apples_grabbed;
}
