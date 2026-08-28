################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/SERVICES/GLOVE_HANDLER/GLOVE_HANDLER_Program.c 

OBJS += \
./MCAL/SERVICES/GLOVE_HANDLER/GLOVE_HANDLER_Program.o 

C_DEPS += \
./MCAL/SERVICES/GLOVE_HANDLER/GLOVE_HANDLER_Program.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/SERVICES/GLOVE_HANDLER/%.o: ../MCAL/SERVICES/GLOVE_HANDLER/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


