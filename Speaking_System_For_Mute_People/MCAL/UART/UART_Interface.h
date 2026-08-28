/*
 * UART_Interface.h
 *
 *  Created on: Aug 27, 2026
 *      Author: DELL
 */

#ifndef MCAL_UART_UART_INTERFACE_H_
#define MCAL_UART_UART_INTERFACE_H_

#include "../../LIB/STD_Types.h" // Ensure your custom data types (u8, u16) are included first
void UART_Init(u16 baud);
void UART_Transmit(u8 data);
u8 UART_Receive(void);
void UART_TransmitString(u8* Copy_ptrString);

#endif /* MCAL_UART_UART_INTERFACE_H_ */
