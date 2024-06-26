#ifndef WALL_H
#define WALL_H
#include "game_object.h"

class Wall : public GameObject {
public:
    Wall(int h, int w);
    void update(int key_pressed, std::vector<special_cell>& general_special_cells) override;
    void check_death(std::vector<special_cell>& general_special_cells) override;
    void draw() override;
    std::string get_obj_name() override;

private:
    int screen_width;
    int screen_height;
};

#endif // WALL_H