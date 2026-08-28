################################################################################
# AVR build file
################################################################################

-include ../makefile.init

RM := rm -rf

-include sources.mk
-include MCAL/UART/subdir.mk
-include MCAL/SERVICES/SHOW/subdir.mk
-include MCAL/SERVICES/GLOVE_HANDLER/subdir.mk
-include MCAL/SERVICES/GET_WORD_SOUND/subdir.mk
-include MCAL/SERVICES/CALIBRATION/subdir.mk
-include MCAL/DIO/subdir.mk
-include MCAL/ADC/subdir.mk
-include HAL/TILT_SENSOR/subdir.mk
-include HAL/M16P_HANDLER/subdir.mk
-include HAL/LCD/subdir.mk
-include HAL/FLEX_SENSOR/subdir.mk
-include APP/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

LSS += \
Speaking_System_For_Mute_People.lss \

SIZEDUMMY += \
sizedummy \

all: Speaking_System_For_Mute_People.elf secondary-outputs

Speaking_System_For_Mute_People.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Speaking_System_For_Mute_People.map -mmcu=atmega32 -o "Speaking_System_For_Mute_People.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Speaking_System_For_Mute_People.lss: Speaking_System_For_Mute_People.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Speaking_System_For_Mute_People.elf >"Speaking_System_For_Mute_People.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Speaking_System_For_Mute_People.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Speaking_System_For_Mute_People.elf
	@echo 'Finished building: $@'
	@echo ' '

clean:
	-$(RM) $(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Speaking_System_For_Mute_People.elf
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
