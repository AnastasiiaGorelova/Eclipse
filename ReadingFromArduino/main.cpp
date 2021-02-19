//  main.cpp

// A serial port utility for MacOS X

// For communicating with serial devices (e.g. microcontrollers)
// usually via USB serial.

// Includes
#include <iostream>
#include "SerialPort.hpp"
#include "TypeAbbreviations.hpp"

 int main() {
    //* Open port, and connect to a device
    const char devicePathStr[] = "/dev/tty.usbmodem143101";
    const int baudRate = 57600;
    int sfd = openAndConfigureSerialPort(devicePathStr, baudRate);
    //    if (sfd < 0) {
    //        if (sfd == -1) {
    //            printf("Unable to connect to serial port.\n");
    //        }
    //        else { //sfd == -2
    //            printf("Error setting serial port attributes.\n");
    //        }
    //        return 0;
    //    }

    char *bytes = nullptr;
    size_t length = 10;
    for (int i = 0; i < 10; i++) {
        if (serialPortIsOpen()) {
            ssize_t reading = readSerialData(bytes, length);
            std::cout << reading << '\n';
        }
    }
    closeSerialPort();
    // * Read using readSerialData(char* bytes, size_t length)

    // * Write using writeSerialData(const char* bytes, size_t length)

    // * Remember to flush potentially buffered data when necessary

    // * Close serial port when done

    return 0;
}
//#include <unistd.h>
//#include <fstream>
//#include <iostream>
//
//using namespace std;
//
//int main() {
////    unsigned int angle;
//    fstream arduino("/dev/tty.usbmodem143101");
//
//    if (arduino) {
//        string smth;
//        while (arduino >> smth) {
////            if (command == "load") {
////                fin >> file_name;
////                employees::load(file_name);
////            } else if (command == "save") {
////                std::string type;
////                fin >> type;
//            arduino << smth;
////                employees::save(type, file_name);
////            } else {
////                employees::list_devs();
////            }
//        }
//    } else {
//        cout << "File not found" << '\n';
//    }
//    arduino.close();
//}