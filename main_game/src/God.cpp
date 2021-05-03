#include "God.h"
#include "game.h"
#include "game_fwd.h"
#include <Modification_store.h>
#include <iostream>
#include <memory>
#include "name_enter_qt.h"

extern Modification_store train;

void God::show_menu() {
    menu = new game_window();
    menu->show_menu_first();
}

void God::close_menu() const {
    menu->close();
}

void God::show_game_field() {
    game_view = new main_window();
    game_view->make_field();
    menu->hide();
    game_view->show();
    new_name = new name_enter_qt();
    new_name->show();
}

void God::show_selection_window() {
    selection_window = new Selection();
    selection_window->show();
}

void God::close_game_field() const {
    game_view->close();
    menu->show();
}

void God::set_object(int x,
                     int y,
                     int size,
                     const std::string &hash,
                     const std::string &object_name) const {
    game_view->set(x, y, size, hash, object_name);
}

void God::move_object(int x, int y, const std::string &hash) const {
    game_view->move(x, y, hash);
}

void God::delete_object(const std::string &hash) const {
    game_view->delete_obj(hash);
}

void God::clicked_on_start() {
    game = std::make_unique<eclipse::Game>();

    close_menu();
    show_game_field();
    make_changes_in_qt();

    game_view->set_lives();
    game_view->set_timer();
}

void God::clicked_on_exit() {
    game = nullptr;
    //просто вывести таймер??
    close_menu();
}

void God::make_changes_in_qt() const {
    for (auto &i : game->changes) {
        switch (i.action) {
            case eclipse::Delete_object:
                delete_object(i.id);
                break;
            case eclipse::Move_object:
                move_object(i.new_coordinates.first, i.new_coordinates.second,
                            i.id);
                break;
            case eclipse::Create_ship:
                set_object(i.new_coordinates.first, i.new_coordinates.second,
                           i.size, i.id, "ship");
                break;
            case eclipse::Create_asteroid:
                set_object(i.new_coordinates.first, i.new_coordinates.second,
                           i.size, i.id, "asteroid");
                break;
            case eclipse::Create_shot:
                set_object(i.new_coordinates.first, i.new_coordinates.second,
                           i.size, i.id, "shot");
                break;
            case eclipse::Break_asteroid:
                set_crack_asteroid_pic(i.id, i.size);
                break;
            case eclipse::Decrease_lives:
                decrease_lives_ui();
                break;
            case eclipse::Finish_game:
                decrease_lives_ui();
                std::cerr << "LOSER ";
                //close_game_field();
                //"вы проиграли" --> вывести результат
                break;
        }
    }
    game->changes.clear();
}

void God::make_move_in_logic() const {
    auto [direction, steps] = train.give_changes();
    game->make_move(direction);
    make_changes_in_qt();
}

void God::shoot_in_God() const {
    game->shoot();
}

void God::select_game_controller(eclipse::Controllers controller_) {
    switch (controller_) {
        case eclipse::Key:
            controller.key_controller = new Key_Controller();
            break;
        case eclipse::Arduino:
            //тут можно создать все необходимое для контроллера ардуино
            break;
        default:
            break;
    }
    game_view->start_timer();
}

void God::decrease_lives_ui() const {
    game_view->decrease_lives();
}

std::string God::get_time() const {
    auto [min, sec] = game_view->get_cur_time();
    return min + ":" + sec;
}

void God::set_crack_asteroid_pic(const std::string &hash, int size) const {
    game_view->change_asteroid_crack(hash, size);
}
