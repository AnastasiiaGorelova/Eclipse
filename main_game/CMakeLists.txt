cmake_minimum_required(VERSION 3.16.3)
project(Eclipse)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.71 REQUIRED COMPONENTS filesystem)
message(STATUS "Boost version: ${Boost_VERSION}") # boost
find_package(Qt5Widgets REQUIRED QUIET COMPONENTS Core Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
find_package(Threads REQUIRED)
find_package(Boost REQUIRED thread system)

file(GLOB_RECURSE SOURCES "src_qt/*.cpp" "src/*.cpp" "src_in_controllers/*.cpp" "src_local_leaderboard/*.cpp" "upstream_leaderboard/*.cpp")
qt5_wrap_cpp(SOURCES "include_qt/game_window.h" "include_qt/main_window.h" "include_qt/selection.h" "include_qt/name_enter_qt.h" "include_qt/game_finish_window.h" "include_qt/error_massage_window.h" "include_qt/buy_live_for_coins_window.h" "include_qt/leaderboard_ui.h" "include_qt/legend_window.h")
add_subdirectory(dependencies)

# GAME
#add_executable(main_game ${SOURCES})
#target_include_directories(main_game PUBLIC "include" "include_qt" "include_in_controllers" "include_leaderboard" "upstream_leaderboard")
#target_link_libraries(main_game serial)
#target_link_libraries(main_game Boost::filesystem)
#target_link_libraries(main_game Qt5::Widgets)



# Server
add_executable(server_eclipse server/main.cpp)
target_include_directories(server_eclipse PUBLIC "thirdparty")
target_link_libraries(server_eclipse PRIVATE Threads::Threads)
target_link_libraries(server_eclipse PRIVATE Boost::thread Boost::system)

## For Arduino test
#add_executable(arduino_info "test_arduino/main.cpp" "src_in_controllers/arduino.cpp" "src_in_controllers/ports.cpp")
#target_include_directories(arduino_info PUBLIC "include_in_controllers")
#target_link_libraries(arduino_info serial)