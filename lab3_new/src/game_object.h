#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

class GameObject {
public:
    virtual ~GameObject() = default;

    virtual void update(int key_pressed) = 0;
    virtual void draw() = 0;
protected:
    int w;
    int h;
    bool is_dead;
};

#endif // GAME_OBJECT_H
