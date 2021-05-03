#ifndef MAIN_GAME_GOD_H
#define MAIN_GAME_GOD_H

#include <memory>
#include "../include_in_controllers/arduino.h"
#include "Key_Controller_.h"
#include "Selection.h"
#include "game.h"
#include "game_fwd.h"
#include "game_window.h"
#include "main_window.h"

class God {
public:
    std::unique_ptr<eclipse::Game> game;
    game_window *menu;
    main_window *game_view;
    Selection *selection_window;

    union {
        Key_Controller *key_controller;
        // one_more_for_arduino
        ReadingFromPort::Arduino *arduino_controller;
    } controller;

    // God(const eclipse::Game &game):
    // game(std::make_unique<eclipse::Game>(game)){}

    // controller_out (qt)
    void show_menu();
    void close_menu() const;
    void show_game_field();
    void close_game_field() const;
    void set_object(int x,
                    int y,
                    int size,
                    const std::string &hash,
                    const std::string &object_name) const;
    void move_object(int x, int y, const std::string &hash) const;
    void delete_object(const std::string &hash) const;
    void decrease_lives_ui() const;

    // controllers_in
    void select_game_controller(
        eclipse::Controllers controller_);  //запрос приходит из диалогового
                                            //окна выбора контроллера

    // for logic
    void clicked_on_start();
    void clicked_on_exit();
    void make_move_in_logic()
        const;  //принимает измнения из стора, работает на тиках

    // both
    void make_changes_in_qt() const;  //боженька принимает изменения из логики,
                                      //тыкает qt подвинуть/создать объект
    // timer?

    void shoot_in_God() const;
};

#endif  // MAIN_GAME_GOD_H
