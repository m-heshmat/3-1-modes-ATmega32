/*#define PORTD_REG (*(volatile uint8_t *)(0x32))
#define DDRD_REG  (*(volatile uint8_t *)(0x31))
#define PIND_REG (*(volatile u8 *)(0x30))


#define PORTB_REG (*(volatile u8 *)(0x38))
#define DDRB_REG (*(volatile u8 *)(0x37))
#define PINB_REG (*(volatile u8 *)(0x36))

#define PD4 4
#define PB4 4


#define OUTPUT 1
#define INPUT 0

#define HIGH 1
#define LOW 0*/



/*#define MENU_OPTIONS 3  // Number of menu options
#define INT2_PIN PD2    // INT2 pin connected to PORTD2

#define EICRA   *((volatile uint8_t *)0x69)
#define EIMSK   *((volatile uint8_t *)0x3D)
#define ISC11   3
#define ISC10   2
#define ISC21   7
#define ISC20   6
#define INT1    7
#define INT2    6

volatile uint8_t selectedOption = 0; // Selected menu option

// Function prototypes
void displayMenu();
void handleButtonPress();

// Interrupt service routine for INT2
ISR(INT2_vect) {
    handleButtonPress();
}

int main(void) {
    // Initialize LCD
    LCD_Initilaize();

    // Set INT2 pin as input
    DDRD &= ~(1 << INT2_PIN);
    // Enable pull-up resistor for INT2 pin
    PORTD |= (1 << INT2_PIN);

    // Set up external interrupt INT2 (falling edge triggers interrupt)
    EICRA |= (1 << ISC21) | (0 << ISC20);  // Falling edge triggers interrupt
    EIMSK |= (1 << INT2);  // Enable INT2 interrupt

    // Enable global interrupts
    sei();

    LCD_WriteString("WELCOME", 0, 0);
            _delay_ms(2000);

    LCD_WriteString("Select mode", 0, 0);
        _delay_ms(2000);
        LCD_WriteCmd(0x01); // Clear display

        // Display abbreviated menu options
        displayMenu();




    while (1) {
        // Main program loop
    }
    return 0;
}

// Function to display menu options on the LCD
void displayMenu() {
	LCD_WriteString("1.Calc.", 0, 0);
	    LCD_WriteString("2.Timer", 0, 9);
	    LCD_WriteString("3. Stopwatch", 1, 0);
}

// Function to handle button press
void handleButtonPress() {
    _delay_ms(50); // Debouncing delay
    if (!(PIND & (1 << INT2_PIN))) { // Check if button is still pressed
        // Button is pressed
        selectedOption++; // Increment selected option
        if (selectedOption > MENU_OPTIONS) {
            selectedOption = 0; // Loop back to the first option
        }
        displayMenu(); // Update LCD with new selection
    }
}


/*#define LCD_ROW_1 0
#define LCD_ROW_2 1

#define PINB_REG  (*(volatile u8 *)(0x36))
#define PIND_REG  (*(volatile u8 *)(0x30))

#define PORTD_REG (*(volatile uint8_t *)(0x32))
#define DDRD_REG  (*(volatile uint8_t *)(0x31))
#define PINB_REG  (*(volatile uint8_t *)(0x36))

#define PD2 2
#define PB4 4
*/

/*
#define EICRA   *((volatile uint8_t *)0x69)
#define EIMSK   *((volatile uint8_t *)0x3D)
#define ISC11   3
#define ISC10   2
#define ISC21   7
#define ISC20   6
#define INT1    7
#define INT2    6

volatile unsigned int hours = 0;
volatile unsigned int minutes = 0;
volatile unsigned int seconds = 0;
volatile uint8_t paused = 0;

void update_display() {
    char time_string[9]; // Format: "HH:MM:SS\0"
    sprintf(time_string, "%02d:%02d:%02d", hours, minutes, seconds);
    LCD_GoToPos(LCD_ROW_1, 0);
    LCD_WriteString(time_string, LCD_ROW_1, 0);
}

ISR(INT2_vect) {
    // Reset button pressed
    hours = 0;
    minutes = 0;
    seconds = 0;
    paused = 0; // Reset pause state
}

ISR(INT1_vect) {
    // Pause/Resume button pressed
    paused = 1 - paused; // Toggle pause state
}*/

