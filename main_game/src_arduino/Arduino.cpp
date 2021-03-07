#include "Arduino.h"

namespace ReadingFromPort {

Ports::Ports()
    : devices_found_(serial::list_ports()), iter_(devices_found_.begin()) {
}

void Ports::show_ports() {
    cout << "=====================================================" << endl;
    while (iter_ != devices_found_.end()) {
        serial::PortInfo device = *iter_++;

        cout << "port: " << device.port.c_str() << '\n';
        cout << "description: " << device.description.c_str() << '\n';
        cout << "hardware_id: " << device.hardware_id.c_str() << '\n' << endl;
    }
    cout << "=====================================================" << endl;
}

void Ports::is_port_open(Arduino &my_serial) {
    cout << "Is the serial port open?"
         << "\n";
    if (my_serial.serial_.isOpen()) {
        cout << "-Yes." << endl;
    } else {
        cout << "-No." << endl;
    }
    cout << endl;
}

void Ports::get_informarmation(Arduino &my_serial) {
    cout << "ReadLine: " << my_serial.serial_.readline() << '\n';
    cout << "CTS: " << my_serial.serial_.getCTS() << '\n';
    cout << "DSR: " << my_serial.serial_.getDSR() << '\n';
    cout << "RI: " << my_serial.serial_.getRI() << '\n';
    cout << "CD: " << my_serial.serial_.getCD() << '\n' << endl;
}
std::string Ports::get_arduino() const {
    for (const auto& device : devices_found_) {
        if (device.description.find("Arduino") != std::string::npos) {
            return device.port;
        }
    }
    throw std::runtime_error("There is no Arduino plugged into port");
}

Arduino::Arduino(const std::string &port, uint32_t baudrate = 9600) {
    serial::Timeout timeout(
        serial::Timeout::simpleTimeout(serial::Timeout::max()));
    serial_.setBaudrate(baudrate);
    serial_.setPort(port);
    serial_.setTimeout(timeout);
    serial_.open();
}

Move Arduino::make_a_move() {
    string line;
    line = serial_.readline();
    if (line == "MENU\n") {
        return menu;
    }
    if (line == "RIGHT\n") {
        return right;
    }
    if (line == "LEFT\n") {
        return left;
    }
}

Arduino::~Arduino() {
    serial_.close();
}

}  // namespace ReadingFromPort