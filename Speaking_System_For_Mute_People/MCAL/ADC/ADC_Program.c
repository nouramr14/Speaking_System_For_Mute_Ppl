/*
 * ADC_Program.c
 *
 * ATmega32 ADC driver.
 * The application uses software-triggered, blocking conversions because
 * the glove needs a complete sensor frame before gesture recognition.
 */

#include <avr/io.h>
#include <stdint.h>

#include "../../LIB/STD_Types.h"
#include "ADC_Interface.h"

static u16* ADC_pu16ReadingVariable = NULL;
static void (*ADC_pvCallback)(void) = NULL;

void ADC_vidAdcInit(u8 voltage_reference)
{
    /* Disable ADC before configuration. */
    ADCSRA = 0;

    /* Right-adjust result; select reference voltage. */
    switch (voltage_reference)
    {
        case INTERNAL_2_56_:
            ADMUX = (1u << REFS1) | (1u << REFS0);
            break;

        case VCC:
            ADMUX = (1u << REFS0);
            break;

        case AREF_VOLTAGE:
        default:
            ADMUX = 0;
            break;
    }

    /* Enable ADC, prescaler = 128 => 62.5 kHz ADC clock at 8 MHz CPU. */
    ADCSRA = (1u << ADEN) |
             (1u << ADPS2) |
             (1u << ADPS1) |
             (1u << ADPS0);
}

void ADC_vidAdcPinInit(u8 adc_pin)
{
    if (adc_pin == ADC_ALL)
    {
        DDRA &= (u8)~0xFFu;
    }
    else if (adc_pin < 8u)
    {
        DDRA &= (u8)~(1u << adc_pin);
    }
}

void ADC_vidSetReadingVariable(u16* adc_read)
{
    ADC_pu16ReadingVariable = adc_read;
}

void ADC_vidSetCallBack(void (*func)(void))
{
    ADC_pvCallback = func;
}

void ADC_vidAdcGetRead(u8 adc_pin)
{
    u16 local_read;

    if (adc_pin > ADC_7 || ADC_pu16ReadingVariable == NULL)
    {
        return;
    }

    /* Keep the reference bits and replace only the channel bits. */
    ADMUX = (ADMUX & 0xE0u) | (adc_pin & 0x07u);

    ADCSRA |= (1u << ADSC);

    while (ADCSRA & (1u << ADSC))
    {
        /* Wait for conversion. */
    }

    local_read = ADC;
    *ADC_pu16ReadingVariable = local_read;

    if (ADC_pvCallback != NULL)
    {
        ADC_pvCallback();
    }
}

void ADC_vidGetAutoTriggerRead(void)
{
    /* Compatibility function. The project uses software triggering. */
}

void ADC_VIDSetAutoTriggerMode(u8 mode)
{
    if (mode == AUTO_TRIGGER)
    {
        ADCSRA |= (1u << ADATE);
    }
    else
    {
        ADCSRA &= (u8)~(1u << ADATE);
    }
}
