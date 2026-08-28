################################################################################
# Calibration service build rules
################################################################################

C_SRCS += \
../MCAL/SERVICES/CALIBRATION/CALIBRATION_Program.c

OBJS += \
./MCAL/SERVICES/CALIBRATION/CALIBRATION_Program.o

C_DEPS += \
./MCAL/SERVICES/CALIBRATION/CALIBRATION_Program.d

MCAL/SERVICES/CALIBRATION/%.o: ../MCAL/SERVICES/CALIBRATION/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
