#pragma once

#include "RadioMessage.h"

class NothingToDoMessage final : public RadioMessage {
private:
public:
    NothingToDoMessage() = default;

    ~NothingToDoMessage() override = default;

    RadioMessageType get_type() const override;
};

inline RadioMessageType NothingToDoMessage::get_type() const {
    return RadioMessageType::NOTHING_TO_DO;
}
