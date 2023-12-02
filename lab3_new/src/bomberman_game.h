#ifndef BOMBERMAN_GAME_H
#define BOMBERMAN_GAME_H

#include <vector>
#include <SFML/Audio/Music.hpp>
#include "game_object.h"
#include "player.h"
#include "bomb.h"
#include <memory>

class BombermanGame {
public:
    BombermanGame();
    ~BombermanGame();
    void run_game();

private:
    void handle_input(int input);
    void update_objects();
    void render_objects() ;
    void render_title();
    void render_border() ;
    void lose();
    void start_screen();

    int h1;
    int w1;
    const char* title_format_str = "Bomberman Game. Bombs: %lu";
    const int16_t main_color_pair = 1;
    const int16_t player_color_pair = 2;
    const int16_t bullet_color_pair = 3;
    const int16_t lose_screen_color_pair = 4;
    const int16_t start_screen_color_pair = 5;

    std::vector<std::unique_ptr<GameObject>> game_objects;
};

#endif // BOMBERMAN_GAME_H
