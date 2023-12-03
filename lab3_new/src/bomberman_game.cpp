#include "bomberman_game.h"
#include "utils.h"

#include <ncurses.h>
#include <algorithm>
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

    player_object = std::make_shared<Player>(w1, h1);
    game_objects.push_back(player_object);

}

BombermanGame::~BombermanGame(){
    endwin();
}

void BombermanGame::render_title() {
    ssize_t title_size = snprintf(NULL, 0, title_format_str, 5);
    wmove(stdscr, 1, (w1 - title_size) / 2);
    wprintw(stdscr, title_format_str, "Залупка");
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

void BombermanGame::run_game() {
    int c;
    
    while ('q' != (c = getch())) {
        clear();

        manage_objects(c);
        update_objects(c);
        render_title();
        render_border();
        render_objects();

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
        obj->update(key_pressed);
    }
}

void BombermanGame::manage_objects(int key_pressed) {
    delete_dead_objects();
    
    // Bomb Creation
    if (key_pressed == ' ') {

        auto player_cords = player_object->get_cords();
        auto bomb_object = std::make_unique<Bomb>(player_cords.first, player_cords.second, now());
        game_objects.push_back(std::move(bomb_object));
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
