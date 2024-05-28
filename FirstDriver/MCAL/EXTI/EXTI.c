/*
 * EXTI.c
 *
 *  Created on: Mar 29, 2024
 *      Author: Administrator
 */
#include "EXTI.h"


void EXTI_INIT(void)
{

	CLR_BIT(MCUCR_REG,0);
	CLR_BIT(MCUCR_REG,1);
	CLR_BIT(MCUCR_REG,2);
	CLR_BIT(MCUCR_REG,3);
	CLR_BIT(MCUCSR_REG,6);


#if		EXTI0_MODE  == EXTI_LOW_LEVEL
	MCUCR_REG |= EXTI_LOW_LEVEL;
#elif	EXTI0_MODE	== EXTI_ANY_LOGICAL_CHANGE
	MCUCR_REG |= EXTI_ANY_LOGICAL_CHANGE;
#elif	EXTI0_MODE	== EXTI_FALLING_EDGE
	MCUCR_REG |= EXTI_FALLING_EDGE;
#elif	EXTI0_MODE	== EXTI_RISING_EDGE
	MCUCR_REG |= EXTI_RISING_EDGE;
#endif

#if		EXTI1_MODE  == EXTI_LOW_LEVEL
	MCUCR_REG |= (EXTI_LOW_LEVEL << 2);
#elif	EXTI1_MODE	== EXTI_ANY_LOGICAL_CHANGE
	MCUCR_REG |= (EXTI_ANY_LOGICAL_CHANGE << 2);
#elif	EXTI1_MODE	== EXTI_FALLING_EDGE
	MCUCR_REG |= (EXTI_FALLING_EDGE<< 2);
#elif	EXTI1_MODE	== EXTI_RISING_EDGE
	MCUCR_REG |=(EXTI_RISING_EDGE <<2);
#endif

#if		EXTI2_MODE  == EXTI_INT2_FALLING_EDGE
	MCUCSR_REG |= EXTI_INT2_FALLING_EDGE;
#elif	EXTI2_MODE	== EXTI_INT2_RISING_EDGE
	MCUCSR_REG |= EXTI_INT2_RISING_EDGE;
#endif
}

void EXTI_ENGlobal(void)  	/*enable Global interrupt*/
{
	SET_BIT(SREG_REG,7);
}

void EXTI_DIGlobal(void) /*Disable Global interrupt*/
{
	CLR_BIT(SREG_REG,7);
}


void EXTI_EN0(void)			/*enable external interrupt*/
{
	SET_BIT(GICR_REG,6);
}

void EXTI_DI0(void)			/*disable external interrupt*/
{

	CLR_BIT(GICR_REG,6);

}

void EXTI_SetCallBack( void (*CopyFuncPtr) (void))
{

}

