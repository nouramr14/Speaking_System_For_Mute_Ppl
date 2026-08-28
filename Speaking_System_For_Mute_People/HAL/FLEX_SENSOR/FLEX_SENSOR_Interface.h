/*
 * FLEX_SENSOR_Interface.h
 */
#ifndef HAL_FLEX_SENSOR_FLEX_SENSOR_INTERFACE_H_
#define HAL_FLEX_SENSOR_FLEX_SENSOR_INTERFACE_H_

#include "../../LIB/STD_Types.h"

#define FLEX_0  ADC_0
#define FLEX_1  ADC_1
#define FLEX_2  ADC_2
#define FLEX_3  ADC_3
#define FLEX_4  ADC_4
#define FLEX_5  ADC_5
#define FLEX_6  ADC_6
#define FLEX_7  ADC_7
#define FLEX_ALL ADC_ALL

void FLEX_vidFlexInit(u8 sensor_pin);
void FLEX_vidGetFlexRead(u16* sensor_read, u8 sensor_pin);
void FLEX_vidSetCallBack(void (*func)(void));

#endif /* HAL_FLEX_SENSOR_FLEX_SENSOR_INTERFACE_H_ */
