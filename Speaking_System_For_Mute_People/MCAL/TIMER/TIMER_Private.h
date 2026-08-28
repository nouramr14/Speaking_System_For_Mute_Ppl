/*
 * TIMER_Private.h
 *
 *  Created on: Aug 27, 2026
 *      Author: DELL
 */

#ifndef MCAL_TIMER_TIMER_PRIVATE_H_
#define MCAL_TIMER_TIMER_PRIVATE_H_


// Memory addresses for Timer0 registers
#define TCCR0_REG     (*((volatile u8 *)0x53))  // Timer/Counter Control Register
#define TCNT0_REG     (*((volatile u8 *)0x52))  // Timer/Counter Register
#define OCR0_REG      (*((volatile u8 *)0x5C))  // Output Compare Register
#define TIMSK_REG     (*((volatile u8 *)0x59))  // Timer Interrupt Mask Register
#define TIFR_REG      (*((volatile u8 *)0x58))  // Timer Interrupt Flag Register
#define SREG	      (*((volatile u8 *)0x5F))

// Bit positions
#define TCCR0_CS00    0
#define TCCR0_CS01    1
#define TCCR0_CS02    2
#define TCCR0_WGM01   3
#define TCCR0_COM00   4
#define TCCR0_COM01   5
#define TCCR0_WGM00   6
#define TCCR0_FOC0    7

#define TIMSK_TOIE0   0
#define TIMSK_OCIE0   1
/*Timer mode options*/
#define NORMAL_T_MODE		    	1
#define PWM_T_MODE			    	2
#define CTC_T_MODE			    	3
#define FAST_PWM_T_MODE		    	4

/*Prescaler options*/
#define NO_CLOCK_SOURCE				0
#define CLK							1
#define	CLK_8                       2
#define CLK_64            		 	3
#define CLK_256             		4
#define CLK_1024             		5
#define EXTC0_FALLING_EDGE          6
#define EXTC0_RISING_EDGE           7
#define TCCR1A			(*(volatile uint8_t*)0x4F)			//Timer/Counter1 control register A
/*TCCR1A register bits*/
#define	WGM10						(uint8_t)0
#define	WGM11						(uint8_t)1
#define	FOC1B						(uint8_t)2
#define	FOC1A						(uint8_t)3
#define	COM1B0						(uint8_t)4
#define	COM1B1						(uint8_t)5
#define	COM1A0						(uint8_t)6
#define	COM1A1						(uint8_t)7


#define TCCR1B			(*(volatile uint8_t*)0x4E) 			//Timer/Counter1 control register B
/*TCCR1B register bits*/
#define	CS10						(u8)0
#define	CS11						(u8)1
#define	CS12						(u8)2
#define	WGM12						(u8)3
#define	WGM13						(u8)4
/*------------------------------*/
#define	ICES1						(uint8_t)6
#define	ICNC1						(uint8_t)7


#define TCNT1H			(*(volatile uint8_t*)0x4D)			//Timer/Counter1 High Register

#define TCNT1L			(*(volatile uint8_t*)0x4C)			//Timer/Counter2 Low Register


#define OCR1AH			(*(volatile uint8_t*)0x4B)			//Output Compare High Register 1 A

#define OCR1AL			(*(volatile uint8_t*)0x4A)			//Output Compare Low Register 1 A


#define OCR1BH			(*(volatile uint8_t*)0x49)			//Output Compare High Register 1 B

#define OCR1BL			(*(volatile uint8_t*)0x48)			//Output Compare Low Register 1 B


#define ICR1H			(*(volatile uint8_t*)0x47)			//Input Capture High Register 1

#define ICR1L			(*(volatile uint8_t*)0x46)			//Input Capture Low Register 1


#define TIMSK			(*(volatile uint8_t*)0x59)			//Timer/Counter interrupt mask register
/*TIMSK register bits*/
#define	TOIE1						(uint8_t)2
#define	OCIE1B						(uint8_t)3
#define	OCIE1A						(uint8_t)4
#define	TICIE1						(uint8_t)5


#define TIFR			(*(volatile uint8_t*)0x58)			//Timer/Counter interrupt flag register
/*TIFR register bits*/
#define	TOV1						(uint8_t)2
#define	OCF1B						(uint8_t)3
#define	OCF1A						(uint8_t)4
#define	ICF1						(uint8_t)5


#endif /* MCAL_TIMER_TIMER_PRIVATE_H_ */