/*int main(void) {
    // Initialize LCD

    // Set PORTD pin 2 (PD2) as output
       SET_BIT(DDRD_REG, PD2);
       while (1) {
    if (GET_BIT(PINB_REG, PB4) == HIGH) {
               // If the button is pressed, turn on the LED
               SET_BIT(PORTD_REG, PD2);
           } else {
               // If the button is not pressed, turn off the LED
               CLR_BIT(PORTD_REG, PD2);
           }
    return 0;
       }
}*/

/*
    // Set up external interrupts
    EICRA |= (1 << ISC11) | (1 << ISC10); // INT1 triggered on rising edge
    EICRA |= (1 << ISC21) | (1 << ISC20); // INT2 triggered on rising edge
    EIMSK |= (1 << INT1) | (1 << INT2); // Enable INT1 and INT2

    sei(); // Enable global interrupts

    while (1) {
        if (!paused) {
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
            // Update display
            update_display();
        }
        _delay_ms(1000); // Update every second
    }

    return 0;
}
*/



/*#include "MCAL/DIO/DIO.h"
#include "HAL/KEYPAD/KEYPAD.h"
#include "HAL/LCD.h"
#include "LIB/std.h"
#include "LIB/bit_math.h"
#include <avr/delay.h>
#include <stdio.h>
#include <string.h>


#define OUTPUT 1
#define INPUT 0
#define HIGH 1
#define LOW 0

void init_buttons() {
    // Set buttons pins as inputs
    DIO_SetPinDirection(PORTA,PIN0, input);
    DIO_SetPinDirection(PORTA,PIN1, input);
    DIO_SetPinDirection(PORTB,PIN4, input);

    // Enable pull-up resistors for buttons
    DIO_EnablePullup(PORTA,PIN0);
    DIO_EnablePullup(PORTA,PIN1);
    DIO_EnablePullup(PORTB,PIN4);
}

void start_stopwatch() {
    // Stopwatch variables
    uint8_t minutes = 0;
    uint8_t seconds = 0;
    char time_str[6];

    // Loop until the pause button is pressed
    while (DIO_GetPinValue(PORTA, PIN1) == HIGH) {
        // Increment seconds
        seconds++;
        if (seconds == 60) {
            // Increment minutes and reset seconds
            minutes++;
            seconds = 0;
        }

        // Display elapsed time on LCD
        LCD_GoToPos(0, 0); // Set cursor to beginning of first line
        sprintf(time_str, "%02d:%02d", minutes, seconds);
        LCD_WriteString(time_str, 0, 0);

        // Delay for 1 second
        _delay_ms(1000);
    }
}

int main(void) {
    // Initialize buttons
    init_buttons();

    // Initialize LCD
    LCD_Initilaize();

    while (1) {
        // Check if the start button is pressed
        if (DIO_GetPinValue(PORTA, PIN0) == LOW) {
            // Start the stopwatch
            start_stopwatch();
        }

        // Check if the reset button is pressed
        if (DIO_GetPinValue(PORTB, PIN4) == LOW) {
            // Clear LCD display
            LCD_WriteCmd(0x01);
            _delay_ms(2);
        }

        // Add delay for stability
        _delay_ms(100);
    }

    return 0;
}

*/






