#include <src/boosterpack/led/led.h>

#include <ti/devices/msp432p4xx/driverlib/gpio.h>

void led_init() {
    GPIO_setAsOutputPin(LED_PORT, LED_PIN);
    GPIO_setOutputLowOnPin(LED_PORT, LED_PIN);
}

void led_turn_on() {
    GPIO_setOutputHighOnPin(LED_PORT, LED_PIN);
}

void led_turn_off() {
    GPIO_setOutputLowOnPin(LED_PORT, LED_PIN);
}
