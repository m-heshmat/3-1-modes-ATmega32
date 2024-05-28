#include <avr/delay.h>

#include "../LIB/std.h"
#include "../LIB/bit_math.h"

#include "../MCAL/DIO/DIO_types.h"
#include "../MCAL/DIO/DIO.h"


static u8 InitStepFinished = 0;


void LCD_Initilaize(void)//initialize the LCD
{
	DIO_SetPortDirection(PORTA , output);

	_delay_ms(30);

	LCD_WriteCmd(0x20); //0010 0000 (LCD 4-BIT mode)
	LCD_WriteCmd(0x20); //0010 0000 (repeat)
	LCD_WriteCmd(0x80); //1000 0000 (2-line display)

	_delay_ms(1);

	LCD_WriteCmd(0x00); //next command
	LCD_WriteCmd(0xF0); //1DCB, to turn on the display,cursor,and blinking
	_delay_ms(1);

	LCD_WriteCmd(0x00);  //next command
	LCD_WriteCmd(0x01); //for display clear as datasheet
	_delay_ms(2);



	InitStepFinished=1;
}


void LCD_WriteCmd(u8 CMD)//to send instruction to the LCD

{


	DIO_SetPinValue(PORTA ,PIN1,LOW);  //RS=0
	DIO_SetPinValue(PORTA ,PIN2,LOW);  //RW=0


	/*MSB ON THE LEFT SIDE*/

	DIO_SetPinValue(PORTA ,PIN4,GET_BIT(CMD , 4));  //DB4
	DIO_SetPinValue(PORTA ,PIN5,GET_BIT(CMD , 5));  //DB5
	DIO_SetPinValue(PORTA ,PIN6,GET_BIT(CMD , 6));  //DB6
	DIO_SetPinValue(PORTA ,PIN7,GET_BIT(CMD , 7));  //DB7

	DIO_SetPinValue(PORTA,PIN3,HIGH); //EN

	_delay_ms(1);//because of the falling edge from high to low

	DIO_SetPinValue(PORTA,PIN3,LOW); //EN

	if(InitStepFinished)//since it becomes 1 the LSB will work
	{

	/*LSB ON THE RIGHT SIDE*/

	DIO_SetPinValue(PORTA ,PIN4,GET_BIT(CMD , 0));  //DB4
	DIO_SetPinValue(PORTA ,PIN5,GET_BIT(CMD , 1));  //DB5
	DIO_SetPinValue(PORTA ,PIN6,GET_BIT(CMD , 2));  //DB6
	DIO_SetPinValue(PORTA ,PIN7,GET_BIT(CMD , 3));  //DB7

	DIO_SetPinValue(PORTA,PIN3,HIGH);  //EN
	_delay_ms(1);

	DIO_SetPinValue(PORTA,PIN3,LOW);   //EN
	}
	_delay_ms(2);//because maximum seconds can an instruction wait is 1.53ms so we choose 2 in general


}

void LCD_WriteData(u8 DATA)

{
		DIO_SetPinValue(PORTA ,PIN1,HIGH);  //RS=1,when it comes to write data on the LCD RS=1,RW=0;
		DIO_SetPinValue(PORTA ,PIN2,LOW);  //RW=0


		/*MSB ON THE LEFT SIDE*/

		DIO_SetPinValue(PORTA ,PIN4,GET_BIT(DATA , 4));  //DB4
		DIO_SetPinValue(PORTA ,PIN5,GET_BIT(DATA , 5));  //DB5
		DIO_SetPinValue(PORTA ,PIN6,GET_BIT(DATA , 6));  //DB6
		DIO_SetPinValue(PORTA ,PIN7,GET_BIT(DATA , 7));  //DB7

		DIO_SetPinValue(PORTA,PIN3,HIGH);  //EN

		_delay_ms(1);//because of the falling edge from high to low

		DIO_SetPinValue(PORTA,PIN3,LOW);   //EN



		/*LSB ON THE RIGHT SIDE*/

		DIO_SetPinValue(PORTA ,PIN4,GET_BIT(DATA , 0));  //DB4
		DIO_SetPinValue(PORTA ,PIN5,GET_BIT(DATA , 1));  //DB5
		DIO_SetPinValue(PORTA ,PIN6,GET_BIT(DATA , 2));  //DB6
		DIO_SetPinValue(PORTA ,PIN7,GET_BIT(DATA , 3));  //DB7

		DIO_SetPinValue(PORTA,PIN3,HIGH);
		_delay_ms(1);

		DIO_SetPinValue(PORTA,PIN3,LOW);

		_delay_ms(2);//because maximum seconds can an instruction wait is 1.53ms so we choose 2 in general


}

void LCD_GoToPos(u8 ROW , u8 COL)
{
	u8 address;
	if(ROW < 2 && COL <16)
	{
		address = (ROW *0x40)+COL;
		address = SET_BIT(address,7);
		LCD_WriteCmd(address);
	}
}
void LCD_WriteString(u8 *str,u8 ROW , u8 COL)
{
	LCD_GoToPos(ROW,COL);
	u8 index = 0;
	u8 line0 = 0;
	while(str[index] != '\0' && ((ROW * 16) + (index + COL ))< 32)//by default it will continue working until finding '\0'
	{
		if(((ROW * 16) + (index + COL ))< 16) //row=0,col=0,index=0
		{
		LCD_WriteData(str[index]); //r=0,col=1,index=1
		index++;
		}
		else if(((ROW * 16) + (index + COL ))==16 && line0 ==0)
		{
			LCD_GoToPos(1,0);
			line0++;
		}
		else if(((ROW * 16) + (index + COL ))<32 && line0 ==1)
		{
			LCD_WriteData(str[index]);
			index++;
		}

	}
}

void LCD_Clear()
{
	LCD_WriteCmd(0x01);
}
/*void LCD_printInt(f32 no)
{
  char toprint[4] = {0};
  sprintf(toprint, "%d", no);
  int i = 0;
  while(toprint[i] != '\0')
  {
    LCD_WriteData(toprint[i]);
    i++;
  }
}*/
