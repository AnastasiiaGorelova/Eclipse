#include "Arduino.h"

using namespace std;

int main() {
    freopen("a.out", "w", stdout);

    uint32_t baudrate = 9600;
    const string port = "/dev/tty.usbmodem143101";

    ReadingFromPort::Arduino my_arduino(port, baudrate);

    /// Получить порты
    ReadingFromPort::Ports my_ports;
    my_ports.enumerate_ports();

    string line;
    my_ports.get_informarmation(my_arduino);
    my_ports.is_port_open(my_arduino);

    while (line != "MENU\n") {
        line = my_arduino.serial_.readline();
        cout << "ReadLine: " << line;
    }

    my_arduino.serial_.close();
    cout << my_arduino.serial_.getPort() << '\n';
}
