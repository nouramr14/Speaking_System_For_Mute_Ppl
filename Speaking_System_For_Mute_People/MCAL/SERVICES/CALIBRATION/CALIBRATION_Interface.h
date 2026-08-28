/*
 * CALIBRATION_Interface.h
 */
#ifndef MCAL_SERVICES_CALIBRATION_CALIBRATION_INTERFACE_H_
#define MCAL_SERVICES_CALIBRATION_CALIBRATION_INTERFACE_H_

#include "../../../LIB/STD_Types.h"

#define CALIBRATION_ANALOG_SENSORS ((u8)5)

void CAL_vidInit(void);
u8 CAL_u8IsValid(void);
void CAL_vidCalibrateFromStopping(const u16* sensor_reads);
void CAL_vidApply(u16* sensor_reads);
void CAL_vidClear(void);

#endif /* MCAL_SERVICES_CALIBRATION_CALIBRATION_INTERFACE_H_ */
