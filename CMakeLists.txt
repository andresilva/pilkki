cmake_minimum_required(VERSION 3.14)


project(flasher LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps/argparse/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps/magic_enum/include)

if (WIN32)
  set(SERIAL_IMPL src/serial_win.cpp)
elseif(UNIX)
  set(SERIAL_IMPL src/serial_linux.cpp)
else()
    message(FATAL "There is no implementation of serial for that platform")
endif()

add_executable(
    flasher
    src/flasher.cpp
    ${SERIAL_IMPL}
)

target_link_libraries(flasher PRIVATE udev)
