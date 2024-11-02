################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Lib/big_sine_wave.c \
../Core/Lib/c_filters.c \
../Core/Lib/chorus.c \
../Core/Lib/delay.c \
../Core/Lib/dynamic_smooth.c \
../Core/Lib/envelopes.c \
../Core/Lib/float_expo_table.c \
../Core/Lib/lerp.c \
../Core/Lib/lfo.c \
../Core/Lib/noise.c \
../Core/Lib/opamp.c \
../Core/Lib/operator.c \
../Core/Lib/shared_delays.c 

OBJS += \
./Core/Lib/big_sine_wave.o \
./Core/Lib/c_filters.o \
./Core/Lib/chorus.o \
./Core/Lib/delay.o \
./Core/Lib/dynamic_smooth.o \
./Core/Lib/envelopes.o \
./Core/Lib/float_expo_table.o \
./Core/Lib/lerp.o \
./Core/Lib/lfo.o \
./Core/Lib/noise.o \
./Core/Lib/opamp.o \
./Core/Lib/operator.o \
./Core/Lib/shared_delays.o 

C_DEPS += \
./Core/Lib/big_sine_wave.d \
./Core/Lib/c_filters.d \
./Core/Lib/chorus.d \
./Core/Lib/delay.d \
./Core/Lib/dynamic_smooth.d \
./Core/Lib/envelopes.d \
./Core/Lib/float_expo_table.d \
./Core/Lib/lerp.d \
./Core/Lib/lfo.d \
./Core/Lib/noise.d \
./Core/Lib/opamp.d \
./Core/Lib/operator.d \
./Core/Lib/shared_delays.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Lib/%.o Core/Lib/%.su Core/Lib/%.cyclo: ../Core/Lib/%.c Core/Lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I../Core/Lib/include -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fcommon -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Lib

clean-Core-2f-Lib:
	-$(RM) ./Core/Lib/big_sine_wave.cyclo ./Core/Lib/big_sine_wave.d ./Core/Lib/big_sine_wave.o ./Core/Lib/big_sine_wave.su ./Core/Lib/c_filters.cyclo ./Core/Lib/c_filters.d ./Core/Lib/c_filters.o ./Core/Lib/c_filters.su ./Core/Lib/chorus.cyclo ./Core/Lib/chorus.d ./Core/Lib/chorus.o ./Core/Lib/chorus.su ./Core/Lib/delay.cyclo ./Core/Lib/delay.d ./Core/Lib/delay.o ./Core/Lib/delay.su ./Core/Lib/dynamic_smooth.cyclo ./Core/Lib/dynamic_smooth.d ./Core/Lib/dynamic_smooth.o ./Core/Lib/dynamic_smooth.su ./Core/Lib/envelopes.cyclo ./Core/Lib/envelopes.d ./Core/Lib/envelopes.o ./Core/Lib/envelopes.su ./Core/Lib/float_expo_table.cyclo ./Core/Lib/float_expo_table.d ./Core/Lib/float_expo_table.o ./Core/Lib/float_expo_table.su ./Core/Lib/lerp.cyclo ./Core/Lib/lerp.d ./Core/Lib/lerp.o ./Core/Lib/lerp.su ./Core/Lib/lfo.cyclo ./Core/Lib/lfo.d ./Core/Lib/lfo.o ./Core/Lib/lfo.su ./Core/Lib/noise.cyclo ./Core/Lib/noise.d ./Core/Lib/noise.o ./Core/Lib/noise.su ./Core/Lib/opamp.cyclo ./Core/Lib/opamp.d ./Core/Lib/opamp.o ./Core/Lib/opamp.su ./Core/Lib/operator.cyclo ./Core/Lib/operator.d ./Core/Lib/operator.o ./Core/Lib/operator.su ./Core/Lib/shared_delays.cyclo ./Core/Lib/shared_delays.d ./Core/Lib/shared_delays.o ./Core/Lib/shared_delays.su

.PHONY: clean-Core-2f-Lib

