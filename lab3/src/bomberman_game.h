#ifndef GAME_BOMBERMAN_GAME_H
#define GAME_BOMBERMAN_GAME_H
#include <vector>

#include "bullet.h"
#include "player.h"

class BombermanGame {
   private:
    int h1;
    int w1;
    Player player;
    std::vector<Bullet> bullets;

    const char* title_format_str = "Bomberman Game. Bullets: %lu";
    const int16_t main_color_pair = 1;
    const int16_t player_color_pair = 2;
    const int16_t bullet_color_pair = 3;

   public:
    BombermanGame();
    ~BombermanGame();

    void render_title();
    void render_bullets();
    void render_border() const;
    void handle_input(int c);

    void run_game();
};

#endif  //GAME_BOMBERMAN_GAME_H