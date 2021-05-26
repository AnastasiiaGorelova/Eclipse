#include "game_ui.h"

#define local_leaderboard 0
#define server_leaderboard 1

void Controller_out::show_menu(God* damn) {
    menu_window_ = new game_window();
    menu_window_-> set_god(damn);
    menu_window_->show_menu_first();
}

void Controller_out::close_menu() {
    menu_window_->close();
    menu_window_->deleteLater();
    menu_window_ = nullptr;
}

void Controller_out::show_game_field(God* damn) {
    game_window_ = new main_window();
    game_window_->make_field();
    game_window_->set_God(damn);
    game_window_->set_lives();
    game_window_->set_timer();
    game_window_->set_coins_counter();
    game_window_->show();
}

void Controller_out::close_game_field() {
    game_window_->close();
    game_window_->deleteLater();
    game_window_ = nullptr;
}

void Controller_out::show_name_enter_window(God* damn) {
    name_enter_window_ = new name_enter_qt();
    name_enter_window_->set_god(damn);
    name_enter_window_->show();
}

void Controller_out::close_name_enter_window() {
    name_enter_window_->close();
    name_enter_window_->deleteLater();
    name_enter_window_ = nullptr;
}

void Controller_out::show_selection_window(God* damn) {
    selection_window_ = new Selection();
    selection_window_->set_god(damn);
    selection_window_->show();
}

void Controller_out::close_selection_window() {
    selection_window_->close();
    selection_window_->deleteLater();
    selection_window_ = nullptr;
}

void Controller_out::set_obj(int x,
                             int y,
                             int size,
                             const std::string &hash,
                             const std::string &object_name) const {
    game_window_->set(x, y, size, hash, object_name);
}

void Controller_out::move_obj(int x, int y, const std::string &hash) const {
    game_window_->move(x, y, hash);
}

void Controller_out::delete_obj(const std::string &hash) const {
    game_window_->delete_obj(hash);
}

void Controller_out::change_obj_pic(const std::string &hash, int size) const {
    game_window_->change_asteroid_crack(hash, size);
}

void Controller_out::show_game_finish_window(God* damn) {
    game_finish_window_ = new game_finish_window();
    game_finish_window_->set_god(damn);
    game_finish_window_->show();
}

std::pair<std::string, std::string> Controller_out::get_current_time() {
    return game_window_->get_cur_time();
}

void Controller_out::show_error_massage_window_arduino(God * damn) {
    error_massage_window_ = new error_massage_window();
    error_massage_window_->arduino_setting_error();
    error_massage_window_->set_god(damn);
    error_massage_window_->show();
}

void Controller_out::add_live() {
    game_window_->add_life();
}

void Controller_out::start_game_preview() {
    game_window_->start_timer_for_beginning();
}

void Controller_out::change_coins_counter(int count) const {
    game_window_->change_coins_counter(count);
}

void Controller_out::delete_live() {
    game_window_->decrease_lives();
}

void Controller_out::stop_timers() const {
    game_window_->timer->stop();
    game_window_->timer_for_shots->stop();
    game_window_->timer_for_ticks->stop();
    game_window_->timer_for_monster->stop();
}

void Controller_out::show_live_for_coins_window(int n, int k, God* damn) {
    buy_live_for_coins_window_ = new buy_live_for_coins_window();
    buy_live_for_coins_window_->set_god(damn);
    buy_live_for_coins_window_->set_window_options();
    buy_live_for_coins_window_->buy_for_n_coins(n, k);
    buy_live_for_coins_window_->show();
}

void Controller_out::start_timers() {
    game_window_->start_timer();
}

void Controller_out::close_game_finish_window() {
    game_finish_window_->close();
    game_finish_window_->deleteLater();
    game_finish_window_ = nullptr;
}

void Controller_out::close_live_for_coins_window() {
    buy_live_for_coins_window_->close();
    buy_live_for_coins_window_->deleteLater();
    buy_live_for_coins_window_ = nullptr;
}

void Controller_out::close_error_massage_window() {
    error_massage_window_->close();
    error_massage_window_->deleteLater();
    error_massage_window_ = nullptr;
}

void Controller_out::show_leaderboard(int param) {
    local_leaderboard_ui_ = new local_leaderboard_ui();
    if (param == local_leaderboard) {
        local_leaderboard_ui_->download_local_leaderboard();
    } else if (param == server_leaderboard){
        local_leaderboard_ui_->download_server_leaderboard();
    }
    local_leaderboard_ui_->show();
}

void Controller_out::show_legend_window() {
    legend_window_ = new legend_window();
    legend_window_->show();
}

void Controller_out::game_pause() {
    game_window_->set_game_on_pause();
}



