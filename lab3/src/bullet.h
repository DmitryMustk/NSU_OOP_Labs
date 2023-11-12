#ifndef GAME_BULLET_H
#define GAME_BULLET_H
#include <chrono>

using namespace std::chrono_literals;
using steady_clock_t = std::chrono::time_point<std::chrono::steady_clock>;

class Bullet{
   public:
    int w;
    int h;
    steady_clock_t last_time;

    Bullet(int w, int h, steady_clock_t last_time);
};
#endif  //GAME_BULLET_H
