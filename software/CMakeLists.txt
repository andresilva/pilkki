cmake_minimum_required(VERSION 3.24)


project(pilkki LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
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
    pilkki
    src/pilkki.cpp
    ${SERIAL_IMPL}
)

target_link_libraries(pilkki PRIVATE udev)

install(TARGETS pilkki DESTINATION bin)