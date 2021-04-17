#include "../include_in_controllers/arduino.h"

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
    line = serial_.readline(); // get line from arduino
    if (line == "MENU\n") {
        /// тыкнуть функцию выхода в меню
        return menu;
    } else if (line == "RIGHT\n") {
        /// тыкнуть функцию сдвига вправо
        return right;
    } else if (line == "LEFT\n") {
        /// тыкнуть функцию сдвига влево
        return left;
    } else {
        return exception;
    }
}

Arduino::~Arduino() {
    serial_.close();
}

}  // namespace ReadingFromPort