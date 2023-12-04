#include "enemy.h"

#include "vector"

Enemy::Enemy(int h1, int w1) : Player(h1, w1){
     icon = "E";
}

void Enemy::draw(){
    attron(COLOR_PAIR(3));
    out(h, w, icon);
    attroff(COLOR_PAIR(3));
}

std::string Enemy::get_obj_name() {
    return std::string("Enemy");
}

void Enemy::update(int key_pressed, std::vector<special_cell>& general_special_cells) {
    check_death(general_special_cells);
    std::vector<int> dirs = {KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN, 0};
    key_pressed = dirs[std::rand() % 5];
    update_special_cells();
    move_player(key_pressed, general_special_cells);    
}

void Enemy::check_death(std::vector<special_cell>& general_special_cells) {
    const auto player_cords = get_cords();
    for(const auto& cell : general_special_cells){
        if(cell.cords == player_cords && cell.is_kill  ){
            is_dead = true;
            break;
        }
    }
}

void Enemy::update_special_cells(){
    special_cells.clear();
    std::vector<std::pair<int, int>> cell_cords = {{h - 1, w}, {h + 1, w}, {h, w - 1}, {h, w + 1}};
    for(const auto& cords : cell_cords){
        special_cell cell(cords.first, cords.second);
        cell.is_enemy = true;
        special_cells.push_back(cell);
    }
}