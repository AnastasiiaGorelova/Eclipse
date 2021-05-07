#ifndef MAIN_GAME_GOD_H
#define MAIN_GAME_GOD_H

#include <memory>
#include "Key_Controller_.h"
#include "../include_in_controllers/arduino.h"
#include "../include_leaderboard/local_leaderboard.h"
#include "game.h"
#include "game_ui.h"

enum message_errors {
    no_errors,
    arduino_setting_error
};

class God {
public:
    std::unique_ptr<eclipse::Game> game;
    Controller_out controller_out;
    Player cur_player;
    Modification_store train;

    union {
        Key_Controller *key_controller;
        ReadingFromPort::Arduino *arduino_controller;
    } controller_in;

    //controller_out (qt)
    void show_menu();
    void show_game_finish_window();
    void close_game_finish_window();
    void show_buy_live_for_coins_window(int n = 5);
    void close_buy_live_for_coins_window();
    void close_error_massage_window();

    void make_changes_in_out_controller();

    //controller_in
    void select_game_controller(eclipse::Controllers controller_);
    void check_connection_message(message_errors error);
    std::string get_time();

    //for logic
    void make_shoot() const;

    //both
    void start_game();
    void cancel_game();
    void make_move_in_logic_and_ui();
    void stop_timers() const;
    void start_timers();
    void add_life_and_restart_game();
    void name_entered(const std::string &player_name);

    void delete_controller_in();

    void show_selection_window();
};

#endif// MAIN_GAME_GOD_H
