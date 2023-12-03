#ifndef BOMBERMAN_SPECIAL_CELL_H
#define BOMBERMAN_SPECIAL_CELL_H
#include <utility>
enum property{
    OBSTACLE,
    KILL,
};

struct special_cell{
    std::pair<int, int> cords;
    property prop;

    special_cell(int h, int w, property pr);
};
#endif //BOMBERMAN_SPECIAL_CELL_H