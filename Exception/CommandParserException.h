#pragma once

#include <exception>

class CommandParserException final : public std::exception {
private:
    const char *message;

public:
    explicit CommandParserException(const char *message);

    ~CommandParserException() override = default;

    const char *what() const noexcept override;
};
