#include "special_cell.h"

special_cell::special_cell(int h, int w){
    cords = std::make_pair(h, w);
    is_kill = false;
    is_enemy = false;
    is_obstacle = false;
}

