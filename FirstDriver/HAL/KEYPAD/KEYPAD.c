
#include <util/delay.h>

#include "KEYPAD.h"
#include "../../MCAL/DIO/DIO.h"

u8 static KEYPAD_Buttons_Arr [KEYPAD_NUM_ROWS][KEYPAD_NUM_COLS] = {
		{'1' ,'2' ,'3' ,'/'},
		{'4' ,'5' ,'6' ,'*'},
		{'7' ,'8' ,'9' ,'-'},
		{'P' ,'0' ,'=' ,'+'}
};
/*______________________________________________________________________________
 |                               Functions Definitions                          |
 |______________________________________________________________________________|
 */

u8 KEYPAD_getPressedKey(void)
{
	u8 col,row;
	DIO_SetPinDirection(PORTC, PIN0, input);
	DIO_SetPinDirection(PORTC, PIN1, input);
	DIO_SetPinDirection(PORTC, PIN2, input);
	DIO_SetPinDirection(PORTC, PIN3, input);

	DIO_SetPinDirection(PORTC,PIN4, input);
	DIO_SetPinDirection(PORTC, PIN5, input);
	DIO_SetPinDirection(PORTC, PIN6, input);
#if(KEYPAD_NUM_COLS == 4) //to characterize it between other keypads (4*3,4*6)
	DIO_SetPinDirection(PORTC, PIN7, input);
#endif
	while(1)
	{
		for(row=0 ; row<KEYPAD_NUM_ROWS ; row++) /* loop for rows */
		{
			/*
			 -> Each time setup the direction for all keypad port as input pins,
			    except this row will be output pin
			 */
			DIO_SetPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row,output);

			/* Set/Clear the row output pin */
			DIO_SetPinValue(KEYPAD_ROW_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID+row, KEYPAD_BUTTON_PRESSED);

			for(col=0 ; col<KEYPAD_NUM_COLS ; col++) /* loop for columns */
			{
				/* Check if the switch is pressed in this column */
				if(DIO_GetPinValue(KEYPAD_COL_PORT_ID,KEYPAD_FIRST_COL_PIN_ID+col) == KEYPAD_BUTTON_PRESSED)
				{
					return KEYPAD_Buttons_Arr [row][col];
				}
			}
			DIO_SetPinDirection(KEYPAD_ROW_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+row,input);
			_delay_ms(10); /* Add small delay to fix CPU load issue in proteus */
		}
	}
}
