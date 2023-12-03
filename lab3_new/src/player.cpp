#include <ncurses.h>

#include "player.h"
#include "utils.h"
#include <algorithm>
#include "game_logger.h"

Player::Player(int screen_h, int screen_w) {
    w = screen_w/ 2;
    h = screen_h / 2;
    screen_width = screen_w;
    screen_height = screen_h;
    icon = "P";
    is_dead = false;
}

void Player::check_death(std::vector<std::pair<int, int>>& kill_cells) {
    auto it = std::find(kill_cells.begin(), kill_cells.end(), get_cords());
    if(it != kill_cells.end())
        is_dead = true;}

void Player::move_player(int key_pressed){
    switch (key_pressed) {
        case KEY_LEFT:
            if(w > 1)
                --w;
            break;
        case KEY_RIGHT:
            if(w < screen_width - 2)
                ++w;
            break;
        case KEY_UP:
            if (h > 1)
                --h;
            break;
        case KEY_DOWN:
            if (h < screen_height - 2)    
                ++h;
            break;
        default:
            break;
    }
}

//TODO: decompose
void Player::update(int key_pressed, std::vector<std::pair<int, int>>& kill_cells) {
    check_death(kill_cells);
    move_player(key_pressed);    
}

void Player::draw() {
    attron(COLOR_PAIR(2));
    out(h, w, icon);
    attroff(COLOR_PAIR(2));
}

std::pair<int, int> Player::get_cords(){
    return std::make_pair(h, w);
}