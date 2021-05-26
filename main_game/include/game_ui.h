
#ifndef MAIN_GAME_GAME_UI_H
#define MAIN_GAME_GAME_UI_H

#include <game_window.h>
#include <selection.h>
#include <name_enter_qt.h>
#include <game_finish_window.h>
#include <error_massage_window.h>
#include <buy_live_for_coins_window.h>
#include <leaderboard_ui.h>
#include <legend_window.h>

class Controller_out {
    game_window *menu_window_;
    main_window *game_window_;
    Selection *selection_window_;
    name_enter_qt* name_enter_window_;
    game_finish_window *game_finish_window_;
    error_massage_window* error_massage_window_;
    buy_live_for_coins_window * buy_live_for_coins_window_;
    local_leaderboard_ui * local_leaderboard_ui_;
    legend_window * legend_window_;

public:
    //показ - скрытие окон отображения
    void show_menu(God* damn);
    void close_menu();
    void show_game_field(God* damn);
    void close_game_field();
    void show_name_enter_window(God* damn);
    void close_name_enter_window();
    void show_selection_window(God* damn);
    void close_selection_window();
    void show_game_finish_window(God* damn);
    void close_game_finish_window();
    void show_error_massage_window_arduino(God* damn);
    void close_error_massage_window();
    void start_game_preview();
    void show_live_for_coins_window(int n, int k, God* damn);
    void close_live_for_coins_window();
    void show_leaderboard(int param);
    void show_legend_window();

    //отрисовка - перемещение - удаление объектов
    void set_obj(int x,
                 int y,
                 int size,
                 const std::string &hash,
                 const std::string &object_name) const;
    void move_obj(int x, int y, const std::string &hash) const;
    void delete_obj(const std::string &basicString) const;
    void change_obj_pic(const std::string &hash, int size) const;
    void add_live();
    void delete_live();
    void change_coins_counter(int count) const;

    //вспомогательные функцию
    std::pair<std::string, std::string> get_current_time();
    void start_timers();
    void stop_timers() const;
    void game_pause();
};

#endif //MAIN_GAME_GAME_UI_H
