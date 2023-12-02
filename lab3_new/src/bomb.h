// bomb.h
#ifndef BOMB_H
#define BOMB_H

#include "game_object.h"

class Bomb : public GameObject {
public:
    void update(int key_pressed) override;
    void draw() override;

};

#endif // BOMB_H
