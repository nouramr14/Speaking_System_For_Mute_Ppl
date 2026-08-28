# Speaking System - calibration and build

## Target

- MCU: ATmega32
- CPU clock: 8 MHz
- Flex inputs: ADC0..ADC4
- Tilt inputs: TILT_2 and TILT_3 (PD1 and PD2)
- Audio: M16P/DFPlayer-style module through UART at 9600 baud

## First power-up calibration

The firmware now stores five flex-sensor offsets in the ATmega32 EEPROM.

1. Put the glove in the same pose used for `STOPPING_WORD`.
2. Power the system.
3. Keep the hand still while the LCD shows `Hold STOP` / `Calibrating`.
4. The measured values are stored as offsets in EEPROM.
5. The system then enters normal operation.

If you need to recalibrate, set `FORCE_CALIBRATION` to `1` in `APP/main.h`, build and flash once, then return it to `0` for normal use.

## TRAIN mode

Set `APP_MODE` to `TRAIN` in `APP/main.h` to display the seven sensor values. This is useful for collecting new reference values.

## Gesture recognition

The classifier uses squared Euclidean distance and rejects a reading when the closest reference is farther than `GESTURE_DISTANCE_THRESHOLD`.

The threshold is intentionally configurable in:

`MCAL/SERVICES/GET_WORD_SOUND/GET_WORD_SOUND_Config.h`

If valid gestures are being rejected, increase the threshold gradually. If unrelated hand positions are being accepted, decrease it.

## Audio file organization

`SHOW_Program.c` sends:

- folder = sentence number
- file = word number

So the expected audio organization is conceptually:

- folder 1: words 1, 2
- folder 2: word 1
- folder 3: words 1, 2, 3
- ...
- folder 7: words 1, 2, 3, 4

Use the naming/folder convention required by the exact audio module and SD-card firmware you are using.

## Important data issue

`SEN_4_WORD_1` and `SEN_7_WORD_1` currently have identical sensor values. The same is true for `SEN_4_WORD_2` and `SEN_7_WORD_2`.

A sensor-only classifier cannot distinguish two labels that have exactly the same reference vector. New measurements for the affected gestures must be collected and entered into `GET_WORD_SOUND_Config.h` before those four labels can be reliably distinguished.

`SEN_5_WORD_3` also contains a value of `408` for its fifth flex channel. Verify this value using TRAIN mode before changing it.

## Build

Open a terminal in:

`Speaking_System_For_Mute_People/Debug`

and run:

`make clean`

then:

`make`

The build configuration targets `atmega32` with `F_CPU=8000000UL`.
