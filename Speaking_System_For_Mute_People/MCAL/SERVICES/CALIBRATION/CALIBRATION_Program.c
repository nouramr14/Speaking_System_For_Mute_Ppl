/*
 * CALIBRATION_Program.c
 *
 * Stores per-channel flex-sensor offsets in the ATmega32 EEPROM.
 * Calibration uses the existing STOPPING_WORD pose as the reference pose.
 *
 * The first five values are the five flex/ADC channels in the same order
 * used by GLOVE_HANDLER and GET_WORD_SOUND.
 */

#include <avr/eeprom.h>
#include <stdint.h>

#include "../../../LIB/STD_Types.h"
#include "CALIBRATION_Interface.h"

#define CAL_EEPROM_MAGIC ((u8)0xC7)

/* Reference values are the first five sensor values of STOPPING_WORD. */
static const u16 CAL_STOP_REFERENCE[CALIBRATION_ANALOG_SENSORS] =
{
    180u, 155u, 190u, 192u, 190u
};

static u8 EEMEM CAL_EEPROM_MAGIC_BYTE = 0xFFu;
static int16_t EEMEM CAL_EEPROM_OFFSETS[CALIBRATION_ANALOG_SENSORS];

static int16_t CAL_offsets[CALIBRATION_ANALOG_SENSORS];
static u8 CAL_valid = 0u;

void CAL_vidInit(void)
{
    u8 i;

    if (eeprom_read_byte(&CAL_EEPROM_MAGIC_BYTE) == CAL_EEPROM_MAGIC)
    {
        for (i = 0u; i < CALIBRATION_ANALOG_SENSORS; i++)
        {
            CAL_offsets[i] = (int16_t)eeprom_read_word(
                (const uint16_t*)&CAL_EEPROM_OFFSETS[i]);
        }
        CAL_valid = 1u;
    }
    else
    {
        for (i = 0u; i < CALIBRATION_ANALOG_SENSORS; i++)
        {
            CAL_offsets[i] = 0;
        }
        CAL_valid = 0u;
    }
}

u8 CAL_u8IsValid(void)
{
    return CAL_valid;
}

void CAL_vidCalibrateFromStopping(const u16* sensor_reads)
{
    u8 i;
    int32_t offset;

    if (sensor_reads == NULL)
    {
        return;
    }

    for (i = 0u; i < CALIBRATION_ANALOG_SENSORS; i++)
    {
        offset = (int32_t)sensor_reads[i] - (int32_t)CAL_STOP_REFERENCE[i];

        if (offset > 1023L)
        {
            offset = 1023L;
        }
        else if (offset < -1023L)
        {
            offset = -1023L;
        }

        CAL_offsets[i] = (int16_t)offset;
        eeprom_update_word((uint16_t*)&CAL_EEPROM_OFFSETS[i],
                           (uint16_t)CAL_offsets[i]);
    }

    eeprom_update_byte(&CAL_EEPROM_MAGIC_BYTE, CAL_EEPROM_MAGIC);
    CAL_valid = 1u;
}

void CAL_vidApply(u16* sensor_reads)
{
    u8 i;
    int32_t corrected;

    if ((sensor_reads == NULL) || (CAL_valid == 0u))
    {
        return;
    }

    for (i = 0u; i < CALIBRATION_ANALOG_SENSORS; i++)
    {
        corrected = (int32_t)sensor_reads[i] - (int32_t)CAL_offsets[i];

        if (corrected < 0L)
        {
            corrected = 0L;
        }
        else if (corrected > 1023L)
        {
            corrected = 1023L;
        }

        sensor_reads[i] = (u16)corrected;
    }
}

void CAL_vidClear(void)
{
    u8 i;

    eeprom_update_byte(&CAL_EEPROM_MAGIC_BYTE, 0xFFu);

    for (i = 0u; i < CALIBRATION_ANALOG_SENSORS; i++)
    {
        CAL_offsets[i] = 0;
    }

    CAL_valid = 0u;
}
