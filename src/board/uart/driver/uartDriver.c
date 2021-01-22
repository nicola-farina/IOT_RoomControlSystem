#include <src/boosterpack/buzzer/buzzer.h>
#include <src/board/uart/driver/uartDriver.h>
#include <src/board/uart/uartIO.h>

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

/* Clock frequency of 3MHz (defines UART baud rate) */
#define CLOCK_FREQUENCY CS_DCO_FREQUENCY_3

/* Configuration parameters for UART, calculated to have
 * a baud rate of 9600 */
const eUSCI_UART_ConfigV1 uartConfig = {
        EUSCI_A_UART_CLOCKSOURCE_SMCLK,
        19,
        8,
        85,
        EUSCI_A_UART_NO_PARITY,
        EUSCI_A_UART_LSB_FIRST,
        EUSCI_A_UART_ONE_STOP_BIT,
        EUSCI_A_UART_MODE,
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION,
        EUSCI_A_UART_8_BIT_LEN
};

/* Initialize the UART channel for communicating with ESP8266 (A2) */
void uart_init() {
    // Set appropriate pins into UART mode
    GPIO_setAsPeripheralModuleFunctionInputPin(UART_PORT,
          UART_RX | UART_TX, GPIO_PRIMARY_MODULE_FUNCTION);

    // Set clock frequency to 12MHz
    CS_setDCOCenteredFrequency(CLOCK_FREQUENCY);

    // Enable module and receive interrupts
    UART_initModule(UART_BASE, &uartConfig);
    UART_enableModule(UART_BASE);
    UART_enableInterrupt(UART_BASE, UART_RECEIVE_INTERRUPT);
    Interrupt_enableInterrupt(UART_INT);
}

/* Write given data to the specified UART */
void uart_write(uint8_t *data, uint32_t size) {
    uint32_t i;
    // Transmit byte per byte
    for(i=0; i<size; i++) {
        UART_transmitData(UART_BASE, data[i]);
    }
}
