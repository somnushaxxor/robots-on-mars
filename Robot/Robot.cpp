#include "Robot.h"
#include "../../Command/Command.h"
#include "../Exception/RadioMessageHandlerException.h"
#include "../Radio/RadioMessage/MapUpdateMessage.h"
#include "../Radio/RadioMessage/NothingToDoMessage.h"
#include <iostream>
#include <utility>

Robot::Robot(Terrain &terrain, RadioChannel *radio_channel, const size_t &id, const RobotWeight &weight,
             const bool &is_armoured, std::list<std::string> preinstalled_modes_names)
        : terrain(terrain), id(id), position(terrain.get_new_robot_position()), weight(weight),
          is_armoured(is_armoured), is_just_landed(true), message_handler(RobotMessageHandler(this)), mode(nullptr),
          preinstalled_modes_names(std::move(preinstalled_modes_names)) {
    terrain.add_robot(this, position);
    radio_module.set_radio_channel(radio_channel);
    map.set_cell_type(position, TerrainCellType::EMPTY);
}

Robot::~Robot() {
    delete mode;
    mode = nullptr;
}

bool Robot::has_preinstalled_mode(const std::string &mode_name) const {
    bool is_found = false;
    for (const auto &preinstalled_modes_name: preinstalled_modes_names) {
        if (preinstalled_modes_name == mode_name) {
            is_found = true;
            break;
        }
    }
    return is_found;
}

void Robot::do_step() {
    std::vector<RadioMessage *> incoming_messages = radio_module.receive_messages();
    if (!incoming_messages.empty()) {
        for (auto incoming_message: incoming_messages) {
            try {
                message_handler.handle_message(incoming_message);
            } catch (RadioMessageHandlerException &exception) {
                std::cerr << exception.what() << std::endl;
            }
            delete incoming_message;
            incoming_message = nullptr;
        }
    }
    if (is_just_landed) {
        RadioMessage *message = new MapUpdateMessage(map.get_last_set_cells_copy());
        this->send_message_to_dispatcher(message);
        map.clear_last_set_cells();
        is_just_landed = false;
    } else {
        if (mode) {
            mode->execute_next_command();
            if (mode->get_stopped_state()) {
                delete mode;
                mode = nullptr;
            }
        } else {
            RadioMessage *message = new NothingToDoMessage();
            this->send_message_to_dispatcher(message);
        }
    }
}
