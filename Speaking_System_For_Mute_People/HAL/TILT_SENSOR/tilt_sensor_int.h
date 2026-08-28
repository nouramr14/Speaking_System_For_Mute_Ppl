#ifndef HAL_TILT_SENSOR_TILT_SENSOR_INT_H_
#define HAL_TILT_SENSOR_TILT_SENSOR_INT_H_

#include "../../LIB/STD_Types.h"

#define TILT_0 ((u8)0)
#define TILT_1 ((u8)1)
#define TILT_2 ((u8)2)
#define TILT_3 ((u8)3)
#define TILT_4 ((u8)4)
#define TILT_5 ((u8)5)
#define TILT_6 ((u8)6)
#define TILT_7 ((u8)7)
#define ALL_TILT ((u8)8)

void TILT_vidInit(u8 tilt_pin);
void TILT_vidGetTiltRead(u8* tilt_read, u8 tilt_pin);
void TILT_vidGetAllTiltRead(u8* tilt_read);

#endif
