#ifndef BOMBERMAN_GAME_LOGGER_H
#define BOMBERMAN_GAME_LOGGER_H
#include <ctime>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

class GameLogger{
public:
    GameLogger();
    GameLogger(const std::string& log_file_name);
    ~GameLogger();
    void log(const std::string& message);
    void log(const std::string& message, int w, int h);
    void log(const std::string& message, std::vector<std::pair<int,int>> dmg_cords, std::pair<int, int> player_cords);
private:
    std::ofstream log_file;
    std::string log_file_name;
};

#endif  //BOMBERMAN_GAME_LOGGER_H