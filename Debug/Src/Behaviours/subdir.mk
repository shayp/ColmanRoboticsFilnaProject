################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/Behaviours/Behavior.cpp \
../Src/Behaviours/GoForward.cpp \
../Src/Behaviours/TurnInPlace.cpp \
../Src/Behaviours/TurnLeft.cpp \
../Src/Behaviours/TurnRight.cpp 

OBJS += \
./Src/Behaviours/Behavior.o \
./Src/Behaviours/GoForward.o \
./Src/Behaviours/TurnInPlace.o \
./Src/Behaviours/TurnLeft.o \
./Src/Behaviours/TurnRight.o 

CPP_DEPS += \
./Src/Behaviours/Behavior.d \
./Src/Behaviours/GoForward.d \
./Src/Behaviours/TurnInPlace.d \
./Src/Behaviours/TurnLeft.d \
./Src/Behaviours/TurnRight.d 


# Each subdirectory must supply rules for building sources it contributes
Src/Behaviours/%.o: ../Src/Behaviours/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/local/include/player-2.0/ -I/usr/local/include/player-2.0 -I/usr/local/include/ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


