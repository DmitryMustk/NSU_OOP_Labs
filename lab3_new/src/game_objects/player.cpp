#include "../game_logger.h"
#include "../utils.h"
#include "player.h"

#include <algorithm>
#include <ncurses.h>

Player::Player(int screen_h, int screen_w) {
    w = screen_w / 2;
    h = screen_h / 2;
    screen_width = screen_w;
    screen_height = screen_h;
    icon = "P";
    is_dead = false;
}

std::string Player::get_obj_name() {
    return std::string("Player");
}

void Player::check_death(std::vector<special_cell>& general_special_cells) {
    const auto player_cords = get_cords();
    for(const auto& cell : general_special_cells){
        if(cell.cords == player_cords && (cell.is_kill || cell.is_enemy) ){
            is_dead = true;
            break;
        }
    }
}

bool Player::can_move(int h, int w, std::vector<special_cell>& general_special_cells){
    const auto go_cords = std::make_pair(h, w);
    for(const auto& cell : general_special_cells){
        if(cell.cords == go_cords && cell.is_obstacle){
            return false;
        }
    }
    return true;
}

void Player::move_player(int key_pressed, std::vector<special_cell>& general_special_cells){
    switch (key_pressed) {
        case KEY_LEFT:
            if(w > 1 && can_move(h, w - 1, general_special_cells))
                --w;
            break;
        case KEY_RIGHT:
            if(w < screen_width - 2 && can_move(h, w + 1, general_special_cells))
                ++w;
            break;
        case KEY_UP:
            if (h > 1 && can_move(h - 1, w, general_special_cells))
                --h;
            break;
        case KEY_DOWN:
            if (h < screen_height - 2 && can_move(h + 1, w, general_special_cells))    
                ++h;
            break;
        default:
            break;
    }
}

void Player::update(int key_pressed, std::vector<special_cell>& general_special_cells) {
    check_death(general_special_cells);
    move_player(key_pressed, general_special_cells);    
}

void Player::draw() {
    attron(COLOR_PAIR(2));
    out(h, w, icon);
    attroff(COLOR_PAIR(2));
}

std::pair<int, int> Player::get_cords(){
    return std::make_pair(h, w);
}