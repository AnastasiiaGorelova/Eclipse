#ifndef MAIN_GAME_ARDUINO_H
#define MAIN_GAME_ARDUINO_H

#include <serial/serial.h>
#include <iostream>
#include <stdexcept>

namespace ReadingFromPort {

using std::cerr, std::string, std::cin, std::cout, std::vector, std::endl;

enum Move{
    menu,
    left,
    right
};

struct Arduino {
    serial::Serial serial_;

    Arduino(const std::string &port, uint32_t baudrate);
    Move make_a_move();
    ~Arduino();
};

struct Ports {
    vector<serial::PortInfo> devices_found_;
    vector<serial::PortInfo>::iterator iter_;

    Ports();
    void show_ports();
    void is_port_open(Arduino &my_serial);
    void get_informarmation(Arduino &my_serial);
    std::string get_arduino() const;
};

}  // namespace ReadingFromPort

#endif  // MAIN_GAME_ARDUINO_H
