#pragma once

#include <exception>

class DispatcherException final : public std::exception {
private:
    const char *message;

public:
    explicit DispatcherException(const char *message);

    ~DispatcherException() override = default;

    const char *what() const noexcept override;
};
