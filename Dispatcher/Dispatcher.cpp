#include "Dispatcher.h"
#include "../Command/Command.h"
#include "../Exception/DispatcherException.h"
#include "../Exception/RadioMessageHandlerException.h"
#include "../Radio/RadioChannel.h"
#include "../Radio/RadioMessage/MapUpdateMessage.h"
#include "../Robot/BasicMovementRobot/Collector.h"
#include "../Robot/BasicMovementRobot/Sapper.h"
#include <iostream>

Dispatcher::Dispatcher(Terrain &terrain, InputHandler &input_handler)
        : terrain(terrain), input_handler(input_handler), message_handler(DispatcherMessageHandler(this)),
          is_exploration_suspended(false), last_robot_id(0), total_apples_grabbed(0) {
    this->send_radiobeacon();
    this->deploy_robot(RobotType::COLLECTOR);
}

Dispatcher::~Dispatcher() {
    for (auto & robots_radio_channel : robots_radio_channels) {
        RadioChannel *radio_channel = robots_radio_channel.second;
        delete radio_channel;
        radio_channel = nullptr;
    }
}

void Dispatcher::send_radiobeacon() {
    terrain.place_radiobeacon();
}

void Dispatcher::send_message_to_current_robot(RadioMessage *message) {
    radio_module.send_message(message);
}

void Dispatcher::send_message_to_robot_by_id(const size_t &robot_id, RadioMessage *message) {
    if (robots_radio_channels.find(robot_id) != robots_radio_channels.end()) {
        RadioChannel *radio_channel = robots_radio_channels.at(robot_id);
        radio_module.set_radio_channel(radio_channel);
        radio_module.send_message(message);
    } else {
        throw DispatcherException("Invalid Robot ID");
    }
}

void Dispatcher::deploy_robot(const RobotType &type) {
    if (type == RobotType::COLLECTOR) {
        auto *radio_channel = new RadioChannel();
        auto *collector = new Collector(terrain, radio_channel, last_robot_id + 1);
        robots_radio_channels[last_robot_id + 1] = radio_channel;
        last_robot_id++;
        TerrainMap &collector_map = collector->get_terrain_map();
        std::map<std::pair<int, int>, TerrainCellType> &collector_map_cells = collector_map.get_cells();
        collector_map_cells = map.get_cells_copy();

    } else if (type == RobotType::SAPPER) {
        auto *radio_channel = new RadioChannel();
        auto *sapper = new Sapper(terrain, radio_channel, last_robot_id + 1);
        robots_radio_channels[last_robot_id + 1] = radio_channel;
        last_robot_id++;
        TerrainMap &sapper_map = sapper->get_terrain_map();
        std::map<std::pair<int, int>, TerrainCellType> &sapper_map_cells = sapper_map.get_cells();
        sapper_map_cells = map.get_cells_copy();

    } else {
        throw DispatcherException("Invalid robot type");
    }
}

void Dispatcher::do_step() {
    is_exploration_suspended = false;
    message_handler.reset_message_nothing_to_do_counter();

    for (auto iterator = robots_radio_channels.begin(); iterator != robots_radio_channels.end(); iterator) {
        RadioChannel *current_radio_channel = iterator->second;
        radio_module.set_radio_channel(current_radio_channel);
        std::vector<RadioMessage *> incoming_messages = radio_module.receive_messages();
        if (!incoming_messages.empty()) {
            for (auto incoming_message : incoming_messages) {
                try {
                    message_handler.handle_message(incoming_message);
                } catch (RadioMessageHandlerException &exception) {
                    std::cerr << exception.what() << std::endl;
                }
                delete incoming_message;
                incoming_message = nullptr;
            }
            ++iterator;
        } else {
            iterator = robots_radio_channels.erase(iterator);
            delete current_radio_channel;
            current_radio_channel = nullptr;
        }
    }

    if (map.check_last_set_cells_availability()) {
        for (auto & robots_radio_channel : robots_radio_channels) {
            RadioChannel *current_radio_channel = robots_radio_channel.second;
            radio_module.set_radio_channel(current_radio_channel);
            RadioMessage *map_update_message = new MapUpdateMessage(map.get_last_set_cells_copy());
            radio_module.send_message(map_update_message);
        }
        map.clear_last_set_cells();
    }

    if (robots_radio_channels.size() == message_handler.get_message_nothing_to_do_counter()) {
        is_exploration_suspended = true;
    }
}
