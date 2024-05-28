/*
 * EXTI_reg.h
 *
 *  Created on: Mar 29, 2024
 *      Author: Administrator
 */

#ifndef MCAL_EXTI_EXTI_REG_H_
#define MCAL_EXTI_EXTI_REG_H_

#define SREG_REG             (*((volatile u8*)0x5F))
#define MCUCR_REG			 (*((volatile u8*)0x55))
#define MCUCSR_REG			 (*((volatile u8*)0x54))
#define GICR_REG			 (*((volatile u8*)0x5B))
#define GIFR_REG			 (*((volatile u8*)0x5A))



#endif /* MCAL_EXTI_EXTI_REG_H_ */
