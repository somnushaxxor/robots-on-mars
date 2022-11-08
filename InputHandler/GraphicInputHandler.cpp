#include "GraphicInputHandler.h"

GraphicInputHandler::GraphicInputHandler(GraphicView &view)
        : view(view) {
}

std::string GraphicInputHandler::get_input() {
    sf::RenderWindow &window = view.get_window();
    std::string typed_string;
    view.draw_command_line(typed_string);
    std::string input;
    sf::Event event{};
    while (input.empty()) {
        if (window.waitEvent(event)) {
            if (event.type == sf::Event::Closed) {
                input = "END";
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    input = "MOVE U";
                } else if (event.key.code == sf::Keyboard::Down) {
                    input = "MOVE D";
                } else if (event.key.code == sf::Keyboard::Left) {
                    input = "MOVE L";
                } else if (event.key.code == sf::Keyboard::Right) {
                    input = "MOVE R";
                } else if (event.key.code == sf::Keyboard::LControl) {
                    input = "SCAN";
                } else if (event.key.code == sf::Keyboard::LAlt) {
                    input = "GRAB";
                } else if (event.key.code == sf::Keyboard::Backspace) {
                    if (!typed_string.empty()) {
                        typed_string.pop_back();
                    }
                } else if (event.key.code == sf::Keyboard::Enter) {
                    if (!typed_string.empty()) {
                        input = typed_string;
                        typed_string.clear();
                    }
                }
            } else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode > 31 && event.text.unicode < 127) {
                    typed_string += static_cast<char>(event.text.unicode);
                }
            }
        }
        view.draw_command_line(typed_string);
    }
    view.draw_command_line(typed_string);
    return input;
}
