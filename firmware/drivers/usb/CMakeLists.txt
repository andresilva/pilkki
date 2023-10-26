

add_library(
    stm32g4xx_usb
    STATIC
    usb_device.c
    usbd_cdc_if.c
    usbd_desc.c
    usbd_conf.c
    usbd_cdc.c
    usbd_core.c
    usbd_ctlreq.c
    usbd_ioreq.c
)

target_include_directories(
    stm32g4xx_usb
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)


target_include_directories(
    stm32g4xx_usb
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(stm32g4xx_usb PRIVATE stm32g4xx_cmsis stm32g4xx_hal)
