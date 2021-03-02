# - Try to find Serial
# Once done, this will define
#  Serial_FOUND
#  Serial_INCLUDE_DIRS
#  Serial_LIBRARIES

include(LibFindMacros)

# Dependencies
if (APPLE)
    libfind_pkg_detect(IOKit - FIND_LIBRARY IOKit)
    libfind_pkg_detect(Foundation - FIND_LIBRARY Foundation)
    list(APPEND DEPS "IOKit_LIBRARY" "Foundation_LIBRARY")
elseif (UNIX)
    libfind_package(Serial Threads)
    libfind_pkg_detect(RT - FIND_LIBRARY rt)
    list(APPEND DEPS "CMAKE_THREAD_LIBS_INIT" "RT_LIBRARY")
else ()
    list(APPEND DEPS "setupapi")
endif ()

# Required to be able to compile includes
find_path(HAVE_STDINT_H NAMES stdint.h)
if (HAVE_STDINT_H)
    add_compile_options(-DHAVE_STDINT_H)
endif ()

find_path(Serial_INCLUDE_DIR NAMES serial/serial.h)
find_library(Serial_LIBRARY NAMES serial)

set(Serial_PROCESS_INCLUDES Serial_INCLUDE_DIR)
set(Serial_PROCESS_LIBS Serial_LIBRARY "${DEPS}")
libfind_process(Serial)
