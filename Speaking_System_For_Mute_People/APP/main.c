/*
 * main.c
 *
 *  Created on: Aug 26, 2026
 *      Author: DELL
 */
#include <avr/io.h>

#include <avr/interrupt.h>

#include <util/delay.h>

#include "LIB/STD_Types.h"

#include "LIB/BIT_MATH.h"

#include "MCAL/DIO/DIO_interface.h"

#include "MCAL/ADC/ADC_Interface.h"

#include "MCAL/SPI/SPI_interface.h"

#include "MCAL/TIMER/TIMER_Interface.h"

#include "../HAL/LCD/LCD_Interface.h"



#include "../HAL/ADC/ADC_Interface.h"





#include "../SERVICES/GLOVE_HANDLER/GLOVE_HANDLER_Interface.h"
#include "../SERVICES/GET_WORD_SOUND/GET_WORD_SOUND_Interface.h"
#include "../..MCAL/SERVICE/SHOW/SHOW_Interface.h"
#include "../HAL/M16P_handler/M16P_HANDLER_Interface.h"
#include "../HAL/LED/LED_Interface.h"
#include "../MCAL/GIE/GIE_Interface.h"
#include "../mcal/TIMER/TIMER_Interface.h"
#include "util/delay.h"
#include "main.h"
#include "../HAL/LCD/LCD_Interface.h"

u16 sensor_reads[8];

#if APP_MODE == TRAIN

/*
 *
 * 179
 * 156
 * 190
 * 192
 * 190
 * 0
 * 1
 *
 * */

int main()
{
	u8 s1[9] =  "Thumb : ";
	u8 s2[11] = "Finger1 : ";
	u8 s3[11] = "Finger2 : ";
	u8 s4[11] = "Finger3 : ";
	u8 s5[11] = "Finger4 : ";
	u8 s6[19] = "Horizontal tilt : ";
	u8 s7[17] = "Vertical tilt : ";

	LCD_vidInit();
	GLOVE_vidSensorsInit();
	GLOVE_vidSetGloveParams(&sensor_reads[0],7);

	while(1)
	{
		GLOVE_vidGetHandRead();
		if(sensor_reads[7]==1)
		{
			LCD_vidClearDisplay();
			LCD_vidDisplayString(&s1[0]);
			LCD_vidWriteInteger(sensor_reads[4]);
			LCD_vidNewLine();
			LCD_vidDisplayString(&s2[0]);
			LCD_vidWriteInteger(sensor_reads[0]);
			_delay_ms(2000);
			LCD_vidClearDisplay();
			LCD_vidDisplayString(&s3[0]);
			LCD_vidWriteInteger(sensor_reads[2]);
			LCD_vidNewLine();
			LCD_vidDisplayString(&s4[0]);
			LCD_vidWriteInteger(sensor_reads[1]);
			_delay_ms(2000);
			LCD_vidClearDisplay();
			LCD_vidDisplayString(&s5[0]);
			LCD_vidWriteInteger(sensor_reads[3]);
			_delay_ms(2000);
			LCD_vidClearDisplay();
			LCD_vidDisplayString(&s6[0]);
			LCD_vidNewLine();
			LCD_vidWriteInteger(sensor_reads[5]);
			_delay_ms(2000);
			LCD_vidClearDisplay();
			LCD_vidDisplayString(&s7[0]);
			LCD_vidNewLine();
			LCD_vidWriteInteger(sensor_reads[6]);
			_delay_ms(2000);
		}

	}
	return 0;
}



#else

uint8_t word_location[10];
uint8_t get_another_read_flag = 1;
uint8_t ready_flag = 0;

extern u16 compare_cnt1;
void get_word();

int main()
{
	GLOBAL_INTERRUPT_vidGlobalInterruptEnable(ENABLED);
	uint8_t compare_value;
	GLOVE_vidSensorsInit();
	GLOVE_vidSetGloveParams(&sensor_reads[0],7);
	TIMER1_voidInit();
	TIMER1_voidGetNumCountCTC(1000, &compare_cnt1, &compare_value);
	TIMER1_voidSetCTCTime(compare_value);
	TIMER1_voidSetCallBackCTC(&get_word);
	GLOVE_vidGetHandRead();
	SHOW_vidShowAndPlayInit(&ready_flag);
	while(1)
	{
		while(ready_flag || get_another_read_flag);

		SHOW_vidShowAndPlay(&word_location[0]);
		get_another_read_flag = 1;
		GLOVE_vidGetHandRead();
	}

	return 0;
}


void get_word()
{
	static uint8_t i = 0;
	if(i<5 && sensor_reads[7] && get_another_read_flag)
	{
		LED_u8LedToggle(PORT_D, PIN_7);
		GET_vidGetWordAndSound(&sensor_reads[0], &word_location[i*2]);
		if(word_location[i*2]== 0 && word_location[i*2+1]== 1 )i--;
		else if(word_location[i*2]== 0 && word_location[i*2+1]== 0 )i=5;
		GLOVE_vidGetHandRead();
		i++;
	}else if (i == 5){
		word_location[9] = 0;
		word_location[10] = 0;
		i = 0;
		get_another_read_flag = 0;
	}else{
		i = 0;
		get_another_read_flag = 0;
	}

}
