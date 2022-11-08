#include "ManualMode.h"
#include "../Command/Command.h"
#include "../Command/CommandParser/ManualModeCommandParser.h"
#include "../Exception/CommandException.h"
#include "../Radio/RadioMessage/ApplesGrabbedMessage.h"
#include "../Radio/RadioMessage/CommandRequestMessage.h"
#include "../Radio/RadioMessage/MapUpdateMessage.h"
#include "../Radio/RadioMessage/StepDoneMessage.h"
#include "../Robot/BasicMovementRobot/Collector.h"
#include <iostream>

ManualMode::ManualMode(Robot *robot)
        : Mode(robot, new ManualModeCommandParser(robot)) {
}

void ManualMode::execute_next_command() {
    Robot *robot = this->get_robot();
    Command *next_command = this->pop_next_command();
    if (!next_command) {
        RadioMessage *message = new CommandRequestMessage();
        robot->send_message_to_dispatcher(message);
    } else {
        try {
            next_command->execute();
        } catch (CommandException &exception) {
            std::cerr << exception.what() << std::endl;
        }
        delete next_command;
        next_command = nullptr;
        auto *collector = dynamic_cast<Collector *>(robot);
        TerrainMap &map = robot->get_terrain_map();
        if (map.check_last_set_cells_availability()) {
            RadioMessage *message = new MapUpdateMessage(map.get_last_set_cells_copy());
            robot->send_message_to_dispatcher(message);
            map.clear_last_set_cells();
        }
        if (collector->get_last_apples_grabbed()) {
            RadioMessage *message = new ApplesGrabbedMessage(collector->get_last_apples_grabbed());
            robot->send_message_to_dispatcher(message);
            collector->clear_last_apples_grabbed();
        }
        RadioMessage *message = new StepDoneMessage();
        robot->send_message_to_dispatcher(message);
    }
}
