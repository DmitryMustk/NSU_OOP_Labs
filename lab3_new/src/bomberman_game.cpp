#include "bomberman_game.h"
#include "game_logger.h"
#include "utils.h"

#include <algorithm>
#include <ncurses.h>
#include <stdexcept>
#include <ctime>
#include <unistd.h>

BombermanGame::BombermanGame() : logger("logs.txt"){
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

    start_color();
    init_pair(main_color_pair, COLOR_WHITE, COLOR_BLACK);
    init_pair(player_color_pair, COLOR_YELLOW, COLOR_BLUE);
    init_pair(bullet_color_pair, COLOR_RED, COLOR_BLACK);
    init_pair(lose_screen_color_pair, COLOR_BLACK, COLOR_RED);

    mult = 1;
    
    //get console dimensions
    getmaxyx(stdscr, h1, w1);
    fill_map();
    srand(time(0));
}

BombermanGame::~BombermanGame(){
    endwin();
}

void BombermanGame::fill_map(){
    player_object = std::make_shared<Player>(h1, w1);
    game_objects.push_back(player_object);

    create_walls();  
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
    std::pair<std::string, std::string> messages = std::make_pair("Game Over - You Lose!", "Press 'q' to quit. Your score: " + std::to_string(mult - 1));
    int16_t lose_screen_color_pair = 4;
    wbkgd(stdscr, COLOR_PAIR(lose_screen_color_pair));
    out(h1 / 2, (w1 - messages.first.size()) / 2, messages.first);
    out(h1 / 2 + 1, (w1 - messages.second.size()) / 2, messages.second);
}

void BombermanGame::play_music(sf::Music& music) {
    if (!music.openFromFile("../resources/nc_output.wav")) {
        logger.log("Cannot open music file");
        return;
    }
    music.play();
}

void BombermanGame::start_screen() {
    std::ifstream input("../resources/start_screen.txt");
    if (!input.is_open())
        throw std::runtime_error("Can not open the start_screen file");
    std::vector<std::string> message;
    std::string line;
    while (std::getline(input, line))
        message.push_back(line);

    show_message(message, 0, 8, h1, w1);
    show_message(message, 10, 18, h1, w1);
    show_message(message, 19, 26, h1, w1);
}

void BombermanGame::run_game() {
    int c;
    sf::Music music;
    play_music(music);
    start_screen();
    while ('q' != (c = getch())) {
        clear();

        if(player_object->is_dead){
            lose();
            continue;
        }

        if (music.getStatus() != sf::Music::Playing) {
            music.play();
        }
               
        render_border();
        render_objects();
        update_special_cells();
        update_objects(c);
        manage_objects(c);

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

int BombermanGame::get_enemy_count() {
    int count = 0;
    for(auto& obj : game_objects){
        if(obj->get_obj_name() == "Enemy"){
            count++;
        }
    }
    return count;
}

void BombermanGame::manage_objects(int key_pressed) {
    delete_dead_objects();
    
    // Bomb Creation
    if (key_pressed == ' ') {
        auto player_cords = player_object->get_cords();
        auto bomb_object = std::make_shared<Bomb>(player_cords.first, player_cords.second, now());
        game_objects.push_back(std::move(bomb_object));
    }

    //Enemy waves
    GameLogger logger("logs.txt");
    logger.log("AXAXAXA", get_enemy_count(), 228);
    if(!get_enemy_count()){
        for(size_t i = 0; i < mult; ++i){
            auto enemy_object = std::make_shared<Enemy>(10 + i, 10);
            game_objects.push_back(std::move(enemy_object));
        }
        mult*=2;
    }
}

void BombermanGame::create_walls(){
    size_t walls_num = h1 * w1 / 100;
    for(size_t i = 0; i < h1 - 2 ; ++i){
        for(size_t j = 0; j < w1 - 2; ++j)
            if(std::rand() % 100 < 5 && i != h1 / 2 && j != w1 / 2){
                auto wall_object = std::make_shared<Wall>(i, j);
                game_objects.push_back(std::move(wall_object));
            }
    }
    auto wall_object = std::make_shared<Wall>(h1 - 2, w1 - 2);
    game_objects.push_back(std::move(wall_object));
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
