#pragma once

#include "RadioMessageHandler.h"
#include <cstddef>

class Dispatcher;

class DispatcherMessageHandler final : public RadioMessageHandler {
private:
    Dispatcher *dispatcher;
    size_t message_nothing_to_do_counter;

public:
    explicit DispatcherMessageHandler(Dispatcher *dispatcher);

    ~DispatcherMessageHandler() override = default;

    size_t get_message_nothing_to_do_counter() const;

    void reset_message_nothing_to_do_counter();

    void handle_message(RadioMessage *message) override;
};

inline size_t DispatcherMessageHandler::get_message_nothing_to_do_counter() const {
    return message_nothing_to_do_counter;
}

inline void DispatcherMessageHandler::reset_message_nothing_to_do_counter() {
    message_nothing_to_do_counter = 0;
}
