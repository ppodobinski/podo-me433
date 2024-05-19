#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/spi.h"
#include <math.h>
#include "hardware/pwm.h"

//

uint16_t wrap = 62500; // when to rollover, must be less than 65535
void initializing_pwm();
void set_servo_angle();
#define pinPWM 16
float div = 40; // must be between 1-255. Basically, if we start with 125 MHz, this is 1.25e8 Hz, and divide by wrap (62,500) and div (40) to get 50 Hz

//

void initializing_pwm() {
    
    gpio_set_function(pinPWM, GPIO_FUNC_PWM); // Set the PWM pin to be PWM

    uint slice_num = pwm_gpio_to_slice_num(pinPWM); // Get PWM slice number
        
    pwm_set_clkdiv(slice_num, div); // divider
    pwm_set_wrap(slice_num, wrap);
    pwm_set_enabled(slice_num, true); // turn on the PWM

}

//

void set_servo_angle() {
    // goal: servo moves from 0 degrees to 180 degrees and back in 4 seconds
    // 2 seconds to move from 0 to 180
    // 2 seconds to move from 180 to 0
    pwm_set_gpio_level(pinPWM, wrap * 0.025); // 0 degrees, minimum duty cycle is 2.5%
    sleep_ms(2000);
    pwm_set_gpio_level(pinPWM, wrap * 0.125); // 180 degrees, maximum duty cycle is 12.5%
    sleep_ms(2000);

}

//

int main() {

    initializing_pwm(); // call this helper function one time

    while(1) {
        set_servo_angle(); // call this helper function in an infinite while loop
    }

}