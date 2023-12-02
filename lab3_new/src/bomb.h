// bomb.h
#ifndef BOMB_H
#define BOMB_H

#include "game_object.h"

class Bomb : public GameObject {
public:
    void update() override;
    void draw() const override;

    // Другие методы и свойства для бомбы
};

#endif // BOMB_H
