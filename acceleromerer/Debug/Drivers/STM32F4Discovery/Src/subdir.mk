################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/STM32F4Discovery/Src/lsm303dlhc.c \
../Drivers/STM32F4Discovery/Src/stm32f411e_discovery.c \
../Drivers/STM32F4Discovery/Src/stm32f411e_discovery_accelerometer.c 

OBJS += \
./Drivers/STM32F4Discovery/Src/lsm303dlhc.o \
./Drivers/STM32F4Discovery/Src/stm32f411e_discovery.o \
./Drivers/STM32F4Discovery/Src/stm32f411e_discovery_accelerometer.o 

C_DEPS += \
./Drivers/STM32F4Discovery/Src/lsm303dlhc.d \
./Drivers/STM32F4Discovery/Src/stm32f411e_discovery.d \
./Drivers/STM32F4Discovery/Src/stm32f411e_discovery_accelerometer.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/STM32F4Discovery/Src/%.o: ../Drivers/STM32F4Discovery/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F411xE -I"/Users/macbookpro/Desktop/STM_Labki/acceleromerer/Inc" -I"/Users/macbookpro/Desktop/STM_Labki/acceleromerer/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/macbookpro/Desktop/STM_Labki/acceleromerer/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/macbookpro/Desktop/STM_Labki/acceleromerer/Middlewares/ST/STM32_USB_Host_Library/Core/Inc" -I"/Users/macbookpro/Desktop/STM_Labki/acceleromerer/Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc" -I"/Users/macbookpro/Desktop/STM_Labki/acceleromerer/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/macbookpro/Desktop/STM_Labki/acceleromerer/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


