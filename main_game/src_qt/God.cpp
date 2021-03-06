#include "include_qt/God.h"
#include <memory>
#include "game.h"
#include "game_fwd.h"

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

void God::set_object(int x,
                     int y,
                     int size,
                     const std::string &hash,
                     const std::string &object_name) {
    game_view->set(x, y, size, hash, object_name);
}

void God::move_object(int x, int y, const std::string &hash) {
    game_view->move(x, y, hash);
}

void God::delete_object(const std::string &hash) {
    game_view->delete_obj(hash);
}

void God::clicked_on_start() {
    game = std::make_unique<eclipse::Game>();  //создаем новую игру
    //запустить таймер???

    // JUST FOR DEBUG
    close_menu();
    show_game_field();
    set_object(500, 200, 125, "aaa", "Ship");
    set_object(500, 200, 100, "bbb", "Big Asteroid");
    game_view->set_lives();
    game_view->set_timer();
    /*move_object(200, 200, "aaa");
    delete_object("aaa");*/
}

void God::clicked_on_exit() {
    game = nullptr;
    //просто вывести таймер??
    // JUST FOR DEBUG
    close_menu();
}

void God::pushed_button_left() {
    game->make_move(eclipse::kLeft);

    // JUST FOR DEBUG
    move_object(200, 450, "aaa");
}

void God::pushed_button_right() {
    game->make_move(eclipse::kRight);

    // JUST FOR DEBUG
    move_object(350, 450, "aaa");
}

void God::make_move_in_logic() {  //если из qt не пришло право/лево, то просто
                                  //запускаем эту функцию раз в какое-то время в
                                  //таймере
    game->make_move();
}

void God::make_changes_in_qt() {
    for (auto &i : game->changes) {
        if (i.object_name.empty()) {
            move_object(i.new_coordinates.first, i.new_coordinates.second,
                        i.id);
        } else {
            set_object(i.new_coordinates.first, i.new_coordinates.second,
                       i.size, i.id, i.object_name);
        }
    }
    game->changes.clear();
}
