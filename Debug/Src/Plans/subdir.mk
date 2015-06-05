################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/Plans/Plan.cpp \
../Src/Plans/PlnObstacleAvoid.cpp 

OBJS += \
./Src/Plans/Plan.o \
./Src/Plans/PlnObstacleAvoid.o 

CPP_DEPS += \
./Src/Plans/Plan.d \
./Src/Plans/PlnObstacleAvoid.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Plans/%.o: ../Src/Plans/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/local/include/player-2.0/ -I/usr/local/include/player-2.0 -I/usr/local/include/ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


