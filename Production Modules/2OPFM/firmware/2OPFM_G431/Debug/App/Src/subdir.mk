################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/Src/2op_main.c \
../App/Src/dynamic_smooth.c \
../App/Src/loop.c 

OBJS += \
./App/Src/2op_main.o \
./App/Src/dynamic_smooth.o \
./App/Src/loop.o 

C_DEPS += \
./App/Src/2op_main.d \
./App/Src/dynamic_smooth.d \
./App/Src/loop.d 


# Each subdirectory must supply rules for building sources it contributes
App/Src/%.o: ../App/Src/%.c App/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G431xx -c -I../Core/Inc -I../App/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-App-2f-Src

clean-App-2f-Src:
	-$(RM) ./App/Src/2op_main.d ./App/Src/2op_main.o ./App/Src/dynamic_smooth.d ./App/Src/dynamic_smooth.o ./App/Src/loop.d ./App/Src/loop.o

.PHONY: clean-App-2f-Src

