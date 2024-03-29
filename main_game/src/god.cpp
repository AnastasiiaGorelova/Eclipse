#include "god.h"

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
    for (auto &i : game->changes) {
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
            case eclipse::Create_alien:
                controller_out.set_obj(i.new_coordinates.first,
                                       i.new_coordinates.second, i.size, i.id,
                                       "monster");
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
            case eclipse::Create_alien_shot:
                controller_out.set_obj(i.new_coordinates.first,
                                       i.new_coordinates.second, i.size, i.id,
                                       "monster_shot");
                break;
            case eclipse::Create_diamond:
                controller_out.set_obj(i.new_coordinates.first,
                                       i.new_coordinates.second, i.size, i.id,
                                       "diamond");
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
            case eclipse::Create_alien_heart:
                controller_out.set_obj(i.new_coordinates.first,
                                       i.new_coordinates.second, i.size, i.id,
                                       "monster_heart");
                break;
            case eclipse::Break_asteroid:
                controller_out.change_obj_pic(i.id, i.size);
                break;
            case eclipse::Slow_down_game:
                controller_out.slow_down_game();
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
        }
        id++;
    }
    game->changes.clear();
}

void God::finish_or_continue_game() {
    make_changes_in_out_controller();
    if (!game->get_game_state()) {
        stop_timers();
        if (game->coins >= game->coins_to_buy_live) {
            game->coins -= game->coins_to_buy_live;
            show_buy_live_for_coins_window(game->coins_to_buy_live,
                                           game->coins);
            game->coins_to_buy_live += 3;
        } else {
            show_game_finish_window();
        }
    }
}

void God::make_move_in_logic_and_ui() {
    auto direction = modificationStore.get_aggregated_changes();
    if (direction == eclipse::kChangeGameState) {
        controller_out.stop_timers();
        controller_out.game_pause();
        return;
    }
    game->make_move(direction);
    finish_or_continue_game();
}

void God::make_shoot() const {
    game->shoot();
}

void God::select_game_controller(eclipse::Controllers controller_) {
    controller_out.close_selection_window();
    message_errors error = no_errors;
    switch (controller_) {
        case eclipse::Key:
            controller_in = new Key_Controller();
            controller_in->set_God(this);
            break;
        case eclipse::Arduino: {
            ReadingFromPort::Ports my_ports;
            std::string port = my_ports.get_arduino_port();

            if (port == "There is no Arduino plugged into port") {
                error = arduino_setting_error;
            } else {
                controller_in = new ReadingFromPort::Arduino(port);
                controller_in->set_God(this);
            }

        } break;
        default:
            break;
    }
    check_connection_message(error);
}

void God::show_game_finish_window() {
    game_speed = 65;
    controller_out.delete_obj(game->get_ship_id());
    delete_controller_in();
    cur_player.time = get_time();
    update_local_leaderboard(cur_player);                        ///
    std::thread t(upload_json_from_server_to_file, cur_player);  ///
    t.detach();
    controller_out.show_game_finish_window(this);
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

void God::show_buy_live_for_coins_window(int n, int k) {
    controller_out.show_live_for_coins_window(n, k, this);
    if (dynamic_cast<ReadingFromPort::Arduino *>(controller_in) != nullptr) {
        controller_in->write_to_port_for_coins();
    }
}

void God::stop_timers() const {
    controller_out.stop_timers();
}

void God::add_life_and_restart_game(int coins) {
    game->game_state = eclipse::kOngoing;
    gamer_choice = wait;

    controller_out.change_coins_counter(coins);
    controller_out.close_live_for_coins_window();
    controller_out.add_live();
    controller_out.start_timers();
    game->lives++;
    game->game_state = eclipse::kOngoing;
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
        delete dynamic_cast<ReadingFromPort::Arduino *>(controller_in);
        controller_in = nullptr;
    }
}

void God::show_selection_window() {
    controller_out.show_selection_window(this);
}

void God::show_leaderboard(int param) {
    controller_out.show_leaderboard(param);
}

void God::show_legend_window() {
    controller_out.show_legend_window();
}

bool God::check_field_and_set_monster() {
    auto direction = modificationStore.get_aggregated_changes();
    if (!game->check_the_field()) {
        game->move_objects_without_generating(direction);
        finish_or_continue_game();
        return false;
    }
    game->set_alien();
    finish_or_continue_game();
    return true;
}

void God::make_move_in_logic_and_ui_with_monster() {
    auto direction = modificationStore.get_aggregated_changes();
    if (direction == eclipse::kChangeGameState) {
        controller_out.stop_timers();
        controller_out.game_pause();
        return;
    }
    game->make_move_with_alien(direction);
    finish_or_continue_game();
}

void God::change_game_speed(int diff) {
    game_speed += diff;
    if (game_speed < 65) {
        game->check_for_speed = false;
    } else {
        game->check_for_speed = true;
    }
}
