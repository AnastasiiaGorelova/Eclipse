#ifndef MAIN_GAME_GOD_H
#define MAIN_GAME_GOD_H

#include "game.h"
#include "game_fwd.h"
#include "game_window.h"
#include "main_window.h"
#include <memory>

extern std::unique_ptr<eclipse::Game> game;

class God {
public:
    //for qt
    static void show_menu();
    static void close_menu();
    static void show_game_field();
    static void close_game_field();
    static void set_object(int x, int y, int size, const std::string &hash, const std::string &object_name);
    static void move_object(int x, int y, const std::string &hash);
    static void delete_object(const std::string &hash);

    //for logic
    static void clicked_on_start();
    static void clicked_on_exit();
    static void pushed_button_left();
    static void pushed_button_right();
    static void make_move_in_logic();//раз в какое-то время меняем картинку, если ничего не нажали

    //both
    static void make_changes_in_qt();//боженька приниает изменения из логики, тыкает qt подвинуть/создать объект
    //timer?
};

#endif//MAIN_GAME_GOD_H
