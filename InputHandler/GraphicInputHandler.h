#pragma once

#include "../View/GraphicView.h"
#include "InputHandler.h"

class GraphicInputHandler final : public InputHandler {
private:
    GraphicView &view;

public:
    explicit GraphicInputHandler(GraphicView &view);

    ~GraphicInputHandler() override = default;

    std::string get_input() override;
};
