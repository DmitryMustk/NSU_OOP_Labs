#include "wall.h"
#include "utils.h"

void Wall::draw_wall() {
    out(h, w, symbol);
}
Wall::Wall(int w, int h) : w(w), h(h), is_breakable(false), symbol("#"){}

BreakableWall::BreakableWall(int w, int h) : Wall(w, h){}
