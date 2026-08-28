/*
 * ADC_Interface.h

 *
 *  Created on: Aug 27, 2026
 *      Author: DELL
 */


#ifndef MCAL_ADC_ADC_INTERFACE_H_
#define MCAL_ADC_ADC_INTERFACE_H_
#include "ADC_Private.h"
#include"ADC_Config.h"
#include<stdint.h>
/*modes to use with ADC_TRIGGERING_MODE*/
#define AUTO_TRIGGER	  0
#define SOFTWARE_TRIGGER  1

/*modes to use with ADC_READING_NO_OF_BITS*/
#define _8_BIT_MODE	  0
#define _16_BIT_MODE  1

/*modes to use with ADC_READING_TECHNIQUE*/
#define INTERRUPT_MODE	0
#define BOOLING_MODE	1

/*adcs to use with the adc_pin param*/
#define ADC_0	(u8)0
#define ADC_1	(u81
#define ADC_2	(u8)2
#define ADC_3	(u8)3
#define ADC_4	(u8)4
#define ADC_5	(u8)5
#define ADC_6	(u8)6
#define ADC_7	(u8)7
#define ADC_ALL (u8)8

/*modes to use with set auto trigger mode param*/
#define INT_0		(u8)1

/*adcs to use with the voltage_reference param*/
#define INTERNAL_2_56_	(u8)0
#define VCC	(uint8_t)1
#define AREF_VOLTAGE	(u8)2

void ADC_vidAdcInit(uint8_t voltage_reference);

void ADC_vidAdcPinInit(uint8_t adc_pin);

void ADC_vidAdcGetRead(uint8_t adc_pin);

void ADC_vidGetAutoTriggerRead();

void ADC_VIDSetAutoTriggerMode(u8 mode);

void ADC_vidSetReadingVariable(u8* adc_read);

void ADC_vidSetCallBack( void (*func)(void));

#endif /* MCAL_ADC_ADC_INTERFACE_H_ */
