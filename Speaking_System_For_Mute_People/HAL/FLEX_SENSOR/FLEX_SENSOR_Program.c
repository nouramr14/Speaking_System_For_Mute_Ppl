/*
 * FLEX_SENSOR_Program.c
 *
 *  Created on: Aug 28, 2026
 *      Author: DELL
 */

#include"../../LIB/BIT_MATH.h"
#include"../../LIB/STD_Types.h"
#include"../../MCAL/ADC/ADC_Interface.h"
#include"FLEX_SENSOR_Interface.h"


void FLEX_vidFlexInit(u8 sensor_pin)
{

	ADC_vidAdcInit(AREF_VOLTAGE);
	ADC_vidAdcPinInit(sensor_pin);

}

void FLEX_vidGetFlexRead(u16* sensor_read, uint8_t sensor_pin)
{
	ADC_vidSetReadingVariable(sensor_read);
	ADC_vidAdcGetRead(sensor_pin);
}

void FLEX_vidSetCallBack(void (*func)(void))
{
	ADC_vidSetCallBack(func);
}
