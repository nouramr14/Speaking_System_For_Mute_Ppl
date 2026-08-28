/*
 * SHOW_Program.c
 *
 * Displays the recognized sentence on the LCD and sends each word to the
 * M16P/DFPlayer-style module using folder = sentence and file = word.
 */

#include <util/delay.h>

#include "../../../LIB/STD_Types.h"
#include "../../../HAL/LCD/LCD_Interface.h"
#include "../../../HAL/M16P_HANDLER/M16P_HANDLER_Interface.h"
#include "../../../HAL/M16P_HANDLER/M16P_HANDLER_Config.h"
#include "SHOW_Interface.h"

#define SHOW_MAX_WORDS ((u8)5)

void SHOW_vidShowAndPlayInit(void)
{
    LCD_vidInit();
    M16P_vidInit(BAUD);
    M16P_vidSetReply(0u);
    M16P_vidSetVolume(25u);
}

void SHOW_vidShowAndPlay(const u8* word_location)
{
    u8 i;
    u8 sentence;
    u8 word;

    if (word_location == NULL)
    {
        return;
    }

    LCD_vidClearDisplay();

    for (i = 0u; i < SHOW_MAX_WORDS; i++)
    {
        sentence = word_location[i * 2u];
        word = word_location[i * 2u + 1u];

        if (sentence == 0u && word == 0u)
        {
            break;
        }

        if (sentence == 0u && word == 1u)
        {
            continue;
        }

        LCD_vidDisplayString((u8*)"S");
        LCD_vidWriteInteger(sentence);
        LCD_vidDisplayString((u8*)"W");
        LCD_vidWriteInteger(word);
        LCD_vidDisplayString((u8*)" ");

        /* Folder = sentence number, file = word number. */
        M16P_vidPlayFileInFolder((u16)sentence, (u16)word);
        _delay_ms(500);
    }

    _delay_ms(1000);
    LCD_vidClearDisplay();
}
