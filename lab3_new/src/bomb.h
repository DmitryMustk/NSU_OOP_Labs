// bomb.h
#ifndef BOMB_H
#define BOMB_H

#include "game_object.h"
#include "utils.h"
#include <vector>

class Bomb : public GameObject {
public:
    Bomb(int w1, int h1, steady_clock_t b_time);
    void update(int key_pressed, std::vector<std::pair<int, int>>& kill_cells) override;
    void draw() override;
    virtual void check_death(std::vector<std::pair<int, int>>& kill_cells) override;

    void update_damage_cords();
private: 
    steady_clock_t born_time;
    float countdown;
    int boom_radius;
    float time_to_blow;

    void draw_boom();
};

#endif // BOMB_H
