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

struct Arduino : virtual Controller_in {
private:
    serial::Serial serial_;
    std::thread ta;
    std::atomic<bool> keep_going{};

public:
    Arduino(const std::string &port, uint32_t baudrate = 9600);
    Arduino(const Arduino &) = delete;
    Arduino(Arduino &&) = delete;
    Arduino &operator=(const Arduino &) = delete;
    Arduino &operator=(Arduino &&) = delete;

    void make_a_move();
    void start_thread();
    void write_to_port() override;
    void set_God(God *damn_) override;

    virtual ~Arduino();
    friend struct Ports;
};

struct Ports {
private:
    std::vector<serial::PortInfo> devices_found_;

public:
    Ports();

    /// Printing only
    void print_ports();
    static void is_port_open(Arduino &my_serial);
    static void print_information(Arduino &my_serial);

    /// Get arduino port
    [[nodiscard]] std::string get_arduino_port() const;
};

}  // namespace ReadingFromPort

#endif  // MAIN_GAME_ARDUINO_H
