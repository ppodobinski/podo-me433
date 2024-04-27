#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

void printVoltage(int num) {
    for (int i = 0; i < num; ++i) {
        uint16_t result = adc_read();
        //printf("%d",result);
        float voltage = result / 4096.0 * 3.3;
        //printf("%d\r\n", result);
        printf("%.3f\r\n", voltage);
        sleep_ms(10);
    }
}

int main() {

    stdio_init_all();

    // button (INPUT)
    gpio_init(22);
    gpio_set_dir(22,GPIO_IN);
    //gpio_pull_up(22);

    // LED (OUTPUT)
    gpio_init(16);
    gpio_set_dir(16,GPIO_OUT);

    while (!stdio_usb_connected()) {
        sleep_ms(100);
    }
    printf("Start!\n");

    adc_init(); // init the adc module
    adc_gpio_init(26); // set ADC0 pin to be adc input instead of GPIO
    adc_select_input(0); // select to read from ADC0

    while (1) {
        
        gpio_put(16,1);
        if (gpio_get(22) != 0) {
            gpio_put(16,0);
            char message[100];
            printf("Enter a number of analog samples to take:\r\n");
            scanf("%s", message);                        
            int num = atoi(message);
            printf("Number: %d\r\n",num);
            printVoltage(num);
        }
    }
}
