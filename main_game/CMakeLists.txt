cmake_minimum_required(VERSION 3.17)
project(main_game)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined -fsanitize=address -Wall -Wextra -Werror")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra")

include_directories(include include_qt)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if (APPLE)
    find_package(Qt6Widgets REQUIRED)
else ()
    find_package(Qt5Widgets REQUIRED)
endif ()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/src)

if (APPLE)
    set(CMAKE_PREFIX_PATH "/Users/katya/Qt/6.0.1/clang_64")
    find_package(Qt6Widgets REQUIRED)
else ()
    #set(CMAKE_PREFIX_PATH "/home/alena/Qt/5.15.2/gcc_64")
    #set(CMAKE_PREFIX_PATH "/home/anastasia/Qt/5.15.2/gcc_64")
    find_package(Qt5Widgets REQUIRED)
endif ()

file(GLOB_RECURSE SOURCES "src_qt/*.cpp" "src/*cpp")
file(GLOB_RECURSE HEADERS "include_qt/*.h" "include/*h")

add_executable(main_game ${HEADERS} ${SOURCES} src_qt/GameObject.cpp)

# For Arduino and libs
add_subdirectory(dependencies)
add_executable(arduino_example "src_arduino/main.cpp" "src_arduino/Arduino.cpp" "src_arduino/Arduino.h")
target_link_libraries(arduino_example serial)

if (APPLE)
    target_link_libraries(main_game Qt6::Widgets)
else ()
    target_link_libraries(main_game Qt5::Widgets)
endif ()
