/*
 * GESTURE_Config.h
 *
 *  Created on: Aug 26, 2026
 *      Author: DELL
 */

#ifndef HAL_GESTURE_GESTURE_CONFIG_H_
#define HAL_GESTURE_GESTURE_CONFIG_H_

#define TOTAL_WORDS         6
#define NUM_SENSORS         3
#define SENSOR_TOLERANCE    20
#define MAX_WORD_LENGTH     16

// Binary Protocol Definitions
#define CMD_START_BYTE      0x7E // Binary start frame (0b01111110)
#define CMD_PLAY_FILE       0x03 // Binary command code for play (0b00000011)
#define CMD_END_BYTE        0xEF // Binary end frame (0b11101111)

#endif /* HAL_GESTURE_GESTURE_CONFIG_H_ */
