#include "bomb.h"

#include <string>

Bomb::Bomb(int h1, int w1, steady_clock_t b_time){
    h = h1;
    w = w1;
    born_time = b_time;
    is_dead = false;
    boom_radius = 2;
    countdown = 3;
    icon = "B";
}

void Bomb::check_death(std::vector<special_cell>& general_special_cells){
    if(time_to_blow <= -500)
        is_dead = true;
}

void Bomb::update_special_cells(){
    if((time_to_blow) > 0)
        return;
    for (int i = w - boom_radius / 2; i <= w - boom_radius / 2 + boom_radius; ++i)
        special_cells.emplace_back(h, i, KILL);
    for (int i = h - boom_radius / 2; i <= h - boom_radius / 2 + boom_radius; ++i)
        special_cells.emplace_back(i, w, KILL);
}

void Bomb::update(int key_pressed, std::vector<special_cell>& general_special_cells) {
    time_to_blow = countdown * 1000 - (now() - born_time) / 1ms ;
    check_death(general_special_cells);
    update_special_cells();
    icon = std::to_string(static_cast<int>(time_to_blow / 1000));
}

void Bomb::draw(){
    if(time_to_blow < 0){
        draw_boom();
        return;
    }
    out(h, w, icon);
}

void Bomb::draw_boom(){
    for (auto& cell : special_cells) {
        out(cell.cords.first, cell.cords.second, "B");
    }
}
