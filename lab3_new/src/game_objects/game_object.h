#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "../special_cell.h"

#include <string>
#include <vector>

class GameObject {
public:
    virtual ~GameObject() = default;

    virtual void update(int key_pressed, std::vector<special_cell>& general_special_cells) = 0;
    virtual std::string get_obj_name() = 0;
    virtual void draw() = 0;
    virtual void check_death(std::vector<special_cell>& general_special_cells) = 0;
    bool is_dead;
    std::vector<special_cell> special_cells;
protected:
    int w;
    int h;
    std::string icon;
};

#endif // GAME_OBJECT_H
