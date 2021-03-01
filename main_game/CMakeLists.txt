cmake_minimum_required(VERSION 3.17)
project(main_game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "/home/alena/Qt/5.15.2") #set your local path to qt
find_package(Qt5Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/src)

file(GLOB_RECURSE SOURCES "src_qt/*.cpp")
file(GLOB_RECURSE HEADERS "include_qt/*.h")


add_executable(main_game ${HEADERS} ${SOURCES})

target_link_libraries(main_game Qt5::Widgets)
