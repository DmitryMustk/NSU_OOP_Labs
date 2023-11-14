#include "game_logger.h"

#include <utility>

GameLogger::GameLogger(const std::string&  log_file_name) : log_file_name(log_file_name) {
    log_file.open(log_file_name, std::ios::app);
}

void GameLogger::log(const std::string& message) {
    std::time_t current_time = std::time(nullptr);
    std::tm* local_time = std::localtime(&current_time);

    log_file << "[" << std::put_time(local_time, "%Y-%m-%d %H:%M:%S") << "]" << message << std::endl;
}
GameLogger::~GameLogger() {
    log_file.close();
}
void GameLogger::log(std::string& message, int w, int h) {
    std::string new_message = message + "on w=" + std::to_string(w) + ", h=" + std::to_string(h);
    log(new_message);
}
