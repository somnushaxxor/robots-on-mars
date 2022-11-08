#pragma once

#include "../Mode/Mode.h"
#include "../Radio/RadioMessageHandler/RobotMessageHandler.h"
#include "../Radio/RadioModule.h"
#include "../Terrain/Terrain.h"
#include "../TerrainMap/TerrainMap.h"
#include "Direction.h"
#include "RobotWeight.h"
#include <list>
#include <string>

class RadioChannel;

class Robot {
private:
    const std::size_t id;
    std::pair<int, int> position;
    RobotWeight weight;
    bool is_armoured;
    bool is_just_landed;
    Terrain &terrain;
    TerrainMap map;
    Mode *mode;
    const std::list<std::string> preinstalled_modes_names;
    RadioModule radio_module;
    RobotMessageHandler message_handler;

protected:
    void set_position(const std::pair<int, int> &position);

public:
    Robot(Terrain &terrain, RadioChannel *radio_channel, const size_t &id, const RobotWeight &weight,
          const bool &is_armoured, std::list<std::string> preinstalled_modes_names);

    virtual ~Robot();

    Terrain &get_terrain();

    const Terrain &get_terrain() const;

    std::pair<int, int> get_position() const;

    size_t get_id() const;

    TerrainMap &get_terrain_map();

    const TerrainMap &get_terrain_map() const;

    Mode *get_mode();

    void set_mode(Mode *mode);

    RobotWeight get_weight() const;

    bool get_armoured_state() const;

    bool get_just_landed_state() const;

    bool has_preinstalled_mode(const std::string &mode_name) const;

    void send_message_to_dispatcher(RadioMessage *message);

    void do_step();

    virtual void move(const Direction &direction) = 0;
};

inline Terrain &Robot::get_terrain() {
    return terrain;
}

inline const Terrain &Robot::get_terrain() const {
    return terrain;
}

inline TerrainMap &Robot::get_terrain_map() {
    return map;
}

inline const TerrainMap &Robot::get_terrain_map() const {
    return map;
}

inline std::pair<int, int> Robot::get_position() const {
    return position;
}

inline size_t Robot::get_id() const {
    return id;
}

inline void Robot::set_position(const std::pair<int, int> &position) {
    this->position = position;
}

inline Mode *Robot::get_mode() {
    return mode;
}

inline void Robot::set_mode(Mode *mode) {
    delete this->mode;
    this->mode = mode;
}

inline RobotWeight Robot::get_weight() const {
    return weight;
}

inline bool Robot::get_armoured_state() const {
    return is_armoured;
}

inline bool Robot::get_just_landed_state() const {
    return is_just_landed;
}

inline void Robot::send_message_to_dispatcher(RadioMessage *message) {
    radio_module.send_message(message);
}
