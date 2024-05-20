#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"
#include <math.h>

//

#ifdef PICO_DEFAULT_SPI_CSN_PIN
static inline void cs_select() {
    asm volatile("nop \n nop \n nop");
    gpio_put(PICO_DEFAULT_SPI_CSN_PIN, 0);  // Active low
    asm volatile("nop \n nop \n nop");
}

static inline void cs_deselect() {
    asm volatile("nop \n nop \n nop");
    gpio_put(PICO_DEFAULT_SPI_CSN_PIN, 1);
    asm volatile("nop \n nop \n nop");
}
#endif

// writing the "write_register" helper function

static void write_register(uint8_t reg, uint16_t data) {

    uint8_t buf[2];
    //buf[0] = reg & 0x7f;  // remove read bit as this is a write
    //buf[1] = data;

    uint16_t new_data = data << 2; // bit shift left twice to have all the data bits all the way on the right

    uint8_t first_byte = (new_data >> 8) & 0xFF;
    uint8_t second_byte = (new_data) & 0xFF;
    buf[1] = second_byte;

    if (reg == 1) {
        buf[0] = (0b10110000 | first_byte);
    } else {
        buf[0] = (0b00110000 | first_byte);
    }
    
    cs_select();
    spi_write_blocking(spi_default, buf, 2);
    cs_deselect();
    sleep_ms(10);
}

//

int main() {
    stdio_init_all();
#
    printf("Hello, mcp4912! Reading raw data from registers via SPI...\n");

    spi_init(spi_default, 500 * 1000);
    gpio_set_function(PICO_DEFAULT_SPI_RX_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_TX_PIN, GPIO_FUNC_SPI);
    
    // Chip select is active-low, so we'll initialise it to a driven-high state
    gpio_init(PICO_DEFAULT_SPI_CSN_PIN);
    gpio_set_dir(PICO_DEFAULT_SPI_CSN_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_SPI_CSN_PIN, 1);

    while (1) {
   
        sleep_ms(10);
    }
}