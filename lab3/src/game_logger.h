#ifndef BOMBERMAN_GAME_LOGGER_H
#define BOMBERMAN_GAME_LOGGER_H
#include <ctime>
#include <fstream>
#include <iomanip>
#include <string>

class GameLogger{
   public:
    GameLogger(const std::string& log_file_name);
    ~GameLogger();
    void log(const std::string& message);
    void log(std::string& message, int w, int h);
   private:
    std::ofstream log_file;
    std::string log_file_name
};

#endif  //BOMBERMAN_GAME_LOGGER_H
