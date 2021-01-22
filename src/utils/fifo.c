#include <src/utils/fifo.h>

/* Initializes the FIFO */
void fifo_init(fifo_t *fifo) {
    fifo->readIndex = 0;
    fifo->writeIndex = 0;
    fifo->count = 0;
}

/* Pushes a byte of data into the FIFO
 * return:
 *  - true if success
 *  - false if FIFO is full */
bool fifo_put(fifo_t *fifo, uint8_t data) {
    bool retval = false;
    if(!fifo_is_full(fifo)) {
        fifo->data[fifo->writeIndex] = data;
        fifo->writeIndex = (fifo->writeIndex + 1) % FIFO_SIZE;
        fifo->count++;
        retval = true;
    }
    return retval;
}

/* Gets a byte of data from the FIFO
 * return:
 *  - true if success (data is populated)
 *  - false if FIFO is empty */
bool fifo_get(fifo_t *fifo, uint8_t *data) {
    bool retval = false;
    if(!fifo_is_empty(fifo)) {
        *data = fifo->data[fifo->readIndex];
        fifo->readIndex = (fifo->readIndex + 1) % FIFO_SIZE;
        fifo->count--;
        retval = true;
    }
    return retval;
}

/* Checks if the FIFO is full
 * return:
 *  - true if full
 *  - false otherwise */
bool fifo_is_full(fifo_t *fifo) {
    return fifo->writeIndex == ((fifo->readIndex - 1 + FIFO_SIZE) % FIFO_SIZE);
}

/* Checks if the FIFO is empty
 * return:
 *  - true if empty
 *  - false otherwise */
bool fifo_is_empty(fifo_t *fifo) {
    return fifo->writeIndex == fifo->readIndex;
}

/* Returns how many bytes there are in the FIFO */
uint8_t fifo_get_count(fifo_t *fifo) {
    return fifo->count;
}
