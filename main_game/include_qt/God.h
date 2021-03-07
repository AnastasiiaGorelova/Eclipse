#ifndef MAIN_GAME_GOD_H
#define MAIN_GAME_GOD_H

#include <memory>
#include "game.h"
#include "game_fwd.h"
#include "game_window.h"
#include "main_window.h"

class God {
public:
    std::unique_ptr<eclipse::Game> game;
    game_window *menu;
    main_window *game_view;

    //for qt
    void show_menu();
    void close_menu();
    void show_game_field();
    void close_game_field();
    void set_object(int x, int y, int size, const std::string &hash, const std::string &object_name);
    void move_object(int x, int y, const std::string &hash);
    void delete_object(const std::string &hash);

    //for logic
    void clicked_on_start();
    void clicked_on_exit();
    void pushed_button_left();
    void pushed_button_right();
    void make_move_in_logic();//раз в какое-то время меняем картинку, если ничего не нажали

    //both
    void make_changes_in_qt();//боженька приниает изменения из логики, тыкает qt подвинуть/создать объект
    //timer?

};

#endif  // MAIN_GAME_GOD_H
