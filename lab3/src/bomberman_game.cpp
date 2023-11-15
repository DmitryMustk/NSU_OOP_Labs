#include <ncurses.h>
#include <algorithm>
#include <stdexcept>

#include "bomberman_game.h"
#include "utils.h"

BombermanGame::BombermanGame() : game_logger("logs.txt") {
    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    timeout(50);

    if (has_colors() == FALSE) {
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

BombermanGame::~BombermanGame() {
    endwin();
}

void BombermanGame::render_title() {
    ssize_t title_size = snprintf(NULL, 0, title_format_str, bombs.size());
    wmove(stdscr, 1, (w1 - title_size) / 2);
    wprintw(stdscr, title_format_str, bombs.size());
}

void BombermanGame::render_bullets() {
    attron(COLOR_PAIR(bullet_color_pair));
    for (Bomb& b : bombs) {
        if (b.get_secs_to_blow() > 0) {
            out(b.h, b.w, std::to_string(b.get_secs_to_blow()));
            continue;
        }
        b.draw_boom();
        if(b.w == player.w && b.h == player.h)
            game_logger.log("Player blown up ", b.w, b.h);
        game_logger.log("Boom", b.w, b.h);
        bombs.erase(
            std::remove_if(bombs.begin(), bombs.end(), [](const Bomb& b) { return !(4 - (now() - b.last_time) / 1s); }),
            bombs.end());
    }
    attroff(COLOR_PAIR(bullet_color_pair));

    //remove bullets reached the screen border
    //    bombs.erase(std::remove_if(bombs.begin(), bombs.end(), [](const Bomb& b) {return !(4 - (now() - b.last_time) / 1s); }), bombs.end());
}

void BombermanGame::render_border() const {
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
            if (player.w > 1)
                player.move_left();
            break;
        case KEY_RIGHT:
            if (player.w < w1 - 2)
                player.move_right();
            break;
        case KEY_UP:
            if (player.h > 1)
                player.move_up();
            break;
        case KEY_DOWN:
            if (player.h < h1 - 2)
                player.move_down();
            break;
        case ' ':
            bombs.push_back(Bomb{player.w, player.h, now()});
            break;
        default:
            break;
    }
}


void BombermanGame::playMusic(sf::Music& music) {
    if (!music.openFromFile("nc_output.wav")) {
        game_logger.log("Cannot open music file");
        return;
    }
    music.play();
}


void BombermanGame::run_game() {
    int c;
    sf::Music music;
    playMusic(music);
    while ('q' != (c = getch())) {
        // clear the screen
        clear();
        if (music.getStatus() != sf::Music::Playing) {
            music.play();
        }

        render_title();
        render_bullets();
        render_border();
        player.display();
        handle_input(c);

        // don't forget to call refresh/wrefresh to make your changes visible
        refresh();
    }
}