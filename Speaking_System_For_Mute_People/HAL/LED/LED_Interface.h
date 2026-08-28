/*
 * LED_Interface.h
 *
 *  Created on: Aug 28, 2026
 *      Author: DELL
 */

#ifndef HAL_LED_LED_INTERFACE_H_
#define HAL_LED_LED_INTERFACE_H_

/*
 * macros to be used in port_id param
 */
#define PORT_A (u8)0
#define PORT_B (u8)1
#define PORT_C (u8)2
#define PORT_D (u8)3

/*
 * macros to be used with pin_no param
 */
#define PIN_0 (u8)0
#define PIN_1 (u8)1
#define PIN_2 (u8)2
#define PIN_3 (u8)3
#define PIN_4 (u8)4
#define PIN_5 (u8)5
#define PIN_6 (u8)6
#define PIN_7 (u8)7

/*
 * error messages
 */
#define E_OK (u8)0
#define E_NOK (u8)1

u8 LED_u8LedOn(u8 port_id,u8 led_pin);
u8 LED_u8LedOff(u8 port_id,u8 led_pin);
u8 LED_u8LedToggle(u8 port_id,u8 led_pin);
u8 LED_u8LedBlink(u8 port_id,u8 led_pin,u16 delay_time_ms);

u8 LED_u8LedPortOn(u8 port_id);
u8 LED_u8LedPortOff(u8 port_id);
u8 LED_u8LedPortToggle(u8 port_id);
u8 LED_u8LedPortBlink(u8 port_id,u16 delay_time_ms);
u8 LED_u8InitializeLed(u8 port_id,u8 led_pin);
u8 LED_u8InitializeLedPort(u8 port_id);

#endif /* HAL_LED_LED_INTERFACE_H_ */
