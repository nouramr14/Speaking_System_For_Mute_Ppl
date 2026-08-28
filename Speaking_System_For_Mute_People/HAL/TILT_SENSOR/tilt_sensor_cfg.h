/*
 * tilt_sensor_cfg.h
 */
#ifndef HAL_TILT_SENSOR_TILT_SENSOR_CFG_H_
#define HAL_TILT_SENSOR_TILT_SENSOR_CFG_H

/* Eight physical positions are defined; this project uses TILT_2 and TILT_3. */
#define NO_OF_SENSORS ((uint8_t)8)

#define TILT_1_PIN {PORT_D, PIN_0}
#define TILT_2_PIN {PORT_D, PIN_1}
#define TILT_3_PIN {PORT_D, PIN_2}
#define TILT_4_PIN {PORT_D, PIN_3}
#define TILT_5_PIN {PORT_D, PIN_4}
#define TILT_6_PIN {PORT_D, PIN_5}
#define TILT_7_PIN {PORT_D, PIN_6}
#define TILT_8_PIN {PORT_D, PIN_7}

#endif /* HAL_TILT_SENSOR_TILT_SENSOR_CFG_H_ */
