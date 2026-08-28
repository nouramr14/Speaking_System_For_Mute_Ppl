/*
 * TIMER_Program.c
 *
 *  Created on: Aug 27, 2026
 *      Author: DELL
 */
#include "../../LIB/STD_Types.h"
#include "../../LIB/BIT_MATH.h"
#include"TIMER_Config.h"
#include"TIMER_private.h"
#include"TIMER_Interface.h"

void (* TIMER1_voidpSetCallBackNormal)(void) = NULL;

void (* TIMER1_voidpSetCallBackCTC)(void) = NULL;

u16 compare_cnt1;

void TIMER1_voidInit(void){

	//Setting timer mode;
#if TIMER1_MODE == NORMAL_T_MODE

	CLR_BIT(TCCR1A , WGM10);
	CLR_BIT(TCCR1A , WGM11);
	CLR_BIT(TCCR1B , WGM12);
	CLR_BIT(TCCR1B , WGM13);

	//Enabling timer flag;
	SET_BIT(TIMSK , TOIE1);

	//selecting prescaler;
	TCCR1B &= 0b11111000;
	TCCR1B |= TIMER1_PRESCALER;

#elif TIMER1_MODE == PWM_T_MODE

	SET_BIT(TCCR1A , WGM10);
	CLR_BIT(TCCR1A , WGM11);
	CLR_BIT(TCCR1B , WGM12);
	CLR_BIT(TCCR1B , WGM13);

	//selecting prescaler;
	TCCR1B &= 0b11111000;
	TCCR1B |= TIMER1_PRESCALER;

#elif TIMER1_MODE == CTC_T_MODE

	CLR_BIT(TCCR1A , WGM10);
	CLR_BIT(TCCR1A , WGM11);
	SET_BIT(TCCR1B , WGM12);
	CLR_BIT(TCCR1B , WGM13);

	//Enabling timer flag;
	SET_BIT(TIMSK , OCIE1A);

	//selecting prescaler;
	TCCR1B &= 0b11111000;
	TCCR1B |= TIMER1_PRESCALER;

#elif TIMER1_MODE == FAST_PWM_T_MODE

	SET_BIT(TCCR1A , WGM10);
	CLR_BIT(TCCR1A , WGM11);
	SET_BIT(TCCR1B , WGM12);
	CLR_BIT(TCCR1B , WGM13);

	//selecting prescaler;
	TCCR1B &= 0b11111000;
	TCCR1B |= TIMER1_PRESCALER;

#else

#error "wrong timer mode"

#endif
}

void TIMER1_voidDisable(void){

	TCCR1B &= 0b11111000;

}

u8 TIMER1_uint8SetPrescaler(u8 Copy_uint8Prescaler){

	u8 Local_uint8ErrorState = 0;

	if(Copy_uint8Prescaler <8){

		//selecting prescaler;
		TCCR1B &= 0b11111000;
		TCCR1B |= Copy_uint8Prescaler;

	}
	else{

		Local_uint8ErrorState = 1;

	}

	return Local_uint8ErrorState;

}
void TIMER1_voidSetCounterRegister(u8 Copy_uint8Counter1Start){

	TCNT1L = Copy_uint8Counter1Start;
}

void TIMER1_voidSetCTCTime(u8 Copy_uint8CompareTime){

	 OCR1AL = Copy_uint8CompareTime;

}

void TIMER1_voidGetNumCountCTC(u16 Copy_uint8DesiredTime, u16 * Copy_uint16pNumOfCounts, u8 * Copy_uint8pCompareValue){

#define PRESCALER		TIMER1_PRESCALER

#if PRESCALER == CLK_1024
#define TICK_TIME		128

	* Copy_uint16pNumOfCounts = (u16)(((u32)Copy_uint8DesiredTime*1000)/((u32)TICK_TIME*250));
	* Copy_uint8pCompareValue = 250;

#elif PRESCALER == CLK_256
#define TICK_TIME		32

	* Copy_uint16pNumOfCounts = (uint16_)(((uint32_t)Copy_uint8DesiredTime*1000)/((uint32_t)TICK_TIME*250));
	* Copy_uint8pCompareValue = 250;

#elif PRESCALER == CLK_64
#define TICK_TIME		8

	* Copy_uint16pNumOfCounts = (uint16_)(((uint32_t)Copy_uint8DesiredTime*1000)/((uint32_t)TICK_TIME*250));
	* Copy_uint8pCompareValue = 250;

#elif PRESCALER == CLK_8

	* Copy_uint16pNumOfCounts = (uint16_)(((uint32_t)Copy_uint8DesiredTime*1000)/250);
	* Copy_uint8pCompareValue = 250;

#elif PRESCALER == CLK
#define TICK_TIME		12/100
	* Copy_uint16pNumOfCounts = (uint16_)(((uint32_t)Copy_uint8DesiredTime*1000)/(250*TICK_TIME));
	* Copy_uint8pCompareValue = 250;

#endif
}


void TIMER1_voidSetCallBackNormal(void (* Copy_uint8pSetCallBackNormal1)(void)){

	TIMER1_voidpSetCallBackNormal = Copy_uint8pSetCallBackNormal1;

}

void TIMER1_voidSetCallBackCTC(void (* Copy_uint8pSetCallBackCTC1)(void)){

	TIMER1_voidpSetCallBackCTC = Copy_uint8pSetCallBackCTC1;

}

void __vector_7(void) __attribute__((signal));
void __vector_7(void){

	static u16 cnt = 0;
	//extern uint16_ compare_cnt;
	cnt++;
	if(cnt == compare_cnt1){

//		TIMER_voidSetCounterRegister(123);
		if(TIMER1_voidpSetCallBackCTC != NULL){

			TIMER1_voidpSetCallBackCTC();
			cnt = 0;
		}
		else{

			//do nothing;

		}

	}


}

void __vector_9(void) __attribute__((signal));
void __vector_9(void){

	if(TIMER1_voidpSetCallBackNormal != NULL){

		TIMER1_voidpSetCallBackNormal();

	}
	else{

		//do nothing;

	}

}
