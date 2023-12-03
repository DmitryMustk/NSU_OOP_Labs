#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include <string>

class GameObject {
public:
    virtual ~GameObject() = default;

    virtual void update(int key_pressed) = 0;
    virtual void draw() = 0;
    bool is_dead;
protected:
    int w;
    int h;
    std::string icon;
};

#endif // GAME_OBJECT_H
