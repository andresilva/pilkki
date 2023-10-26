
ExternalProject_Add(
  efm32pg23_external_project
  SOURCE_DIR        ${CMAKE_CURRENT_SOURCE_DIR}/efm32pg23
  BINARY_DIR        ${CMAKE_CURRENT_BINARY_DIR}/efm32pg23
  CMAKE_ARGS -D3DPARTY_DIR=${3DPARTY_DIR}
  BUILD_BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/efm32pg23/src/target-efm32pg23.bin
  BUILD_ALWAYS ON
  INSTALL_COMMAND   ""
)

add_custom_target(
  efm32pg23_external_project-clean
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/efm32pg23
  COMMAND ${CMAKE_COMMAND} --build . --target clean
  COMMENT "Cleaning build outputs for target efm32pg23..."
)

add_dependencies(mrproper efm32pg23_external_project-clean)


add_custom_target(
  target-efm32pg23-obj

  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/efm32pg23/src/target-efm32pg23.bin
  COMMENT "generate target-efm32pg23-obj"
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/efm32pg23/src
  BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/efm32pg23/src/target-efm32pg23.obj
  COMMAND arm-none-eabi-ld -r -b binary -o target-efm32pg23.obj target-efm32pg23.bin
)

add_library(target-efm32pg23-objlib OBJECT IMPORTED GLOBAL)

set_property(
    TARGET target-efm32pg23-objlib PROPERTY IMPORTED_OBJECTS
  "${CMAKE_CURRENT_BINARY_DIR}/efm32pg23/src/target-efm32pg23.obj"
)
add_dependencies(target-efm32pg23-objlib target-efm32pg23-obj)
