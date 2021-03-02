#include <serial/serial.h>
#include <iostream>

using namespace std;

void enumerate_ports() {
    cout << "=====================================================" << endl;

    vector<serial::PortInfo> devices_found = serial::list_ports();

    vector<serial::PortInfo>::iterator iter = devices_found.begin();

    while (iter != devices_found.end()) {
        serial::PortInfo device = *iter++;

        cout << "port: " << device.port.c_str() << '\n';
        cout << "description: " << device.description.c_str() << '\n';
        cout << "hardware_id: " << device.hardware_id.c_str() << '\n' << endl;
    }
    cout << "=====================================================" << endl;
}

int main() {
    freopen("a.out", "w", stdout);

    serial::Timeout timeout;
    serial::Serial my_serial("/dev/tty.usbmodem143101", 9600,
                             serial::Timeout::simpleTimeout(serial::Timeout::max()));

    cout << "Is the serial port open?"
         << "\n";
    if (my_serial.isOpen()) {
        cout << "-Yes." << endl;
    } else {
        cout << "-No." << endl;
    }
    cout << endl;

    enumerate_ports();

    string line;

    cout << "ReadLine: " << my_serial.readline() << '\n';
    cout << "CTS: " << my_serial.getCTS() << '\n';
    cout << "DSR: " << my_serial.getDSR() << '\n';
    cout << "RI: " << my_serial.getRI() << '\n';
    cout << "CD: " << my_serial.getCD() << '\n' << endl;

    while(line != "MENU\n") {
        line = my_serial.readline();
        cout << "ReadLine: " << line;
    }

    my_serial.close();
    cout << my_serial.getPort() << '\n';
}
