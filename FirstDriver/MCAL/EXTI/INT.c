/*
 * INT.c
 *
 *  Created on: Apr 8, 2024
 *      Author: Administrator
 */
/*#include "INT.h"
#inclu
void INT_vidSetPin( u8 pin, u8 mode )
{
	// parameters check:
	if( (mode != LOW_LEVEL && mode != LOGICAL_CHANGE
			&& mode != FALLING_EDGE && mode != RISING_EDGE)
			|| (pin != PB2 && pin != PD2 && pin != PD3) )
	{ return; }

	// setting pin as input with pull-up:
	DIO_vidSetPinDir( pin, input );
	DIO_vidSetPinVal( pin, HIGH );

	// setting interrupt mode and enabling interrupt:
	switch( pin )
	{
	// INT0:
	case PD2:
		// ISC00:
		if( mode == LOW_LEVEL || mode == FALLING_EDGE )
		{ clearBit( MCUCR, ISC00 ); }
		else
		{ setBit( MCUCR, ISC00 ); }
		// ISC01:
		if( mode == LOW_LEVEL || mode == LOGICAL_CHANGE )
		{ clearBit( MCUCR, ISC01 ); }
		else
		{ setBit( MCUCR, ISC01 ); }
		// enable interrupt mask in
		// General Interrupt Control Register:
		setBit( GICR, 6 );
		break;

	// INT1
	case PD3:
		// ISC10:
		if( mode == LOW_LEVEL || mode == FALLING_EDGE )
		{ clearBit( MCUCR, ISC10 ); }
		else
		{ setBit( MCUCR, ISC10 ); }
		// ISC11:
		if( mode == LOW_LEVEL || mode == LOGICAL_CHANGE )
		{ clearBit( MCUCR, ISC11 ); }
		else
		{ setBit( MCUCR, ISC11 ); }
		setBit( GICR, 7 );
		break;

	// INT2
	case PB2:
		if( mode == FALLING_EDGE )
		{ clearBit( MCUCSR, ISC2); }
		else if( mode == RISING_EDGE )
		{ setBit( MCUCSR, ISC2 ); }
		setBit( GICR, 5 );
	}
}

void
INT_vidClearFlag( u8 num )
{
	switch( num )
	{
	case 0:
		clearBit( GIFR, INTF0 );
		break;

	case 1:
		clearBit( GIFR, INTF1 );
		break;

	case 2:
		clearBit( GIFR, INTF2 );
		break;
	}
}

u8
INT_u8ReadFlag( u8 num )
{
	u8 flag = 0;

	switch( num )
	{
	case 0:
		flag = getBit( GIFR, INTF0 );
		break;

	case 1:
		flag = getBit( GIFR, INTF1 );
		break;

	case 2:
		flag = getBit( GIFR, INTF2 );
		break;
	}
	return flag;
}
*/
