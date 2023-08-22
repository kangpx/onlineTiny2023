################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../X-CUBE-AI/App/combination.c \
../X-CUBE-AI/App/combination_data.c \
../X-CUBE-AI/App/combination_data_params.c 

OBJS += \
./X-CUBE-AI/App/combination.o \
./X-CUBE-AI/App/combination_data.o \
./X-CUBE-AI/App/combination_data_params.o 

C_DEPS += \
./X-CUBE-AI/App/combination.d \
./X-CUBE-AI/App/combination_data.d \
./X-CUBE-AI/App/combination_data_params.d 


# Each subdirectory must supply rules for building sources it contributes
X-CUBE-AI/App/%.o X-CUBE-AI/App/%.su X-CUBE-AI/App/%.cyclo: ../X-CUBE-AI/App/%.c X-CUBE-AI/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F756xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/AI/Inc -I../X-CUBE-AI/App -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-X-2d-CUBE-2d-AI-2f-App

clean-X-2d-CUBE-2d-AI-2f-App:
	-$(RM) ./X-CUBE-AI/App/combination.cyclo ./X-CUBE-AI/App/combination.d ./X-CUBE-AI/App/combination.o ./X-CUBE-AI/App/combination.su ./X-CUBE-AI/App/combination_data.cyclo ./X-CUBE-AI/App/combination_data.d ./X-CUBE-AI/App/combination_data.o ./X-CUBE-AI/App/combination_data.su ./X-CUBE-AI/App/combination_data_params.cyclo ./X-CUBE-AI/App/combination_data_params.d ./X-CUBE-AI/App/combination_data_params.o ./X-CUBE-AI/App/combination_data_params.su

.PHONY: clean-X-2d-CUBE-2d-AI-2f-App

