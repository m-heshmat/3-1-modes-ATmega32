/*
 * LCD.c
 *
 *  Created on: Mar 24, 2024
 *      Author: Administrator

#include <avr/delay.h>

void LCDD()
{
	LCD_Initilaize();
	LCD_WriteData('A');
	LCD_WriteData('H');
	LCD_WriteData('M');
	LCD_WriteData('E');
	LCD_WriteData('D');
	_delay_ms(3000);
	LCD_WriteCmd(0x01);

}
*/
