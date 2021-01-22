#ifndef SRC_NETWORK_NETWORK_H_
#define SRC_NETWORK_NETWORK_H_

/* Supported commands */
#define INTRUDER "I \n"
#define ALARM_EN "E\n"
#define ALARM_DIS "D\n"
#define ALARM_OFF "O"
#define LIGHT_ON "H\n"
#define LIGHT_OFF "L\n"

void network_send_intruder_alert();

#endif
