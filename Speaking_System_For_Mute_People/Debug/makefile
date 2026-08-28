################################################################################
# Standalone AVR build file for Speaking_System_For_Mute_People
################################################################################

MCU := atmega32
CC := avr-gcc
OBJCOPY := avr-objcopy
SIZE := avr-size
RM := rm -rf
TARGET := Speaking_System_For_Mute_People

CFLAGS := -mmcu=$(MCU) -DF_CPU=8000000UL -Os -std=gnu99 -Wall -Wextra
INCLUDES := \
-I../LIB \
-I../APP \
-I../HAL/FLEX_SENSOR \
-I../HAL/TILT_SENSOR \
-I../HAL/LCD \
-I../HAL/M16P_HANDLER \
-I../MCAL/ADC \
-I../MCAL/DIO \
-I../MCAL/UART \
-I../MCAL/SERVICES/CALIBRATION \
-I../MCAL/SERVICES/GET_WORD_SOUND \
-I../MCAL/SERVICES/GLOVE_HANDLER \
-I../MCAL/SERVICES/SHOW

CFLAGS += $(INCLUDES)

SOURCES := \
../APP/main.c \
../HAL/FLEX_SENSOR/FLEX_SENSOR_Program.c \
../HAL/TILT_SENSOR/tilt_sensor_prog.c \
../HAL/LCD/LCD_Program.c \
../HAL/M16P_HANDLER/M16P_HANDLER_Program.c \
../MCAL/ADC/ADC_Program.c \
../MCAL/DIO/DIO_Program.c \
../MCAL/UART/UART_Program.c \
../MCAL/SERVICES/CALIBRATION/CALIBRATION_Program.c \
../MCAL/SERVICES/GET_WORD_SOUND/GET_WORD_SOUND_Program.c \
../MCAL/SERVICES/GLOVE_HANDLER/GLOVE_HANDLER_Program.c \
../MCAL/SERVICES/SHOW/SHOW_Program.c

OBJECTS := $(SOURCES:.c=.o)

all: $(TARGET).hex $(TARGET).eep $(TARGET).lss

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).elf: $(OBJECTS)
	$(CC) -mmcu=$(MCU) -o $@ $^ -lm

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

$(TARGET).eep: $(TARGET).elf
	$(OBJCOPY) -O ihex -j .eeprom --set-section-flags=.eeprom="alloc,load" --no-change-warnings --change-section-lma .eeprom=0 $< $@

$(TARGET).lss: $(TARGET).elf
	avr-objdump -h -S $< > $@

size: $(TARGET).elf
	$(SIZE) --format=avr --mcu=$(MCU) $<

clean:
	$(RM) $(OBJECTS) $(TARGET).elf $(TARGET).hex $(TARGET).eep $(TARGET).lss

.PHONY: all clean size
