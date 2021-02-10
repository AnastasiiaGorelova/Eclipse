cmake_minimum_required(VERSION 3.17)
project(Eclipse_project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined -fsanitize=address -Wall -Wextra -Werror")
set(CMAKE_CXX_STANDARD 17)

add_executable(Eclipse_project src/main.cpp src/game.cpp src/space_ship.cpp src/asteroids.cpp)