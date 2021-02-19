cmake_minimum_required(VERSION 3.17)
project(main_game)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "/home/alena/Qt/5.15.2")
find_package(Qt5Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/src)

file(GLOB_RECURSE HEADERS "include/*.h")
file(GLOB_RECURSE SOURCES "src/*.cpp")


add_executable(main_game ${HEADERS} ${SOURCES} src/asteroids_presentation.cpp src/asteroids_qt.cpp)

target_link_libraries(main_game Qt5::Widgets)
