#include "../include_in_controllers/arduino.h"
#include "God.h"

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

Arduino::Arduino(const std::string &port, uint32_t baudrate) {
    serial::Timeout timeout(
        serial::Timeout::simpleTimeout(serial::Timeout::max()));
    serial_.setBaudrate(baudrate);
    serial_.setPort(port);
    serial_.setTimeout(timeout);
    serial_.open();
    //                auto worker = [&]() {
//                    while (true) {
//                        controller_in->make_a_move();
//                    }
//                };
//                std::thread ta(worker);
//                ta.detach();
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
    serial_.close();
}

}  // namespace ReadingFromPort