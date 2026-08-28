/*
 * UART_Program.c
 *
 *  Created on: Aug 27, 2026
 *      Author: DELL
 */
#include "../../LIB/STD_Types.h"
#include "../../LIB/BIT_MATH.h"

#include "UART_Config.h"
#include "UART_Private.h"
#include "UART_Interface.h"

void UART_Init(u16 baud) {
    u16 ubrr = (u16)(((u32)8000000/16)/baud-1);

    UBRRH = (u8)(ubrr>>8);
    UBRRL = (u8)ubrr;
    SET_BIT(UCSRB,4);
    SET_BIT(UCSRB,3);
    UCSRC = (1<<7) | (3<<1);
}

void UART_Transmit(u8 data) {
    while (!GET_BIT(UCSRA,5));
    UDR = data;
}

u8 UART_Receive(void) {
    while (!GET_BIT(UCSRA,7));
    return UDR;
}
