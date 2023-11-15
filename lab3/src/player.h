#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

class Player {
   public:
    int w;
    int h;
    bool is_dead;

    Player();
    Player(int initial_W, int initial_H);
    void move_left();
    void move_right();
    void move_up();
    void move_down();

    void move_to(int w_new, int h_new);

    void display();
};

#endif  //GAME_PLAYER_H
