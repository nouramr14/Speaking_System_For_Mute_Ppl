#include "../../../LIB/STD_Types.h"
#include "GET_WORD_SOUND_Interface.h"
#include "GET_WORD_SOUND_Config.h"

#define SENSOR_VALUE_COUNT ((u8)7)

typedef struct
{
    u16 sensor[SENSOR_VALUE_COUNT];
    u8 sentence;
    u8 word;
} GestureReference;

static const GestureReference words[TOTAL_NO_OF_WORDS] =
{
    SEN_1_WORD_1, SEN_1_WORD_2,
    SEN_2_WORD_1,
    SEN_3_WORD_1, SEN_3_WORD_2, SEN_3_WORD_3,
    SEN_4_WORD_1, SEN_4_WORD_2, SEN_4_WORD_3, SEN_4_WORD_4,
    SEN_5_WORD_1, SEN_5_WORD_2, SEN_5_WORD_3, SEN_5_WORD_4,
    SEN_6_WORD_1, SEN_6_WORD_2,
    SEN_7_WORD_1, SEN_7_WORD_2, SEN_7_WORD_3, SEN_7_WORD_4,
    STOPPING_WORD,
    NOT_FOUND
};

static u32 GET_u32AbsDifference(u16 a, u16 b)
{
    return (a >= b) ? ((u32)a - (u32)b) : ((u32)b - (u32)a);
}

static u32 GET_u32CalculateDistanceSquared(const u16* readings,
                                           const GestureReference* ref)
{
    u8 i;
    u32 diff;
    u32 distance = 0UL;

    for (i = 0u; i < 5u; i++)
    {
        diff = GET_u32AbsDifference(readings[i], ref->sensor[i]);
        distance += diff * diff;
    }

    /* Tilt is binary and would otherwise have almost no effect. */
    for (i = 5u; i < SENSOR_VALUE_COUNT; i++)
    {
        if (readings[i] != ref->sensor[i]) distance += TILT_MISMATCH_PENALTY;
    }

    return distance;
}

static u8 GET_u8FindClosestSensor(const u16* readings, u8 count, u32* best)
{
    u8 i;
    u8 index = 0u;
    u32 distance;
    u32 minimum;

    if ((readings == NULL) || (count == 0u))
    {
        if (best != NULL) *best = 0xFFFFFFFFUL;
        return 0u;
    }

    minimum = GET_u32CalculateDistanceSquared(readings, &words[0]);

    for (i = 1u; i < count; i++)
    {
        distance = GET_u32CalculateDistanceSquared(readings, &words[i]);
        if (distance < minimum)
        {
            minimum = distance;
            index = i;
        }
    }

    if (best != NULL) *best = minimum;
    return index;
}

void GET_vidGetWordAndSound(u16* sensor_reads, u8* word_location)
{
    u8 index;
    u32 distance_squared;
    u32 threshold_squared =
        (u32)GESTURE_DISTANCE_THRESHOLD * (u32)GESTURE_DISTANCE_THRESHOLD;

    if ((sensor_reads == NULL) || (word_location == NULL)) return;

    index = GET_u8FindClosestSensor(sensor_reads,
                                    (u8)(TOTAL_NO_OF_WORDS - 1u),
                                    &distance_squared);

    if (distance_squared <= threshold_squared)
    {
        word_location[0] = words[index].sentence;
        word_location[1] = words[index].word;
    }
    else
    {
        word_location[0] = 0u;
        word_location[1] = 1u;
    }
}
