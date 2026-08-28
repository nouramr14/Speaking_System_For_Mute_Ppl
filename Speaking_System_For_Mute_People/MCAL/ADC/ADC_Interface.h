/*
 * ADC_Interface.h
 *
 * ATmega32 ADC driver interface.
 */
#ifndef MCAL_ADC_ADC_INTERFACE_H_
#define MCAL_ADC_ADC_INTERFACE_H_

#include "../../LIB/STD_Types.h"
#include <stdint.h>

#define AUTO_TRIGGER       0
#define SOFTWARE_TRIGGER   1

#define _8_BIT_MODE        0
#define _16_BIT_MODE       1

#define INTERRUPT_MODE     0
#define BOOLING_MODE       1

#define ADC_0              ((u8)0)
#define ADC_1              ((u8)1)
#define ADC_2              ((u8)2)
#define ADC_3              ((u8)3)
#define ADC_4              ((u8)4)
#define ADC_5              ((u8)5)
#define ADC_6              ((u8)6)
#define ADC_7              ((u8)7)
#define ADC_ALL             ((u8)8)

#define INT_0              ((u8)1)

#define INTERNAL_2_56_     ((u8)0)
#define VCC                 ((u8)1)
#define AREF_VOLTAGE        ((u8)2)

void ADC_vidAdcInit(u8 voltage_reference);
void ADC_vidAdcPinInit(u8 adc_pin);
void ADC_vidAdcGetRead(u8 adc_pin);
void ADC_vidGetAutoTriggerRead(void);
void ADC_VIDSetAutoTriggerMode(u8 mode);
void ADC_vidSetReadingVariable(u16* adc_read);
void ADC_vidSetCallBack(void (*func)(void));

#endif /* MCAL_ADC_ADC_INTERFACE_H_ */
