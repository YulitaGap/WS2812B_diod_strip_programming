################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Src/usbh_cdc.c 

OBJS += \
./Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Src/usbh_cdc.o 

C_DEPS += \
./Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Src/usbh_cdc.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Src/%.o: ../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F411xE -I"/Users/macbookpro/Desktop/STM_Labki/ws2812b_diod_strip/Inc" -I"/Users/macbookpro/Desktop/STM_Labki/ws2812b_diod_strip/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/Users/macbookpro/Desktop/STM_Labki/ws2812b_diod_strip/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/Users/macbookpro/Desktop/STM_Labki/ws2812b_diod_strip/Middlewares/ST/STM32_USB_Host_Library/Core/Inc" -I"/Users/macbookpro/Desktop/STM_Labki/ws2812b_diod_strip/Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc" -I"/Users/macbookpro/Desktop/STM_Labki/ws2812b_diod_strip/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/macbookpro/Desktop/STM_Labki/ws2812b_diod_strip/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


