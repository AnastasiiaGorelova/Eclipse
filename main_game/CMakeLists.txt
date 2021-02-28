cmake_minimum_required(VERSION 3.17)
project(main_game)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined -fsanitize=address -Wall -Wextra -Werror")
set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(main_game src/main.cpp src/asteroids.cpp src/space_ship.cpp src/game.cpp src/shots.cpp)