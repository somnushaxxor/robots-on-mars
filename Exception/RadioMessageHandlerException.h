#pragma once

#include <exception>

class RadioMessageHandlerException final : public std::exception {
private:
    const char *message;

public:
    explicit RadioMessageHandlerException(const char *message);

    ~RadioMessageHandlerException() override = default;

    const char *what() const noexcept override;
};
