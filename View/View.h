#pragma once

class TerrainMap;

class Robot;

#include <map>
#include <cstddef>

class View {
private:
    std::pair<int, int> camera_position;
    const size_t camera_offset_x;
    const size_t camera_offset_y;

protected:
    std::pair<int, int> get_camera_position() const;

    size_t get_camera_offset_x() const;

    size_t get_camera_offset_y() const;

public:
    View(std::pair<int, int> camera_position, const size_t &camera_offset_x, const size_t &camera_offset_y);

    virtual ~View() = default;

    void set_camera_position(const std::pair<int, int> &camera_position);

    virtual void draw_frame(const TerrainMap &map, const std::map<Robot *, std::pair<size_t, size_t>> &robots,
                            const size_t &total_apples_grabbed) = 0;
};

inline std::pair<int, int> View::get_camera_position() const {
    return camera_position;
}

inline size_t View::get_camera_offset_x() const {
    return camera_offset_x;
}

inline size_t View::get_camera_offset_y() const {
    return camera_offset_y;
}
