

add_library(
    stm32g4xx_cmsis
    INTERFACE
)

target_include_directories(
    stm32g4xx_cmsis
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)
