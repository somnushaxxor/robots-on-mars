#pragma once

#include "SFML/Graphics.hpp"
#include "TextureType.h"
#include "View.h"
#include <unordered_map>

const std::string FONTS_PATH("../resources/fonts/");
const std::string WINDOW_ICON_FILE_NAME("icon.png");
const std::string TEXTURES_PATH("../resources/textures/");
const size_t TEXTURES_HEIGHT = 32;
const size_t TEXTURES_WIDTH = 32;

class GraphicView final : public View {
private:
    sf::RenderWindow &window;
    sf::Font default_font;
    std::unordered_map<TextureType, sf::Texture> textures;
    std::vector<sf::Sprite> rendered_background;
    std::vector<sf::Sprite> rendered_visible_terrain_map_cells;
    std::vector<sf::Sprite> rendered_visible_robots;
    std::vector<sf::Text> rendered_total_apples_grabbed;

    void render_background();

    void render_visible_terrain_map_cells(const TerrainMap &map);

    void render_visible_robots(const TerrainMap &map, const std::map<Robot *, std::pair<size_t, size_t>> &robots);

    void render_total_apples_grabbed(const size_t &total_apples_grabbed);

    void draw_background() const;

    void draw_visible_terrain_map_cells() const;

    void draw_visible_robots() const;

    void draw_total_apples_grabbed() const;

public:
    explicit GraphicView(sf::RenderWindow &window);

    ~GraphicView() override;

    sf::RenderWindow &get_window();

    void draw_command_line(const std::string &command_string) const;

    void draw_frame(const TerrainMap &map, const std::map<Robot *, std::pair<size_t, size_t>> &robots,
                    const size_t &total_apples_grabbed) override;
};

inline sf::RenderWindow &GraphicView::get_window() {
    return window;
}
