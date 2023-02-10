################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/Inc/servo_motor.c \
../Application/Inc/step_motor.c 

OBJS += \
./Application/Inc/servo_motor.o \
./Application/Inc/step_motor.o 

C_DEPS += \
./Application/Inc/servo_motor.d \
./Application/Inc/step_motor.d 


# Each subdirectory must supply rules for building sources it contributes
Application/Inc/%.o Application/Inc/%.su: ../Application/Inc/%.c Application/Inc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/grasspeople/OneDrive - The University of Liverpool/STM32workspace/MM_Sorter_New/Application" -I"C:/Users/grasspeople/OneDrive - The University of Liverpool/STM32workspace/MM_Sorter_New/Application/Inc" -I"C:/Users/grasspeople/OneDrive - The University of Liverpool/STM32workspace/MM_Sorter_New/Application/Src" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/Inc/step_motor.o: ../Application/Inc/step_motor.c Application/Inc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/grasspeople/OneDrive - The University of Liverpool/STM32workspace/MM_Sorter_New/Application/Src" -I"C:/Users/grasspeople/OneDrive - The University of Liverpool/STM32workspace/MM_Sorter_New/Application/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-Inc

clean-Application-2f-Inc:
	-$(RM) ./Application/Inc/servo_motor.d ./Application/Inc/servo_motor.o ./Application/Inc/servo_motor.su ./Application/Inc/step_motor.d ./Application/Inc/step_motor.o ./Application/Inc/step_motor.su

.PHONY: clean-Application-2f-Inc

