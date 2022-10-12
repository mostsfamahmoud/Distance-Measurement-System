################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Application.c \
../src/gpio.c \
../src/icu.c \
../src/lcd.c \
../src/ultrasonic_sensor.c 

OBJS += \
./src/Application.o \
./src/gpio.o \
./src/icu.o \
./src/lcd.o \
./src/ultrasonic_sensor.o 

C_DEPS += \
./src/Application.d \
./src/gpio.d \
./src/icu.d \
./src/lcd.d \
./src/ultrasonic_sensor.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


