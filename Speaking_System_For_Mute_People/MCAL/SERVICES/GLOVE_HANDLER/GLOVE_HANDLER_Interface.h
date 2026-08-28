/*
 * GLOVE_HANDLER_Interface.h
 *
 *  Created on: Aug 28, 2026
 *      Author: DELL
 */

#ifndef MCAL_SERVICES_GLOVE_HANDLER_GLOVE_HANDLER_INTERFACE_H_
#define MCAL_SERVICES_GLOVE_HANDLER_GLOVE_HANDLER_INTERFACE_H_
void GLOVE_vidSensorsInit();

void GLOVE_vidSetGloveParams(u16* sensor_read,uint8_t no_of_sensors);

void GLOVE_vidGetHandRead();


#endif /* MCAL_SERVICES_GLOVE_HANDLER_GLOVE_HANDLER_INTERFACE_H_ */
