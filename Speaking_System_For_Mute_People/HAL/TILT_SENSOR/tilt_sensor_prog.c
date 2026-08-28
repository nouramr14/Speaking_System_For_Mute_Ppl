#include "../../LIB/STD_Types.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "tilt_sensor_cfg.h"
#include "tilt_sensor_int.h"

typedef struct
{
    u8 port;
    u8 pin;
} TILT_SENSOR_PIN;

static const TILT_SENSOR_PIN tilt_pins[NO_OF_SENSORS] =
{
    TILT_1_PIN,TILT_2_PIN,TILT_3_PIN,TILT_4_PIN,
    TILT_5_PIN,TILT_6_PIN,TILT_7_PIN,TILT_8_PIN
};

void TILT_vidInit(u8 tilt_pin)
{
    u8 i;
    if (tilt_pin < NO_OF_SENSORS)
    {
        DIO_u8SetPinMode(tilt_pins[tilt_pin].port, tilt_pins[tilt_pin].pin, INPUT);
    }
    else if (tilt_pin == ALL_TILT)
    {
        for (i = 0u; i < NO_OF_SENSORS; i++)
            DIO_u8SetPinMode(tilt_pins[i].port, tilt_pins[i].pin, INPUT);
    }
}

void TILT_vidGetTiltRead(u8* tilt_read, u8 tilt_pin)
{
    if ((tilt_read == NULL) || (tilt_pin >= NO_OF_SENSORS)) return;
    DIO_u8GetPinValue(tilt_pins[tilt_pin].port, tilt_pins[tilt_pin].pin, tilt_read);
}

void TILT_vidGetAllTiltRead(u8* tilt_read)
{
    u8 i;
    if (tilt_read == NULL) return;

    for (i = 0u; i < NO_OF_SENSORS; i++)
        DIO_u8GetPinValue(tilt_pins[i].port, tilt_pins[i].pin, &tilt_read[i]);
}
