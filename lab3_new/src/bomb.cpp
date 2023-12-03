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
    for (int i = w - boom_radius / 2; i <= w - boom_radius / 2 + boom_radius; ++i)
        damage_cords.emplace_back(h, i);
    for (int i = h - boom_radius / 2; i <= h - boom_radius / 2 + boom_radius; ++i)
        damage_cords.emplace_back(i, w);
}

void Bomb::check_death(std::vector<std::pair<int, int>>& kill_cells){
    if(secs_to_blow <= 0)
        is_dead = true;
}

void Bomb::update(int key_pressed, std::vector<std::pair<int, int>>& kill_cells) {
    secs_to_blow = countdown - (now() - born_time) / 1s;
    check_death(kill_cells);
    icon = std::to_string(secs_to_blow);
}

void Bomb::draw(){
    if(is_dead)
        draw_boom();
    out(h, w, icon);
}

void Bomb::draw_boom(){
    for (auto& cords : damage_cords) {
        out(cords.first, cords.second, "B");
    }
}
