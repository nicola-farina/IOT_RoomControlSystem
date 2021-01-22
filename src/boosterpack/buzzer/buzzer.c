#include <src/boosterpack/buzzer/buzzer.h>
#include <src/main.h>

#include <ti/devices/msp432p4xx/driverlib/gpio.h>
#include <ti/devices/msp432p4xx/driverlib/interrupt.h>

/* Flags that tell whether the alarm is enabled/disabled and on/off */
static bool buzzerOn;
static bool buzzerEnabled;

/* Initialize buzzer */
void buzzer_init() {
    // Set buzzer as output
    GPIO_setAsOutputPin(BUZZER_PORT, BUZZER_PIN);
    GPIO_setOutputLowOnPin(BUZZER_PORT, BUZZER_PIN);

    // Setup button S1 (P1.1) for interrupts (enabling/stopping alarm)
    // Using P1.1 because only P1, P2 and A have interrupts enabled
    GPIO_setAsInputPinWithPullUpResistor(BUTTON_ALARM_PORT, BUTTON_ALARM_PIN);
    GPIO_clearInterruptFlag(BUTTON_ALARM_PORT, BUTTON_ALARM_PIN);
    GPIO_enableInterrupt(BUTTON_ALARM_PORT, BUTTON_ALARM_PIN);
    Interrupt_enableInterrupt(INT_PORT1);

    // Initially, buzzer is off
    buzzer_set_off_flags();
}

/* Turn on buzzer */
void buzzer_make_sound() {
    // Only an interrupt will stop the cycle
    uint32_t i;
    while(buzzerOn) {
        GPIO_setOutputHighOnPin(BUZZER_PORT, BUZZER_PIN);
        for(i=0; i<1000; i++);
        GPIO_setOutputLowOnPin(BUZZER_PORT, BUZZER_PIN);
        for(i=0; i<1000; i++);
    }
    // Once out, buzzer_on is false
}

/* Set buzzer flags to turn it off */
void buzzer_set_off_flags() {
    buzzerOn = false;
    buzzerEnabled = false;
}

/* Set buzzer flags to turn it on */
void buzzer_set_on_flags() {
    buzzerOn = true;
    buzzerEnabled = true;
}

/* Toggle buzzer status (enabled or disabled alarm) */
void buzzer_toggle() {
    buzzerEnabled = !buzzerEnabled;
}

/* Enable the alarm */
void buzzer_enable() {
    buzzerEnabled = true;
}

/* Disable the alarm */
void buzzer_disable() {
    buzzerEnabled = false;
}

/* Return if the buzzer is on or not */
bool buzzer_is_on() {
    return buzzerOn;
}

/* Return if the alarm is enabled or not */
bool buzzer_is_enabled() {
    return buzzerEnabled;
}
