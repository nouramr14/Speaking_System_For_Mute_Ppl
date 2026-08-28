#include <avr/io.h>
#include "../../LIB/STD_Types.h"
#include "UART_Config.h"
#include "UART_Private.h"
#include "UART_Interface.h"

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

void UART_Init(u16 baud)
{
    u16 ubrr;

    if (baud == 0u) return;

    ubrr = (u16)((F_CPU / (16UL * (u32)baud)) - 1UL);

    UBRRH = (u8)(ubrr >> 8);
    UBRRL = (u8)ubrr;

    /* 8 data bits, 1 stop bit, no parity, normal asynchronous mode. */
    UCSRA = 0u;
    UCSRB = (1u << RXEN) | (1u << TXEN);
    UCSRC = (1u << URSEL) | (1u << UCSZ1) | (1u << UCSZ0);
}

void UART_Transmit(u8 data)
{
    while ((UCSRA & (1u << UDRE)) == 0u) { }
    UDR = data;
}

u8 UART_Receive(void)
{
    while ((UCSRA & (1u << RXC)) == 0u) { }
    return UDR;
}

void UART_TransmitString(u8* Copy_ptrString)
{
    u16 i = 0u;
    if (Copy_ptrString == NULL) return;
    while (Copy_ptrString[i] != '\0')
    {
        UART_Transmit(Copy_ptrString[i]);
        i++;
    }
}
