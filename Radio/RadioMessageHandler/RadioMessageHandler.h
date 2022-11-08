#pragma once

class RadioMessage;

class RadioMessageHandler {
private:
public:
    RadioMessageHandler() = default;

    virtual ~RadioMessageHandler() = default;

    virtual void handle_message(RadioMessage *message) = 0;
};
