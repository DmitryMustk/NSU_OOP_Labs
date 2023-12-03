#include "bomberman_game.h"
#include "game_logger.h"
#include "utils.h"

#include <algorithm>
#include <ncurses.h>
#include <stdexcept>
#include <unistd.h>

BombermanGame::BombermanGame(){
    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    timeout(50);

    start_color();
    init_pair(main_color_pair, COLOR_WHITE, COLOR_BLACK);
    init_pair(player_color_pair, COLOR_YELLOW, COLOR_BLUE);
    init_pair(bullet_color_pair, COLOR_RED, COLOR_BLACK);
    init_pair(lose_screen_color_pair, COLOR_BLACK, COLOR_RED);

    //get console dimensions
    getmaxyx(stdscr, h1, w1);
    
    player_object = std::make_shared<Player>(h1, w1);
    game_objects.push_back(player_object);

    create_walls();
}

BombermanGame::~BombermanGame(){
    endwin();
}

void BombermanGame::render_title() {
    ssize_t title_size = snprintf(NULL, 0, title_format_str, game_objects.size() - 1);
    wmove(stdscr, 1, (w1 - title_size) / 2);
    wprintw(stdscr, title_format_str, game_objects.size() - 1);
}

void BombermanGame::render_border() {
    for (int i = 1; i < w1; ++i) {
        out(0, i, "-");
        out(h1 - 1, i, "-");
    }
    for (int i = 1; i < h1 - 1; ++i) {
        out(i, 0, "|");
        out(i, w1 - 1, "|");
    }
    out(0, 0, "+");
    out(0, w1 - 1, "+");
    out(h1 - 1, 0, "+");
    out(h1 - 1, w1 - 1, "+");
}

void BombermanGame::lose(){
    std::pair<std::string, std::string> messages = std::make_pair("Game Over - You Lose!", "Press 'q' to quit");
    int16_t lose_screen_color_pair = 4;
    wbkgd(stdscr, COLOR_PAIR(lose_screen_color_pair));
    out(h1 / 2, (w1 - messages.first.size()) / 2, messages.first);
    out(h1 / 2 + 1, (w1 - messages.second.size()) / 2, messages.second);
}

void BombermanGame::run_game() {
    int c;
    
    while ('q' != (c = getch())) {
        clear();

        if(player_object->is_dead){
            lose();
            continue;
        }

        manage_objects(c);
        update_objects(c);
        render_title();
        render_border();
        render_objects();
        update_special_cells();

        refresh();
    }
}

void BombermanGame::render_objects() {
    for(auto& obj : game_objects){
        obj->draw();
    }
}

void BombermanGame::update_objects(int key_pressed) {
    for(auto& obj : game_objects){
        obj->update(key_pressed, general_special_cells);
    }
}

void BombermanGame::manage_objects(int key_pressed) {
    delete_dead_objects();
    
    // Bomb Creation
    if (key_pressed == ' ') {
        auto player_cords = player_object->get_cords();
        auto bomb_object = std::make_shared<Bomb>(player_cords.first, player_cords.second, now());
        game_objects.push_back(std::move(bomb_object));
    }
}

void BombermanGame::create_walls(){
    for(int i = 10; i < 20; ++i){
        auto wall_object = std::make_shared<Wall>(30, i);
        game_objects.push_back(std::move(wall_object));
    }
}

void BombermanGame::update_special_cells(){
    general_special_cells.clear();
    for(const auto& obj : game_objects){
        for(const auto& cell : obj->special_cells){
            general_special_cells.push_back(cell);
        }
    }
}

void BombermanGame::delete_dead_objects(){
    game_objects.erase(
        std::remove_if(
            game_objects.begin(), 
            game_objects.end(), 
            [](const auto& obj) { return obj->is_dead; }
        ), 
        game_objects.end()
    );
}
