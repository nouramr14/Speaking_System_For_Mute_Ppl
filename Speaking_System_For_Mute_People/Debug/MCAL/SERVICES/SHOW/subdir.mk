################################################################################
# SHOW service build rules
################################################################################

C_SRCS += \
../MCAL/SERVICES/SHOW/SHOW_Program.c

OBJS += \
./MCAL/SERVICES/SHOW/SHOW_Program.o

C_DEPS += \
./MCAL/SERVICES/SHOW/SHOW_Program.d

MCAL/SERVICES/SHOW/%.o: ../MCAL/SERVICES/SHOW/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
