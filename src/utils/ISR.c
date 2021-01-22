#include <src/board/infrared/infrared.h>
#include <src/board/uart/uartIO.h>
#include <src/boosterpack/buzzer/buzzer.h>
#include <src/main.h>

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#include <stdbool.h>

/* UART A2 Interrupt Handler (communication with ESP8266) */
void EUSCIA2_IRQHandler(void) {
    uint32_t status = UART_getEnabledInterruptStatus(EUSCI_A2_BASE);
    UART_clearInterruptFlag(EUSCI_A2_BASE, status);

    if(status & EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG) {
        // Receive a single byte of data
        uint8_t data = UART_receiveData(EUSCI_A2_BASE);

        //Turn alarm off if it's the "O" command
        if(data == 'O') {
            buzzer_set_off_flags();
        } else {
            // Put the received data into a buffer
            uartIO_put_data_into_buffer(data);
            // If "\n", a command was fully received: warn main process
            if(data == '\n') {
                main_set_network_interrupt();
            }
        }
    }
}

// PORT 1 Interrupt Handler (button P1.1 to toggle alarm status)
void PORT1_IRQHandler() {
    // Check if the interrupt is coming from alarm button
    uint_fast16_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P1);
    GPIO_clearInterruptFlag(GPIO_PORT_P1, status);

    // Button
    if(status & BUTTON_ALARM_PIN) {
        main_set_alarm_interrupt();
        bool buzzerOn = buzzer_is_on();
        if(buzzerOn) {
            // Set it off
            buzzer_set_off_flags();
        } else {
            // Toggle alarm status
            buzzer_toggle();
        }
    }

    // Infrared
    if(status & INFRARED_PIN) {
        // High = no detection, Low = detection
        uint8_t movement = GPIO_getInputPinValue(INFRARED_PORT, INFRARED_PIN);
        if(movement == GPIO_INPUT_PIN_LOW) {
            // Movement detected, check if alarm is enabled or not
            bool alarmEnabled = buzzer_is_enabled();
            if(alarmEnabled) {
                buzzer_set_on_flags();
                main_set_alarm_interrupt();
            }
        }
    }
}

// PORT 2 Interrupt Handler (infrared sensor)
void PORT2_IRQHandler() {
    // Check if the interrupt is coming from alarm button
    uint_fast16_t status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P2);
    GPIO_clearInterruptFlag(GPIO_PORT_P2, status);

    // Infrared
    if(status & INFRARED_PIN) {
        // High = no detection, Low = detection
        uint8_t movement = GPIO_getInputPinValue(INFRARED_PORT, INFRARED_PIN);
        if(movement == GPIO_INPUT_PIN_LOW) {
            // Movement detected, check if alarm is enabled or not
            bool alarmEnabled = buzzer_is_enabled();
            if(alarmEnabled) {
                buzzer_set_on_flags();
                main_set_alarm_interrupt();
            }
        }
    }


}
