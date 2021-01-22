#ifndef SRC_BOARD_INFRARED_INFRARED_H_
#define SRC_BOARD_INFRARED_INFRARED_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#define INFRARED_PORT GPIO_PORT_P2
#define INFRARED_PORT_INT INT_PORT2
#define INFRARED_PIN GPIO_PIN3


void infrared_init();
void infrared_disable_interrupts();
void infrared_enable_interrupts();

#endif
