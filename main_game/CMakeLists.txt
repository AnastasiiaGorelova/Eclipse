cmake_minimum_required(VERSION 3.17)
project(main_game)

set(CMAKE_CXX_STANDARD 17)

add_executable(main_game src/main.cpp src/asteroids.cpp src/space_ship.cpp include/space_ship.h src/game.cpp include/game.h include/game_fwd.h src/shots.cpp include/shots.h)