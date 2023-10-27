
add_definitions(
    -DEFM32PG23B200F512IM40
    -Dsram_layout
)

add_compile_options(
    -mfloat-abi=hard -mfpu=fpv4-sp-d16
    -mcpu=cortex-m33 -mcmse
)
set(LINKER_SCRIPT_PATH ${CMAKE_SOURCE_DIR}/STM32G431KBUX_FLASH.ld)

add_link_options(
    -mfloat-abi=hard -mfpu=fpv4-sp-d16
    -mcpu=cortex-m33 -mcmse
    -Wl,--no-warn-rwx-segments
)