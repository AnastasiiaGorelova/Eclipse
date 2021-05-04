#ifndef MAIN_GAME_GOD_H
#define MAIN_GAME_GOD_H

#include <name_enter_qt.h>
#include <memory>
#include "Key_Controller_.h"
#include "../include_in_controllers/arduino.h"
#include "Selection.h"
#include "../include_leaderboard/local_leaderboard.h"
#include "game.h"
#include "game_fwd.h"
#include "game_window.h"
#include "main_window.h"
#include "game_finish_window.h"
#include <name_enter_qt.h>
#include <error_massage_window.h>
#include <buy_live_for_coins_window.h>

enum message_errors {
    no_errors,
    arduino_setting_error
};

class God {
public:
    std::unique_ptr<eclipse::Game> game;
    game_window *menu;
    main_window *game_view;
    Selection *selection_window;
    name_enter_qt* new_name;
    game_finish_window *finish_window;
    error_massage_window* error_massage_window_;
    buy_live_for_coins_window * buy_live_for_coins_window_;
    Player cur_player;

    union {
        Key_Controller *key_controller;
        ReadingFromPort::Arduino *arduino_controller;
    } controller;

    //controller_out (qt)
    void show_menu();
    void close_menu() const;
    void show_game_field();
    void close_game_field() const;
    void set_object(int x, int y, int size, const std::string &hash, const std::string &object_name) const;
    void move_object(int x, int y, const std::string &hash) const;
    void delete_object(const std::string &hash) const;
    void decrease_lives_ui() const;
    std::string get_time() const;
    void set_crack_asteroid_pic(const std::string &hash, int size) const;
    void show_selection_window();
    void finish_game();
    void change_coins_counter_ui(int count) const;
    void show_buy_live_for_coins_window(int n = 5);

    //controllers_in
    void select_game_controller(eclipse::Controllers controller_);
    void arduino_setting_error_massage();
    void connection_message(int connected, message_errors error);

    //for logic
    void clicked_on_start();
    void clicked_on_exit();
    void make_move_in_logic();

    //both
    void make_changes_in_qt();
    void shoot_in_God() const;

    void add_life_and_restart_game() const;

    void stop_timers() const;
};

#endif// MAIN_GAME_GOD_H
