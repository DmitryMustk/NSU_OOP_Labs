#include "utils.h"


void out(int y, int x, const std::string& s) {
    wmove(stdscr, y, x);
    wprintw(stdscr, "%s", s.c_str());
}

steady_clock_t now() {
    return std::chrono::steady_clock::now();
}

void show_message(std::vector<std::string>& message, int from, int to, int h1, int w1) {
    for (int j = 0; j < to - from; ++j) {
        clear();
        for (int i = from; i < to - j; ++i) {
            out(h1 / 2 + (i - from) - (to - from) / 2, (w1 - message[i].size()) / 2, message[i]);
        }
        refresh();
        usleep(100000);
    }
}