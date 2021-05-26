cmake_minimum_required(VERSION 3.17)
project(main_game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

find_package(Boost 1.75.0 COMPONENTS program_options REQUIRED) # boost
find_package(nlohmann_json 3.2.0 REQUIRED) # json
find_package(Qt5Widgets REQUIRED QUIET COMPONENTS Core Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

file(GLOB_RECURSE SOURCES "src_qt/*.cpp" "src/*.cpp" "src_in_controllers/*.cpp" "src_local_leaderboard/*.cpp")
qt5_wrap_cpp(SOURCES "include_qt/game_window.h" "include_qt/main_window.h" "include_qt/Selection.h" "include_qt/name_enter_qt.h" "include_qt/game_finish_window.h" "include_qt/error_massage_window.h" "include_qt/buy_live_for_coins_window.h" "include_qt/local_leaderboard_ui.h" "include_qt/legend_window.h")
add_subdirectory(dependencies)

# GAME
add_executable(main_game ${SOURCES})
target_include_directories(main_game PUBLIC "include" "include_qt" "include_in_controllers" "include_leaderboard")
target_link_libraries(main_game serial)
target_link_libraries(main_game nlohmann_json::nlohmann_json) # json
target_link_libraries(main_game Boost::program_options)
target_link_libraries(main_game Qt5::Widgets)

# For Leaderboard test
add_executable(local_leaderboard "src_local_leaderboard/local_leaderboard.cpp" "test_leaderboard/main.cpp")
target_link_libraries(local_leaderboard nlohmann_json::nlohmann_json) # json

# For Arduino test
add_executable(arduino_info "test_arduino/main.cpp" "src_in_controllers/arduino.cpp" "src_in_controllers/ports.cpp")
target_include_directories(arduino_info PUBLIC "include_in_controllers")
target_link_libraries(arduino_info serial)

## For Server test
#add_executable(server "src_upstream_leaderboard/server.cpp")
#
## For client test
#add_executable(client "src_upstream_leaderboard/client.cpp")
