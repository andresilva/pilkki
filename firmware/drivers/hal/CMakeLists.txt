


add_library(
    stm32g4xx_hal
    STATIC
    stm32g4xx_hal_rcc_ex.c
    stm32g4xx_hal_spi_ex.c
    stm32g4xx_hal_dma.c
    stm32g4xx_hal.c
    stm32g4xx_hal_uart_ex.c
    stm32g4xx_hal_adc.c
    stm32g4xx_hal_flash_ex.c
    stm32g4xx_hal_rng.c
    stm32g4xx_hal_adc_ex.c
    stm32g4xx_hal_spi.c
    stm32g4xx_hal_flash.c
    stm32g4xx_hal_tim_ex.c
    stm32g4xx_hal_gpio.c
    stm32g4xx_hal_exti.c
    stm32g4xx_hal_tim.c
    stm32g4xx_hal_crc.c
    stm32g4xx_ll_adc.c
    stm32g4xx_hal_rcc.c
    stm32g4xx_hal_pwr_ex.c
    stm32g4xx_hal_cortex.c
    stm32g4xx_hal_pcd_ex.c
    stm32g4xx_ll_usb.c
    stm32g4xx_hal_pcd.c
    stm32g4xx_hal_flash_ramfunc.c
    stm32g4xx_hal_dma_ex.c
    stm32g4xx_hal_uart.c
    stm32g4xx_hal_pwr.c
    stm32g4xx_hal_crc_ex.c
)

target_include_directories(stm32g4xx_hal INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
# target_include_directories(stm32g4xx_hal PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Inc)
target_link_libraries(stm32g4xx_hal PRIVATE stm32g4xx_cmsis)
