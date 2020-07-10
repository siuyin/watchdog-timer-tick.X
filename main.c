/*
 * File:   main.c
 * Author: siuyin
 *
 * Created on 10 July, 2020, 4:00 PM
 */

// README: The pull-up resistor on MCLR is absolutely required.

// During normal operation, a WDT time-out
// generates a device RESET. If the device is in SLEEP
// mode, a WDT wake-up causes the device to wake-up
// and continue with normal operation.
//
// The WDT has a nominal time-out period of 18 ms, (with
// no prescaler).

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = ON        // Watchdog Timer (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (Power-up Timer is disabled)
#pragma config CP = OFF         // Code Protection bit (Code protection disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#define _XTAL_FREQ 740000   // 6.8k and 100pF resistor is 10% and capacitor is 20% tolerance
#define UPPER_LED RB2
#define LOWER_LED RB3

void setup_portb(void);

void main(void) {
    PSA = 0; // prescaler set to TMR0 and not watchdog timer

    setup_portb();

    const unsigned char lower_led_task_period_ticks = 27; // about 500ms
    unsigned char lower_led_task_ctr = lower_led_task_period_ticks;

    const unsigned char upper_led_task_period_ticks = 27; // about 500ms
    unsigned char upper_led_task_ctr = upper_led_task_period_ticks;

    while (1) {
        if (lower_led_task_ctr == 0) {
            LOWER_LED = ~LOWER_LED;
            lower_led_task_ctr = lower_led_task_period_ticks;
        }
        if (upper_led_task_ctr == 0) {
            UPPER_LED = ~UPPER_LED;
            upper_led_task_ctr = upper_led_task_period_ticks;
        }

        SLEEP(); // WDT timer wakes up device and continues execution.
        if (lower_led_task_ctr > 0)lower_led_task_ctr--;
        if (upper_led_task_ctr > 0)upper_led_task_ctr--;
    }

    return;
}

void setup_portb(void) {
    PORTB = 0; // set all of port b to outputs
    TRISB = 0;

    LOWER_LED = 1;
}
