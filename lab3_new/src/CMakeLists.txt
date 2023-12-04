cmake_minimum_required(VERSION 3.14)

project(BomberMan CXX)

set(CMAKE_CXX_STANDARD 17)

set(exe_name ${PROJECT_NAME})

add_executable(${exe_name} main.cpp
    bomberman_game.cpp
    utils.cpp
    game_logger.cpp
    special_cell.cpp
    game_objects/player.cpp
    game_objects/bomb.cpp
    game_objects/wall.cpp
    game_objects/enemy.cpp
)
find_package(SFML 2.5 COMPONENTS system audio REQUIRED)

target_link_libraries(${exe_name} curses sfml-system sfml-audio)


