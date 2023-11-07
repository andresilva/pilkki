cmake_minimum_required(VERSION 3.20)

project(pilkki LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)

FetchContent_Declare(
  magic_enum
  GIT_REPOSITORY https://github.com/Neargye/magic_enum.git
  GIT_TAG        v0.9.3
)
FetchContent_Declare(
  argparse
  GIT_REPOSITORY https://github.com/morrisfranken/argparse.git
  GIT_TAG        5d3710809364e694f33243810bbd1345975ae1c3
)

FetchContent_GetProperties(argparse)
FetchContent_GetProperties(magic_enum)
if(NOT argparse_POPULATED)
  FetchContent_Populate(argparse)
  add_subdirectory(${argparse_SOURCE_DIR} ${argparse_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

if(NOT magic_enum_POPULATED)
  FetchContent_Populate(magic_enum)
  add_subdirectory(${magic_enum_SOURCE_DIR} ${magic_enum_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

if (WIN32)
  add_library(serial_impl OBJECT src/serial_win.cpp)
elseif(APPLE)
  add_library(serial_impl OBJECT src/serial_unix.cpp src/autodetect_mac.cpp)
elseif(UNIX)
  add_library(serial_impl OBJECT src/serial_unix.cpp src/autodetect_linux.cpp)
  target_link_libraries(serial_impl PRIVATE udev)
else()
  message(FATAL "There is no implementation of serial for that platform")
endif()

if (
  CMAKE_CXX_COMPILER_ID MATCHES "(Clang|GNU)"
)
  add_compile_options(-Wall -Wextra -pedantic)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  # using Visual Studio C++
endif()

add_executable(
  pilkki
  src/pilkki.cpp
)

target_link_libraries(pilkki PRIVATE serial_impl argparse magic_enum::magic_enum)

install(TARGETS pilkki DESTINATION bin)
