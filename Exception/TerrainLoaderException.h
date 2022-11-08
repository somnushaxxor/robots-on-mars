#pragma once

#include <exception>

class TerrainLoaderException final : public std::exception {
private:
    const char *message;

public:
    explicit TerrainLoaderException(const char *message);

    ~TerrainLoaderException() override = default;

    const char *what() const noexcept override;
};
