#ifndef SRC_BOOSTERPACK_BUZZER_BUZZER_H_
#define SRC_BOOSTERPACK_BUZZER_BUZZER_H_

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#include <stdbool.h>

#define BUZZER_PORT GPIO_PORT_P2
#define BUZZER_PIN GPIO_PIN7
#define BUTTON_ALARM_PORT GPIO_PORT_P1
#define BUTTON_ALARM_PIN GPIO_PIN1

void buzzer_init();
void buzzer_make_sound();
void buzzer_set_on_flags();
void buzzer_set_off_flags();
void buzzer_enable();
void buzzer_disable();
void buzzer_toggle();
bool buzzer_is_on();
bool buzzer_is_enabled();

#endif
