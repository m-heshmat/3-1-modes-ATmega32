

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "../../LIB/std.h"

/*______________________________________________________________________________
 |                               		Definitions                        		|
 |______________________________________________________________________________|
 */

/* Keypad configurations for number of rows and columns */
#define KEYPAD_NUM_COLS                   4
#define KEYPAD_NUM_ROWS                   4

/* Keypad Port Configurations */
#define KEYPAD_ROW_PORT_ID                PORTC
#define KEYPAD_FIRST_ROW_PIN_ID           PIN0

#define KEYPAD_COL_PORT_ID                PORTC
#define KEYPAD_FIRST_COL_PIN_ID           PIN4

/* Keypad button logic configurations */
#define KEYPAD_BUTTON_PRESSED            LOW
#define KEYPAD_BUTTON_RELEASED           HIGH

/*______________________________________________________________________________
 |                               Functions Prototypes                           |
 |______________________________________________________________________________|
 */

/*
 * Description :
 -> Get the Keypad pressed button
 */
u8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_H_ */
