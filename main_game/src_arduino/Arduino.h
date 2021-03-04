#ifndef MAIN_GAME_ARDUINO_H
#define MAIN_GAME_ARDUINO_H

#include <serial/serial.h>
#include <iostream>

namespace ReadingFromPort {

using std::cin, std::cout, std::vector, std::endl;

struct Arduino {
    serial::Serial serial_;

    Arduino(const std::string &port, uint32_t baudrate);
    ~Arduino();
};

struct Ports {
    vector<serial::PortInfo> devices_found_;
    vector<serial::PortInfo>::iterator iter_;

    Ports();
    void enumerate_ports();
    void is_port_open(Arduino &my_serial);
    void get_informarmation(Arduino &my_serial);
};

}  // namespace ReadingFromPort

#endif  // MAIN_GAME_ARDUINO_H
