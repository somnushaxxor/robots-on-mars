#pragma once

#include "../../Terrain/TerrainCellType.h"
#include "RadioMessage.h"
#include <map>

class MapUpdateMessage final : public RadioMessage {
private:
    std::map<std::pair<int, int>, TerrainCellType> cells_on_update;

public:
    explicit MapUpdateMessage(std::map<std::pair<int, int>, TerrainCellType> cells_on_update);

    ~MapUpdateMessage() override = default;

    const std::map<std::pair<int, int>, TerrainCellType> &get_cells_on_update() const;

    RadioMessageType get_type() const override;
};

inline RadioMessageType MapUpdateMessage::get_type() const {
    return RadioMessageType::MAP_UPDATE;
}

inline const std::map<std::pair<int, int>, TerrainCellType> &MapUpdateMessage::get_cells_on_update() const {
    return cells_on_update;
}
