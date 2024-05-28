#ifndef MCAL_DIO_DIO_H_
#define MCAL_DIO_DIO_H_

#include "std.h"
#include "DIO_types.h"

void DIO_SetPortDirection(DIO_PORT_ID port_ID , DIO_Direction direction);
void DIO_SetPortValue(DIO_PORT_ID port_ID , u8 value);
void DIO_SetPinDirection(DIO_PORT_ID port_ID , DIO_PIN_ID pin_ID, DIO_Direction direction);
void DIO_SetPinValue(DIO_PORT_ID port_ID , DIO_PIN_ID pin_ID , DIO_Value value);
void DIO_EnablePullup(DIO_PORT_ID port_ID, DIO_PIN_ID pin_ID);
DIO_Value DIO_GetPinValue(DIO_PORT_ID port_ID , DIO_PIN_ID pin_ID);

#endif /* MCAL_DIO_DIO_H_ */
