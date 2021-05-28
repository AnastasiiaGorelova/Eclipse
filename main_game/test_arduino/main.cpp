#include "arduino.h"

int main() {
    freopen("last_info_about_ports.txt", "w", stdout);

    ReadingFromPort::Ports my_ports;

    /// Printing all ports
    my_ports.print_ports();

    /// Get arduino port
    std::string port = my_ports.get_arduino_port();

    ReadingFromPort::Arduino my_arduino(port);

    /// Print all ports opened in this computer
    my_ports.print_information(my_arduino);
    /// Is there arduino plugged
    my_ports.is_port_open(my_arduino);

    while (true) {
        my_arduino.make_a_move();
    }
}
