/*
 * main.h
 *
 * Application configuration
 */
#ifndef APP_MAIN_H_
#define APP_MAIN_H_

#define TRAIN       0
#define IMPLEMENT   1

/* Normal operation. Change to TRAIN only when collecting/calibrating sensor data. */
#define APP_MODE IMPLEMENT

/*
 * If set to 1, the application performs a new calibration at startup.
 * Hold the STOPPING gesture while the LCD says CALIBRATE.
 */
#define FORCE_CALIBRATION 0

/* Number of words that can be collected before playback. */
#define MAX_WORDS_IN_SENTENCE 5

/* Time between two sensor samples in milliseconds. */
#define GESTURE_SAMPLE_DELAY_MS 250

#endif /* APP_MAIN_H_ */
