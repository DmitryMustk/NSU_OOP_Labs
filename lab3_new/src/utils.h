#ifndef GAME_UTILS_H
#define GAME_UTILS_H
#include <ncurses.h>
#include <string>
#include <chrono>

using namespace std::chrono_literals;
using steady_clock_t = std::chrono::time_point<std::chrono::steady_clock>;

void out(int y, int x, const std::string& s);

steady_clock_t now();

#endif  //GAME_UTILS_H
