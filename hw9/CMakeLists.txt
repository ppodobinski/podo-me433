cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(my_project)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
add_executable(hw9
    src/hw9.c
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(hw9 pico_stdlib hardware_spi hardware_adc hardware_i2c ssd1306 hardware_irq hardware_uart pico_binary_info)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(hw9)

pico_enable_stdio_usb(hw9 1)
pico_enable_stdio_uart(hw9 0)