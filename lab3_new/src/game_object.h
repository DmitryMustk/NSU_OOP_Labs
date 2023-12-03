#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include <string>
#include <vector>
#include <unordered_set>

class GameObject {
public:
    virtual ~GameObject() = default;

    virtual void update(int key_pressed, std::vector<std::pair<int, int>>& kill_cells) = 0;
    virtual void draw() = 0;
    virtual void check_death(std::vector<std::pair<int, int>>& kill_cells) = 0;
    bool is_dead;
    std::vector<std::pair<int, int>> damage_cords;
protected:
    int w;
    int h;
    std::string icon;
};

#endif // GAME_OBJECT_H
