/*
 * M16P_HANDLER_Interface.h
 *
 *  Created on: Aug 28, 2026
 *      Author: DELL
 */

#ifndef HAL_M16P_HANDLER_M16P_HANDLER_INTERFACE_H_
#define HAL_M16P_HANDLER_M16P_HANDLER_INTERFACE_H_
void M16P_vidInit(u16 baud);
void M16P_vidSetReply(u8 state);
void M16P_vidPlayTrack(u16 num);
void M16P_vidNextTrack();
void M16P_vidPreviousTrack();
void M16P_vidSetVolume(u16 volume);
void M16P_vidSetEQ(u16 eq);
void M16P_vidSetPlaybackSource(u16 device);
void M16P_vidSleep();
void M16P_vidReset();
void M16P_vidPlayback();
void M16P_vidPause();
void M16P_vidPlayFileInFolder(u16 folder, u16 file);
void M16P_vidPlayByNumber(u16 num);
void M16P_vidGetState();
void M16P_vidGetVolume();
void M16P_vidGetUSum();
void M16P_vidGetTFSum();
void M16P_vidGetFlashSum();
void M16P_vidGetTFCurrent();
void M16P_vidGetUCurrent();
void M16P_vidGetFlashCurrent();
uint8_t M16P_u8GetDataBuffer();



#endif /* HAL_M16P_HANDLER_M16P_HANDLER_INTERFACE_H_ */
