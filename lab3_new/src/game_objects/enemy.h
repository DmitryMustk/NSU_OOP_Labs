#ifndef ENEMY_H
#define ENEMY_H
#include "player.h"
#include "../utils.h"
#include "game_object.h"

#include <vector>

class Enemy : public Player {
public:
    Enemy(int w1, int h1);
    void update(int key_pressed, std::vector<special_cell>& general_special_cells) override;
    void check_death(std::vector<special_cell>& general_special_cells) override;
    void draw() override;
    std::string get_obj_name() override;
    void update_special_cells();
private:
    steady_clock_t last_time_walk;
};

#endif // ENEMY_H