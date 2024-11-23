cmake_minimum_required(VERSION 3.12)

# Automatically set the project name based on the folder name
get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PROJECT_NAME} C CXX ASM)

# Specify the path to the ARM toolchain binaries
set(TOOLCHAIN_PATH /opt/gcc-arm-none-eabi/bin)

# Define the SVD file path
set(SVD_FILE ${CMAKE_CURRENT_SOURCE_DIR}/Debug/STM32F411.svd)

# Custom target to copy the SVD file to the build directory
add_custom_target(copy_svd ALL
    COMMAND ${CMAKE_COMMAND} -E copy ${SVD_FILE} ${CMAKE_BINARY_DIR}/STM32F411.svd
    COMMENT "Copying SVD file to build directory for debugging"
)

# Toolchain settings
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_C_COMPILER ${TOOLCHAIN_PATH}/arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PATH}/arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PATH}/arm-none-eabi-gcc)

# Ensure that the compiler can find libraries and headers in the sysroot
set(CMAKE_FIND_ROOT_PATH /opt/gcc-arm-none-eabi)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Set the output directory for compiled binaries
set(OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

# Specify compiler options and flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -g")

# Linker flags to use newlib-nano (a small C library) and suppress unnecessary functions like `exit`
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --specs=nano.specs -Wl,--gc-sections -ffunction-sections -fdata-sections")

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/Device/Inc
)

# Source files for the core application
set(SOURCES
    Core/Src/main.c
    Drivers/Device/Src/system_stm32f4xx.c
    Drivers/Device/Src/minimal_exit.c
    # Add more source files here if needed
)

# Add assembly startup file
set(ASSEMBLY_SOURCE startup_stm32f411xe.s)

# Add the executable target
add_executable(${PROJECT_NAME}.elf ${SOURCES} ${ASSEMBLY_SOURCE})

# Specify the linker script
set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/STM32F411CEUx_FLASH.ld)
set_target_properties(${PROJECT_NAME}.elf PROPERTIES LINK_FLAGS "-T ${LINKER_SCRIPT}")

# Specify the output name to match the project name with .elf extension
set_target_properties(${PROJECT_NAME}.elf PROPERTIES OUTPUT_NAME "${PROJECT_NAME}.elf")

# Generate .bin file after building
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${TOOLCHAIN_PATH}/arm-none-eabi-objcopy -O binary ${OUTPUT_DIRECTORY}/${PROJECT_NAME}.elf ${OUTPUT_DIRECTORY}/${PROJECT_NAME}.bin
    COMMAND ${CMAKE_COMMAND} -E echo "Generated ${PROJECT_NAME}.bin from ELF file."
    COMMENT "Converting ELF to BIN"
)

# Define the flash command for the binary
add_custom_target(flash
    COMMAND ${CMAKE_COMMAND} -E echo "Flashing the STM32F411CEU6..."
    COMMAND st-flash write ${OUTPUT_DIRECTORY}/${PROJECT_NAME}.bin 0x8000000
    DEPENDS ${PROJECT_NAME}.elf
    COMMENT "Flashing target: ${PROJECT_NAME}.elf"
)

# Define a clear target to remove all files in the output folder
add_custom_target(clear
    COMMAND ${CMAKE_COMMAND} -E remove ${OUTPUT_DIRECTORY}/*
    COMMAND ${CMAKE_COMMAND} -E echo "Cleared contents of output directory."
    COMMENT "Clearing output directory contents"
)
