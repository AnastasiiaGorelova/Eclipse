cmake_minimum_required(VERSION 3.0)
project(MyController)

# include(FindPackageHandleStandardArgs)

find_path(SERIAL_INCLUDE_DIR serial/serial.h REQUIRED)
find_library(SERIAL_LIBRARY serial REQUIRED)
# find_package_handle_standard_args(serial DEFAULT_MSG SERIAL_INCLUDE_DIR SERIAL_LIBRARY)

message(STATUS ${SERIAL_INCLUDE_DIR})
message(STATUS ${SERIAL_LIBRARY})

include_directories(${SERIAL_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-DHAVE_STDINT_H ${CMAKE_CXX_FLAGS}")

add_executable(MyController main.cpp)
target_link_libraries(MyController ${SERIAL_LIBRARY})

if (APPLE)
    find_library(IOKIT_LIB IOKit)
    find_library(FOUNDATION_LIB Foundation)
    target_link_libraries(MyController ${FOUNDATION_LIB} ${IOKIT_LIB})
endif()

