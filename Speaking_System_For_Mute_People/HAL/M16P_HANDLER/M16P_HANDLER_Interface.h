#ifndef HAL_M16P_HANDLER_M16P_HANDLER_INTERFACE_H_
#define HAL_M16P_HANDLER_M16P_HANDLER_INTERFACE_H_

#include "../../LIB/STD_Types.h"

void M16P_vidInit(u16 baud);
void M16P_vidSetReply(u8 state);
void M16P_vidPlayTrack(u16 num);
void M16P_vidNextTrack(void);
void M16P_vidPreviousTrack(void);
void M16P_vidSetVolume(u16 volume);
void M16P_vidSetEQ(u16 eq);
void M16P_vidSetPlaybackSource(u16 device);
void M16P_vidSleep(void);
void M16P_vidReset(void);
void M16P_vidPlayback(void);
void M16P_vidPause(void);
void M16P_vidPlayFileInFolder(u16 folder, u16 file);
void M16P_vidPlayByNumber(u16 num);
void M16P_vidGetState(void);
void M16P_vidGetVolume(void);
void M16P_vidGetUSum(void);
void M16P_vidGetTFSum(void);
void M16P_vidGetFlashSum(void);
void M16P_vidGetTFCurrent(void);
void M16P_vidGetUCurrent(void);
void M16P_vidGetFlashCurrent(void);
 u8 M16P_u8GetDataBuffer(void);

#endif
