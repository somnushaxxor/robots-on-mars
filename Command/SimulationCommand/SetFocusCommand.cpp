#include "SetFocusCommand.h"
#include "../../Exception/CommandException.h"
#include "../../Robot/Robot.h"

SetFocusCommand::SetFocusCommand(Simulation *simulation, const std::vector<std::string> &arguments)
        : SimulationCommand(simulation, arguments) {
}

void SetFocusCommand::execute() {
    const std::vector<std::string> &arguments = this->get_arguments();
    if (arguments.size() != 1) {
        throw CommandException("Bad number of arguments");
    } else {
        Simulation *simulation = this->get_simulation();
        Terrain &terrain = simulation->get_terrain();
        size_t robot_id = std::stoull(arguments[0]);
        std::map<Robot *, std::pair<size_t, size_t>> &robots = terrain.get_robots();
        Robot *new_focused_robot = nullptr;
        for (auto &iterator: robots) {
            Robot *robot = iterator.first;
            if (robot->get_id() == robot_id) {
                new_focused_robot = robot;
                break;
            }
        }
        if (new_focused_robot) {
            simulation->set_focused_robot(new_focused_robot);
        } else {
            throw CommandException("Invalid Robot ID");
        }
    }
}
