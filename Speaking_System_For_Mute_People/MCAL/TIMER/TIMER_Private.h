#ifndef MCAL_TIMER_TIMER_PRIVATE_H_
#define MCAL_TIMER_TIMER_PRIVATE_H_

#include "../../LIB/STD_Types.h"

#define TCCR0_REG (*((volatile u8*)0x53))
#define TCNT0_REG (*((volatile u8*)0x52))
#define OCR0_REG  (*((volatile u8*)0x5C))
#define TIMSK_REG (*((volatile u8*)0x59))
#define TIFR_REG  (*((volatile u8*)0x58))
#define SREG      (*((volatile u8*)0x5F))

#define TCCR0_CS00 0u
#define TCCR0_CS01 1u
#define TCCR0_CS02 2u
#define TCCR0_WGM01 3u
#define TCCR0_COM00 4u
#define TCCR0_COM01 5u
#define TCCR0_WGM00 6u
#define TCCR0_FOC0 7u
#define TIMSK_TOIE0 0u
#define TIMSK_OCIE0 1u

#define NORMAL_T_MODE 1u
#define PWM_T_MODE 2u
#define CTC_T_MODE 3u
#define FAST_PWM_T_MODE 4u

#define NO_CLOCK_SOURCE 0u
#define CLK 1u
#define CLK_8 2u
#define CLK_64 3u
#define CLK_256 4u
#define CLK_1024 5u
#define EXTC0_FALLING_EDGE 6u
#define EXTC0_RISING_EDGE 7u

#define TCCR1A (*((volatile u8*)0x4F))
#define WGM10 0u
#define WGM11 1u
#define FOC1B 2u
#define FOC1A 3u
#define COM1B0 4u
#define COM1B1 5u
#define COM1A0 6u
#define COM1A1 7u

#define TCCR1B (*((volatile u8*)0x4E))
#define CS10 0u
#define CS11 1u
#define CS12 2u
#define WGM12 3u
#define WGM13 4u
#define ICES1 6u
#define ICNC1 7u

#define TCNT1H (*((volatile u8*)0x4D))
#define TCNT1L (*((volatile u8*)0x4C))
#define OCR1AH (*((volatile u8*)0x4B))
#define OCR1AL (*((volatile u8*)0x4A))
#define OCR1BH (*((volatile u8*)0x49))
#define OCR1BL (*((volatile u8*)0x48))
#define ICR1H  (*((volatile u8*)0x47))
#define ICR1L  (*((volatile u8*)0x46))

#define TIMSK (*((volatile u8*)0x59))
#define TOIE1 2u
#define OCIE1B 3u
#define OCIE1A 4u
#define TICIE1 5u

#define TIFR (*((volatile u8*)0x58))
#define TOV1 2u
#define OCF1B 3u
#define OCF1A 4u
#define ICF1 5u

#endif
