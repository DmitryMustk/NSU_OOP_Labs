#ifndef GAME_UTILS_H
#define GAME_UTILS_H
#include <string>
#include "bullet.h"
#include <ncurses.h>

void out(int y, int x, const std::string& s);

steady_clock_t now();

#endif  //GAME_UTILS_H
