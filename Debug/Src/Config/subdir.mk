################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/Config/SimulationConfig.cpp 

OBJS += \
./Src/Config/SimulationConfig.o 

CPP_DEPS += \
./Src/Config/SimulationConfig.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Config/%.o: ../Src/Config/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/local/include/player-2.0/ -I/usr/local/include/player-2.0 -I/usr/local/include/ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


