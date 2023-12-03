#include "special_cell.h"

special_cell::special_cell(int h, int w, property pr){
    cords = std::make_pair(h, w);
    prop = pr;
}