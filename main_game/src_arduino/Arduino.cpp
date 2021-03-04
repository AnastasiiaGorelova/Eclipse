#include "Arduino.h"

namespace ReadingFromPort {

void Ports::enumerate_ports() {
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

Ports::Ports()
    : devices_found_(serial::list_ports()), iter_(devices_found_.begin()) {
}
void Ports::get_informarmation(Arduino &my_serial) {
    cout << "ReadLine: " << my_serial.serial_.readline() << '\n';
    cout << "CTS: " << my_serial.serial_.getCTS() << '\n';
    cout << "DSR: " << my_serial.serial_.getDSR() << '\n';
    cout << "RI: " << my_serial.serial_.getRI() << '\n';
    cout << "CD: " << my_serial.serial_.getCD() << '\n' << endl;
}

Arduino::Arduino(const std::string &port, uint32_t baudrate) {
    serial::Timeout timeout(
        serial::Timeout::simpleTimeout(serial::Timeout::max()));
    serial_.setBaudrate(baudrate);
    serial_.setPort(port);
    serial_.setTimeout(timeout);
    serial_.open();
}

Arduino::~Arduino() {
    serial_.close();
}

}  // namespace ReadingFromPort