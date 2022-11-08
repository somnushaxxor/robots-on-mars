#include "GraphicView.h"
#include "../Robot/Robot.h"

GraphicView::GraphicView(sf::RenderWindow &window)
        : View(std::make_pair<int, int>(0, 0), window.getSize().x / TEXTURES_WIDTH / 2,
               window.getSize().y / TEXTURES_HEIGHT / 2), window(window) {
    window.setFramerateLimit(60);
    default_font.loadFromFile(FONTS_PATH + "HighlandGothicFLF.ttf");
    sf::Image window_icon;
    window_icon.loadFromFile(TEXTURES_PATH + WINDOW_ICON_FILE_NAME);
    window.setIcon(window_icon.getSize().x, window_icon.getSize().y, window_icon.getPixelsPtr());
    sf::Texture background_texture;
    background_texture.loadFromFile(TEXTURES_PATH + "background.jpg", sf::IntRect(0, 200, 800, 800));
    textures[TextureType::BACKGROUND] = background_texture;
    sf::Texture empty_cell_texture;
    empty_cell_texture.loadFromFile(TEXTURES_PATH + "empty.png");
    textures[TextureType::EMPTY] = empty_cell_texture;
    sf::Texture rock_cell_texture;
    rock_cell_texture.loadFromFile(TEXTURES_PATH + "rock.png");
    textures[TextureType::ROCK] = rock_cell_texture;
    sf::Texture bomb_cell_texture;
    bomb_cell_texture.loadFromFile(TEXTURES_PATH + "bomb.png");
    textures[TextureType::BOMB] = bomb_cell_texture;
    sf::Texture apple_cell_texture;
    apple_cell_texture.loadFromFile(TEXTURES_PATH + "apple.png");
    textures[TextureType::APPLE] = apple_cell_texture;
    sf::Texture unknown_cell_texture;
    unknown_cell_texture.loadFromFile(TEXTURES_PATH + "unknown.png");
    textures[TextureType::UNKNOWN] = unknown_cell_texture;
    sf::Texture robot_texture;
    robot_texture.loadFromFile(TEXTURES_PATH + "robot.png");
    textures[TextureType::ROBOT] = robot_texture;
    sf::Texture black_bar_texture;
    black_bar_texture.loadFromFile(TEXTURES_PATH + "black_bar.png");
    textures[TextureType::BLACK_BAR] = black_bar_texture;
}

GraphicView::~GraphicView() {
    window.close();
}

void GraphicView::render_background() {
    rendered_background.clear();

    sf::Sprite background;
    background.setTexture(textures.at(TextureType::BACKGROUND));
    rendered_background.push_back(background);
}

void GraphicView::render_visible_terrain_map_cells(const TerrainMap &map) {
    rendered_visible_terrain_map_cells.clear();

    int visible_cells_min_x = std::max<int>(this->get_camera_position().first - this->get_camera_offset_x(),
                                            map.get_top_left_corner_position().first - 1);
    size_t window_margin_x =
            (this->get_camera_offset_x() - (this->get_camera_position().first - visible_cells_min_x)) * TEXTURES_WIDTH;
    int visible_cells_max_x = std::min<int>(this->get_camera_position().first + this->get_camera_offset_x(),
                                            map.get_bottom_right_corner_position().first + 1);

    int visible_cells_min_y = std::max<int>(this->get_camera_position().second - this->get_camera_offset_y(),
                                            map.get_top_left_corner_position().second - 1);
    size_t window_margin_y =
            (this->get_camera_offset_y() - (this->get_camera_position().second - visible_cells_min_y)) *
            TEXTURES_HEIGHT;
    int visible_cells_max_y = std::min<int>(this->get_camera_position().second + this->get_camera_offset_y(),
                                            map.get_bottom_right_corner_position().second + 1);

    size_t window_position_y = 0;
    for (int y = visible_cells_min_y; y <= visible_cells_max_y; y++) {
        size_t window_position_x = 0;
        for (int x = visible_cells_min_x; x <= visible_cells_max_x; x++) {
            sf::Sprite cell;
            cell.setPosition(window_position_x + window_margin_x, window_position_y + window_margin_y);
            const std::pair<int, int> cell_position(x, y);
            if (map.check_cell_existence(cell_position)) {
                if (map.get_cell_type(cell_position) == TerrainCellType::EMPTY) {
                    cell.setTexture(textures.at(TextureType::EMPTY));
                    rendered_visible_terrain_map_cells.push_back(cell);
                } else if (map.get_cell_type(cell_position) == TerrainCellType::ROCK) {
                    cell.setTexture(textures.at(TextureType::ROCK));
                    rendered_visible_terrain_map_cells.push_back(cell);
                } else if (map.get_cell_type(cell_position) == TerrainCellType::BOMB) {
                    cell.setTexture(textures.at(TextureType::BOMB));
                    rendered_visible_terrain_map_cells.push_back(cell);
                } else if (map.get_cell_type(cell_position) == TerrainCellType::APPLE) {
                    cell.setTexture(textures.at(TextureType::APPLE));
                    rendered_visible_terrain_map_cells.push_back(cell);
                }
            } else {
                cell.setTexture(textures.at(TextureType::UNKNOWN));
                rendered_visible_terrain_map_cells.push_back(cell);
            }
            window_position_x += TEXTURES_WIDTH;
        }
        window_position_y += TEXTURES_HEIGHT;
    }
}

