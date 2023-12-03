// bomb.h
#ifndef BOMB_H
#define BOMB_H

#include "game_object.h"
#include "utils.h"
#include <vector>

class Bomb : public GameObject {
public:
    Bomb(int w1, int h1, steady_clock_t b_time);
    void update(int key_pressed) override;
    void draw() override;
private: 
    steady_clock_t born_time;
    int countdown;
    int boom_radius;
    std::vector<std::pair<int, int>> damage_cords;

    void draw_boom();
};

#endif // BOMB_H
