#include <ncurses.h>

#include "player.h"
#include "utils.h"

Player::Player() {
    w = 0;
    h = 0;
    is_dead = false;
}

void Player::move_down() {
    ++h;
}

void Player::move_left() {
    --w;
}

void Player::move_right() {
    ++w;
}

void Player::move_up() {
    --h;
}

void Player::display() {
    attron(COLOR_PAIR(2));
    out(h, w, "P");
    attroff(COLOR_PAIR(2));
}
void Player::move_to(const int w_new, const int h_new) {
    w = w_new;
    h = h_new;
}
