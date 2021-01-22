#include <src/board/infrared/infrared.h>

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#include <stdbool.h>

void infrared_init() {
    // Set as input and enable interrupts
    GPIO_setAsInputPinWithPullUpResistor(INFRARED_PORT, INFRARED_PIN);
    infrared_enable_interrupts();
}

void infrared_disable_interrupts() {
    GPIO_disableInterrupt(INFRARED_PORT, INFRARED_PIN);
    Interrupt_disableInterrupt(INFRARED_PORT_INT);
}

void infrared_enable_interrupts() {
    GPIO_clearInterruptFlag(INFRARED_PORT, INFRARED_PIN);
    // Enable interrupts when transitioning from high to low (low = movement detected)
    GPIO_interruptEdgeSelect(INFRARED_PORT, INFRARED_PIN, GPIO_HIGH_TO_LOW_TRANSITION);
    GPIO_enableInterrupt(INFRARED_PORT, INFRARED_PIN);
    Interrupt_enableInterrupt(INFRARED_PORT_INT);
}
