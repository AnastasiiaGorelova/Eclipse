#include "include_qt/God.h"
#include "game.h"
#include "game_fwd.h"

extern game_window *menu;
extern main_window *game_view;

void God::show_menu() {
    menu = new game_window();
    menu->show_menu_first();
}

void God::close_menu() {
    menu->close();
}

void God::show_game_field() {
    game_view = new main_window();
    game_view->make_field();
    menu->hide();
    game_view->show();
}

void God::close_game_field() {
    game_view->close();
    menu->show();
}

void God::set_object(int x, int y, int size, const std::string &hash, const std::string &object_name) {
    game_view->set(x, y, size, hash, object_name);
}

void God::move_object(int x, int y, const std::string &hash) {
    game_view->move(x, y, hash);
}

void God::delete_object(const std::string &hash) {
    game_view->delete_obj(hash);
}


void God::clicked_on_start() {
    //тыкнутся функции в логике как-то запускающие игру для логики
    //запустить таймер, создать объект Game??

    //JUST FOR DEBUG
    close_menu();
    show_game_field();
    set_object(500, 200, 100, "aaa", "Ship");
    /*move_object(200, 200, "aaa");
    delete_object("aaa");*/
}

void God::clicked_on_exit() {

    //просто вывести таймер??
    //JUST FOR DEBUG
    close_menu();
}

void God::pushed_button_left(eclipse::Game &game) {//в qt передать объект Game
    game.make_move(eclipse::kLeft);

    //JUST FOR DEBUG
    move_object(200, 200, "aaa");
}

void God::pushed_button_right(eclipse::Game &game) {
    game.make_move(eclipse::kRight);

    //JUST FOR DEBUG
    move_object(400, 200, "aaa");
}

void God::make_move_in_logic(eclipse::Game &game) {
    game.make_move();
}
