#include "ModeUpdateMessage.h"

#include <utility>

ModeUpdateMessage::ModeUpdateMessage(std::string mode_name, std::string mode_argument)
        : mode_name(std::move(mode_name)), mode_argument(std::move(mode_argument)) {
}
