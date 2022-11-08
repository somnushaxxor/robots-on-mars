#pragma once

#include "BasicMovementRobot.h"

class Collector final : public BasicMovementRobot {
private:
    size_t apples_grabbed;
    size_t last_apples_grabbed;

public:
    Collector(Terrain &terrain, RadioChannel *radio_channel, const size_t &id);

    ~Collector() override = default;

    void scan();

    void grab();

    size_t get_last_apples_grabbed() const;

    void clear_last_apples_grabbed();
};

inline size_t Collector::get_last_apples_grabbed() const {
    return last_apples_grabbed;
}

inline void Collector::clear_last_apples_grabbed() {
    last_apples_grabbed = 0;
}
