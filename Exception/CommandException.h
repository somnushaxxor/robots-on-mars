#pragma once

#include <exception>

class CommandException final : public std::exception {
private:
    const char *message;

public:
    explicit CommandException(const char *message);

    ~CommandException() override = default;

    const char *what() const noexcept override;
};
