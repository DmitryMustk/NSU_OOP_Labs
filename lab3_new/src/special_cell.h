#ifndef BOMBERMAN_SPECIAL_CELL_H
#define BOMBERMAN_SPECIAL_CELL_H
#include <utility>

struct special_cell{
    std::pair<int, int> cords;
    bool is_kill;
    bool is_obstacle;
    bool is_player;
    bool is_enemy;
    
    special_cell(int h, int w);
    bool operator==(const special_cell& other) const;
};
#endif //BOMBERMAN_SPECIAL_CELL_H