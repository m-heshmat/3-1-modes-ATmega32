################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../APP/CALCULATOR/calculator.c 

OBJS += \
./APP/CALCULATOR/calculator.o 

C_DEPS += \
./APP/CALCULATOR/calculator.d 


# Each subdirectory must supply rules for building sources it contributes
APP/CALCULATOR/%.o: ../APP/CALCULATOR/%.c APP/CALCULATOR/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


