/*
 * EXTI.h
 *
 *  Created on: Mar 29, 2024
 *      Author: Administrator
 */

#ifndef MCAL_EXTI_EXTI_H_
#define MCAL_EXTI_EXTI_H_
#include "EXTI_types.h"
#include "EXTI_reg.h"
#include "EXT_Config.h"
#include "std.h"
#include "bit_math.h"


void EXTI_INIT(void);

void EXTI_EN0(void);

void EXTI_DI0(void);

void EXTI_ENGlobal(void);

void EXTI_DIGlobal(void);


void EXTI_SetCallBack( void (*CopyFuncPtr) (void));



#endif /* MCAL_EXTI_EXTI_H_ */
