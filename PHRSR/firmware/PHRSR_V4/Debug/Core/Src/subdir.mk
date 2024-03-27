################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/main.c \
../Core/Src/syscalls.c \
../Core/Src/system_stm32f30x.c 

OBJS += \
./Core/Src/main.o \
./Core/Src/syscalls.o \
./Core/Src/system_stm32f30x.o 

C_DEPS += \
./Core/Src/main.d \
./Core/Src/syscalls.d \
./Core/Src/system_stm32f30x.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_STDPERIPH_DRIVER -DSTM32F334x8 -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/system_stm32f30x.d ./Core/Src/system_stm32f30x.o

.PHONY: clean-Core-2f-Src

