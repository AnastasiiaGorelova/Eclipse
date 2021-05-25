#include "arduino.h"
#include "God.h"
#include "game.h"

namespace ReadingFromPort {

Ports::Ports() : devices_found_(serial::list_ports()) {
}

std::string Ports::get_arduino_port() const {
    for (const auto &device : devices_found_) {
        if (device.description.find("Arduino") != std::string::npos) {
            return device.port;
        }
    }
    return "There is no Arduino plugged into port";
}

void Arduino::write_to_port() {
    //std::unique_lock l(m);
    std::cerr << "!!!!!write_to_port!!!!!" << std::endl;
    size_t bytes_wrote = serial_.write("1");
    std::cerr << "bytes_wrote: " << bytes_wrote << std::endl;
}

void Arduino::make_a_move_void() {
    while (keep_going) {
        //std::unique_lock l(m);
        std::string line;
        line = serial_.readline();  // get line from arduino
        if (line == "MENU\n") {
            std::cerr << "m" << std::endl;
            // TODO тыкнуть функцию выхода в меню

        } else if (line == "RIGHT\n") {
            std::cerr << "r" << std::endl;
            damn->train.pushed_button_right();  // тык

        } else if (line == "LEFT\n") {
            std::cerr << "l" << std::endl;
            damn->train.pushed_button_left();  // тык

        } else if (line == "NO\n") {
            std::cerr << "n" << std::endl;
            /*damn->controller_out.close_live_for_coins_window();
            damn->show_game_finish_window();*/
            damn->gamer_choice = God::stop_game;

        } else if (line == "YES\n") {
            std::cerr << "y" << std::endl;
            /*damn->add_life_and_restart_game(damn->game->coins);*/
            damn->gamer_choice = God::continue_game;

        } else {
            // std::cerr << "wtf??" << std::endl;
            continue;
        }
    }
}

void Arduino::start_thread() {
    ta = std::thread(&Arduino::make_a_move_void, this);
}

Arduino::Arduino(const std::string &port, uint32_t baudrate) {
    serial::Timeout timeout(
        serial::Timeout::simpleTimeout(serial::Timeout::max()));
    serial_.setBaudrate(baudrate);
    serial_.setPort(port);
    serial_.setTimeout(timeout);
    serial_.open();
    keep_going = true;
    this->start_thread();
}

Move Arduino::make_a_move() {
    std::string line;
    line = serial_.readline();  // get line from arduino
    if (line == "MENU\n") {
        // TODO тыкнуть функцию выхода в меню
        return menu;
    } else if (line == "RIGHT\n") {
        damn->train.pushed_button_right();  // тык
        std::cerr << "r" << std::endl;
        return right;
    } else if (line == "LEFT\n") {
        damn->train.pushed_button_left();  // тык
        std::cerr << "l" << std::endl;
        return left;
    } else {
        return exception;
    }
}

void Arduino::set_God(God *damn_) {
    damn = damn_;
}

Arduino::~Arduino() {
    keep_going = false;
    if (ta.joinable()) {
        ta.join();
    }
    serial_.close();
}

}  // namespace ReadingFromPort