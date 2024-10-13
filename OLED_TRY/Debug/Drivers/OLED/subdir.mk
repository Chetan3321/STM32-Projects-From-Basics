################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/OLED/delay.c \
../Drivers/OLED/fonts.c \
../Drivers/OLED/i2c.c \
../Drivers/OLED/oled.c \
../Drivers/OLED/test.c 

OBJS += \
./Drivers/OLED/delay.o \
./Drivers/OLED/fonts.o \
./Drivers/OLED/i2c.o \
./Drivers/OLED/oled.o \
./Drivers/OLED/test.o 

C_DEPS += \
./Drivers/OLED/delay.d \
./Drivers/OLED/fonts.d \
./Drivers/OLED/i2c.d \
./Drivers/OLED/oled.d \
./Drivers/OLED/test.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/OLED/%.o Drivers/OLED/%.su Drivers/OLED/%.cyclo: ../Drivers/OLED/%.c Drivers/OLED/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/Learing/STm32F401_projects/OLED_TRY/Drivers/OLED" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-OLED

clean-Drivers-2f-OLED:
	-$(RM) ./Drivers/OLED/delay.cyclo ./Drivers/OLED/delay.d ./Drivers/OLED/delay.o ./Drivers/OLED/delay.su ./Drivers/OLED/fonts.cyclo ./Drivers/OLED/fonts.d ./Drivers/OLED/fonts.o ./Drivers/OLED/fonts.su ./Drivers/OLED/i2c.cyclo ./Drivers/OLED/i2c.d ./Drivers/OLED/i2c.o ./Drivers/OLED/i2c.su ./Drivers/OLED/oled.cyclo ./Drivers/OLED/oled.d ./Drivers/OLED/oled.o ./Drivers/OLED/oled.su ./Drivers/OLED/test.cyclo ./Drivers/OLED/test.d ./Drivers/OLED/test.o ./Drivers/OLED/test.su

.PHONY: clean-Drivers-2f-OLED

