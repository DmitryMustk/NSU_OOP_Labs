#ifndef GAME_UTILS_H
#define GAME_UTILS_H
#include <chrono>
#include <ncurses.h>
#include <string>
#include <vector>
#include <unistd.h>

using namespace std::chrono_literals;
using steady_clock_t = std::chrono::time_point<std::chrono::steady_clock>;

void out(int y, int x, const std::string& s);
void show_message(std::vector<std::string>& message, int from, int to, int h1, int w1);

steady_clock_t now();
#endif  //GAME_UTILS_H
