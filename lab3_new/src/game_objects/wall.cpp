#include "../utils.h"
#include "wall.h"

#include <algorithm>

Wall::Wall(int init_w, int init_h) {
    w = init_w;
    h = init_h;
    icon = "W";
}

void Wall::update(int key_pressed, std::vector<special_cell>& general_special_cells){
    check_death(general_special_cells);
    update_special_cells();
}

void Wall::update_special_cells(){
    special_cells.emplace_back(h, w, OBSTACLE);
}   

void Wall::draw() {
    out(h, w, icon);
};

void Wall::check_death(std::vector<special_cell>& general_special_cells){
    const auto wall_cords = std::make_pair(h, w);
    for(const auto& cell: general_special_cells){
        if(cell.cords == wall_cords && cell.prop == KILL){
            is_dead = true;
            break;
        }
    }
}

