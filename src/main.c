#include <src/boosterpack/lcd/lcd.h>
#include <src/boosterpack/buzzer/buzzer.h>
#include <src/board/infrared/infrared.h>
#include <src/board/uart/driver/uartDriver.h>
#include <src/board/uart/uartIO.h>
#include <src/boosterpack/led/led.h>
#include <src/network/network.h>

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>

#include <stdbool.h>
#include <string.h>

/* The size of the command buffer */
#define COMMAND_BUFFER_SIZE 256

/* Flags to tell if the interrupt is alarm or network related */
static bool alarm_interrupt;
static bool network_interrupt;

/* Initialization functions */
void init() {
    // Hold Watchdog Timer
    WDT_A_holdTimer();

    // Setup modules
    lcd_init();
    buzzer_init();
    infrared_init();
    led_init();
    uart_init();
    uartIO_init();

    // Enable interrupts
    Interrupt_enableMaster();
}

int main(void) {
    // Initialize all modules
    init();

    // Draw LCD screen
    lcd_draw_screen();

    while(1) {
        // Go to sleep and wait for interrupts
        PCM_gotoLPM0();

        // If here, an interrupt woke it up
        // Could be the alarm going off, or a message from UART

        if(alarm_interrupt) {
            // Interrupt generated from the alarm
            alarm_interrupt = false;

            // Check if the alarm is buzzing
            bool isAlarmOn = buzzer_is_on();

            if(isAlarmOn) {
                // Disable infrared interrupts until alarm is off
                infrared_disable_interrupts();
                // Send a command to WiFi module to alert user on Telegram
                network_send_intruder_alert();
                // Turn on buzzer
                buzzer_make_sound();
                infrared_enable_interrupts();
            }

            // Check alarm status and refresh LCD accordingly
            bool isAlarmEnabled = buzzer_is_enabled();
            lcd_draw_alarm_status(isAlarmEnabled);
        }

        if(network_interrupt) {
            // A message has arrived from the ESP8266, read it from UART buffer
            char msg[COMMAND_BUFFER_SIZE];
            uint32_t msgSize;
            msgSize = uartIO_get_string(msg, COMMAND_BUFFER_SIZE);
            if(msgSize) {
                if(strcmp(msg, ALARM_EN) == 0) {
                    // Enable alarm
                    buzzer_enable();
                    lcd_draw_alarm_status(true);
                } else if(strcmp(msg, ALARM_DIS) == 0) {
                    // Disable alarm
                    buzzer_disable();
                    lcd_draw_alarm_status(false);
                } else if(strcmp(msg, LIGHT_ON) == 0) {
                    // Light on
                    led_turn_on();
                } else if(strcmp(msg, LIGHT_OFF) == 0) {
                    // Light on
                    led_turn_off();
                }
            }
            // If there are no more messages, flag network as off
            if(!uartIO_available()) {
                network_interrupt = false;
            }
        }
    }
}

/* Function used for alarm related modules to say that the interrupt originated there */
void main_set_alarm_interrupt() {
    alarm_interrupt = true;
}

/* Function used for network related modules to say that the interrupt originated there */
void main_set_network_interrupt() {
    network_interrupt = true;
}



