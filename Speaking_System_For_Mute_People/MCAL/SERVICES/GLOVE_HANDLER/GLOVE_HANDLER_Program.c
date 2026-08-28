/*
 * GLOVE_HANDLER_Program.c
 *
 *  Created on: Aug 28, 2026
 *      Author: DELL
 */
#include"../../LIB/STD_Types.h"
#include"../../MCAL/ADC/ADC_Interface.h"
#include"../../HAL/FLEX_SENSOR/FLEX_SENSOR_Interface.h"

#include"../../HAL/TILT_SENSOR/tilt_sensor_int.h"

u16* SENSOR_READ = NULL;

u8 NO_OF_FLEX_SENSORS=0;

u16 READ = 0;
u16 i = 0;
u8 FLEX_SENSORS[8] = {FLEX_0, FLEX_1, FLEX_2, FLEX_3, FLEX_4, FLEX_5, FLEX_6, FLEX_7};


void GLOVE_vidCallBack()
{
	SENSOR_READ[i]=READ;
	if(i < NO_OF_FLEX_SENSORS-1)
	{
		SENSOR_READ[NO_OF_FLEX_SENSORS + 2]=0;
		i++;
		READ=0;
		FLEX_vidGetFlexRead(&READ,FLEX_SENSORS[i]);
	}else if(i == NO_OF_FLEX_SENSORS-1)
	{
		i=0;
		READ=0;
		SENSOR_READ[NO_OF_FLEX_SENSORS + 2]=1;
	}
}

void GLOVE_vidSensorsInit()
{
	FLEX_vidFlexInit(FLEX_ALL);
	TILT_vidInit(TILT_2);
	TILT_vidInit(TILT_3);
	FLEX_vidSetCallBack(&GLOVE_vidCallBack);
}

void GLOVE_vidSetGloveParams(u16* sensor_read, uint8_t no_of_sensors)
{
	SENSOR_READ = sensor_read;
	if(no_of_sensors<=8)NO_OF_FLEX_SENSORS = no_of_sensors - 2;
}

void GLOVE_vidGetHandRead()
{
	if(i==0)
	{
		TILT_vidGetTiltRead(&SENSOR_READ[NO_OF_FLEX_SENSORS],TILT_2);
		TILT_vidGetTiltRead(&SENSOR_READ[NO_OF_FLEX_SENSORS + 1],TILT_3);
		FLEX_vidGetFlexRead(&READ,FLEX_SENSORS[i]);
	}
}

