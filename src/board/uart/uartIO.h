#ifndef SRC_BOARD_UART_UARTIO_H_
#define SRC_BOARD_UART_UARTIO_H_

#include <stdint.h>
#include <stdbool.h>

void uartIO_init();
bool uartIO_put_data_into_buffer(uint8_t data);
void uartIO_print_string(const char *string);
uint8_t uartIO_available();
uint8_t uartIO_get_string(char *string, uint32_t size);

#endif
