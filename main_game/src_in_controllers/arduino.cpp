#include "../include_in_controllers/arduino.h"
#include "Key_Controller_.h"

extern Modification_store train;

namespace ReadingFromPort {

Ports::Ports() : devices_found_(serial::list_ports()) {
}

std::string Ports::get_arduino_port() const {
    for (const auto &device : devices_found_) {
        if (device.description.find("Arduino") != std::string::npos) {
            return device.port;
        }
    }
    throw std::runtime_error("There is no Arduino plugged into port");
    // TODO окошко предупреждение, что ардуинка не подключена
}

Arduino::Arduino(const std::string &port, uint32_t baudrate) {
    serial::Timeout timeout(
        serial::Timeout::simpleTimeout(serial::Timeout::max()));
    serial_.setBaudrate(baudrate);
    serial_.setPort(port);
    serial_.setTimeout(timeout);
    serial_.open();
}

Move Arduino::make_a_move() {
    std::string line;
    line = serial_.readline();  // get line from arduino
    if (line == "MENU\n") {
        //TODO тыкнуть функцию выхода в меню
        return menu;
    } else if (line == "RIGHT\n") {
        train.pushed_button_right(); // тык
        std::cerr << "r" << std::endl;
        return right;
    } else if (line == "LEFT\n") {
        train.pushed_button_left(); // тык
        std::cerr << "l" << std::endl;
        return left;
    } else {
        return exception;
    }
}

Arduino::~Arduino() {
    serial_.close();
}

}  // namespace ReadingFromPort