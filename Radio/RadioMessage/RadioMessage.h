#pragma once

#include "RadioMessageType.h"

class RadioMessage {
private:
public:
    RadioMessage() = default;

    virtual ~RadioMessage() = default;

    virtual RadioMessageType get_type() const = 0;
};
