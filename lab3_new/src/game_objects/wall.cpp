#include "../utils.h"
#include "wall.h"

#include <algorithm>

Wall::Wall(int init_h, int init_w) {
    h = init_h;
    w = init_w;
    icon = "W";
    special_cell cell(h, w);
    cell.is_obstacle = true;
    special_cells.push_back(cell);
}

std::string Wall::get_obj_name() {
    return std::string("Wall");
}

void Wall::update(int key_pressed, std::vector<special_cell>& general_special_cells){
    check_death(general_special_cells);
} 

void Wall::draw() {
    out(h, w, icon);
};

void Wall::check_death(std::vector<special_cell>& general_special_cells){
    const auto wall_cords = std::make_pair(h, w);
    for(const auto& cell: general_special_cells){
        if(cell.cords == wall_cords && cell.is_kill){
            is_dead = true;
            break;
        }
    }
}

