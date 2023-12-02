#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

class GameObject {
public:
    virtual ~GameObject() = default;

    virtual void update() = 0;
    virtual void draw() const = 0;
};

#endif // GAME_OBJECT_H
