#include "MCAL/DIO/DIO.h"
#include "HAL/KEYPAD/KEYPAD.h"
#include "HAL/LCD.h"
#include "LIB/std.h"
#include "LIB/bit_math.h"
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>

#define LCD_ROW_1 0
#define LCD_ROW_2 1

typedef enum {
    CALCULATOR, //0
    STOPWATCH, //1
    TIMER //2
} SystemMode;

volatile SystemMode currentMode = CALCULATOR; // Start in calculator mode
volatile SystemMode lastMode = -1;  // Variable to store the last mode for comparison
volatile char welcomeDisplayed = 0;

volatile unsigned int hours = 0;
volatile unsigned int minutes = 0;
volatile unsigned int seconds = 0;
volatile char time_paused = 0; // To track if the clock is paused

void floatToString(char *str, float value) {
    int tmpInt1 = (int)value;
    float tmpFrac = value - tmpInt1;
    int tmpInt2 = trunc(tmpFrac * 1000);
    sprintf(str, "%d.%03d", tmpInt1, tmpInt2 < 0 ? -tmpInt2 : tmpInt2);  // Handle negative fractions
}


void intToString(char *str, int32_t value) {
    sprintf(str, "%ld", value);
}

void setupIO() {
    // Set PORTD.4 as output
    DDRD |= (1 << 4);
    PORTD &= ~(1 << 4);  // Initially set the LED to off
}

// INT0 Interrupt Service Routine - Toggles pause/resume for the clock
ISR(INT0_vect) {
    if (currentMode == STOPWATCH || currentMode == TIMER) {
        time_paused = !time_paused; // Toggle the pause state only in clock mode
        LCD_Clear();
    }
}

// INT1 Interrupt Service Routine - Resets the time in clock mode
ISR(INT1_vect) {
    if (currentMode == STOPWATCH) {
        hours = 0;
        minutes = 0;
        seconds = 0;
        LCD_Clear();
    } else if (currentMode == TIMER) {
        minutes = 0;
        seconds = 0;
        PORTD |= (1 << 4);
        LCD_Clear();
    }
}

// INT2 Interrupt Service Routine - Switches modes flexibly
ISR(INT2_vect) {
    if (currentMode == STOPWATCH) {
        currentMode = TIMER; // Direct switch to Clock from Timer
    } else {
        currentMode = (currentMode + 1) % 3; // Cycles through the modes normally
    }
    LCD_Clear(); // Clear Display command
}

void setupInterrupts() {
    // Configure INT0,INT1,and INT2 to trigger on the rising edge
    MCUCR |= (1 << ISC01) | (1 << ISC00) | (1 << ISC11) | (1 << ISC10) | (1 << ISC2);

    // Enable INT0, INT1, and INT2
    GICR |= (1 << INT0) | (1 << INT1) | (1 << INT2);

    // Global interrupt enable
    sei();
}

