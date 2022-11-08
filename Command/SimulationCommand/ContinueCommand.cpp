#include "ContinueCommand.h"
#include "../../Exception/CommandException.h"

ContinueCommand::ContinueCommand(Simulation *simulation, const std::vector<std::string> &arguments)
        : SimulationCommand(simulation, arguments) {
}

void ContinueCommand::execute() {
    const std::vector<std::string> &arguments = this->get_arguments();
    if (!arguments.empty()) {
        throw CommandException("Bad number of arguments");
    } else {
        Simulation *simulation = this->get_simulation();
        simulation->stop_command_awaiting();
    }
}
