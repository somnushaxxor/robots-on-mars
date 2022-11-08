#include "MapUpdateMessage.h"

#include <utility>

MapUpdateMessage::MapUpdateMessage(std::map<std::pair<int, int>, TerrainCellType> cells_on_update)
        : cells_on_update(std::move(cells_on_update)) {
}
