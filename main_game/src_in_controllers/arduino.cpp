#include "arduino.h"
#include "god.h"

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

void Arduino::write_to_port_for_coins() {
    std::string change_arduino_screen_coins = "coins";
    size_t bytes_wrote = serial_.write(change_arduino_screen_coins);
}

void Arduino::write_to_port_for_pause() {
    std::string change_arduino_screen_pause = "pause";
    size_t bytes_wrote = serial_.write(change_arduino_screen_pause);
    while (!keep_going) {
        std::string line;
        line = serial_.readline();  // get line from arduino
        if (line == "CONTINUE\n") {
            serial_.flush();
            damn->train.pushed_pause_or_play();
            keep_going = true;
            return;
        }
    }
}

void Arduino::make_a_move() {
    while (keep_going) {
        std::string line;
        line = serial_.readline();  // get line from arduino
        if (line == "PAUSE\n") {
            serial_.flush();
            damn->train.pushed_pause_or_play();
            keep_going = false;
            write_to_port_for_pause();

        } else if (line == "RIGHT\n") {
            serial_.flush();
            damn->train.pushed_button_right();  // тык

        } else if (line == "LEFT\n") {
            serial_.flush();
            damn->train.pushed_button_left();  // тык

        } else if (line == "NO\n") {
            serial_.flush();
            damn->gamer_choice = God::stop_game;
            keep_going = false;

        } else if (line == "YES\n") {
            serial_.flush();
            damn->gamer_choice = God::continue_game;

        } else {
            continue;
        }
    }
}

void Arduino::start_thread() {
    ta = std::thread(&Arduino::make_a_move, this);
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