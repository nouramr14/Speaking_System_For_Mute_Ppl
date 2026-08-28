#include <util/delay.h>
#include "../../../LIB/STD_Types.h"
#include "../../../HAL/LCD/LCD_Interface.h"
#include "../../../HAL/M16P_HANDLER/M16P_HANDLER_Interface.h"
#include "../../../HAL/M16P_HANDLER/M16P_HANDLER_Config.h"
#include "SHOW_Interface.h"

#define SHOW_MAX_WORDS ((u8)5)

void SHOW_vidShowAndPlayInit(void)
{
    M16P_vidInit(BAUD);
    M16P_vidSetReply(0u);
    M16P_vidSetVolume(25u);
}

void SHOW_vidShowAndPlay(const u8* word_location)
{
    u8 i;
    u8 sentence;
    u8 word;
    const u8 s[] = "S";
    const u8 w[] = "W";
    const u8 space[] = " ";

    if (word_location == NULL) return;

    LCD_vidClearDisplay();

    for (i = 0u; i < SHOW_MAX_WORDS; i++)
    {
        sentence = word_location[i * 2u];
        word = word_location[i * 2u + 1u];

        if (sentence == 0u && word == 0u) break;
        if (sentence == 0u && word == 1u) continue;

        LCD_vidDisplayString(s);
        LCD_vidWriteInteger(sentence);
        LCD_vidDisplayString(w);
        LCD_vidWriteInteger(word);
        LCD_vidDisplayString(space);

        M16P_vidPlayFileInFolder((u16)sentence, (u16)word);
        _delay_ms(500);
    }

    _delay_ms(500);
    LCD_vidClearDisplay();
}
