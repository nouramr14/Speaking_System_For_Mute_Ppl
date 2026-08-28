/*
 * GET_WORD_SOUND_Program.c
 *
 *  Created on: Aug 28, 2026
 *      Author: DELL
 */

#include "../../LIB/STD_Types.h"
#include "GET_WORD_SOUND_Interface.h"
#include "GET_WORD_SOUND_Config.h"
#include "math.h"

typedef struct{

	u16 thumb;
	u16 finger_1;
	u16 finger_2;
	u16 finger_3;
	u16 finger_4;

	u16 tilt0;
	u16 tilt1;

	u16 sentence;
	u16 word;

} word;

word words[TOTAL_NO_OF_WORDS] = {SEN_1_WORD_1, SEN_1_WORD_2, SEN_2_WORD_1, SEN_3_WORD_1,
									  SEN_3_WORD_2, SEN_3_WORD_3, SEN_4_WORD_1, SEN_4_WORD_2,
									  SEN_4_WORD_3, SEN_4_WORD_4, SEN_5_WORD_1, SEN_5_WORD_2,
									  SEN_5_WORD_3, SEN_5_WORD_4, SEN_6_WORD_1, SEN_6_WORD_2,
									  SEN_7_WORD_1, SEN_7_WORD_2, SEN_7_WORD_3, SEN_7_WORD_4,
									  STOPPING_WORD, NOT_FOUND};

// HELPING FUNCTIONS

// 1. Function to calculate Euclidean distance between two sensor readings
f32 GET_float32CalculateDistance(u16* sensor_reads, word* word) {

    f32 distance = 0.0;

    distance += pow((f32)(sensor_reads[0] - word->thumb), 2);
    distance += pow((f32)(sensor_reads[1] - word->finger_1), 2);
    distance += pow((f32)(sensor_reads[2] - word->finger_2), 2);
    distance += pow((f32)(sensor_reads[3] - word->finger_3), 2);
    distance += pow((f32)(sensor_reads[4] - word->finger_4), 2);
    distance += pow((f32)(sensor_reads[5] - word->tilt0), 2);
    distance += pow((f32)(sensor_reads[6] - word->tilt1), 2);

    return sqrt(distance);

}


// 2. Function to find the closest predefined sensor data
u8 GET_u8FindClosestSensor(word* words, u16* sensor_reads, u8 num_words) {

    uint8_t closest_index = 0;

    f32 min_distance = GET_float32CalculateDistance(sensor_reads, &words[0]);

    for (uint8_t i = 1; i < num_words; i++) {
        f32 distance = GET_float32CalculateDistance(sensor_reads, &words[i]);
        if (distance < min_distance) {
            min_distance = distance;
            closest_index = i;
        }
    }

    return closest_index;
}


// Main Function
void GET_vidGetWordAndSound(u16 * sensor_reads, uint8_t * word_location )
{

uint8_t i = GET_u8FindClosestSensor(words, sensor_reads, TOTAL_NO_OF_WORDS-1);

word_location[0] = words[i].sentence;
word_location[1] = words[i].word;

}
