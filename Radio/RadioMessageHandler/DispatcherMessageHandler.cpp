#include "DispatcherMessageHandler.h"
#include "../../Dispatcher/Dispatcher.h"
#include "../../Exception/RadioMessageHandlerException.h"
#include "../RadioMessage/ApplesGrabbedMessage.h"
#include "../RadioMessage/CommandResponseMessage.h"
#include "../RadioMessage/MapUpdateMessage.h"

DispatcherMessageHandler::DispatcherMessageHandler(Dispatcher *dispatcher)
        : dispatcher(dispatcher), message_nothing_to_do_counter(0) {
}

void DispatcherMessageHandler::handle_message(RadioMessage *message) {
    if (message->get_type() == RadioMessageType::NOTHING_TO_DO) {
        message_nothing_to_do_counter++;

    } else if (message->get_type() == RadioMessageType::COMMAND_REQUEST) {
        InputHandler &input_handler = dispatcher->get_input_handler();
        std::string command_string = input_handler.get_input();
        RadioMessage *message = new CommandResponseMessage(command_string);
        dispatcher->send_message_to_current_robot(message);

    } else if (message->get_type() == RadioMessageType::STEP_DONE) {
        // :)

    } else if (message->get_type() == RadioMessageType::MAP_UPDATE) {
        auto *map_update_message = dynamic_cast<MapUpdateMessage *>(message);
        TerrainMap &map = dispatcher->get_terrain_map();
        const std::map<std::pair<int, int>, TerrainCellType> &cells_on_update = map_update_message->get_cells_on_update();
        for (const auto &iterator: cells_on_update) {
            map.set_cell_type(iterator.first, iterator.second);
        }

    } else if (message->get_type() == RadioMessageType::APPLES_GRABBED) {
        auto *apples_grabbed_message = dynamic_cast<ApplesGrabbedMessage *>(message);
        dispatcher->add_apples_grabbed(apples_grabbed_message->get_apples_grabbed());

    } else {
        throw RadioMessageHandlerException("Unknown or unavailable message type");
    }
}
