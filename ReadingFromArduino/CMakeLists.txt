cmake_minimum_required(VERSION 3.17)
project(ReadingFromArduino)

set(CMAKE_CXX_STANDARD 14)

add_executable(ReadingFromArduino main.cpp SerialPort.cpp)