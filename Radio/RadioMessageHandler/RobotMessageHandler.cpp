#include "RobotMessageHandler.h"
#include "../../Command/Command.h"
#include "../../Command/CommandParser/RobotCommandParser.h"
#include "../../Exception/CommandParserException.h"
#include "../../Exception/RadioMessageHandlerException.h"
#include "../../Mode/AutoDefuseMode.h"
#include "../../Mode/AutoGrabMode.h"
#include "../../Mode/AutoScanMode.h"
#include "../../Mode/ManualMode.h"
#include "../../Robot/Robot.h"
#include "../RadioMessage/CommandRequestMessage.h"
#include "../RadioMessage/CommandResponseMessage.h"
#include "../RadioMessage/MapUpdateMessage.h"
#include "../RadioMessage/ModeUpdateMessage.h"
#include <iostream>

RobotMessageHandler::RobotMessageHandler(Robot *robot)
        : robot(robot) {
}

void RobotMessageHandler::handle_message(RadioMessage *message) {
    if (message->get_type() == RadioMessageType::COMMAND_RESPONSE) {
        auto *command_response_message = dynamic_cast<CommandResponseMessage *>(message);
        Mode *mode = robot->get_mode();
        RobotCommandParser *command_parser = mode->get_command_parser();
        if (command_parser) {
            Command *command = nullptr;
            try {
                command = command_parser->parse_command_string(command_response_message->get_command_string());
                mode->push_command_to_deque(command);
            } catch (CommandParserException &exception) {
                std::cerr << exception.what() << std::endl;
                delete command;
                command = nullptr;
            }
        } else {
            throw RadioMessageHandlerException("No CommandParser available");
        }

    } else if (message->get_type() == RadioMessageType::MAP_UPDATE) {
        auto *map_update_message = dynamic_cast<MapUpdateMessage *>(message);
        TerrainMap &map = robot->get_terrain_map();
        const std::map<std::pair<int, int>, TerrainCellType> &cells_on_update = map_update_message->get_cells_on_update();
        for (const auto & iterator : cells_on_update) {
            map.set_cell_type(iterator.first, iterator.second);
        }
        map.clear_last_set_cells();

    } else if (message->get_type() == RadioMessageType::MODE_UPDATE) {
        auto *mode_update_message = dynamic_cast<ModeUpdateMessage *>(message);
        std::string mode_name = mode_update_message->get_mode_name();
        std::string mode_argument = mode_update_message->get_mode_argument();
        if (robot->has_preinstalled_mode(mode_name)) {
            if (mode_name == "MANUAL") {
                Mode *mode = new ManualMode(robot);
                robot->set_mode(mode);
            } else if (mode_name == "AUTO_SCAN") {
                size_t iterations_number = std::stoull(mode_argument);
                if (iterations_number > 0) {
                    Mode *mode = new AutoScanMode(robot, iterations_number);
                    robot->set_mode(mode);
                } else {
                    throw RadioMessageHandlerException("Invalid iterations number for AutoScanMode");
                }
            } else if (mode_name == "AUTO_GRAB") {
                Mode *mode = new AutoGrabMode(robot);
                robot->set_mode(mode);
            } else if (mode_name == "AUTO_DEFUSE") {
                Mode *mode = new AutoDefuseMode(robot);
                robot->set_mode(mode);
            }
        } else {
            throw RadioMessageHandlerException("Desired mode is not preinstalled");
        }

    } else {
        throw RadioMessageHandlerException("Unknown or unavailable message type");
    }
}
