################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC.c \
../DHT22.c \
../DIO.c \
../EXTERNAL_INTERRUPT.c \
../LCD.c \
../SPI.c \
../TIMER0.c \
../TIMER1.c \
../TIMER2.c \
../UART.c \
../ULTRASONIC.c \
../main.c 

OBJS += \
./ADC.o \
./DHT22.o \
./DIO.o \
./EXTERNAL_INTERRUPT.o \
./LCD.o \
./SPI.o \
./TIMER0.o \
./TIMER1.o \
./TIMER2.o \
./UART.o \
./ULTRASONIC.o \
./main.o 

C_DEPS += \
./ADC.d \
./DHT22.d \
./DIO.d \
./EXTERNAL_INTERRUPT.d \
./LCD.d \
./SPI.d \
./TIMER0.d \
./TIMER1.d \
./TIMER2.d \
./UART.d \
./ULTRASONIC.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=12000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


