/*
 * stopwatch.c
 *
 *  Created on: Apr 8, 2024
 *      Author: Administrator
 */

/*
#include <avr/io.h>
#include "..//..//MCAL/DIO/DIO.h"
#include "..//..//MCAL/DIO/bit_math.h"
#include "..//../HAL/KEYPAD/KEYPAD.h"
#include "..//..//HAL/LCD.h"
#include "..//..//LIB/std.h"
#include <avr/delay.h>
#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>

#define LCD_ROW_1 0
#define LCD_ROW_2 1

volatile unsigned int hours = 0;
volatile unsigned int minutes = 0;
volatile unsigned int seconds = 0;
volatile char time_paused = 0; // To track if the clock is paused



// INT0 Interrupt Service Routine - Toggles pause/resume
ISR(INT0_vect) {
    time_paused = !time_paused; // Toggle the pause state
}

// INT1 Interrupt Service Routine - Resets the time
ISR(INT1_vect) {
    hours = 0;
    minutes = 0;
    seconds = 0;
}

void setupInterrupts() {
    // Configure INT0 and INT1 to trigger on the rising edge
    MCUCR |= (1 << ISC01) | (1 << ISC00) | (1 << ISC11) | (1 << ISC10);
    // Enable INT0 and INT1
    GICR |= (1 << INT0) | (1 << INT1);

    // Global interrupt enable
    sei();
}

int main(void) {
    // Initialize LCD
    LCD_Initilaize();

    // Setup interrupts for INT0 and INT1
    setupInterrupts();

    while (1) {
        if (!time_paused) {
            // Increment seconds and adjust time accordingly
            seconds++;
            if (seconds >= 60) {
                seconds = 0;
                minutes++;
                if (minutes >= 60) {
                    minutes = 0;
                    hours++;
                    if (hours >= 24) {
                        hours = 0;
                    }
                }
            }

            // Display time on LCD
            char time_string[9]; // Format: "HH:MM:SS\0"
            sprintf(time_string, "%02d:%02d:%02d", hours, minutes, seconds);
            LCD_GoToPos(LCD_ROW_1, 0);
            LCD_WriteString(time_string, LCD_ROW_1, 0);
        }

        _delay_ms(1000); // Update every second
    }

    return 0;
}*/
