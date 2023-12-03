#ifndef PLAYER_H
#define PLAYER_H
#include "game_object.h"

class Player : public GameObject {
public:
    Player(int w, int h);
    void update(int key_pressed, std::vector<std::pair<int, int>>& kill_cells) override;
    void check_death(std::vector<std::pair<int, int>>& kill_cells) override;
    void draw() override;

    void move_player(int key_pressed);
    std::pair<int, int> get_cords();

private:
    int screen_width;
    int screen_height;
};

#endif // PLAYER_H
