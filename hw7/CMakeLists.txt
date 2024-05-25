cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(my_project)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
add_executable(hw7
    src/hw7.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(hw7 pico_stdlib hardware_uart)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(hw7)

pico_enable_stdio_usb(hw7 1)
pico_enable_stdio_uart(hw7 0)