#ifndef MAIN_GAME_ARDUINO_H
#define MAIN_GAME_ARDUINO_H

#include <serial/serial.h>
#include <iostream>
#include <thread>
#include <stdexcept>

namespace ReadingFromPort {

enum Move { menu, left, right, exception };

struct Arduino {
    serial::Serial serial_;

    Arduino(const std::string &port, uint32_t baudrate = 9600);
    Move make_a_move();
    ~Arduino();
};

struct Ports {
    std::vector<serial::PortInfo> devices_found_;

    Ports();

    /// Printing only
    void print_ports();
    void is_port_open(Arduino &my_serial);
    void print_information(Arduino &my_serial);

    /// Get arduino port
    std::string get_arduino_port() const;
};

}  // namespace ReadingFromPort

#endif  // MAIN_GAME_ARDUINO_H
