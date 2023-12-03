#ifndef PLAYER_H
#define PLAYER_H

#include "game_object.h"

class Player : public GameObject {
  public:
    Player(int w, int h);
    void update(int key_pressed) override;
    void draw() override;
    std::pair<int, int> get_cords();

  private:
    int screen_width;
    int screen_height;

};

#endif // PLAYER_H
