#include "RadioChannel.h"
#include "RadioMessage/RadioMessage.h"

RadioChannel::RadioChannel() = default;

RadioChannel::~RadioChannel() {
    if (!messages.empty()) {
        for (auto message: messages) {
            delete message;
            message = nullptr;
        }
    }
}
