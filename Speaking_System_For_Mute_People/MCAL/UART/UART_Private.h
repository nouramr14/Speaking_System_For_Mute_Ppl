/*
 * UART_Private.h
 *
 *  Created on: Aug 27, 2026
 *      Author: DELL
 */

#ifndef MCAL_UART_UART_PRIVATE_H_
#define MCAL_UART_UART_PRIVATE_H_


/* Register Bit Definitions */
#define RXC_BIT      7   // USART Receive Complete flag
#define TXC_BIT      6   // USART Transmit Complete flag
#define UDRE_BIT     5   // Data Register Empty flag

/* Private Internal Function Prototypes */
static void UART_voidCalculateBaudRate(u32 Copy_u32Baud);
#define UBRRH (*((volatile u8*)0x40))
#define UBRRL (*((volatile u8*)0x29))
#define UCSRA (*((volatile u8*)0x2B))
#define UCSRB (*((volatile u8*)0x2A))
#define UCSRC (*((volatile u8*)0x40))
#define UDR   (*((volatile u8*)0x2C))
#endif /* MCAL_UART_UART_PRIVATE_H_ */
