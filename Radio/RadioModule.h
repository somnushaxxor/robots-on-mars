#pragma once

#include <vector>

class RadioChannel;

class RadioMessage;

class RadioModule final {
private:
    RadioChannel *radio_channel;

public:
    RadioModule();

    ~RadioModule() = default;

    void set_radio_channel(RadioChannel *radio_channel);

    RadioChannel *get_radio_channel();

    std::vector<RadioMessage *> receive_messages() const;

    void send_message(RadioMessage *message) const;
};

inline void RadioModule::set_radio_channel(RadioChannel *radio_channel) {
    this->radio_channel = radio_channel;
}

inline RadioChannel *RadioModule::get_radio_channel() {
    return radio_channel;
}
