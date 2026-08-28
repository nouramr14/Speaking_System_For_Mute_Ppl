/*
 * M16P_HANDLER_Program.c
 *
 *  Created on: Aug 28, 2026
 *      Author: DELL
 */

#include "../../LIB/STD_Types.h"
#include "../M16P_handler/M16P_HANDLER_Interface.h"
#include "../../MCAL/UART/UART_Interface.h"
#include "../M16P_handler/M16P_HANDLER_Config.h"

static u8 send_buf[SERIAL_BUFF_SIZE] = {0x7E, 0xFF, 06, 00, 00, 00, 00, 00, 00, 0xEF};
static u8 recv_buf[SERIAL_BUFF_SIZE];
static u8 is_reply = 0;

void M16P_vidInit(u16 baud) {
    is_reply = 0;
    UART_Init(baud);
}

void M16P_vidSetReply(u8 state) {
    is_reply = state;
    send_buf[4] = is_reply;
}

static void M16P_vidFillBufUint16(u8 *thebuf, u16 data) {
    *thebuf = (u8)(data >> 8);
    *(thebuf + 1) = (u8)data;
}

static u16 M16P_Uu16GetCheckSum(u8 *thebuf) {
    u16 sum = 0;
    for (int i = 1; i < 7; i++) {
        sum += thebuf[i];
    }
    return -sum;
}

static void M16P_vidFillCheckSum() {
    u16 checksum = M16P_Uu16GetCheckSum(send_buf);
    M16P_vidFillBufUint16(send_buf + 7, checksum);
}

static void M16P_vidSendFunc() {
    for (int i = 0; i < SERIAL_BUFF_SIZE; i++) {
        UART_Transmit(send_buf[i]);
    }
}

static void M16P_vidSendCmd(uint8_t cmd, u16 arg1, u16 arg2) {
    send_buf[3] = cmd;
    send_buf[5] = arg1;
    send_buf[6] = arg2;
    M16P_vidFillCheckSum();
    M16P_vidSendFunc();
}

static void M16P_vidSendCmdSingleArg(u8 cmd, u16 arg) {
    send_buf[3] = cmd;
    M16P_vidFillBufUint16((send_buf + 5), arg);
    M16P_vidFillCheckSum();
    M16P_vidSendFunc();
}

static void M16P_vidSendCmdNoArg(u8 cmd) {
    send_buf[3] = cmd;
    M16P_vidFillBufUint16((send_buf + 5), 0);
    M16P_vidFillCheckSum();
    M16P_vidSendFunc();
}

void M16P_vidPlayTrack(u16 num) {
    M16P_vidSendCmdSingleArg(0x03, num);
}

void M16P_vidNextTrack() {
    M16P_vidSendCmdNoArg(0x01);
}

void M16P_vidPreviousTrack() {
    M16P_vidSendCmdNoArg(0x02);
}

void M16P_vidSetVolume(u16 volume) {
    M16P_vidSendCmdSingleArg(0x06, volume);
}

void M16P_vidSetEQ(u16 eq) {
    M16P_vidSendCmdSingleArg(0x07, eq);
}

void M16P_vidSetPlaybackSource(u16 device) {
    M16P_vidSendCmdSingleArg(0x09, device);
}

void M16P_vidSleep() {
    M16P_vidSendCmdNoArg(0x0a);
}

void M16P_vidReset() {
    M16P_vidSendCmdNoArg(0x0c);
}

void M16P_vidPlayback() {
    M16P_vidSendCmdNoArg(0x0d);
}

void M16P_vidPause() {
    M16P_vidSendCmdNoArg(0x0e);
}

void M16P_vidPlayFileInFolder(u16 folder, u16 file) {
    M16P_vidSendCmd(0x0f, folder, file);
}

void M16P_vidPlayByNumber(u16 num) {
    M16P_vidSendCmdSingleArg(0x12, num);
}



/*---------------------------------------------------------------------------*/



void M16P_vidGetState() {
    M16P_vidSendCmdNoArg(0x42);
}

void M16P_vidGetVolume() {
    M16P_vidSendCmdNoArg(0x43);
}

void M16P_vidGetUSum() {
    M16P_vidSendCmdNoArg(0x47);
}

void M16P_vidGetTFSum() {
    M16P_vidSendCmdNoArg(0x48);
}

void M16P_vidGetFlashSum() {
    M16P_vidSendCmdNoArg(0x49);
}

void M16P_vidGetTFCurrent() {
    M16P_vidSendCmdNoArg(0x4c);
}

void M16P_vidGetUCurrent() {
    M16P_vidSendCmdNoArg(0x4b);
}

void M16P_vidGetFlashCurrent() {
    M16P_vidSendCmdNoArg(0x4d);
}

uint8_t M16P_u8GetDataBuffer() {
    if (UART_Receive() != 0x7E) {
        return 0;
    }else{
    	recv_buf[0] = 0x7E;
    	for (int i = 1; i < SERIAL_BUFF_SIZE; i++) {
    		recv_buf[i] = UART_Receive();
    	}
    	return 1;
    }
}
