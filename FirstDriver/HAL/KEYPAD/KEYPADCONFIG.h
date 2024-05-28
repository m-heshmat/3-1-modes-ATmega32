/*
 * KEYPADCONFIG.h
 *
 *  Created on: Mar 24, 2024
 *      Author: Administrator


#ifndef HAL_KEYPADCONFIG_H_
#define HAL_KEYPADCONFIG_H_



/*************************************************_SELECT_KEYPAD_DATA_PORT_***************************/
#define KEYPAD_PORT  					 PORTC

/****************************************************_SELECT_KEYPAD_PIN_***************************/
#define KEYPAD_R0_PIN                    PIN0
#define KEYPAD_R1_PIN                    PIN1
#define KEYPAD_R2_PIN                    PIN2
#define KEYPAD_R3_PIN                    PIN3
#define KEYPAD_C0_PIN                    PIN4
#define KEYPAD_C1_PIN                    PIN5
#define KEYPAD_C2_PIN                    PIN6
#define KEYPAD_C3_PIN                    PIN7


/***************************************************_SELECT_KEYPAD_MODEL_****************************/
/*_OPTION_1 -> [ MODEL_A ]   */
/*_OPTION_2 -> [ MODEL_B ]   */
/*_OPTION_2 -> [ MODEL_C ]   */
#define KEYPAD_MODEL                 MODEL_B

/**********************************************_SELECT_PUSHBUTTON_DEBOUNCING_TIME_***************************/
/*_SELECT_TIME_IN_MILLI_SECONDS_*/
#define KEYPAD_DEBOUNCING_TIME          1


#endif /* HAL_KEYPADCONFIG_H_ */

