#pragma once

#include <vector>

class RadioMessage;

class RadioChannel final {
private:
    std::vector<RadioMessage *> messages;

public:
    RadioChannel();

    ~RadioChannel();

    std::vector<RadioMessage *> pop_messages();

    void push_message(RadioMessage *message);
};

inline std::vector<RadioMessage *> RadioChannel::pop_messages() {
    std::vector<RadioMessage *> tmp;
    if (!messages.empty()) {
        tmp = messages;
        messages.clear();
    }
    return tmp;
}

inline void RadioChannel::push_message(RadioMessage *message) {
    messages.push_back(message);
}
