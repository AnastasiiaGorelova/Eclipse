#include "God.h"
#include <Modification_store.h>
#include <iostream>
#include <memory>
#include "../include_in_controllers/arduino.h"
#include "game.h"
#include "game_fwd.h"
#include "name_enter_qt.h"

extern Modification_store train;

void God::show_menu() {
    menu = new game_window();  // NOLINT
    menu->show_menu_first();
}

void God::close_menu() const {
    menu->close();
}

void God::show_game_field() {
    game_view = new main_window();  // NOLINT
    game_view->make_field();
    menu->hide();
    game_view->show();
    selection_window = new Selection();  // NOLINT
    new_name = new name_enter_qt();
    new_name->show();
}

void God::show_selection_window() {
    // delete selection_window;

    selection_window = new Selection();
    selection_window->show();
}

void God::close_game_field() const {
    game_view->timer->stop();
    game_view->timer_for_shots->stop();
    game_view->timer_for_ticks->stop();
    game_view->close();
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

void God::make_changes_in_qt() {
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
                finish_game();
                break;
        }
    }
    game->changes.clear();
}

void God::make_move_in_logic() {
    auto [direction, steps] = train.give_changes();
    game->make_move(direction);
    make_changes_in_qt();
}

void God::shoot_in_God() const {
    game->shoot();
}

void God::select_game_controller(eclipse::Controllers controller_) {
    int connection = 1;
    message_errors error = no_errors;
    switch (controller_) {
        case eclipse::Key:
            controller.key_controller = new Key_Controller();
            break;
        case eclipse::Arduino: {
            ReadingFromPort::Ports my_ports;
            std::string port = my_ports.get_arduino_port();

            if (port == "There is no Arduino plugged into port") {
                connection = 0;
                error = arduino_setting_error;
            } else {
                controller.arduino_controller =
                    new ReadingFromPort::Arduino(port);
                auto worker = [&]() {
                    while (true) {
                        controller.arduino_controller->make_a_move();
                    }
                };
                std::thread ta(worker);
                ta.detach();
            }

        } break;
        default:
            break;
    }
    connection_message(connection, error);
}

void God::decrease_lives_ui() const {
    game_view->decrease_lives();
}

void God::set_crack_asteroid_pic(const std::string &hash, int size) const {
    game_view->change_asteroid_crack(hash, size);
}

void God::finish_game() {
    finish_window = new game_finish_window();
    cur_player.time = get_time();
    close_game_field();
    finish_window->show();
}

std::string God::get_time() const {
    auto [min, sec] = game_view->get_cur_time();
    return min + ":" + sec;
}

void God::arduino_setting_error_massage() {
    error_massage_window_ = new error_massage_window();
    error_massage_window_->arduino_setting_error();
    error_massage_window_->show();
}

void God::connection_message(int connected, message_errors error) {
    if (connected) {
        game_view->start_timer();
    } else {
        switch (error) {
            case arduino_setting_error:
                arduino_setting_error_massage();
                break;
        }
    }
}
