/*
 * GESTURE_Interface.h
 *
 *  Created on: Aug 26, 2026
 *      Author: DELL
 */

#ifndef HAL_GESTURE_GESTURE_INTERFACE_H_
#define HAL_GESTURE_GESTURE_INTERFACE_H_
#include <avr/io.h>

// Words defined directly as 8-bit binary literals (HEX / BINARY)
typedef enum {
    WORD_YES       = 0b00000001, // 0x01
    WORD_NO        = 0b00000010, // 0x02
    WORD_HELP      = 0b00000011, // 0x03
    WORD_WATER     = 0b00000100, // 0x04
    WORD_FOOD      = 0b00000101, // 0x05
    WORD_THANK_YOU = 0b00000110  // 0x06
} WordBinaryCode_t;

void Gesture_Init(void);
void Gesture_TriggerBinaryOutput(uint8_t matched_index);


#endif /* HAL_GESTURE_GESTURE_INTERFACE_H_ */
