#pragma once

#include "RadioMessage.h"

class StepDoneMessage final : public RadioMessage {
private:
public:
    StepDoneMessage() = default;

    ~StepDoneMessage() override = default;

    RadioMessageType get_type() const override;
};

inline RadioMessageType StepDoneMessage::get_type() const {
    return RadioMessageType::STEP_DONE;
}
