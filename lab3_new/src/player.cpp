#include <ncurses.h>

#include "player.h"
#include "utils.h"

Player::Player(int screen_w, int screen_h) {
    w = screen_w/ 2;
    h = screen_h / 2;
    screen_width = screen_w;
    screen_height = screen_h;
    is_dead = false;
}

void Player::update(int key_pressed) {
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

void Player::draw() {
    attron(COLOR_PAIR(2));
    out(h, w, "P");
    attroff(COLOR_PAIR(2));
}