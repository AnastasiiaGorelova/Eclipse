#include "../include_in_controllers/arduino.h"

namespace ReadingFromPort {

void Ports::print_ports() {
    std::cout << "====================================================="
              << std::endl;
    for (const auto &item : devices_found_) {
        std::cout << "port: " << item.port.c_str() << '\n';
        std::cout << "description: " << item.description.c_str() << '\n';
        std::cout << "hardware_id: " << item.hardware_id.c_str() << '\n'
                  << std::endl;
    }
    std::cout << "====================================================="
              << std::endl;
}

void Ports::is_port_open(Arduino &my_serial) {
    std::cout << "Is the serial port open?"
              << "\n";
    if (my_serial.serial_.isOpen()) {
        std::cout << "-Yes." << std::endl;
    } else {
        std::cout << "-No." << std::endl;
    }
    std::cout << std::endl;
}

void Ports::print_information(Arduino &my_serial) {
    std::cout << "ReadLine: " << my_serial.serial_.readline() << '\n';
    std::cout << "CTS: " << my_serial.serial_.getCTS() << '\n';
    std::cout << "DSR: " << my_serial.serial_.getDSR() << '\n';
    std::cout << "RI: " << my_serial.serial_.getRI() << '\n';
    std::cout << "CD: " << my_serial.serial_.getCD() << '\n' << std::endl;
}

}  // namespace ReadingFromPort