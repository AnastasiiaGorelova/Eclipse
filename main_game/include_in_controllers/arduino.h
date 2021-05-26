#ifndef MAIN_GAME_ARDUINO_H
#define MAIN_GAME_ARDUINO_H

#include <serial/serial.h>
#include <atomic>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <thread>
#include "controllers_in.h"

class God;

namespace ReadingFromPort {

enum Move { menu, left, right, exception };

struct Arduino : virtual Controller_in {
    serial::Serial serial_;
    std::thread ta;
    std::atomic<bool> keep_going{};
    std::mutex m;

    Arduino(const std::string &port, uint32_t baudrate = 9600);

    void make_a_move();

    void start_thread();

    void write_to_port() override;

    void set_God(God *damn_) override;

    virtual ~Arduino();
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
