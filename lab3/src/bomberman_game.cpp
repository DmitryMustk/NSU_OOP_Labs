#include <ncurses.h>
#include <algorithm>
#include <stdexcept>
#include <unistd.h>

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
    init_pair(lose_screen_color_pair, COLOR_BLACK, COLOR_RED);

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

void BombermanGame::render_bombs() {
    attron(COLOR_PAIR(bullet_color_pair));
    for (Bomb& b : bombs) {
        b.draw_bomb();
        if(!b.is_blown)
            continue;
        if (is_player_blown(b))
            lose();
        bombs.erase(
            std::remove_if(bombs.begin(), bombs.end(), [](const Bomb& b) { return !(4 - (now() - b.last_time) / 1s); }),
            bombs.end());
    }
    attroff(COLOR_PAIR(bullet_color_pair));
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
            bombs.emplace_back(player.w, player.h, now());
            break;
        default:
            break;
    }
}

void BombermanGame::play_music(sf::Music& music) {
    if (!music.openFromFile("../resources/nc_output.wav")) {
        game_logger.log("Cannot open music file");
        return;
    }
    music.play();
}

void BombermanGame::run_game() {
    int c;
    start_screen();
    sf::Music music;
    play_music(music);
    while ('q' != (c = getch())) {
        if (player.is_dead) {
            lose();
            continue;
        }
        clear();
        if (music.getStatus() != sf::Music::Playing) {
            music.play();
        }

        render_title();

        render_bombs();
        render_border();
        player.display();
        handle_input(c);

        refresh();
    }
}
bool BombermanGame::is_player_blown(Bomb& b) {
    std::vector<std::pair<int, int>> damage_cords = b.get_damage_cords();
    std::pair<int, int> player_cords = std::make_pair(player.h, player.w);

    return std::any_of(damage_cords.begin(), damage_cords.end(),
                       [&player_cords](const auto& cords) { return cords == player_cords; });
}

void BombermanGame::lose() {
    player.is_dead = true;

    std::pair<std::string, std::string> messages = std::make_pair("Game Over - You Lose!", "Press 'q' to quit");
    wbkgd(stdscr, COLOR_PAIR(lose_screen_color_pair));
    out(h1 / 2, (w1 - messages.first.size()) / 2, messages.first);
    out(h1 / 2 + 1, (w1 - messages.second.size()) / 2, messages.second);
    refresh();
}

void BombermanGame::start_screen() {
    std::ifstream input("../resources/start_screen.txt");
    if (!input.is_open())
        throw std::runtime_error("Can not open the start_screen file");
    std::vector<std::string> message;
    std::string line;
    while (std::getline(input, line))
        message.push_back(line);

    show_message(message, 0, 8);
    show_message(message, 10, 18);
    show_message(message, 19, 26);
}

void BombermanGame::show_message(std::vector<std::string>& message, int from, int to) const{
    for (int j = 0; j < to - from; ++j) {
        clear();
        for (int i = from; i < to - j; ++i) {
            out(h1 / 2 + (i - from) - (to - from) / 2, (w1 - message[i].size()) / 2, message[i]);
        }
        refresh();
        usleep(50000);
    }
}