/*


#define DEBOUNCE_DELAY_MS 300 // Increased debounce delay to 300 milliseconds
#define LED_PORT PORTD
#define LED_PIN PIN2

volatile unsigned int minutes = 0;
volatile unsigned int seconds = 0;
volatile int timer_set = 0;

void update_display(unsigned int min, unsigned int sec) {
    char display_string[6];
    sprintf(display_string, "%02d:%02d", min, sec);
    LCD_WriteCmd(0x01); // Clear display
    LCD_WriteString(display_string, 0, 0);
}

void set_timer(unsigned int min, unsigned int sec) {
    minutes = min;
    seconds = sec;
    timer_set = 1;
}

void decrement_timer() {
    if (timer_set) {
        if (seconds > 0 || minutes > 0) {
            if (seconds == 0) {
                if (minutes > 0) {
                    minutes--;
                    seconds = 59;
                }
            } else {
                seconds--;
            }
        } else {
            // Timer has reached zero
            DIO_SetPinValue(LED_PORT, LED_PIN, HIGH); // Turn on LED
            return;
        }
        update_display(minutes, seconds);
    }
}

void get_timer_from_user() {
    unsigned int min = 0;
    unsigned int sec = 0;
    unsigned char value;

    LCD_WriteString("Set Timer: MM:SS", 0, 0);
    _delay_ms(2000); // Wait for 2 seconds
    LCD_WriteCmd(0x01); // Clear display

    while (1) {
        // Get the minutes
        value = KEYPAD_getPressedKey();
        if (value >= '0' && value <= '9') {
            min = (min * 10) + (value - '0');
            LCD_WriteData(value);
            _delay_ms(DEBOUNCE_DELAY_MS);
        } else if (value == ':' && min < 60) {
            // Move to seconds input if minutes are less than 60
            LCD_WriteString(":", 0, 2);
            LCD_WriteString("SS", 0, 3);
            _delay_ms(1000); // Wait for 1 second
            break;
        } else if (value == '*' || value == '#') {
            continue;
        } else {
            min = 0; // Reset minutes if invalid input
        }
    }

    while (1) {
        // Get the seconds
        value = KEYPAD_getPressedKey();
        if (value >= '0' && value <= '9') {
            sec = (sec * 10) + (value - '0');
            LCD_WriteData(value);
            _delay_ms(DEBOUNCE_DELAY_MS);
        } else if (value == '=') {
            // Start the timer
            if (sec < 60) {
                set_timer(min, sec);
                break;
            } else {
                sec = 0; // Reset seconds if invalid input
            }
        } else if (value == '*' || value == '#') {
            continue;
        } else {
            sec = 0; // Reset seconds if invalid input
        }
    }
}


int main(void) {
    // Initialize LCD and keypad
    LCD_Initilaize();

    DIO_SetPinDirection(LED_PORT, LED_PIN, output); // Set LED pin as output
    _delay_ms(200); // Wait for LCD initialization

    get_timer_from_user();

    while (1) {
        decrement_timer();
        _delay_ms(1000); // Update every second
    }

    return 0;
}


*/














/*#define PORTD_REG (*(volatile uint8_t *)(0x32))
#define DDRD_REG  (*(volatile uint8_t *)(0x31))
#define PINB_REG  (*(volatile uint8_t *)(0x36))

#define PD2 2
#define PB4 4

#define OUTPUT 1
#define INPUT 0

#define HIGH 1
#define LOW 0

int main(void) {
    // Set PORTD pin 2 (PD2) as output
    SET_BIT(DDRD_REG, PD2);

    while (1) {
        // Check if the button connected to PORTB pin 4 (PB4) is pressed
        if (GET_BIT(PINB_REG, PB4) == HIGH) {
            // If the button is pressed, turn on the LED
            SET_BIT(PORTD_REG, PD2);
        } else {
            // If the button is not pressed, turn off the LED
            CLR_BIT(PORTD_REG, PD2);
        }
    }

    return 0;
}

*/






/*void push()
{

	//DIO_SetPinDirection(PORTB , PIN4, input);
	DIO_SetPinDirection(PORTD , PIN2, output);
while(1)
{

	DIO_SetPinValue(PORTD , PIN2, HIGH);

}
}

int main()
{
	push();
}
*/
