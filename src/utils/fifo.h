#ifndef SRC_BOARD_UART_FIFO_H_
#define SRC_BOARD_UART_FIFO_H_

#include <stdint.h>
#include <stdbool.h>

#define FIFO_ELEMENTS 254
#define FIFO_SIZE (FIFO_ELEMENTS+1)

typedef struct {
    uint8_t data[FIFO_SIZE];
    uint8_t readIndex;
    uint8_t writeIndex;
    uint8_t count;
} fifo_t;

void fifo_init(fifo_t *fifo);

bool fifo_put(fifo_t *fifo, uint8_t data);
bool fifo_get(fifo_t *fifo, uint8_t *data);

bool fifo_is_full(fifo_t *fifo);
bool fifo_is_empty(fifo_t *fifo);
uint8_t fifo_get_count(fifo_t *fifo);

#endif
