#include "AddCommand.h"
#include "../../Exception/CommandException.h"

AddCommand::AddCommand(Simulation *simulation, const std::vector<std::string> &arguments)
        : SimulationCommand(simulation, arguments) {
}

void AddCommand::execute() {
    const std::vector<std::string> &arguments = this->get_arguments();
    if (arguments.size() != 1) {
        throw CommandException("Bad number of arguments");
    } else {
        Simulation *simulation = this->get_simulation();
        Dispatcher &dispatcher = simulation->get_dispatcher();
        if (arguments[0] == "COLLECTOR") {
            dispatcher.deploy_robot(RobotType::COLLECTOR);
        } else if (arguments[0] == "SAPPER") {
            dispatcher.deploy_robot(RobotType::SAPPER);
        } else {
            throw CommandException("Invalid arguments");
        }
    }
}
