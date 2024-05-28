/*
 * LCD.h
 *
 *  Created on: Mar 24, 2024
 *      Author: Administrator
 */

#ifndef HAL_LCD_H_
#define HAL_LCD_H_

void LCD_Initialize();
void LCD_Clear();
void LCD_WriteCmd(u8 CMD);
void LCD_WriteData(u8 DATA);  //probably keypad usage
void LCD_WriteString(u8 *Str,u8 ROW , u8 COL); //string
void LCD_GoToPos(u8 ROW , u8 COL);
//void LCD_printInt(f32 num);








#endif /* HAL_LCD_H_ */
