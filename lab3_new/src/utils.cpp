#include "utils.h"


void out(int y, int x, const std::string& s) {
    wmove(stdscr, y, x);
    wprintw(stdscr, "%s", s.c_str());
}

steady_clock_t now() {
    return std::chrono::steady_clock::now();
}
