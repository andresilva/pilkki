

add_library(
    pilkki-firmware-common
    INTERFACE
)

target_include_directories(
    pilkki-firmware-common
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
