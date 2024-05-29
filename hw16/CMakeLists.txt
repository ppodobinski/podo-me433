cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(my_project)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
add_executable(hw16
    src/hw16.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(hw16 pico_stdlib hardware_spi hardware_i2c)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(hw16)

pico_enable_stdio_usb(hw16 1)
pico_enable_stdio_uart(hw16 0)