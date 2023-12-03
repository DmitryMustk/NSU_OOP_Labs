#ifndef BOMBERMAN_GAME_H
#define BOMBERMAN_GAME_H
#include "game_objects/bomb.h"
#include "game_objects/game_object.h"
#include "game_objects/player.h"

#include <memory>
#include <unordered_set>
#include <vector>

class BombermanGame {
public:
    BombermanGame();
    ~BombermanGame();
    void run_game();

private:
    void manage_objects(int key_pressed);
    void delete_dead_objects();
    void update_kill_cells();
    void update_objects(int key_pressed);
    void render_objects() ;
    void render_title();
    void render_border() ;
    void lose();
    void start_screen();

    int h1;
    int w1;
    std::shared_ptr<Player> player_object;

    const char* title_format_str = "Bomberman Game. Bombs: %lu";
    const int16_t main_color_pair = 1;
    const int16_t player_color_pair = 2;
    const int16_t bullet_color_pair = 3;
    const int16_t lose_screen_color_pair = 4;
    const int16_t start_screen_color_pair = 5;

    std::vector<std::shared_ptr<GameObject>> game_objects;
    std::vector<std::pair<int, int>> kill_cells;
};

#endif // BOMBERMAN_GAME_H
