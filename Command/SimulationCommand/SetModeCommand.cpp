#include "SetModeCommand.h"
#include "../../Exception/CommandException.h"
#include "../../Radio/RadioMessage/ModeUpdateMessage.h"
#include "../../Robot/Robot.h"

SetModeCommand::SetModeCommand(Simulation *simulation, const std::vector<std::string> &arguments)
        : SimulationCommand(simulation, arguments) {
}

void SetModeCommand::execute() {
    const std::vector<std::string> &arguments = this->get_arguments();
    if (arguments.size() < 2 || arguments.size() > 3) {
        throw CommandException("Bad number of arguments");
    } else {
        Simulation *simulation = this->get_simulation();
        Terrain &terrain = simulation->get_terrain();
        size_t robot_id = std::stoull(arguments[0]);
        std::map<Robot *, std::pair<size_t, size_t>> &robots = terrain.get_robots();
        bool robot_id_exists = false;
        for (auto & iterator : robots) {
            Robot *robot = iterator.first;
            if (robot->get_id() == robot_id) {
                robot_id_exists = true;
                break;
            }
        }
        if (robot_id_exists) {
            std::string mode_name = arguments[1];
            std::string mode_argument;
            if (arguments.size() == 3) {
                mode_argument = arguments[2];
            }
            Dispatcher &dispatcher = simulation->get_dispatcher();
            RadioMessage *message = new ModeUpdateMessage(mode_name, mode_argument);
            dispatcher.send_message_to_robot_by_id(robot_id, message);
        } else {
            throw CommandException("Invalid Robot ID");
        }
    }
}
