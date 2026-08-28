#ifndef MCAL_SERVICES_GET_WORD_SOUND_GET_WORD_SOUND_CONFIG_H_
#define MCAL_SERVICES_GET_WORD_SOUND_GET_WORD_SOUND_CONFIG_H_

#define TOTAL_NO_OF_WORDS ((u8)22)
#define NUM_SENSORS ((u8)7)

/* Maximum Euclidean distance accepted for a known gesture. */
#define GESTURE_DISTANCE_THRESHOLD 150UL

/* Penalty used when a digital tilt sensor does not match. */
#define TILT_MISMATCH_PENALTY 40000UL

/*
 * Sensor order:
 * FLEX_0, FLEX_1, FLEX_2, FLEX_3, FLEX_4, TILT_2, TILT_3.
 * The last two values are digital 0/1 readings.
 */
#define SEN_1_WORD_1 {(u16)145,(u16)135,(u16)227,(u16)167,(u16)207,(u16)1,(u16)1,(u8)1,(u8)1}
#define SEN_1_WORD_2 {(u16)156,(u16)159,(u16)199,(u16)163,(u16)153,(u16)0,(u16)1,(u8)1,(u8)2}
#define SEN_2_WORD_1 {(u16)176,(u16)153,(u16)179,(u16)175,(u16)167,(u16)0,(u16)1,(u8)2,(u8)1}
#define SEN_3_WORD_1 {(u16)184,(u16)147,(u16)184,(u16)184,(u16)159,(u16)0,(u16)1,(u8)3,(u8)1}
#define SEN_3_WORD_2 {(u16)152,(u16)206,(u16)192,(u16)161,(u16)204,(u16)0,(u16)1,(u8)3,(u8)2}
#define SEN_3_WORD_3 {(u16)176,(u16)143,(u16)240,(u16)167,(u16)199,(u16)0,(u16)1,(u8)3,(u8)3}
#define SEN_4_WORD_1 {(u16)209,(u16)127,(u16)255,(u16)216,(u16)204,(u16)0,(u16)1,(u8)4,(u8)1}
#define SEN_4_WORD_2 {(u16)192,(u16)152,(u16)207,(u16)183,(u16)188,(u16)1,(u16)1,(u8)4,(u8)2}
#define SEN_4_WORD_3 {(u16)176,(u16)153,(u16)172,(u16)172,(u16)156,(u16)0,(u16)1,(u8)4,(u8)3}
#define SEN_4_WORD_4 {(u16)193,(u16)176,(u16)206,(u16)199,(u16)188,(u16)0,(u16)1,(u8)4,(u8)4}
#define SEN_5_WORD_1 {(u16)216,(u16)198,(u16)225,(u16)211,(u16)222,(u16)0,(u16)1,(u8)5,(u8)1}
#define SEN_5_WORD_2 {(u16)207,(u16)143,(u16)231,(u16)207,(u16)207,(u16)0,(u16)1,(u8)5,(u8)2}
#define SEN_5_WORD_3 {(u16)224,(u16)143,(u16)206,(u16)195,(u16)408,(u16)1,(u16)1,(u8)5,(u8)3}
#define SEN_5_WORD_4 {(u16)192,(u16)145,(u16)172,(u16)177,(u16)167,(u16)1,(u16)1,(u8)5,(u8)4}
#define SEN_6_WORD_1 {(u16)177,(u16)145,(u16)174,(u16)177,(u16)172,(u16)1,(u16)1,(u8)6,(u8)1}
#define SEN_6_WORD_2 {(u16)174,(u16)152,(u16)176,(u16)179,(u16)159,(u16)1,(u16)1,(u8)6,(u8)2}
#define SEN_7_WORD_1 {(u16)209,(u16)127,(u16)255,(u16)216,(u16)204,(u16)0,(u16)1,(u8)7,(u8)1}
#define SEN_7_WORD_2 {(u16)182,(u16)152,(u16)207,(u16)183,(u16)188,(u16)1,(u16)1,(u8)7,(u8)2}
#define SEN_7_WORD_3 {(u16)182,(u16)152,(u16)209,(u16)206,(u16)190,(u16)0,(u16)1,(u8)7,(u8)3}
#define SEN_7_WORD_4 {(u16)199,(u16)236,(u16)209,(u16)206,(u16)211,(u16)1,(u16)1,(u8)7,(u8)4}

#define STOPPING_WORD {(u16)180,(u16)155,(u16)190,(u16)192,(u16)190,(u16)0,(u16)1,(u8)0,(u8)0}
#define NOT_FOUND {(u16)110,(u16)110,(u16)110,(u16)110,(u16)110,(u16)1,(u16)1,(u8)0,(u8)1}

#endif
