#ifndef PLAYER_H
#define PLAYER_H
#include "game_object.h"

class Player : public GameObject {
public:
    Player(int w, int h);
    void update(int key_pressed, std::vector<special_cell>& general_special_cells) override;
    void update_special_cells() override;
    void check_death(std::vector<special_cell>& general_special_cells) override;
    void draw() override;

    bool can_move(int h, int w, std::vector<special_cell>& general_special_cells);
    void move_player(int key_pressed, std::vector<special_cell>& general_special_cells);
    std::pair<int, int> get_cords();

private:
    int screen_width;
    int screen_height;
};

#endif // PLAYER_H
