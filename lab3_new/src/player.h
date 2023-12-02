#ifndef PLAYER_H
#define PLAYER_H

#include "game_object.h"

class Player : public GameObject {
  public:
    Player(int w, int h);
    void update() override;
    void draw() const override;

  private:
    int w;
    int h;
    bool is_dead;

    void move_left();
    void move_right();
    void move_up();
    void move_down();


};

#endif // PLAYER_H
