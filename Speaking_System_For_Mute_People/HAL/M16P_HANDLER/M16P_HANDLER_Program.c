#include "../../LIB/STD_Types.h"
#include "M16P_HANDLER_Interface.h"
#include "../../MCAL/UART/UART_Interface.h"
#include "M16P_HANDLER_Config.h"

static u8 send_buf[SERIAL_BUFF_SIZE] = {0x7E,0xFF,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0xEF};
static u8 recv_buf[SERIAL_BUFF_SIZE];
static u8 is_reply = 0u;

static void M16P_vidFillU16(u8 *p, u16 value)
{
    p[0] = (u8)(value >> 8);
    p[1] = (u8)value;
}

static u16 M16P_u16Checksum(const u8 *p)
{
    u16 sum = 0u;
    u8 i;
    for (i = 1u; i <= 6u; i++) sum += p[i];
    return (u16)(0u - sum);
}

static void M16P_vidSend(u8 command, u16 parameter)
{
    u16 checksum;
    u8 i;

    send_buf[3] = command;
    send_buf[4] = is_reply;
    M16P_vidFillU16(&send_buf[5], parameter);
    checksum = M16P_u16Checksum(send_buf);
    M16P_vidFillU16(&send_buf[7], checksum);

    for (i = 0u; i < SERIAL_BUFF_SIZE; i++) UART_Transmit(send_buf[i]);
}

void M16P_vidInit(u16 baud)
{
    is_reply = 0u;
    UART_Init(baud);
}

void M16P_vidSetReply(u8 state)
{
    is_reply = state ? 1u : 0u;
}

void M16P_vidPlayTrack(u16 num) { M16P_vidSend(0x03u, num); }
void M16P_vidNextTrack(void) { M16P_vidSend(0x01u, 0u); }
void M16P_vidPreviousTrack(void) { M16P_vidSend(0x02u, 0u); }

void M16P_vidSetVolume(u16 volume)
{
    if (volume > 30u) volume = 30u;
    M16P_vidSend(0x06u, volume);
}

void M16P_vidSetEQ(u16 eq) { M16P_vidSend(0x07u, eq); }
void M16P_vidSetPlaybackSource(u16 device) { M16P_vidSend(0x09u, device); }
void M16P_vidSleep(void) { M16P_vidSend(0x0Au, 0u); }
void M16P_vidReset(void) { M16P_vidSend(0x0Cu, 0u); }
void M16P_vidPlayback(void) { M16P_vidSend(0x0Du, 0u); }
void M16P_vidPause(void) { M16P_vidSend(0x0Eu, 0u); }

void M16P_vidPlayFileInFolder(u16 folder, u16 file)
{
    /* DFPlayer command 0x0F uses folder in high byte and file in low byte. */
    u16 parameter = (u16)(((folder & 0x00FFu) << 8) | (file & 0x00FFu));
    M16P_vidSend(0x0Fu, parameter);
}

void M16P_vidPlayByNumber(u16 num) { M16P_vidSend(0x12u, num); }
void M16P_vidGetState(void) { M16P_vidSend(0x42u, 0u); }
void M16P_vidGetVolume(void) { M16P_vidSend(0x43u, 0u); }
void M16P_vidGetUSum(void) { M16P_vidSend(0x47u, 0u); }
void M16P_vidGetTFSum(void) { M16P_vidSend(0x48u, 0u); }
void M16P_vidGetFlashSum(void) { M16P_vidSend(0x49u, 0u); }
void M16P_vidGetTFCurrent(void) { M16P_vidSend(0x4Cu, 0u); }
void M16P_vidGetUCurrent(void) { M16P_vidSend(0x4Bu, 0u); }
void M16P_vidGetFlashCurrent(void) { M16P_vidSend(0x4Du, 0u); }

u8 M16P_u8GetDataBuffer(void)
{
    u8 i;
    if (UART_Receive() != 0x7Eu) return 0u;
    recv_buf[0] = 0x7Eu;
    for (i = 1u; i < SERIAL_BUFF_SIZE; i++) recv_buf[i] = UART_Receive();
    return 1u;
}
