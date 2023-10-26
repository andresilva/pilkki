

# Target definition
set(CMAKE_SYSTEM_NAME  Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

#---------------------------------------------------------------
# Reset all options (to not be affected by upper level project)
#---------------------------------------------------------------
unset(CMAKE_CXX_FLAGS)
unset(CMAKE_CXX_OPTIONS)
unset(CMAKE_C_FLAGS)
unset(CMAKE_ASM_FLAGS)
unset(OBJECT_GEN_FLAGS)
unset(CMAKE_EXE_LINKER_FLAGS)
unset(COMPILE_DEFINITIONS)
unset(COMPILE_OPTIONS)
unset(LINK_OPTIONS)

message(WARNING "CO:${COMPILE_OPTIONS}, CD:${COMPILE_DEFINITIONS}")

#---------------------------------------------------------------------------------------
# Set toolchain paths
#---------------------------------------------------------------------------------------
set(TOOLCHAIN arm-none-eabi)
if(NOT DEFINED TOOLCHAIN_PREFIX)
    if(CMAKE_HOST_SYSTEM_NAME STREQUAL Linux)
        set(TOOLCHAIN_PREFIX "/usr")
    elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL Darwin)
        set(TOOLCHAIN_PREFIX "/usr/local")
    elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL Windows)
        message(STATUS "Please specify the TOOLCHAIN_PREFIX !\n For example: -DTOOLCHAIN_PREFIX=\"C:/Program Files/GNU Tools ARM Embedded\" ")
    else()
        set(TOOLCHAIN_PREFIX "/usr")
        message(STATUS "No TOOLCHAIN_PREFIX specified, using default: " ${TOOLCHAIN_PREFIX})
    endif()
endif()
set(TOOLCHAIN_BIN_DIR ${TOOLCHAIN_PREFIX}/bin)
set(TOOLCHAIN_INC_DIR ${TOOLCHAIN_PREFIX}/${TOOLCHAIN}/include)
set(TOOLCHAIN_LIB_DIR ${TOOLCHAIN_PREFIX}/${TOOLCHAIN}/lib)




# Set system depended extensions
if(WIN32)
    set(TOOLCHAIN_EXT ".exe" )
else()
    set(TOOLCHAIN_EXT "" )
endif()

#---------------------------------------------------------------------------------------
# Set compilers
#---------------------------------------------------------------------------------------
set(CMAKE_C_COMPILER ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-gcc${TOOLCHAIN_EXT})
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-g++${TOOLCHAIN_EXT})
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-gcc${TOOLCHAIN_EXT})
set(CMAKE_LINKER ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-gcc${TOOLCHAIN_EXT})

# Perform compiler test with static library
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

#---------------------------------------------------------------------------------------
# Set compiler/linker flags
#---------------------------------------------------------------------------------------

# Object build options
# -O0                   No optimizations, reduce compilation time and make debugging produce the expected results.
# -mthumb               Generat thumb instructions.
# -fno-builtin          Do not use built-in functions provided by GCC.
# -Wall                 Print only standard warnings, for all use Wextra
# -ffunction-sections   Place each function item into its own section in the output file.
# -fdata-sections       Place each data item into its own section in the output file.
# -fomit-frame-pointer  Omit the frame pointer in functions that don’t need one.
# -mabi=aapcs           Defines enums to be a variable sized type.
# set(OBJECT_GEN_FLAGS "-mthumb -Wall -Wextra -Wimplicit-function-declaration -Wredundant-decls -Wstrict-prototypes -Wundef -Wshadow -fdata-sections -ffunction-sections")
# -Os \
# -Wall -Wextra -Wimplicit-function-declaration \
# -Wredundant-decls -Wmissing-prototypes -Wstrict-prototypes \
# -Wundef -Wshadow \
# -I../../../include -fno-common \
# -mcpu=cortex-m4 -mthumb $(FP_FLAGS) \
# -Wstrict-prototypes \
# -ffunction-sections -fdata-sections -MD -DSTM32G4

add_compile_options(
    -mthumb
    # -Wall
    # -Wextra
    # -Wimplicit-function-declaration
    # -Wredundant-decls
    # -Wstrict-prototypes
    # -Wundef
    # -Wshadow
    -fno-builtin
    -fdata-sections
    -ffunction-sections
    # -Werror
    $<$<COMPILE_LANGUAGE:Asm>:"-x assembler-with-cpp">
)



# -Wl,--gc-sections     Perform the dead code elimination.
# --specs=nano.specs    Link with newlib-nano.
# --specs=nosys.specs   No syscalls, provide empty implementations for the POSIX system calls.
# set(CMAKE_EXE_LINKER_FLAGS "--specs=nano.specs --specs=nosys.specs -mthumb -Wl,-Map=${CMAKE_PROJECT_NAME}.map" CACHE INTERNAL "Linker options")
add_link_options(
    # --specs=nano.specs
    --specs=nosys.specs
    -mthumb
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
)

set(CMAKE_FIND_ROOT_PATH ${TOOLCHAIN_PREFIX}/${${TOOLCHAIN}} ${CMAKE_PREFIX_PATH})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(OBJCOPY_BIN_PATH ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-objcopy${TOOLCHAIN_EXT})
find_program(OBJCOPY_BIN ${OBJCOPY_BIN_PATH} REQUIRED)

set(ARM_SIZE_PATH ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-size${TOOLCHAIN_EXT})
find_program(ARM_SIZE ${ARM_SIZE_PATH} REQUIRED)

add_compile_options(
    $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-use-cxa-atexit>
)
