#ifndef PLAYER_H
#define PLAYER_H
#include "game_object.h"

class Player : public GameObject {
public:
    Player(int h, int w);
    void update(int key_pressed, std::vector<special_cell>& general_special_cells) override;
    void check_death(std::vector<special_cell>& general_special_cells) override;
    void draw() override;
    std::string get_obj_name() override;

    bool can_move(int h, int w, std::vector<special_cell>& general_special_cells);
    void move_player(int key_pressed, std::vector<special_cell>& general_special_cells);
    std::pair<int, int> get_cords();

protected:
    int screen_width;
    int screen_height;
};

#endif // PLAYER_H