void
GraphicView::render_visible_robots(const TerrainMap &map, const std::map<Robot *, std::pair<size_t, size_t>> &robots) {
    rendered_visible_robots.clear();

    int visible_cells_min_x = std::max<int>(this->get_camera_position().first - this->get_camera_offset_x(),
                                            map.get_top_left_corner_position().first);
    size_t window_margin_x =
            (this->get_camera_offset_x() - (this->get_camera_position().first - visible_cells_min_x)) * TEXTURES_WIDTH;
    int visible_cells_max_x = std::min<int>(this->get_camera_position().first + this->get_camera_offset_x(),
                                            map.get_bottom_right_corner_position().first);

    int visible_cells_min_y = std::max<int>(this->get_camera_position().second - this->get_camera_offset_y(),
                                            map.get_top_left_corner_position().second);
    size_t window_margin_y =
            (this->get_camera_offset_y() - (this->get_camera_position().second - visible_cells_min_y)) *
            TEXTURES_HEIGHT;
    int visible_cells_max_y = std::min<int>(this->get_camera_position().second + this->get_camera_offset_y(),
                                            map.get_bottom_right_corner_position().second);

    size_t window_position_y = 0;
    for (int y = visible_cells_min_y; y <= visible_cells_max_y; y++) {
        size_t window_position_x = 0;
        for (int x = visible_cells_min_x; x <= visible_cells_max_x; x++) {
            sf::Sprite cell;
            cell.setPosition(window_position_x + window_margin_x, window_position_y + window_margin_y);
            const std::pair<int, int> cell_position(x, y);
            for (const auto &robot_iterator: robots) {
                Robot *robot_ptr = robot_iterator.first;
                if (robot_ptr->get_position() == cell_position) {
                    sf::Sprite robot;
                    robot.setTexture(textures.at(TextureType::ROBOT));
                    robot.setPosition(window_position_x + window_margin_x, window_position_y + window_margin_y);
                    rendered_visible_robots.push_back(robot);
                }
            }
            window_position_x += TEXTURES_WIDTH;
        }
        window_position_y += TEXTURES_HEIGHT;
    }
}

void GraphicView::render_total_apples_grabbed(const size_t &total_apples_grabbed) {
    rendered_total_apples_grabbed.clear();

    sf::Text text;
    text.setFont(default_font);
    text.setString("APPLES: " + std::to_string(total_apples_grabbed));
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Green);
    text.setPosition(5, 0);
    rendered_total_apples_grabbed.push_back(text);
}

void GraphicView::draw_background() const {
    for (const auto &rendered_background: rendered_background) {
        window.draw(rendered_background);
    }
}

void GraphicView::draw_visible_terrain_map_cells() const {
    for (const auto &rendered_cell: rendered_visible_terrain_map_cells) {
        window.draw(rendered_cell);
    }
}

void GraphicView::draw_visible_robots() const {
    for (const auto &rendered_robot: rendered_visible_robots) {
        window.draw(rendered_robot);
    }
}

void GraphicView::draw_command_line(const std::string &command_string) const {
    window.clear();
    this->draw_background();
    this->draw_visible_terrain_map_cells();
    this->draw_visible_robots();
    this->draw_total_apples_grabbed();

    sf::Sprite black_bar;
    black_bar.setTexture(textures.at(TextureType::BLACK_BAR));
    black_bar.setPosition(0, window.getSize().y - TEXTURES_HEIGHT);
    window.draw(black_bar);

    sf::Text text;
    text.setFont(default_font);
    text.setString(command_string);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Green);
    text.setPosition(5, window.getSize().y - TEXTURES_HEIGHT);
    window.draw(text);

    window.display();
}

void GraphicView::draw_total_apples_grabbed() const {
    sf::Sprite black_bar;
    black_bar.setTexture(textures.at(TextureType::BLACK_BAR));
    black_bar.setPosition(0, 0);
    window.draw(black_bar);

    for (const auto &rendered_object: rendered_total_apples_grabbed) {
        window.draw(rendered_object);
    }
}

void GraphicView::draw_frame(const TerrainMap &map, const std::map<Robot *, std::pair<size_t, size_t>> &robots,
                             const size_t &total_apples_grabbed) {
    window.clear();
    if (rendered_background.empty()) {
        this->render_background();
    }
    this->draw_background();
    this->render_visible_terrain_map_cells(map);
    this->draw_visible_terrain_map_cells();
    this->render_visible_robots(map, robots);
    this->draw_visible_robots();
    this->render_total_apples_grabbed(total_apples_grabbed);
    this->draw_total_apples_grabbed();
    window.display();
}
