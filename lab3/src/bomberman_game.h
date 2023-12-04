#ifndef GAME_BOMBERMAN_GAME_H
#define GAME_BOMBERMAN_GAME_H
#include <vector>
#include <unistd.h>
#include <SFML/Audio.hpp>

#include "bomb.h"
#include "game_logger.h"
#include "player.h"
#include "wall.h"

class BombermanGame {
   private:
    int h1;
    int w1;
    GameLogger game_logger;
    Player player;

    std::vector<Bomb> bombs;
    std::vector<BreakableWall> breakable_walls;

    const char* title_format_str = "Bomberman Game. Bombs: %lu";
    const int16_t main_color_pair = 1;
    const int16_t player_color_pair = 2;
    const int16_t bullet_color_pair = 3;
    const int16_t lose_screen_color_pair = 4;
    const int16_t start_screen_color_pair = 5;

    void play_music(sf::Music& music);
    bool is_player_blown(Bomb& b);
    void start_screen();
    void show_message(std::vector<std::string>& message, int from, int to) const;
    void lose();

   public:
    BombermanGame();
    ~BombermanGame();

    void render_title();
    void render_bombs();
    void render_border() const;
    void render_walls();
    void handle_input(int c);

    void run_game();
};

#endif  //GAME_BOMBERMAN_GAME_H
