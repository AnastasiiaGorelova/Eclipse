cmake_minimum_required(VERSION 3.17)
project(main_game)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined -fsanitize=address -Wall -Wextra -Werror")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g -Wall -Wextra")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/src)

if (APPLE)
    set(CMAKE_PREFIX_PATH "/Users/katya/Qt/6.0.1/clang_64") #set your local path to qt
    find_package(Qt6 COMPONENTS Widgets REQUIRED)
else ()
    set(CMAKE_PREFIX_PATH "/home/alena/Qt/5.15.2") #set your local path to qt
    find_package(Qt5Widgets REQUIRED)
endif ()

file(GLOB_RECURSE SOURCES "src_qt/*.cpp" "src/*cpp")
file(GLOB_RECURSE HEADERS "include_qt/*.h" "include/*h")
add_executable(main_game ${HEADERS} ${SOURCES})


# For Arduino and libs
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(Serial REQUIRED)
include_directories(${Serial_INCLUDE_DIRS})

add_executable(Arduino "src_arduino/main.cpp")
target_link_libraries(Arduino ${Serial_LIBRARIES})


if (APPLE)
    target_link_libraries(main_game Qt6::Widgets)
else ()
    target_link_libraries(main_game Qt5::Widgets)
endif ()