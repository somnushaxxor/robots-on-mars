#pragma once

#include "RadioMessage.h"
#include <string>

class CommandResponseMessage final : public RadioMessage {
private:
    const std::string command_string;

public:
    explicit CommandResponseMessage(std::string command_string);

    ~CommandResponseMessage() override = default;

    const std::string &get_command_string() const;

    RadioMessageType get_type() const override;
};

inline RadioMessageType CommandResponseMessage::get_type() const {
    return RadioMessageType::COMMAND_RESPONSE;
}

inline const std::string &CommandResponseMessage::get_command_string() const {
    return command_string;
}
