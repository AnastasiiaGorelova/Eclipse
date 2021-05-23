#ifndef MAIN_GAME_GOD_H
#define MAIN_GAME_GOD_H

#include <memory>
#include "../include_in_controllers/arduino.h"
#include "../include_leaderboard/local_leaderboard.h"
#include "Key_Controller_.h"
#include "Modification_store.h"
#include "controllers_in.h"
#include "game.h"
#include "game_ui.h"

enum message_errors { no_errors, arduino_setting_error };

class God {
public:
    std::unique_ptr<eclipse::Game> game;
    Controller_out controller_out;
    Controller_in *controller_in;
    Player cur_player;
    Modification_store train;

    // controller_out (qt)
    void show_menu();
    void show_game_finish_window();
    void close_game_finish_window();
    void show_buy_live_for_coins_window(int n = 5, int k = 0);
    void close_error_massage_window();
    void show_selection_window();

    void make_changes_in_out_controller();

    // controller_in
    void select_game_controller(eclipse::Controllers controller_);
    void check_connection_message(message_errors error);
    std::string get_time();
    void delete_controller_in();

    // for logic
    void make_shoot() const;

    // both
    void start_game();
    void cancel_game();
    void make_move_in_logic_and_ui();
    void stop_timers() const;
    void start_timers();
    void add_life_and_restart_game(int coins);
    void name_entered(const std::string &player_name);
    void finish_or_continue_game();

    void show_local_leaderboard();

    void show_legend_window();
};

#endif  // MAIN_GAME_GOD_H
