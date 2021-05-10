#ifndef MAIN_GAME_ARDUINO_H
#define MAIN_GAME_ARDUINO_H

#include "Key_Controller_.h"
//#include "God.h"
#include <serial/serial.h>
#include <iostream>
#include <stdexcept>
#include <thread>

class God;

namespace ReadingFromPort {

enum Move { menu, left, right, exception };

struct Arduino : virtual Controller_in {
    serial::Serial serial_;
    std::thread ta;

    Arduino(const std::string &port, uint32_t baudrate = 9600);
    Move make_a_move();
    void make_a_move_void();
    void start_thread();
    void set_God(God *damn_) override;
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
