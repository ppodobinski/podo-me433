cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(my_project)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
add_executable(hw4
    src/hw4.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(hw4 pico_stdlib hardware_adc hardware_spi)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(hw4)

pico_enable_stdio_usb(hw4 1)
pico_enable_stdio_uart(hw4 0)