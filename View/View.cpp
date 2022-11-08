#include "View.h"

#include <utility>

View::View(std::pair<int, int> camera_position, const size_t &camera_offset_x, const size_t &camera_offset_y)
        : camera_position(std::move(camera_position)), camera_offset_x(camera_offset_x),
          camera_offset_y(camera_offset_y) {
}

void View::set_camera_position(const std::pair<int, int> &camera_position) {
    this->camera_position = camera_position;
}
