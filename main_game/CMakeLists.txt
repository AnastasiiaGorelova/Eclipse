cmake_minimum_required(VERSION 3.17)
project(main_game)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined -fsanitize=address -Wall -Wextra")
set(CMAKE_CXX_STANDARD 17)

find_package(Qt5 REQUIRED QUIET COMPONENTS Core Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

file(GLOB_RECURSE SOURCES "src_qt/*.cpp" "src/*.cpp" "src_in_controllers/*.cpp")
qt5_wrap_cpp(SOURCES "include_qt/game_window.h" "include_qt/main_window.h" "include_qt/Selection.h")
add_subdirectory(dependencies)

add_executable(main_game ${SOURCES})
target_link_libraries(main_game Qt5::Widgets)
target_link_libraries(main_game serial)
target_include_directories(main_game PUBLIC include include_qt)

# For Arduino and libs
add_executable(arduino_info "test_arduino/main.cpp" "src_in_controllers/arduino.cpp" "src_in_controllers/ports.cpp")
target_link_libraries(arduino_info serial)
