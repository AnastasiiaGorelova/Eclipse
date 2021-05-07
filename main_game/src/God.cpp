
#include "God.h"
#include <unistd.h>

void God::show_menu() {
    controller_out.show_menu(this);
}

void God::close_menu() const {
    controller_out.close_menu();
}

void God::show_game_field() {
    controller_out.show_game_field(this);
}

void God::close_game_field() const {
    stop_timers();
    controller_out.close_game_field();
}

void God::show_enter_name_window() {
    controller_out.show_name_enter_window(this);
}

void God::close_enter_name_window() const {
    controller_out.close_name_enter_window();
}

void God::show_selection_window() {
    controller_out.show_selection_window(this);
}

void God::close_selection_window() const {
    controller_out.close_selection_window();
}

void God::start_game() {
    game = std::make_unique<eclipse::Game>();
    close_menu();
    show_game_field();
    show_enter_name_window();
    make_changes_in_out_controller();
}

void God::cancel_game() {
    game = nullptr;
    close_menu();
}

void God::make_changes_in_out_controller() {
    for (auto &i : game->changes) {
        switch (i.action) {
            case eclipse::Delete_object:
                controller_out.delete_obj(i.id);
                break;
            case eclipse::Move_object:
                controller_out.move_obj(i.new_coordinates.first, i.new_coordinates.second,
                            i.id);
                break;
            case eclipse::Create_ship:
                controller_out.set_obj(i.new_coordinates.first, i.new_coordinates.second,
                           i.size, i.id, "ship");
                break;
            case eclipse::Create_asteroid:
                controller_out.set_obj(i.new_coordinates.first, i.new_coordinates.second,
                           i.size, i.id, "asteroid");
                break;
            case eclipse::Create_shot:
                controller_out.set_obj(i.new_coordinates.first, i.new_coordinates.second,
                           i.size, i.id, "shot");
                break;
            case eclipse::Create_coin:
                controller_out.set_obj(i.new_coordinates.first, i.new_coordinates.second,
                           i.size, i.id, "coin");
                break;
            case eclipse::Create_heart:
                controller_out.set_obj(i.new_coordinates.first, i.new_coordinates.second,
                           i.size, i.id, "heart");
                break;
            case eclipse::Break_asteroid:
                controller_out.change_obj_pic(i.id, i.size);
                break;
            case eclipse::Add_coin:
                controller_out.change_coins_counter(game->coins);
                break;
            case eclipse::Add_heart:
                controller_out.add_live();
                break;
            case eclipse::Decrease_lives:
                controller_out.delete_live();
                break;
            case eclipse::Finish_game:
                controller_out.delete_live();
                stop_timers();
                game->changes.clear();
                game->clear_field();
                make_changes_in_out_controller();
                show_buy_live_for_coins_window();
                break;
        }
    }
    game->changes.clear();
}

void God::make_move_in_logic_and_ui() {
    auto direction = train.give_changes();
    game->make_move(direction);
    make_changes_in_out_controller();
}

void God::make_shoot() const {
    game->shoot();
}

void God::select_game_controller(eclipse::Controllers controller_) {
    close_selection_window();
    message_errors error = no_errors;
    switch (controller_) {
        case eclipse::Key:
            controller_in.key_controller = new Key_Controller();
            controller_in.key_controller->set_God(this);
            break;
        case eclipse::Arduino: {
            /*ReadingFromPort::Ports my_ports;
            std::string port = my_ports.get_arduino_port();

            if (port == "There is no Arduino plugged into port") {
                error = arduino_setting_error;
            } else {
                controller_in.arduino_controller =
                        new ReadingFromPort::Arduino(port);
                auto worker = [&]() {
                    while (true) {
                        controller_in.arduino_controller->make_a_move();
                    }
                };
                std::thread ta(worker);
                ta.detach();
            }*/

        } break;
        default:
            break;
    }
    check_connection_message(error);
}

void God::show_game_finish_window() {
    controller_out.show_game_finish_window(this);
    cur_player.time = get_time();

    //НЕ ТУТ
    close_game_field();
}

std::string God::get_time() {
    auto [min, sec] = controller_out.get_current_time();
    return min + ":" + sec;
}


void God::check_connection_message(message_errors error) {
    switch (error) {
        case no_errors:
            controller_out.start_game_preview();
            break;
        case arduino_setting_error:
            controller_out.show_error_massage_window_arduino(this);
            break;
    }
}

void God::show_buy_live_for_coins_window(int n) {
    controller_out.show_live_for_coins_window(n, this);
}

void God::stop_timers() const {
    controller_out.stop_timers();
}

void God::add_life_and_restart_game() {
    controller_out.start_timers();
    controller_out.add_live();
    game->lives++;
}

void God::name_entered(const std::string &player_name) {
    close_enter_name_window();
    show_selection_window();
    cur_player.name = player_name;
}

void God::start_timers() {
    controller_out.start_timers();
}

