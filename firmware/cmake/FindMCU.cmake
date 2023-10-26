
# function(JOIN VALUES GLUE OUTPUT)

#     string(REGEX REPLACE "([^\\]|^);" "\\1${GLUE}" _TMP_STR "${VALUES}")

#     string(REGEX REPLACE "[\\](.)" "\\1" _TMP_STR "${_TMP_STR}") #fixes escaping

#     set(${OUTPUT} "${_TMP_STR}" PARENT_SCOPE)

# endfunction()

# # Generate linker information for device, based on libopencm3/mk/genlink-config.mk
# if (NOT DEVICE)
#     message(FATAL_ERROR "No DEVICE specified for linker script generator")
# endif ()


# find_program(PYTHON python)
# if (NOT PYTHON)
#     message(FATAL_ERROR "python is required to generate the linker script, please install it.")
# endif ()

# set(GENLINK_SCRIPT "${LIBCORTEXPIPI_DIR}/scripts/genlink.py")
# set(DEVICES_DATA "${LIBCORTEXPIPI_DIR}/ld/devices.data")
# execute_process(
#         COMMAND "${PYTHON}" "${GENLINK_SCRIPT}" "${DEVICES_DATA}" "${DEVICE}" "FAMILY"
#         OUTPUT_VARIABLE GENLINK_FAMILY
# )
# execute_process(
#         COMMAND "${PYTHON}" "${GENLINK_SCRIPT}" "${DEVICES_DATA}" "${DEVICE}" "USBFAMILY"
#         OUTPUT_VARIABLE GENLINK_SUBFAMILY
# )
# execute_process(
#         COMMAND "${PYTHON}" "${GENLINK_SCRIPT}" "${DEVICES_DATA}" "${DEVICE}" "CPU"
#         OUTPUT_VARIABLE GENLINK_CPU
# )
# execute_process(
#         COMMAND "${PYTHON}" "${GENLINK_SCRIPT}" "${DEVICES_DATA}" "${DEVICE}" "FPU"
#         OUTPUT_VARIABLE GENLINK_FPU
# )
# execute_process(
#         COMMAND "${PYTHON}" "${GENLINK_SCRIPT}" "${DEVICES_DATA}" "${DEVICE}" "CPPFLAGS"
#         OUTPUT_VARIABLE GENLINK_CPPFLAGS
# )
# execute_process(
#         COMMAND "${PYTHON}" "${GENLINK_SCRIPT}" "${DEVICES_DATA}" "${DEVICE}" "DEFS"
#         OUTPUT_VARIABLE GENLINK_DEFS
# )

# set(LINKER_SCRIPT "generated.${DEVICE}.ld")
# set(LINKER_SCRIPT_PATH "${CMAKE_CURRENT_BINARY_DIR}/${LINKER_SCRIPT}")
# list(APPEND ARCH_FLAGS -mcpu=${GENLINK_CPU})
# list(APPEND ARCH_FLAGS -mthumb)
# # Check FPU

# if (GENLINK_FPU STREQUAL "soft")
#     list(APPEND ARCH_FLAGS -msoft-float)
# elseif (GENLINK_FPU STREQUAL "hard-fpv4-sp-d16")
#     list(APPEND ARCH_FLAGS -mfloat-abi=hard -mfpu=fpv4-sp-d16)
# elseif (GENLINK_FPU STREQUAL "hard-fpv5-sp-d16")
#     list(APPEND ARCH_FLAGS -mfloat-abi=hard -mfpu=fpv5-sp-d1)
# else ()
#     message(WARNING "No match for the FPU flags")
# endif ()

# string(TOUPPER ${GENLINK_FAMILY} ARCH)
# list(APPEND ARCH_FLAGS ${${ARCH}_CFLAGS})

# string(REPLACE " " ";" GENLINK_DEFS ${GENLINK_DEFS})
# string(REPLACE " " ";" GENLINK_CPPFLAGS ${GENLINK_CPPFLAGS})


# execute_process(
#         COMMAND ${CMAKE_CXX_COMPILER} ${ARCH_FLAGS} ${GENLINK_DEFS} "-P" "-E" "${LIBCORTEXPIPI_DIR}/ld/linker.ld.S"
#         OUTPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/${LINKER_SCRIPT}"
# )






add_definitions(-DSTM32G431xx)

add_compile_options(
    # -mthumb
    -mfloat-abi=hard -mfpu=fpv4-sp-d16
    -fno-common
    -mcpu=cortex-m4
)
# set(LINKER_SCRIPT_PATH ${CMAKE_SOURCE_DIR}/STM32G431KBUX_FLASH.ld)

add_link_options(
    -mfloat-abi=hard -mfpu=fpv4-sp-d16
    -fno-common
    -mcpu=cortex-m4
    # -nostartfiles
    # -T ${LINKER_SCRIPT_PATH}

)
# add_link_options(-T ${LINKER_SCRIPT_PATH} ${ARCH_FLAGS} -Wl,--start-group -lc -lgcc -lnosys -Wl,--end-group -nostartfiles)
