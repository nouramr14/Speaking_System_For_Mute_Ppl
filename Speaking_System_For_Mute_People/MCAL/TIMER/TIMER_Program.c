#include "../../LIB/STD_Types.h"
#include "../../LIB/BIT_MATH.h"
#include "TIMER_Config.h"
#include "TIMER_Private.h"
#include "TIMER_Interface.h"

void (*TIMER1_voidpSetCallBackNormal)(void) = NULL;
void (*TIMER1_voidpSetCallBackCTC)(void) = NULL;

static volatile u16 compare_cnt1 = 0u;

void TIMER1_voidInit(void)
{
#if TIMER1_MODE == NORMAL_T_MODE
    CLR_BIT(TCCR1A, WGM10);
    CLR_BIT(TCCR1A, WGM11);
    CLR_BIT(TCCR1B, WGM12);
    CLR_BIT(TCCR1B, WGM13);
    SET_BIT(TIMSK, TOIE1);

#elif TIMER1_MODE == PWM_T_MODE
    SET_BIT(TCCR1A, WGM10);
    CLR_BIT(TCCR1A, WGM11);
    CLR_BIT(TCCR1B, WGM12);
    CLR_BIT(TCCR1B, WGM13);

#elif TIMER1_MODE == CTC_T_MODE
    CLR_BIT(TCCR1A, WGM10);
    CLR_BIT(TCCR1A, WGM11);
    SET_BIT(TCCR1B, WGM12);
    CLR_BIT(TCCR1B, WGM13);
    SET_BIT(TIMSK, OCIE1A);

#elif TIMER1_MODE == FAST_PWM_T_MODE
    SET_BIT(TCCR1A, WGM10);
    CLR_BIT(TCCR1A, WGM11);
    SET_BIT(TCCR1B, WGM12);
    CLR_BIT(TCCR1B, WGM13);

#else
#error "wrong timer mode"
#endif

    TIMER1_uint8SetPrescaler(TIMER1_PRESCALER);
}

void TIMER1_voidDisable(void)
{
    TCCR1B &= (u8)0xF8u;
}

u8 TIMER1_uint8SetPrescaler(u8 Copy_uint8Prescaler)
{
    if (Copy_uint8Prescaler < 8u)
    {
        TCCR1B &= (u8)0xF8u;
        TCCR1B |= Copy_uint8Prescaler;
        return 0u;
    }
    return 1u;
}

void TIMER1_voidSetCounterRegister(u8 Copy_uint8Counter1Start)
{
    TCNT1H = 0u;
    TCNT1L = Copy_uint8Counter1Start;
}

void TIMER1_voidSetCTCTime(u8 Copy_uint8CompareTime)
{
    OCR1AH = 0u;
    OCR1AL = Copy_uint8CompareTime;
}

void TIMER1_voidGetNumCountCTC(u16 Copy_uint8DesiredTime,
                               u16 *Copy_uint16pNumOfCounts,
                               u8 *Copy_uint8pCompareValue)
{
    u32 ticks_per_ms;
    u32 total_ticks;
    u32 counts;

    if ((Copy_uint16pNumOfCounts == NULL) || (Copy_uint8pCompareValue == NULL))
        return;

    /* F_CPU is expected to be defined by the project build settings. */
#ifndef F_CPU
#define F_CPU 8000000UL
#endif

    switch (TIMER1_PRESCALER)
    {
        case CLK:       ticks_per_ms = F_CPU / 1000UL;       break;
        case CLK_8:     ticks_per_ms = F_CPU / 8000UL;      break;
        case CLK_64:    ticks_per_ms = F_CPU / 64000UL;     break;
        case CLK_256:   ticks_per_ms = F_CPU / 256000UL;    break;
        case CLK_1024:  ticks_per_ms = F_CPU / 1024000UL;   break;
        default:
            *Copy_uint16pNumOfCounts = 0u;
            *Copy_uint8pCompareValue = 0u;
            return;
    }

    total_ticks = (u32)Copy_uint8DesiredTime * ticks_per_ms;
    counts = (total_ticks + 249UL) / 250UL;

    if (counts > 65535UL) counts = 65535UL;
    *Copy_uint16pNumOfCounts = (u16)counts;
    *Copy_uint8pCompareValue = 250u;
    compare_cnt1 = (u16)counts;
}

void TIMER1_voidSetCallBackNormal(void (*Copy_uint8pSetCallBackNormal1)(void))
{
    TIMER1_voidpSetCallBackNormal = Copy_uint8pSetCallBackNormal1;
}

void TIMER1_voidSetCallBackCTC(void (*Copy_uint8pSetCallBackCTC1)(void))
{
    TIMER1_voidpSetCallBackCTC = Copy_uint8pSetCallBackCTC1;
}

void __vector_7(void) __attribute__((signal));
void __vector_7(void)
{
    static volatile u16 cnt = 0u;

    if (TIMER1_voidpSetCallBackCTC != NULL)
    {
        cnt++;
        if ((compare_cnt1 != 0u) && (cnt >= compare_cnt1))
        {
            cnt = 0u;
            TIMER1_voidpSetCallBackCTC();
        }
    }
}

void __vector_9(void) __attribute__((signal));
void __vector_9(void)
{
    if (TIMER1_voidpSetCallBackNormal != NULL)
        TIMER1_voidpSetCallBackNormal();
}
