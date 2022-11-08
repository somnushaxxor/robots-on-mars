#pragma once

#include "RadioMessage.h"
#include <string>

class ModeUpdateMessage final : public RadioMessage {
private:
    const std::string mode_name;
    const std::string mode_argument;

public:
    ModeUpdateMessage(std::string mode_name, std::string mode_argument);

    ~ModeUpdateMessage() override = default;

    const std::string &get_mode_name() const;

    const std::string &get_mode_argument() const;

    RadioMessageType get_type() const override;
};

inline RadioMessageType ModeUpdateMessage::get_type() const {
    return RadioMessageType::MODE_UPDATE;
}

inline const std::string &ModeUpdateMessage::get_mode_name() const {
    return mode_name;
}

inline const std::string &ModeUpdateMessage::get_mode_argument() const {
    return mode_argument;
}
