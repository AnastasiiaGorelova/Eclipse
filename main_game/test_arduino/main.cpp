#include "../include_in_controllers/arduino.h"

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
        ReadingFromPort::Move move = my_arduino.make_a_move();

        switch (move) {
            case ReadingFromPort::menu:
                std::cout << my_arduino.serial_.getPort() << std::endl;
                return 0;
            case ReadingFromPort::right:
                std::cout << "RIGHT" << std::endl;
                break;
            case ReadingFromPort::left:
                std::cout << "LEFT" << std::endl;
                break;
            case ReadingFromPort::exception:
                std::cerr << "Unexpected string!" << std::endl;
                return 0;
        }
    }
}
