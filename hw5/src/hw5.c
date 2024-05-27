// based on adafruit and sparkfun libraries

#include <stdio.h>
#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "pico/stdlib.h"

// device has default bus address of 0x76
#define ADDR _u(0b0100000)

// hardware registers
#define REG_IODIR _u(0x00)
#define REG_GPIO _u(0x09)
#define REG_OLAT _u(0x0A)

// void setPin(unsigned char address, unsigned char register, unsigned char value) {

// }

// unsigned char readPin(unsigned char address, unsigned char register) {

// }

// int main() {
//     stdio_init_all();

// }

void chip_init() {
    // use the "handheld device dynamic" optimal setting (see datasheet)
    uint8_t buf[2];

    // send register number followed by its corresponding value
    buf[0] = REG_IODIR;
    buf[1] = 0b01111111;
    i2c_write_blocking(i2c_default, ADDR, buf, 2, false);

}

void set(char v) {
    // use the "handheld device dynamic" optimal setting (see datasheet)
    uint8_t buf[2];

    // send register number followed by its corresponding value
    buf[0] = REG_OLAT;
    buf[1] = v>>7;
    i2c_write_blocking(i2c_default, ADDR, buf, 2, false);

}

void read() {
    uint8_t buf[1];
    uint8_t reg = REG_GPIO;
    i2c_write_blocking(i2c_default, ADDR, &reg, 1, true);  // true to keep master control of bus
    i2c_read_blocking(i2c_default, ADDR, buf, 6, false);  // false - finished with bus
    
    //     // if gp0 is high
    //         // set gp7 high --> set(1)
    //     // else
    //         // set gp7 low --> set(0)

    if (buf[0] & 0b1 == 0b1){
        set(0x80);
    }
    else {
        set(0x00);
    }
}

int main() {
    stdio_init_all();

    // I2C is "open drain", pull ups to keep signal high when no data is being sent
    i2c_init(i2c_default, 100 * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    // gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    // gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

    chip_init(); // gp7 = output, gp0 = input

    // while (1) {
    //     // blink gp 25
    //     // read from gp0 --> if read(0)
    //     // if gp0 is high
    //         // set gp7 high --> set(1)
    //     // else
    //         // set gp7 low --> set(0)
    //     sleep_ms(500);    
    // }

    #ifndef PICO_DEFAULT_LED_PIN
    #warning blink example requires a board with a regular LED
    #else
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (1) {
        // Blink the builtin green LED at some frequency as a heart-beat
        gpio_put(LED_PIN, 1);
        sleep_ms(100);
        gpio_put(LED_PIN, 0);
        sleep_ms(100);
    
        // read();

    }

    #endif
}
