#pragma once

enum class RadioMessageType {
    NOTHING_TO_DO,
    COMMAND_REQUEST,
    STEP_DONE,
    APPLES_GRABBED,
    MAP_UPDATE,
    COMMAND_RESPONSE,
    MODE_UPDATE
};
