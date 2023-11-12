#include <ncurses.h>
#include <algorithm>
#include <stdexcept>

#include "bomberman_game.h"
#include "utils.h"

BombermanGame::BombermanGame() {
    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    timeout(50);

    if(has_colors() == FALSE){
        endwin();
        throw std::runtime_error("Your terminal does not support colours.\n");
    }

    //init colors
    start_color();
    init_pair(main_color_pair, COLOR_WHITE, COLOR_BLACK);
    init_pair(player_color_pair, COLOR_YELLOW, COLOR_BLUE);
    init_pair(bullet_color_pair, COLOR_RED, COLOR_BLACK);

    //get console dimensions
    getmaxyx(stdscr, h1, w1);
    player.move_to(w1 / 2, h1 / 2);
}

BombermanGame::~BombermanGame(){
    endwin();
}

void BombermanGame::render_title() {
    ssize_t title_size = snprintf(NULL, 0, title_format_str, bullets.size());
    wmove(stdscr, 1, (w1 - title_size) / 2);
    wprintw(stdscr, title_format_str, bullets.size());
}

//TODO: Создать класс бомбы, флаг взорвалась ли, поле с хранением сек до взрыва выводить вместо бомбы секи.
void BombermanGame::render_bullets() {
    attron(COLOR_PAIR(bullet_color_pair));
    for(Bullet& b: bullets){
        if((now() - b.last_time) / 1s > 300) {
            b.h--;
            b.last_time = now();
        }
        out(b.h, b.w, "B");

    }
    attroff(COLOR_PAIR(bullet_color_pair));

    //remove bullets reached the screen border
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& b) {return b.h < 2; }), bullets.end());
}

void BombermanGame::render_border() const{
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

void BombermanGame::handle_input(int c) {
    switch (c) {
        case KEY_LEFT:
            if(player.w)
                player.move_left();
            break;
        case KEY_RIGHT:
            player.move_right();
            break;
        case KEY_UP:
            player.move_up();
            break;
        case KEY_DOWN:
            player.move_down();
            break;
        case ' ':
            bullets.push_back(Bullet{player.w, player.h, now()});
            break;
        default:
            break;
    }
}

void BombermanGame::run_game() {
    int c;
    while ('q' != (c = getch())) {
        // clear the screen
        clear();

        render_title();
        render_bullets();
        render_border();
        player.display();
        handle_input(c);

        // don't forget to call refresh/wrefresh to make your changes visible
        refresh();
    }
}