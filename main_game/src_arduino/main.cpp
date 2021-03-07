#include "Arduino.h"

using namespace std;

int main() {
    freopen("a.out", "w", stdout);

    ReadingFromPort::Ports my_ports;
    uint32_t baudrate = 9600;

    /// Получить порты
    my_ports.show_ports();

    /// поиск Ардуино
    string port = my_ports.get_arduino();

    ReadingFromPort::Arduino my_arduino(port, baudrate);

    my_ports.get_informarmation(my_arduino);
    my_ports.is_port_open(my_arduino);

    while (true) {
        ReadingFromPort::Move move = my_arduino.make_a_move();
        if (move == ReadingFromPort::menu) {
            my_arduino.serial_.close();
            cout << my_arduino.serial_.getPort() << '\n';
            return 0;
        }
        if (move == ReadingFromPort::right) {
            cout << "RIGHT" << endl;
        }
        if (move == ReadingFromPort::left) {
            cout << "LEFT" << endl;
        }
    }

    my_arduino.serial_.close();
    cout << my_arduino.serial_.getPort() << '\n';
}
