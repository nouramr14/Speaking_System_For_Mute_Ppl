/*
 * GESTURE_Private.h
 *
 *  Created on: Aug 26, 2026
 *      Author: DELL
 */

#ifndef HAL_GESTURE_GESTURE_PRIVATE_H_
#define HAL_GESTURE_GESTURE_PRIVATE_H_

#include "GESTURE_config.h"
#include "GESTURE_Interface.h"

typedef struct {
    uint16_t flex_min[NUM_SENSORS];
    uint16_t flex_max[NUM_SENSORS];
    uint8_t  binary_cmd; // Holds the binary track payload
} GestureProfile_t;

// Mapping index to binary command byte
static const uint8_t BINARY_WORD_CODES[TOTAL_WORDS] = {
    0b00000001, // Yes
    0b00000010, // No
    0b00000011, // Help
    0b00000100, // Water
    0b00000101, // Food
    0b00000110  // Thank You
};

static const char WORD_LIST[TOTAL_WORDS][MAX_WORD_LENGTH] = {
    "Yes", "No", "Help", "Water", "Food", "Thank You"
};

static GestureProfile_t learned_gestures[TOTAL_WORDS];

#endif /* HAL_GESTURE_GESTURE_PRIVATE_H_ */
