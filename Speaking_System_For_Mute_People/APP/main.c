/*
 * main.c
 *
 * Application for the gesture-speaking glove.
 * Target: ATmega32, 8 MHz.
 */

#include <util/delay.h>
#include <stdint.h>

#include "../LIB/STD_Types.h"
#include "../HAL/LCD/LCD_Interface.h"
#include "../HAL/LED/LED_Interface.h"
#include "../HAL/M16P_HANDLER/M16P_HANDLER_Interface.h"
#include "../MCAL/SERVICES/GLOVE_HANDLER/GLOVE_HANDLER_Interface.h"
#include "../MCAL/SERVICES/GET_WORD_SOUND/GET_WORD_SOUND_Interface.h"
#include "../MCAL/SERVICES/CALIBRATION/CALIBRATION_Interface.h"
#include "../MCAL/SERVICES/SHOW/SHOW_Interface.h"
#include "main.h"

u16 sensor_reads[8] = {0u};

#if APP_MODE == TRAIN

int main(void)
{
    u8 s1[] = "Thumb : ";
    u8 s2[] = "Finger1 : ";
    u8 s3[] = "Finger2 : ";
    u8 s4[] = "Finger3 : ";
    u8 s5[] = "Finger4 : ";
    u8 s6[] = "H-Tilt : ";
    u8 s7[] = "V-Tilt : ";

    LCD_vidInit();
    GLOVE_vidSensorsInit();
    GLOVE_vidSetGloveParams(sensor_reads, 7u);

    while (1)
    {
        GLOVE_vidGetHandRead();

        if (sensor_reads[7] == 1u)
        {
            LCD_vidClearDisplay();
            LCD_vidDisplayString(s1);
            LCD_vidWriteInteger(sensor_reads[4]);
            LCD_vidNewLine();
            LCD_vidDisplayString(s2);
            LCD_vidWriteInteger(sensor_reads[0]);
            _delay_ms(1200);

            LCD_vidClearDisplay();
            LCD_vidDisplayString(s3);
            LCD_vidWriteInteger(sensor_reads[2]);
            LCD_vidNewLine();
            LCD_vidDisplayString(s4);
            LCD_vidWriteInteger(sensor_reads[1]);
            _delay_ms(1200);

            LCD_vidClearDisplay();
            LCD_vidDisplayString(s5);
            LCD_vidWriteInteger(sensor_reads[3]);
            LCD_vidNewLine();
            LCD_vidDisplayString(s6);
            LCD_vidWriteInteger(sensor_reads[5]);
            _delay_ms(1200);

            LCD_vidClearDisplay();
            LCD_vidDisplayString(s7);
            LCD_vidWriteInteger(sensor_reads[6]);
            _delay_ms(1200);
        }
    }
}

#else

static void APP_vidCalibrateIfNeeded(void)
{
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

        /* Give the user time to hold the STOPPING_WORD pose. */
        _delay_ms(2500);
        GLOVE_vidGetHandRead();
        CAL_vidCalibrateFromStopping(sensor_reads);

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
    u8 word_location[(MAX_WORDS_IN_SENTENCE * 2u) + 1u] = {0u};
    u8 current_word[2] = {0u};
    u8 previous_word[2] = {0xFFu, 0xFFu};
    u8 word_count = 0u;

    LCD_vidInit();
    GLOVE_vidSensorsInit();
    GLOVE_vidSetGloveParams(sensor_reads, 7u);

    APP_vidCalibrateIfNeeded();

    SHOW_vidShowAndPlayInit();

    LCD_vidClearDisplay();
    {
        u8 line1[] = "READY";
        LCD_vidDisplayString(line1);
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

            if (sensor_reads[7] == 0u)
            {
                _delay_ms(20);
                continue;
            }

            GET_vidGetWordAndSound(sensor_reads, current_word);

            /* STOPPING_WORD = {sentence=0, word=0}. */
            if (current_word[0] == 0u && current_word[1] == 0u)
            {
                break;
            }

            /* NOT_FOUND = {sentence=0, word=1}. Ignore it. */
            if (current_word[0] == 0u && current_word[1] == 1u)
            {
                _delay_ms(GESTURE_SAMPLE_DELAY_MS);
                continue;
            }

            /* Prevent one held gesture from filling multiple word slots. */
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

        word_location[word_count * 2u] = 0u;
        word_location[word_count * 2u + 1u] = 0u;
        word_location[(MAX_WORDS_IN_SENTENCE * 2u)] = 0u;

        if (word_count > 0u)
        {
            SHOW_vidShowAndPlay(word_location);
        }

        _delay_ms(500);
    }
}

#endif
