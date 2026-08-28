/* DIO_Interface.h */
#ifndef MCAL_DIO_DIO_INTERFACE_H_
#define MCAL_DIO_DIO_INTERFACE_H_

#include "DIO_Config.h"
#include "DIO_Private.h"
#include "../../LIB/STD_Types.h"
#include "../../LIB/BIT_MATH.h"

#define PORT_A ((u8)0)
#define PORT_B ((u8)1)
#define PORT_C ((u8)2)
#define PORT_D ((u8)3)

#define PIN_0 ((u8)0)
#define PIN_1 ((u8)1)
#define PIN_2 ((u8)2)
#define PIN_3 ((u8)3)
#define PIN_4 ((u8)4)
#define PIN_5 ((u8)5)
#define PIN_6 ((u8)6)
#define PIN_7 ((u8)7)

#define OUTPUT ((u8)1)
#define INPUT  ((u8)0)
#define HIGH ((u8)1)
#define LOW  ((u8)0)
#define Enabled ((u8)1)
#define Disabled ((u8)0)

#define E_OK ((u8)0)
#define E_NOK ((u8)1)

u8 DIO_u8SetPinMode(u8 port_id, u8 pin_no, u8 mode);
u8 DIO_u8SetPinValue(u8 port_id, u8 pin_no, u8 value);
u8 DIO_u8GetPinValue(u8 port_id, u8 pin_no, u8* value);
u8 DIO_u8IsPinOutPut(u8 port_id, u8 pin_no, u8* value);
u8 DIO_u8SetPullUpMode(u8 port_id, u8 pin_no, u8 mode);
u8 DIO_u8SetPortMode(u8 port_id, u8 mode);
u8 DIO_u8SetPortValue(u8 port_id, u8 value);
u8 DIO_u8GetPortValue(u8 port_id, u8* value);
u8 DIO_u8SetPortPullUpMode(u8 port_id, u8 mode);

#endif
