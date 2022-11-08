#include "AutoMode.h"

AutoMode::AutoMode(Robot *robot)
        : Mode(robot, nullptr) {
}

bool AutoMode::set_new_aim() {
    std::deque<Command *> new_commands_deque;
    if (this->find_path(new_commands_deque)) {
        while (!new_commands_deque.empty()) {
            Command *command = new_commands_deque.front();
            this->push_command_to_deque(command);
            new_commands_deque.pop_front();
        }
        return true;
    } else {
        return false;
    }
}
