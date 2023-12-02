#ifndef PLAYER_H
#define PLAYER_H

#include "game_object.h"

class Player : public GameObject {
  public:
    Player(int w, int h);
    void update(int key_pressed) override;
    void draw() override;

  private:
    int w;
    int h;
    int screen_width;
    int screen_height;

    void move_left();
    void move_right();
    void move_up();
    void move_down();
};

#endif // PLAYER_H
