#include "../../LIB/STD_Types.h"
#include "../../LIB/BIT_MATH.h"
#include "DIO_Private.h"
#include "DIO_Interface.h"

uint8_t DIO_u8SetPinMode(u8 port_id,u8 pin_no,u8 mode)
{
    if (pin_no > 7u) return E_NOK;
    switch (port_id)
    {
        case PORT_A: if(mode==INPUT) CLR_BIT(DDRA_REG,pin_no); else if(mode==OUTPUT) SET_BIT(DDRA_REG,pin_no); else return E_NOK; break;
        case PORT_B: if(mode==INPUT) CLR_BIT(DDRB_REG,pin_no); else if(mode==OUTPUT) SET_BIT(DDRB_REG,pin_no); else return E_NOK; break;
        case PORT_C: if(mode==INPUT) CLR_BIT(DDRC_REG,pin_no); else if(mode==OUTPUT) SET_BIT(DDRC_REG,pin_no); else return E_NOK; break;
        case PORT_D: if(mode==INPUT) CLR_BIT(DDRD_REG,pin_no); else if(mode==OUTPUT) SET_BIT(DDRD_REG,pin_no); else return E_NOK; break;
        default: return E_NOK;
    }
    return E_OK;
}

uint8_t DIO_u8SetPinValue(u8 port_id,u8 pin_no,u8 value)
{
    if (pin_no > 7u || value > 1u) return E_NOK;
    switch (port_id)
    {
        case PORT_A: if(value==LOW) CLR_BIT(PORTA_REG,pin_no); else SET_BIT(PORTA_REG,pin_no); break;
        case PORT_B: if(value==LOW) CLR_BIT(PORTB_REG,pin_no); else SET_BIT(PORTB_REG,pin_no); break;
        case PORT_C: if(value==LOW) CLR_BIT(PORTC_REG,pin_no); else SET_BIT(PORTC_REG,pin_no); break;
        case PORT_D: if(value==LOW) CLR_BIT(PORTD_REG,pin_no); else SET_BIT(PORTD_REG,pin_no); break;
        default: return E_NOK;
    }
    return E_OK;
}

uint8_t DIO_u8GetPinValue(u8 port_id,u8 pin_no,u8 *value)
{
    if (pin_no > 7u || value == NULL) return E_NOK;
    switch (port_id)
    {
        case PORT_A: *value = GET_BIT(PINA_REG,pin_no); break;
        case PORT_B: *value = GET_BIT(PINB_REG,pin_no); break;
        case PORT_C: *value = GET_BIT(PINC_REG,pin_no); break;
        case PORT_D: *value = GET_BIT(PIND_REG,pin_no); break;
        default: return E_NOK;
    }
    return E_OK;
}

uint8_t DIO_u8IsPinOutPut(u8 port_id,u8 pin_no,u8 *value)
{
    if (pin_no > 7u || value == NULL) return E_NOK;
    switch (port_id)
    {
        case PORT_A: *value = GET_BIT(DDRA_REG,pin_no); break;
        case PORT_B: *value = GET_BIT(DDRB_REG,pin_no); break;
        case PORT_C: *value = GET_BIT(DDRC_REG,pin_no); break;
        case PORT_D: *value = GET_BIT(DDRD_REG,pin_no); break;
        default: return E_NOK;
    }
    return E_OK;
}

uint8_t DIO_u8SetPullUpMode(u8 port_id,u8 pin_no,u8 mode)
{
    if (pin_no > 7u || mode > 1u) return E_NOK;
    switch (port_id)
    {
        case PORT_A: if(mode==Enabled) SET_BIT(PORTA_REG,pin_no); else CLR_BIT(PORTA_REG,pin_no); break;
        case PORT_B: if(mode==Enabled) SET_BIT(PORTB_REG,pin_no); else CLR_BIT(PORTB_REG,pin_no); break;
        case PORT_C: if(mode==Enabled) SET_BIT(PORTC_REG,pin_no); else CLR_BIT(PORTC_REG,pin_no); break;
        case PORT_D: if(mode==Enabled) SET_BIT(PORTD_REG,pin_no); else CLR_BIT(PORTD_REG,pin_no); break;
        default: return E_NOK;
    }
    return E_OK;
}

uint8_t DIO_u8SetPortMode(u8 port_id,u8 mode)
{
    switch (port_id)
    {
        case PORT_A: DDRA_REG = mode; break;
        case PORT_B: DDRB_REG = mode; break;
        case PORT_C: DDRC_REG = mode; break;
        case PORT_D: DDRD_REG = mode; break;
        default: return E_NOK;
    }
    return E_OK;
}

uint8_t DIO_u8SetPortValue(u8 port_id,u8 value)
{
    switch (port_id)
    {
        case PORT_A: PORTA_REG = value; break;
        case PORT_B: PORTB_REG = value; break;
        case PORT_C: PORTC_REG = value; break;
        case PORT_D: PORTD_REG = value; break;
        default: return E_NOK;
    }
    return E_OK;
}

uint8_t DIO_u8GetPortValue(u8 port_id,u8 *value)
{
    if (value == NULL) return E_NOK;
    switch (port_id)
    {
        case PORT_A: *value = PINA_REG; break;
        case PORT_B: *value = PINB_REG; break;
        case PORT_C: *value = PINC_REG; break;
        case PORT_D: *value = PIND_REG; break;
        default: return E_NOK;
    }
    return E_OK;
}

uint8_t DIO_u8SetPortPullUpMode(u8 port_id,u8 mode)
{
    if (mode > 1u) return E_NOK;
    switch (port_id)
    {
        case PORT_A: PORTA_REG = mode ? 0xFFu : 0x00u; break;
        case PORT_B: PORTB_REG = mode ? 0xFFu : 0x00u; break;
        case PORT_C: PORTC_REG = mode ? 0xFFu : 0x00u; break;
        case PORT_D: PORTD_REG = mode ? 0xFFu : 0x00u; break;
        default: return E_NOK;
    }
    return E_OK;
}
