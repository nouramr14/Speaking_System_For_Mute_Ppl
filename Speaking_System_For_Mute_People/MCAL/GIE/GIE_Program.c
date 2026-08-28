/*
 * GIE_Program.c
 *
 *  Created on: Aug 27, 2026
 *      Author: DELL
 */
#include"../../LIB/STD_Types.h"
#include"../../LIB/BIT_MATH.h"
#include "../GIE/GIE_Interface.h"
#include "../GIE/GIE_Private.h"

void GLOBAL_INTERRUPT_vidGlobalInterruptEnable(uint8_t mode)
{
	switch(mode)
	{
		case ENABLED:
			SET_BIT(SREG,7);
			break;
		case DISABLED:
			CLR_BIT(SREG,7);
			break;
	}
}

