#ifndef GAME_BULLET_H
#define GAME_BULLET_H
#include <chrono>
#include <vector>

using namespace std::chrono_literals;
using steady_clock_t = std::chrono::time_point<std::chrono::steady_clock>;

class Bomb {
   public:
    int w;
    int h;
    steady_clock_t last_time;

    Bomb(int w, int h, steady_clock_t last_time);
    int get_countdown();
    void set_countdown(int new_cd);
    [[nodiscard]] int get_secs_to_blow() const;
    std::vector<std::pair<int, int>> get_damage_cords();
    void draw_boom() const;

   private:
    int countdown;
    int boom_radius;
    std::vector<std::pair<int, int>> damage_cords;
};
#endif  //GAME_BULLET_H
