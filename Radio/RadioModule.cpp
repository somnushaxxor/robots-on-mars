#include "RadioModule.h"
#include "RadioChannel.h"

RadioModule::RadioModule()
        : radio_channel(nullptr) {
}

std::vector<RadioMessage *> RadioModule::receive_messages() const {
    return radio_channel->pop_messages();
}

void RadioModule::send_message(RadioMessage *message) const {
    radio_channel->push_message(message);
}
