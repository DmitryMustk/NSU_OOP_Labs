#ifndef BOMB_H
#define BOMB_H
#include "../utils.h"
#include "game_object.h"

#include <vector>

class Bomb : public GameObject {
public:
    Bomb(int w1, int h1, steady_clock_t b_time);
    void update(int key_pressed, std::vector<special_cell>& general_special_cells) override;
    void draw() override;
    void check_death(std::vector<special_cell>& general_special_cells) override;
    std::string get_obj_name() override;
    void update_special_cells();

private: 
    steady_clock_t born_time;
    float countdown;
    int boom_radius;
    float time_to_blow;


    void draw_boom();

};

#endif // BOMB_H
