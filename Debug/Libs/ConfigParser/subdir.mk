################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Libs/ConfigParser/Config.cpp \
../Libs/ConfigParser/Log.cpp 

OBJS += \
./Libs/ConfigParser/Config.o \
./Libs/ConfigParser/Log.o 

CPP_DEPS += \
./Libs/ConfigParser/Config.d \
./Libs/ConfigParser/Log.d 


# Each subdirectory must supply rules for building sources it contributes
Libs/ConfigParser/%.o: ../Libs/ConfigParser/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/local/include/player-2.0/ -I/usr/local/include/player-2.0 -I/usr/local/include/ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


