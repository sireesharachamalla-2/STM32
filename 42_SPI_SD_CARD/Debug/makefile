################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32L4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
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

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := spi_sd_card_with_ultrasonic
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
spi_sd_card_with_ultrasonic.elf \

MAP_FILES += \
spi_sd_card_with_ultrasonic.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
spi_sd_card_with_ultrasonic.list \

OBJCOPY_HEX += \
spi_sd_card_with_ultrasonic.hex \

OBJCOPY_BIN += \
spi_sd_card_with_ultrasonic.bin \

OBJCOPY_SREC += \
spi_sd_card_with_ultrasonic.srec \


# All Target
all: main-build

# Main-build Target
main-build: spi_sd_card_with_ultrasonic.elf secondary-outputs

# Tool invocations
spi_sd_card_with_ultrasonic.elf spi_sd_card_with_ultrasonic.map: $(OBJS) $(USER_OBJS) C:\stm32\spi_sd_card_with_ultrasonic\STM32L476RGTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "spi_sd_card_with_ultrasonic.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\stm32\spi_sd_card_with_ultrasonic\STM32L476RGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="spi_sd_card_with_ultrasonic.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

spi_sd_card_with_ultrasonic.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "spi_sd_card_with_ultrasonic.list"
	@echo 'Finished building: $@'
	@echo ' '

spi_sd_card_with_ultrasonic.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "spi_sd_card_with_ultrasonic.hex"
	@echo 'Finished building: $@'
	@echo ' '

spi_sd_card_with_ultrasonic.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "spi_sd_card_with_ultrasonic.bin"
	@echo 'Finished building: $@'
	@echo ' '

spi_sd_card_with_ultrasonic.srec: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O srec $(EXECUTABLES) "spi_sd_card_with_ultrasonic.srec"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) default.size.stdout spi_sd_card_with_ultrasonic.bin spi_sd_card_with_ultrasonic.elf spi_sd_card_with_ultrasonic.hex spi_sd_card_with_ultrasonic.list spi_sd_card_with_ultrasonic.map spi_sd_card_with_ultrasonic.srec
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN) $(OBJCOPY_SREC)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
