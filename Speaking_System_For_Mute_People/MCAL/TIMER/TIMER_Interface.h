/*
 * TIMER_Interface.h
 *
 *  Created on: Aug 27, 2026
 *      Author: DELL
 */

#ifndef MCAL_TIMER_TIMER_INTERFACE_H_
#define MCAL_TIMER_TIMER_INTERFACE_H_
#include "TIMER_Config.h"
#include "../../LIB/STD_Types.h"
/*Prescaler options*/
#define NO_CLOCK_SOURCE				0
#define CLK							1
#define	CLK_8                       2
#define CLK_64            		 	3
#define CLK_256             		4
#define CLK_1024             		5
#define EXTC0_FALLING_EDGE          6
#define EXTC0_RISING_EDGE           7
// Initialize the timer with configuration
void TMR0_Init(void);

// Start the timer for a given time in milliseconds
void TMR0_Start(u16 milliseconds);

// Stop the timer
void TMR0_Stop(void);

// Set a callback function to be called after the timer completes
void TMR0_SetCallback(void (*callbackFunc)(void));
void TIMER1_voidInit(void);

void TIMER1_voidDisable(void);

void TIMER1_voidSetCounterRegister(u8 Copy_uint8Counter1Start);

u8 TIMER1_uint8SetPrescaler(u8 Copy_uint8Prescaler);

void TIMER1_voidSetCTCTime(u8 Copy_uint8CompareTime);

void TIMER1_voidSetCallBackNormal(void (* Copy_uint8pSetCallBackNormal1)(void));

void TIMER1_voidSetCallBackCTC(void (* Copy_uint8pSetCallBackCTC1)(void));

void TIMER1_voidGetNumCountCTC(u16 Copy_uint8DesiredTime, u16 * Copy_uint16pNumOfCounts, u8 * Copy_uint8pCompareValue);

#endif /* MCAL_TIMER_TIMER_INTERFACE_H_ */
