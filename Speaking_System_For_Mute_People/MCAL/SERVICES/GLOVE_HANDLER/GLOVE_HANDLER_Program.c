/*
 * GLOVE_HANDLER_Program.c
 *
 * Collects one complete glove frame synchronously:
 *   sensor_reads[0..4] -> five flex sensors
 *   sensor_reads[5..6] -> two tilt sensors
 *   sensor_reads[7]    -> frame-ready flag
 */

#include "../../../LIB/STD_Types.h"
#include "../../../MCAL/ADC/ADC_Interface.h"
#include "../../../HAL/FLEX_SENSOR/FLEX_SENSOR_Interface.h"
#include "../../../HAL/TILT_SENSOR/tilt_sensor_int.h"
#include "../CALIBRATION/CALIBRATION_Interface.h"

#define NO_OF_FLEX_SENSORS ((u8)5)
#define NO_OF_TILT_SENSORS ((u8)2)
#define GLOVE_TOTAL_VALUES ((u8)7)
#define GLOVE_AVERAGE_SAMPLES ((u8)3)

static u16* SENSOR_READ = NULL;

static const u8 FLEX_SENSORS[NO_OF_FLEX_SENSORS] =
{
    FLEX_0, FLEX_1, FLEX_2, FLEX_3, FLEX_4
};

void GLOVE_vidSensorsInit(void)
{
    FLEX_vidFlexInit(FLEX_ALL);
    TILT_vidInit(TILT_2);
    TILT_vidInit(TILT_3);
    CAL_vidInit();
}

void GLOVE_vidSetGloveParams(u16* sensor_read, u8 no_of_sensors)
{
    SENSOR_READ = sensor_read;

    /* The public parameter is the seven recognition sensors. */
    (void)no_of_sensors;
}

void GLOVE_vidGetHandRead(void)
{
    u8 i;
    u8 sample;
    u32 sum;
    u16 read_value;

    if (SENSOR_READ == NULL)
    {
        return;
    }

    SENSOR_READ[GLOVE_TOTAL_VALUES] = 0u;

    /* Average three ADC readings for each flex sensor to reduce noise. */
    for (i = 0u; i < NO_OF_FLEX_SENSORS; i++)
    {
        sum = 0UL;

        for (sample = 0u; sample < GLOVE_AVERAGE_SAMPLES; sample++)
        {
            read_value = 0u;
            FLEX_vidGetFlexRead(&read_value, FLEX_SENSORS[i]);
            sum += read_value;
        }

        SENSOR_READ[i] = (u16)(sum / GLOVE_AVERAGE_SAMPLES);
    }

    /* The two tilt sensors are digital. */
    TILT_vidGetTiltRead((u8*)&SENSOR_READ[5], TILT_2);
    TILT_vidGetTiltRead((u8*)&SENSOR_READ[6], TILT_3);

    /* Apply stored flex-sensor calibration after the raw frame is complete. */
    CAL_vidApply(SENSOR_READ);

    SENSOR_READ[GLOVE_TOTAL_VALUES] = 1u;
}
