#pragma once

#include "RadioMessage.h"

class CommandRequestMessage final : public RadioMessage {
private:
public:
    CommandRequestMessage() = default;

    ~CommandRequestMessage() override = default;

    RadioMessageType get_type() const override;
};

inline RadioMessageType CommandRequestMessage::get_type() const {
    return RadioMessageType::COMMAND_REQUEST;
}
