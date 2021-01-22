#ifndef SRC_BOOSTERPACK_LED_LED_H_
#define SRC_BOOSTERPACK_LED_LED_H_

#include <ti/devices/msp432p4xx/driverlib/gpio.h>

#define LED_PORT GPIO_PORT_P5
#define LED_PIN GPIO_PIN6

void led_init();
void led_turn_on();
void led_turn_off();

#endif
