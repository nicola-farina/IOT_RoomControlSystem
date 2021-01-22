#ifndef SRC_UTILS_UARTDRIVER_H_
#define SRC_UTILS_UARTDRIVER_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#include <stdint.h>

/* The UART channel to use */
#define UART_BASE (EUSCI_A2_BASE)
#define UART_INT (INT_EUSCIA2)
#define UART_PORT (GPIO_PORT_P3)
#define UART_RX (GPIO_PIN2)
#define UART_TX (GPIO_PIN3)
#define UART_RECEIVE_INTERRUPT (EUSCI_A_UART_RECEIVE_INTERRUPT)
#define UART_RECEIVE_INTERRUPT_FLAG (EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG)

void uart_init();
void uart_write(uint8_t *data, uint32_t size);

#endif
