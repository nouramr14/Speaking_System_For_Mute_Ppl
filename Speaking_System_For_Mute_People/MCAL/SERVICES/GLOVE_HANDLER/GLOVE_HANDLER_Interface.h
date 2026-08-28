/*
 * GLOVE_HANDLER_Interface.h
 */
#ifndef MCAL_SERVICES_GLOVE_HANDLER_GLOVE_HANDLER_INTERFACE_H_
#define MCAL_SERVICES_GLOVE_HANDLER_GLOVE_HANDLER_INTERFACE_H_

#include "../../../LIB/STD_Types.h"

void GLOVE_vidSensorsInit(void);
void GLOVE_vidSetGloveParams(u16* sensor_read, u8 no_of_sensors);
void GLOVE_vidGetHandRead(void);

#endif /* MCAL_SERVICES_GLOVE_HANDLER_GLOVE_HANDLER_INTERFACE_H_ */
