#ifndef BOMBERMAN_GAME_H
#define BOMBERMAN_GAME_H
#include "special_cell.h"
#include "game_logger.h"
#include "game_objects/bomb.h"
#include "game_objects/enemy.h"
#include "game_objects/game_object.h"
#include "game_objects/player.h"
#include "game_objects/wall.h"

#include <memory>
#include <SFML/Audio.hpp>
#include <vector>

class BombermanGame {
public:
    BombermanGame();
    ~BombermanGame();
    void run_game();

private:
    void fill_map();
    void manage_objects(int key_pressed);
    void delete_dead_objects();
    void update_special_cells();
    void play_music(sf::Music& music);
    void update_objects(int key_pressed);
    void render_objects() ;
    void render_title();
    void render_border() ;
    void lose();
    void start_screen();

    void create_walls();
    int get_enemy_count();

    int h1;
    int w1;
    std::shared_ptr<Player> player_object;
    size_t mult;

    GameLogger logger;
    const char* title_format_str = "Bomberman Game. Bombs: %lu";
    const int16_t main_color_pair = 1;
    const int16_t player_color_pair = 2;
    const int16_t bullet_color_pair = 3;
    const int16_t lose_screen_color_pair = 4;
    const int16_t start_screen_color_pair = 5;

    std::vector<std::shared_ptr<GameObject>> game_objects;
    std::vector<special_cell> general_special_cells;
};

#endif // BOMBERMAN_GAME_H
