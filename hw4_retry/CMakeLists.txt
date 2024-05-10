cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(my_project)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
add_executable(hw3
    src/hw3.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(hw3 pico_stdlib hardware_adc)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(hw3)

pico_enable_stdio_usb(hw3 1)
pico_enable_stdio_uart(hw3 0)