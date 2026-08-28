#include "../../LIB/STD_Types.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "LCD_Config.h"
#include "LCD_Interface.h"
#include <util/delay.h>

static u8 next_char_position = 0u;

void LCD_vidWriteData(u8 data)
{
    DIO_u8SetPinValue(LCD_RS_PORT, LCD_RS_PIN, HIGH);
    DIO_u8SetPinValue(LCD_RW_PORT, LCD_RW_PIN, LOW);
    DIO_u8SetPortValue(LCD_Data_PORT, data);
    DIO_u8SetPinValue(LCD_EN_PORT, LCD_EN_PIN, HIGH);
    _delay_us(100);
    DIO_u8SetPinValue(LCD_EN_PORT, LCD_EN_PIN, LOW);
    _delay_us(100);
}

void LCD_vidWriteCmd(u8 command)
{
    DIO_u8SetPinValue(LCD_RS_PORT, LCD_RS_PIN, LOW);
    DIO_u8SetPinValue(LCD_RW_PORT, LCD_RW_PIN, LOW);
    DIO_u8SetPortValue(LCD_Data_PORT, command);
    DIO_u8SetPinValue(LCD_EN_PORT, LCD_EN_PIN, HIGH);
    _delay_us(100);
    DIO_u8SetPinValue(LCD_EN_PORT, LCD_EN_PIN, LOW);
    _delay_us(100);
}

void LCD_vidInit(void)
{
    DIO_u8SetPinMode(LCD_RS_PORT, LCD_RS_PIN, OUTPUT);
    DIO_u8SetPinMode(LCD_RW_PORT, LCD_RW_PIN, OUTPUT);
    DIO_u8SetPinMode(LCD_EN_PORT, LCD_EN_PIN, OUTPUT);
    DIO_u8SetPortMode(LCD_Data_PORT, 0xFFu);

    _delay_ms(40);
    LCD_vidWriteCmd(0x38u); /* 8-bit, 2-line, 5x8 font */
    _delay_ms(5);
    LCD_vidWriteCmd(0x0Cu); /* Display ON, cursor OFF */
    _delay_ms(1);
    LCD_vidWriteCmd(0x01u); /* Clear */
    _delay_ms(2);
    LCD_vidWriteCmd(0x06u); /* Increment cursor */
    next_char_position = 0u;
}

void LCD_vidDisplayString(u8* string)
{
    u8 i;
    if (string == NULL) return;

    for (i = 0u; string[i] != '\0'; i++)
    {
        if (next_char_position == 16u)
        {
            LCD_vidWriteCmd(0xC0u);
            next_char_position = 16u;
        }
        LCD_vidWriteData(string[i]);
        if (next_char_position < 32u) next_char_position++;
    }
}

void LCD_vidNewLine(void)
{
    LCD_vidWriteCmd(0xC0u);
    next_char_position = 16u;
}

void LCD_vidDisplayStringLeftShift(u8* string)
{
    if (string == NULL) return;
    LCD_vidDisplayString(string);
    while (1)
    {
        LCD_vidWriteCmd(0x18u);
        _delay_ms(500);
    }
}

void LCD_vidDisplayStringRightShift(u8* string)
{
    if (string == NULL) return;
    LCD_vidDisplayString(string);
    while (1)
    {
        LCD_vidWriteCmd(0x1Cu);
        _delay_ms(500);
    }
}

void LCD_vidClearDisplay(void)
{
    LCD_vidWriteCmd(0x01u);
    _delay_ms(2);
    next_char_position = 0u;
}

void LCD_vidGoTo(u8 x, u8 y)
{
    if (x == 1u && y < 16u)
    {
        LCD_vidWriteCmd((u8)(0x80u + y));
        next_char_position = y;
    }
    else if (x == 2u && y < 16u)
    {
        LCD_vidWriteCmd((u8)(0xC0u + y));
        next_char_position = (u8)(16u + y);
    }
}

void LCD_vidSetCursor(u8 x, u8 y)
{
    LCD_vidGoTo(x, y);
    LCD_vidWriteCmd(0x0Fu);
}

void LCD_vidWriteInteger(u16 number)
{
    u16 divisor = 1u;
    u16 value;

    if (number == 0u)
    {
        LCD_vidWriteData('0');
        if (next_char_position < 32u) next_char_position++;
        return;
    }

    while ((number / divisor) >= 10u && divisor <= 1000u) divisor *= 10u;

    while (divisor > 0u)
    {
        value = number / divisor;
        LCD_vidWriteData((u8)('0' + value));
        if (next_char_position < 32u) next_char_position++;
        number = (u16)(number % divisor);
        if (divisor == 1u) break;
        divisor /= 10u;
    }
}