int main(void) {
    // Initialize LCD
    LCD_Initilaize();
    setupIO();
    char key; // Define key variable here
    int32_t num1 = 0, num2 = 0, result = 0;
    float result1=0;
    char resultStr[32];
    char result1Str[32]; // Buffer to store the result string

    if (!welcomeDisplayed) {
        LCD_WriteString("Welcome", LCD_ROW_1, 0);
        _delay_ms(1000);  // Display welcome message for 2 seconds
        welcomeDisplayed = 1;  // Set the flag to prevent re-displaying
        LCD_Clear(); // Clear Display after welcome message
    }

    // Setup interrupts for INT0, INT1, and INT2
    setupInterrupts();

    char timeInput[6] = {'0', '0', ':', '0', '0', '\0'};  // Preformatted time input MM:SS
    int timeIndex = 0;  // To navigate the timeInput array

    while (1) {
        // Check if the mode has changed to avoid redundant LCD updates
        if (lastMode != currentMode) {
            LCD_Clear();
            lastMode = currentMode; // Update lastMode to currentMode

            if (currentMode == TIMER) {
                LCD_WriteString("Timer Mode", LCD_ROW_1, 0);
                _delay_ms(1000);
                LCD_Clear();
                LCD_WriteString("Enter MM:SS", LCD_ROW_1, 0);
                LCD_GoToPos(LCD_ROW_2, 0);
                LCD_WriteString(timeInput, LCD_ROW_2, 0);
                timeIndex = 0;
            }

            switch (currentMode) {
                case CALCULATOR:
                    LCD_WriteString("Calculator Mode", LCD_ROW_1, 0);
                    _delay_ms(1000);
                    LCD_Clear();
                    break;
                case STOPWATCH:
                    LCD_WriteString("Stopwatch mode", LCD_ROW_1, 0);
                    _delay_ms(1000);  // Display welcome message for 2 seconds
                    LCD_Clear();
                    break;
                case TIMER:
                    break;
            }
            _delay_ms(500); // Allow display to stabilize
        }

        // Mode-specific operations
        switch (currentMode) {
            case CALCULATOR:
                // Read the first operand
                LCD_WriteString("Enter num1:", LCD_ROW_1, 0);
                LCD_GoToPos(LCD_ROW_2, 0);
                num1 = 0;
                while (1 && currentMode == CALCULATOR) {
                    key = KEYPAD_getPressedKey();
                    if (key >= '0' && key <= '9') {
                        num1 = num1 * 10 + (key - '0');
                        LCD_WriteData(key);
                        _delay_ms(250); // Debounce delay
                    } else if (key == '+' || key == '-' || key == '*' || key == '/') {
                        break;
                    }
                }
                LCD_Clear();
                LCD_WriteString("Enter operator:", LCD_ROW_1, 0);
                char op = key; // Store operator

                LCD_GoToPos(1, 0);
                LCD_WriteData(key);
                _delay_ms(500);
                LCD_Clear(); // Clear Display command

                LCD_WriteString("Enter num2:", LCD_ROW_1, 0);
                LCD_GoToPos(LCD_ROW_2, 0);
                num2 = 0;
                while (1 && currentMode == CALCULATOR) {
                    key = KEYPAD_getPressedKey();
                    if (key >= '0' && key <= '9') {
                        num2 = num2 * 10 + (key - '0');
                        LCD_WriteData(key);
                        _delay_ms(250); // Debounce delay
                    } else if (key == '=') {
                        break;
                    }
                }

                switch (op) {
                    case '+':
                        result = num1 + num2;
                        break;
                    case '-':
                        result = num1 - num2;
                        break;
                    case '*':
                        result = num1 * num2;
                        break;
                    case '/':
                        if (num2 == 0) {
                            LCD_Clear();
                            LCD_WriteString("Math Error", LCD_ROW_1, 0);
                            _delay_ms(2000); // Display error for a period
                            continue; // Exit this case
                        }

                        result1 = (float)num1 / (float)num2;
                        break;
                    default:

                        continue;
                }
                if(op=='/')
                {
                	floatToString(result1Str, result1);
					LCD_Clear();
					LCD_WriteString(result1Str, LCD_ROW_1, 0);
					_delay_ms(2000); // Allow time to read the result
					LCD_Clear();
					break;
                }
                else{
                intToString(resultStr, result);
                LCD_Clear();
                LCD_WriteString(resultStr, LCD_ROW_1, 0);
                _delay_ms(2000); // Allow time to read the result
                LCD_Clear();
                break;
                }

            case STOPWATCH:
                if (!time_paused) {
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
                }
                char time_string[16]; // Buffer increased for NULL character
                sprintf(time_string, "%02d:%02d:%02d", hours, minutes, seconds);
                LCD_GoToPos(LCD_ROW_1, 0);
                LCD_WriteString((uint8_t *)time_string, LCD_ROW_1, 0); // Cast to uint8_t pointer to fix warning
                break;

            case TIMER:
                while (currentMode == TIMER) {
                    key = KEYPAD_getPressedKey(); // Get key press
                    _delay_ms(50);
                    if (key >= '0' && key <= '9') {
                        if (timeIndex == 0 || timeIndex == 1 || timeIndex == 3 || timeIndex == 4) {
                            if (timeIndex == 3 && key >= '6') { // Check if tens digit of seconds is invalid
                                continue;
                            }
                            timeInput[timeIndex] = key;  // Update the time input at the correct position
                            LCD_GoToPos(LCD_ROW_2, timeIndex);
                            LCD_WriteData(key);  // Display the digit
                            if (timeIndex == 1 || timeIndex == 4) { // Auto-advance if at the last position of MM or SS
                                timeIndex += 2;
                            } else {
                                timeIndex++;
                            }
                            _delay_ms(50); // Debounce delay
                        }
                    } else if (key == '=') {
                        sscanf(timeInput, "%2d:%2d", &minutes, &seconds);
                        if (seconds > 59) {
                            seconds = 59; // Correct seconds if out of range
                        }
                        LCD_Clear();
                        LCD_WriteString("Timer Starts", LCD_ROW_1, 0);
                        _delay_ms(1000);
                        LCD_Clear();

                        while ((minutes > 0 || seconds > 0) && currentMode == TIMER) {
                            sprintf(timeInput, "%02d:%02d", minutes, seconds);
                            LCD_WriteString(timeInput, LCD_ROW_1, 0);
                            _delay_ms(1000);

                            if (!time_paused) {
                                if (seconds == 0) {
                                    if (minutes > 0) {
                                        minutes--;
                                        seconds = 59;
                                    }
                                } else {
                                    seconds--;
                                }
                                LCD_Clear(); // Clear the display for the next update
                            }
                        }

                        if (currentMode == TIMER) {
                            LCD_WriteString("Time's Up!", LCD_ROW_1, 0);
                            PORTD |= (1 << 4);

                            _delay_ms(1000);
                            PORTD &= ~(1 << 4);
                            _delay_ms(1000);
                            currentMode = CALCULATOR; // Reset to clock mode or desired mode
                            LCD_Clear();
                        }
                    }
                    break;
                }
        }

        _delay_ms(1000); // Main loop delay for stability
    }

    return 0;
}
