/*
 * Dio_types.h
 *
 *  Created on: Mar 22, 2024
 *      Author: Administrator
 */

#ifndef MCAL_DIO_DIO_TYPES_H_
#define MCAL_DIO_DIO_TYPES_H_

typedef enum{
	input, //0
	output //1
}DIO_Direction;

typedef enum{
	PORTA,
	PORTB,
	PORTC,
	PORTD
}DIO_PORT_ID;

typedef enum{
	LOW,
	HIGH
}DIO_Value;

typedef enum{
	PIN0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7
}DIO_PIN_ID;




#endif /* MCAL_DIO_DIO_TYPES_H_ */
