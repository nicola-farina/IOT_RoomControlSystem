#include <src/board/uart/uartIO.h>
#include <src/board/uart/driver/uartDriver.h>
#include <src/utils/fifo.h>

/* The FIFO structure to keep data received from UART */
static fifo_t uartFifo;

/* Function to initialize the UART structure for I/O */
void uartIO_init() {
    fifo_init(&uartFifo);
}

/* Function used by the driver to insert a character into the buffer */
bool uartIO_put_data_into_buffer(uint8_t data) {
    return fifo_put(&uartFifo, data);
}

/* Utility function to print a single character on the UART */
void print_char(char c) {
    uart_write((uint8_t*)&c, 1);
}

/* Send a string on the UART channel specified in uartDriver.h */
void uartIO_print_string(const char *string) {
    // While the string is not the null character
    while(*string) {
        print_char(*string);
        string++;
    }
}

/* Check if data is available to be read on the UART
 * return:
 *  - number of bytes available */
uint8_t uartIO_available() {
    return fifo_get_count(&uartFifo);
}

/* Gets the available data on the UART
 * Attention: the string has to be large enough
 * return:
 *  - number of bytes read */
uint8_t uartIO_get_string(char *string, uint32_t size) {
    uint8_t bytesAvailable = uartIO_available();
    uint8_t i;
    for(i=0; i<bytesAvailable; i++) {
        fifo_get(&uartFifo, (uint8_t *) &string[i]);
    }
    // Put string terminator if there's space
    if(i<size-1) {
        string[i] = 0;
    }
    return bytesAvailable;
}
