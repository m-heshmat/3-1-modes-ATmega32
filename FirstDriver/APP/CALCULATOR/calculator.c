/*#include "..//..//MCAL/DIO/DIO.h"
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


#define DEBOUNCE_DELAY_MS 300 // Increased debounce delay to 200 milliseconds
#define MAX_DIGITS 16

typedef enum {
    false = 0,
    true = 1
} bool;

f32 calc(f32 num1, f32 num2, u8 op, bool *error) {
    f32 result;
    switch(op) {
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
            if (num2 != 0) {
                result = num1 / num2;
            } else {
                // Handle division by zero
                *error = true; // Set error flag
                return 0;      // Return any value other than -1 to indicate division by zero
            }
            break;
        default:
            result = 0; // Set default result value
            break;
    }
    return result;
}

void Calculator() {
    u8 Operator;
    u8 value;
    f32 sum1 = 0;
    f32 sum2 = 0;
    bool is_negative = false; // Flag to track negative values

    // Initialize the LCD (should ideally be done in main())
    LCD_Initilaize();
    LCD_WriteCmd(0x01); // Clear display
    LCD_WriteString("Enter data:", 0, 0); // Display "Enter Data" message immediately upon starting
    _delay_ms(500); // Wait for 0.5 seconds

    while (1) {
        // Clear display
        LCD_WriteCmd(0x01);

        // Reset variables
        sum1 = 0;
        sum2 = 0;
        is_negative = false;

        while (1) {
            // Get input from the keypad with debounce
            do {
                value = KEYPAD_getPressedKey();
                _delay_ms(DEBOUNCE_DELAY_MS); // Delay for debounce
            } while (value == KEYPAD_BUTTON_RELEASED);

            // Check if 'P' is pressed
            if (value == 'P') {
                // Reinitialize LCD and continue loop
            	LCD_Initilaize();
                LCD_WriteCmd(0x01); // Clear display
                break;
            }

            // Handle negative value
            if (value == '-') {
                is_negative = true;
                continue; // Skip further processing for this input
            }

            // Read the first number from the keypad with debounce
            while (!((value == '/') || (value == '*') || (value == '+') || (value == '-'))) {
                // Value is not an operator
                sum1 = (sum1 * 10) + (value - '0');
                LCD_WriteData(value);
                _delay_ms(100);
                // Get input from the keypad with debounce
                do {
                    value = KEYPAD_getPressedKey();
                    _delay_ms(DEBOUNCE_DELAY_MS); // Delay for debounce
                } while (value == KEYPAD_BUTTON_RELEASED);
            }

            // Operator assigning
            Operator = value;
            LCD_WriteData(Operator);
            _delay_ms(500);
            // Get input from the keypad with debounce
            do {
                value = KEYPAD_getPressedKey();
                _delay_ms(DEBOUNCE_DELAY_MS); // Delay for debounce
            } while (value == KEYPAD_BUTTON_RELEASED);

            // Read the second number from the keypad with debounce
            if (value == '=') {
                // '=' pressed before entering the second operand
                LCD_WriteCmd(0x01); // Clear display
                LCD_WriteString("Error:Enter 2nd", 0, 0);
                LCD_WriteString("operand", 1, 0);
                _delay_ms(1000); // Wait for 1 second
                break; // Break out of the loop and restart input process
            }

            while (value != '=') {
                // Second value before equal
                sum2 = (sum2 * 10) + (value - '0');
                LCD_WriteData(value);
                _delay_ms(100);
                // Get input from the keypad with debounce
                do {
                    value = KEYPAD_getPressedKey();
                    _delay_ms(DEBOUNCE_DELAY_MS); // Delay for debounce
                } while (value == KEYPAD_BUTTON_RELEASED);
            }
            _delay_ms(100);
            LCD_WriteData(value);
            _delay_ms(100);

            // Apply negative value if needed
            if (is_negative) {
                sum2 = -sum2;
                is_negative = false; // Reset the flag
            }

            // Calculate the result
            bool error = false; // Error flag for division by zero
            f32 result = calc(sum1, sum2, Operator, &error);
            char result_str[MAX_DIGITS];

            if (error) {
                strcpy(result_str, "Math Error");
            } else {
                // Check if result is exactly -1
                if (result == -1) {
                    sprintf(result_str, "-1");
                } else {
                    // Convert the result to a string
                    sprintf(result_str, "%f", result);
                }
            }

            // Clear display and print result
            LCD_WriteCmd(0x01); // Clear display
            LCD_WriteString("Result:", 0, 0);
            LCD_WriteString(result_str, 1, 0);
            _delay_ms(1500); // Wait for 1.5 seconds

            break; // Break out of the input process and restart from the beginning
        }
    }
}*/
