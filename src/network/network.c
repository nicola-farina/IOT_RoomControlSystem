#include <src/network/network.h>
#include <src/board/uart/uartIO.h>

/* Sends a command to alert the user on Telegram over the UART */
void network_send_intruder_alert() {
    uartIO_print_string(INTRUDER);
}
