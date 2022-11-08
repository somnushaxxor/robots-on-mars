#include "SimulationCommandParser.h"
#include "../../Exception/CommandParserException.h"
#include "../SimulationCommand/AddCommand.h"
#include "../SimulationCommand/ContinueCommand.h"
#include "../SimulationCommand/EndCommand.h"
#include "../SimulationCommand/SetFocusCommand.h"
#include "../SimulationCommand/SetModeCommand.h"
#include <sstream>

SimulationCommandParser::SimulationCommandParser(Simulation *simulation)
        : simulation(simulation) {
}

Command *SimulationCommandParser::parse_command_string(const std::string &command_string) {
    std::stringstream command_stringstream;
    command_stringstream << command_string;
    std::string command_name;
    command_stringstream >> command_name;
    std::vector<std::string> arguments;
    while (command_stringstream.good()) {
        std::string argument;
        command_stringstream >> argument;
        arguments.push_back(argument);
    }
    if (command_name == "END") {
        Command *command = new EndCommand(simulation, arguments);
        return command;
    } else if (command_name == "CONTINUE") {
        Command *command = new ContinueCommand(simulation, arguments);
        return command;
    } else if (command_name == "SET_MODE") {
        Command *command = new SetModeCommand(simulation, arguments);
        return command;
    } else if (command_name == "SET_FOCUS") {
        Command *command = new SetFocusCommand(simulation, arguments);
        return command;
    } else if (command_name == "ADD") {
        Command *command = new AddCommand(simulation, arguments);
        return command;
    } else {
        throw CommandParserException("Unavailable or unknown command");
    }
}
