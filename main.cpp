#include "Dispatcher/Dispatcher.h"
#include "InputHandler/GraphicInputHandler.h"
#include "Simulation/Simulation.h"
#include "Terrain/TerrainLoader/TerrainLoader.h"
#include "View/GraphicView.h"
#include <string>

const size_t WINDOW_WIDTH = 800;
const size_t WINDOW_HEIGHT = 800;
const std::string WINDOW_NAME("Robots On Mars");

int main() {
    std::string terrain_file_name("example.ter");
    TerrainLoader terrain_loader;
    Terrain terrain = terrain_loader.load_from_file(terrain_file_name);

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME);
    GraphicView view(window);
    GraphicInputHandler input_handler(view);

    Dispatcher dispatcher(terrain, input_handler);

    Simulation simulation(dispatcher, terrain, view, input_handler);
    simulation.run();

    return 0;
}
