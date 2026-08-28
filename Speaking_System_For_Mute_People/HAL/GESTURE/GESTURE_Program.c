/*
 * GESTURE_Program.c
 *
 *  Created on: Aug 26, 2026
 *      Author: DELL
 */

#include "GESTURE_Config.h"
#include "GESTURE_Private.h"
#include "GESTURE_Interface.h"
#include "../LCD/LCD_Interface.h"
#include"../LCD/LCD_Config.h"
#include"../LCD/LCD_Private.h"
#include "../../MCAL/UART/UART_Interface.h" // Low-level serial communication driver
#include "../../MCAL/UART/UART_Config.h"
#include "../../MCAL/UART/UART_Private.h"

void Gesture_TriggerBinaryOutput(uint8_t matched_index) {
    if (matched_index >= TOTAL_WORDS) return;

    // 1. Display textual output on LCD
    LCD_String((char*)WORD_LIST[matched_index]);

    // 2. Build binary command packet frame
    uint8_t binary_code = BINARY_WORD_CODES[matched_index];
    uint8_t packet[4] = {
        CMD_START_BYTE, // Frame start
        CMD_PLAY_FILE,  // Action code
        binary_code,    // Payload (Binary word representation)
        CMD_END_BYTE    // Frame end
    };

    // 3. Send binary packet byte-by-byte over UART to the sound module
    for(uint8_t i = 0; i < 4; i++) {
        UART_TransmitByte(packet[i]);
    }
}
