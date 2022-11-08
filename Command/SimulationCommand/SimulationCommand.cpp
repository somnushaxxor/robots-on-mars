#include "SimulationCommand.h"

SimulationCommand::SimulationCommand(Simulation *simulation, const std::vector<std::string> &arguments)
        : Command(arguments), simulation(simulation) {
}
