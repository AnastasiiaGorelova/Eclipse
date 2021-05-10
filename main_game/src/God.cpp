#include "God.h"

void God::show_menu() {
    controller_out.show_menu(this);
}

void God::start_game() {
    game = std::make_unique<eclipse::Game>();
    controller_out.close_menu();
    controller_out.show_game_field(this);
    controller_out.show_name_enter_window(this);
    make_changes_in_out_controller();
}

void God::cancel_game() {
    game = nullptr;
    controller_out.close_menu();
}

void God::make_changes_in_out_controller() {
    int id = 0;
    bool flag = false;
    for (auto &i : game->changes) {
        if (flag) {
            break;
        }
        switch (i.action) {
            case eclipse::Delete_object:
                controller_out.delete_obj(i.id);
                break;
            case eclipse::Move_object:
                controller_out.move_obj(i.new_coordinates.first,
                                        i.new_coordinates.second, i.id);
                break;
            case eclipse::Create_ship:
                controller_out.set_obj(i.new_coordinates.first,
                                       i.new_coordinates.second, i.size, i.id,
                                       "ship");
                break;
            case eclipse::Create_asteroid:
                controller_out.set_obj(i.new_coordinates.first,
                                       i.new_coordinates.second, i.size, i.id,
                                       "asteroid");
                break;
            case eclipse::Create_shot:
                controller_out.set_obj(i.new_coordinates.first,
                                       i.new_coordinates.second, i.size, i.id,
                                       "shot");
                break;
            case eclipse::Create_coin:
                controller_out.set_obj(i.new_coordinates.first,
                                       i.new_coordinates.second, i.size, i.id,
                                       "coin");
                break;
            case eclipse::Create_heart:
                controller_out.set_obj(i.new_coordinates.first,
                                       i.new_coordinates.second, i.size, i.id,
                                       "heart");
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
                if (game->coins >= game->coins_to_buy_live) {
                    reverse(game->changes.begin(), game->changes.end());
                    game->changes.resize(game->changes.size() - id - 1);
                    reverse(game->changes.begin(), game->changes.end());
                    game->clear_field();
                    make_changes_in_out_controller();
                    show_buy_live_for_coins_window(game->coins_to_buy_live);
                    game->coins -= game->coins_to_buy_live;
                    controller_out.change_coins_counter(game->coins);
                    game->coins_to_buy_live += 5;
                } else {
                    flag = true;
                    game->changes.clear();
                    show_game_finish_window();
                    // finish game
                }
                break;
        }
        id++;
    }
    game->changes.clear();
}

void God::make_move_in_logic_and_ui() {
    auto direction = train.get_aggregated_changes();
    game->make_move(direction);
    make_changes_in_out_controller();
}

void God::make_shoot() const {
    game->shoot();
}

void God::select_game_controller(eclipse::Controllers controller_) {
    controller_out.close_selection_window();
    message_errors error = no_errors;
    switch (controller_) {
        case eclipse::Key:
            controller_in = new Key_Controller();  // NOLINT
            controller_in->set_God(this);
            break;
        case eclipse::Arduino: {
            ReadingFromPort::Ports my_ports;
            std::string port = my_ports.get_arduino_port();

            if (port == "There is no Arduino plugged into port") {
                error = arduino_setting_error;
            } else {
                controller_in = new ReadingFromPort::Arduino(port);  // NOLINT
                controller_in->set_God(this);
            }

        } break;
        default:
            break;
    }
    check_connection_message(error);
}

void God::show_game_finish_window() {
    delete_controller_in();
    controller_out.show_game_finish_window(this);
    cur_player.time = get_time();
    controller_out.close_game_field();
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
    controller_out.close_live_for_coins_window();
    controller_out.add_live();
    controller_out.start_timers();
    game->lives++;
}

void God::name_entered(const std::string &player_name) {
    controller_out.close_name_enter_window();
    controller_out.show_selection_window(this);
    cur_player.name = player_name;
}

void God::start_timers() {
    controller_out.start_timers();
}

void God::close_game_finish_window() {
    controller_out.close_game_finish_window();
}

void God::close_error_massage_window() {
    controller_out.close_error_massage_window();
}

void God::delete_controller_in() {
    if (dynamic_cast<Key_Controller *>(controller_in) != nullptr) {
        delete dynamic_cast<Key_Controller *>(controller_in);
        controller_in = nullptr;
    } else {
        // TODO  вряд ли делаю правильно, надо разобраться
        delete dynamic_cast<ReadingFromPort::Arduino *>(controller_in);
        controller_in = nullptr;
    }
}

void God::show_selection_window() {
    controller_out.show_selection_window(this);
}
