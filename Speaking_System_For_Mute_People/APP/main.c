/*
 * main.c
 * Gesture-speaking glove application.
 * Target: ATmega32, 8 MHz.
 */
#include <util/delay.h>
#include "../LIB/STD_Types.h"
#include "../HAL/LCD/LCD_Interface.h"
#include "../MCAL/SERVICES/GLOVE_HANDLER/GLOVE_HANDLER_Interface.h"
#include "../MCAL/SERVICES/GET_WORD_SOUND/GET_WORD_SOUND_Interface.h"
#include "../MCAL/SERVICES/CALIBRATION/CALIBRATION_Interface.h"
#include "../MCAL/SERVICES/SHOW/SHOW_Interface.h"
#include "main.h"

#define SENSOR_COUNT ((u8)7)
#define CAL_SAMPLE_COUNT ((u8)20)

static u16 sensor_reads[SENSOR_COUNT + 1u] = {0u};

#if APP_MODE == TRAIN

int main(void)
{
    u8 labels[7][12] = {
        "Thumb: ", "Finger1: ", "Finger2: ", "Finger3: ",
        "Finger4: ", "H-Tilt: ", "V-Tilt: "
    };
    u8 i;

    LCD_vidInit();
    GLOVE_vidSensorsInit();
    GLOVE_vidSetGloveParams(sensor_reads, SENSOR_COUNT);

    while (1)
    {
        GLOVE_vidGetHandRead();
        if (sensor_reads[SENSOR_COUNT] == 1u)
        {
            for (i = 0u; i < SENSOR_COUNT; i += 2u)
            {
                LCD_vidClearDisplay();
                LCD_vidDisplayString(labels[i]);
                LCD_vidWriteInteger(sensor_reads[i]);
                if ((u8)(i + 1u) < SENSOR_COUNT)
                {
                    LCD_vidNewLine();
                    LCD_vidDisplayString(labels[i + 1u]);
                    LCD_vidWriteInteger(sensor_reads[i + 1u]);
                }
                _delay_ms(1000);
            }
        }
    }
}

#else

static void APP_vidCalibrateIfNeeded(void)
{
    u8 i;
    u8 sample;
    u32 sums[CALIBRATION_ANALOG_SENSORS] = {0UL,0UL,0UL,0UL,0UL};
    u16 average[8] = {0u};

    if (FORCE_CALIBRATION)
    {
        /* Remove old correction so a forced calibration always uses raw ADC values. */
        CAL_vidClear();
    }

    if (FORCE_CALIBRATION || !CAL_u8IsValid())
    {
        LCD_vidClearDisplay();
        {
            u8 line1[] = "Hold STOP";
            u8 line2[] = "Calibrating";
            LCD_vidDisplayString(line1);
            LCD_vidNewLine();
            LCD_vidDisplayString(line2);
        }

        _delay_ms(1500);

        for (sample = 0u; sample < CAL_SAMPLE_COUNT; sample++)
        {
            GLOVE_vidGetHandRead();
            for (i = 0u; i < CALIBRATION_ANALOG_SENSORS; i++)
            {
                sums[i] += sensor_reads[i];
            }
            _delay_ms(20);
        }

        for (i = 0u; i < CALIBRATION_ANALOG_SENSORS; i++)
        {
            average[i] = (u16)(sums[i] / CAL_SAMPLE_COUNT);
        }

        CAL_vidCalibrateFromStopping(average);

        LCD_vidClearDisplay();
        {
            u8 line1[] = "Calibration";
            u8 line2[] = "Saved";
            LCD_vidDisplayString(line1);
            LCD_vidNewLine();
            LCD_vidDisplayString(line2);
        }
        _delay_ms(1000);
    }
}

static u8 APP_u8SameWord(const u8* a, const u8* b)
{
    return (a[0] == b[0] && a[1] == b[1]) ? 1u : 0u;
}

int main(void)
{
    u8 word_location[(MAX_WORDS_IN_SENTENCE + 1u) * 2u] = {0u};
    u8 current_word[2] = {0u,0u};
    u8 previous_word[2] = {0xFFu,0xFFu};
    u8 word_count;

    LCD_vidInit();
    GLOVE_vidSensorsInit();
    GLOVE_vidSetGloveParams(sensor_reads, SENSOR_COUNT);

    APP_vidCalibrateIfNeeded();
    SHOW_vidShowAndPlayInit();

    LCD_vidClearDisplay();
    {
        u8 ready[] = "READY";
        LCD_vidDisplayString(ready);
    }
    _delay_ms(700);

    while (1)
    {
        word_count = 0u;
        previous_word[0] = 0xFFu;
        previous_word[1] = 0xFFu;

        while (word_count < MAX_WORDS_IN_SENTENCE)
        {
            GLOVE_vidGetHandRead();
            if (sensor_reads[SENSOR_COUNT] == 0u)
            {
                _delay_ms(20);
                continue;
            }

            GET_vidGetWordAndSound(sensor_reads, current_word);

            /* STOPPING_WORD terminates the sentence. */
            if (current_word[0] == 0u && current_word[1] == 0u) break;

            /* NOT_FOUND is ignored. */
            if (current_word[0] == 0u && current_word[1] == 1u)
            {
                _delay_ms(GESTURE_SAMPLE_DELAY_MS);
                continue;
            }

            if (!APP_u8SameWord(current_word, previous_word))
            {
                word_location[word_count * 2u] = current_word[0];
                word_location[word_count * 2u + 1u] = current_word[1];
                previous_word[0] = current_word[0];
                previous_word[1] = current_word[1];
                word_count++;
            }

            _delay_ms(GESTURE_SAMPLE_DELAY_MS);
        }

        /* Terminator pair is always inside the allocated buffer. */
        word_location[word_count * 2u] = 0u;
        word_location[word_count * 2u + 1u] = 0u;

        if (word_count > 0u) SHOW_vidShowAndPlay(word_location);
        _delay_ms(500);
    }
}
#endif
