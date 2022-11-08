#pragma once

#include "RadioMessage.h"
#include <cstddef>

class ApplesGrabbedMessage final : public RadioMessage {
private:
    const size_t apples_grabbed;

public:
    explicit ApplesGrabbedMessage(const size_t &apples_grabbed);

    ~ApplesGrabbedMessage() override = default;

    const size_t &get_apples_grabbed() const;

    RadioMessageType get_type() const override;
};

inline RadioMessageType ApplesGrabbedMessage::get_type() const {
    return RadioMessageType::APPLES_GRABBED;
}

inline const size_t &ApplesGrabbedMessage::get_apples_grabbed() const {
    return apples_grabbed;
}
