/*
 * DIO.c
 *
 *  Created on: Mar 22, 2024
 *      Author: Administrator
 */


#include"DIO.h"
#include"DIO_types.h"
#include"DIO_REG.h"
#include"bit_math.h"



void DIO_SetPortDirection(DIO_PORT_ID port_ID , DIO_Direction direction)
{
	if(output == direction)
	{
		switch(port_ID)
		{
		case PORTA: DDRA_REG = 0xFF ; break;
		case PORTB: DDRB_REG = 0xFF ; break;
		case PORTC: DDRC_REG = 0xFF ; break;
		case PORTD: DDRD_REG = 0xFF ; break;
		}
	}
	else if(input == direction)
	{
		switch(port_ID)
	{
		case PORTA: DDRA_REG = 0x00 ; break;
		case PORTB: DDRB_REG = 0x00 ; break;
		case PORTC: DDRC_REG = 0x00 ; break;
		case PORTD: DDRD_REG = 0x00 ; break;

	}
	}

}

void DIO_SetPortValue(DIO_PORT_ID port_ID , u8 value)
{
	switch(port_ID)
	{
	case PORTA : PORTA_REG = value ; break;
	case PORTB : PORTB_REG = value ; break;
	case PORTC : PORTC_REG = value ; break;
	case PORTD : PORTD_REG = value ; break;

	}
}


void DIO_SetPinDirection(DIO_PORT_ID port_ID , DIO_PIN_ID pin_ID, DIO_Direction direction)
{
	if(port_ID <= PORTD && pin_ID <=7)
	{
		if(output == direction)
		{
			switch(port_ID)
			{
			case PORTA: DDRA_REG |= (1<<pin_ID); break;
			case PORTB: DDRB_REG |= (1<<pin_ID); break;
			case PORTC: DDRC_REG |= (1<<pin_ID); break;
			case PORTD: DDRD_REG  |= (1<<pin_ID); break;

			}
		}

		else if(input == direction)
		{
			switch(port_ID)
			{
			case PORTA: DDRA_REG &= ~(1<<pin_ID); break;
			case PORTB: DDRB_REG &= ~(1<<pin_ID); break;
			case PORTC: DDRC_REG &= ~(1<<pin_ID); break;
			case PORTD: DDRD_REG &= ~(1<<pin_ID); break;

			}
		}
	}

}

void DIO_SetPinValue(DIO_PORT_ID port_ID , DIO_PIN_ID pin_ID , DIO_Value value)
{
    if(port_ID <= PORTD && pin_ID <=7)
    {
        if(value == HIGH)
        {
            switch(port_ID)
            {
            case PORTA : SET_BIT(PORTA_REG , pin_ID); break;
            case PORTB : SET_BIT(PORTB_REG , pin_ID); break;
            case PORTC : SET_BIT(PORTC_REG , pin_ID); break;
            case PORTD : SET_BIT(PORTD_REG , pin_ID); break;
            default: break; // Added default case to handle unexpected port_ID
            }
        }
        else if(value == LOW)
        {
            switch(port_ID)
            {
            case PORTA : CLR_BIT(PORTA_REG , pin_ID); break;
            case PORTB : CLR_BIT(PORTB_REG , pin_ID); break;
            case PORTC : CLR_BIT(PORTC_REG , pin_ID); break;
            case PORTD : CLR_BIT(PORTD_REG , pin_ID); break;
            default: break; // Added default case to handle unexpected port_ID
            }
        }
    }
}

/*void DIO_EnablePullup(DIO_PORT_ID port_ID , DIO_PIN_ID pin_ID)
{
	if(port_ID <= PORTD && pin_ID <= PIN7)
		{

			switch(port_ID)
					{
					case PORTA :CLR_BIT(PORTA_REG , pin_ID); break;
					case PORTB :CLR_BIT(PORTB_REG , pin_ID); break;
					case PORTC :CLR_BIT(PORTC_REG , pin_ID); break;
					case PORTD :CLR_BIT(PORTD_REG , pin_ID); break;

					}
			}
}*/


DIO_Value DIO_GetPinValue(DIO_PORT_ID port_ID , DIO_PIN_ID pin_ID)
{
	DIO_Value PinValue;

	if(port_ID <= PORTD && pin_ID <= PIN7)
	{

		switch(port_ID)
				{
				case PORTA : PinValue = GET_BIT(PINA_REG , pin_ID); break;
				case PORTB : PinValue = GET_BIT(PINB_REG , pin_ID); break;
				case PORTC : PinValue = GET_BIT(PINC_REG , pin_ID); break;
				case PORTD : PinValue = GET_BIT(PIND_REG , pin_ID); break;

				}
		}

		return PinValue;
	}


