cmake_minimum_required(VERSION 3.14)

set(
CMAKE_MODULE_PATH
${CMAKE_CURRENT_SOURCE_DIR}/cmake
${3DPARTY_DIR}/embedded-cmake-snippets
${CMAKE_MODULE_PATH}
)


find_package(ArmToolchain REQUIRED)
find_package(MCU  REQUIRED)

project(target-efm32pg23 LANGUAGES C CXX ASM)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../common)

add_subdirectory(${3DPARTY_DIR}/gecko_sdk ${CMAKE_CURRENT_BINARY_DIR}/gecko_sdk)
add_subdirectory(src)
