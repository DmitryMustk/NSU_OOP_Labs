#include "bomb.h"
#include "utils.h"

#include <stdexcept>

Bomb::Bomb(int w, int h, steady_clock_t last_time) : w(w), h(h), last_time(last_time), countdown(3), boom_radius(2) {
    for (int i = w - boom_radius / 2; i <= w - boom_radius / 2 + boom_radius; ++i)
        damage_cords.emplace_back(h, i);
    for (int i = h - boom_radius / 2; i <= h - boom_radius / 2 + boom_radius; ++i)
        damage_cords.emplace_back(i, w);
}

void Bomb::set_countdown(int new_cd) {
    if (new_cd < 0) {
        throw std::runtime_error("Wrong countdown value");
    }
    countdown = new_cd;
}

int Bomb::get_countdown() {
    return countdown;
}
int Bomb::get_secs_to_blow() const {
    int secs_to_blow = countdown - (now() - last_time) / 1s;
    if(secs_to_blow <= 0)
        return 0;
    return secs_to_blow;
}

void Bomb::draw_boom() const{
    for(auto& cords : damage_cords){
        out(cords.first, cords.second, "B");
    }
}
std::vector<std::pair<int, int>> Bomb::get_damage_cords() {
    return damage_cords;
}
