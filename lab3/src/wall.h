#ifndef BOMBERMAN_WALL_H
#define BOMBERMAN_WALL_H
#include <string>

class Wall{
   public:
    int h;
    int w;
    bool is_breakable;
    std::string symbol;
    Wall(int w, int h);
    virtual void draw_wall();
};

class BreakableWall : public Wall{
   public:
    BreakableWall(int w, int h);
    void break_wall();
};

#endif  //BOMBERMAN_WALL_H
