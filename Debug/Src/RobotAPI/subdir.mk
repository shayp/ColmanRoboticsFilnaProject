################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/RobotAPI/Helper.cpp \
../Src/RobotAPI/Location.cpp \
../Src/RobotAPI/Manager.cpp \
../Src/RobotAPI/Map.cpp \
../Src/RobotAPI/Particle.cpp \
../Src/RobotAPI/Robot.cpp \
../Src/RobotAPI/SlamManager.cpp 

OBJS += \
./Src/RobotAPI/Helper.o \
./Src/RobotAPI/Location.o \
./Src/RobotAPI/Manager.o \
./Src/RobotAPI/Map.o \
./Src/RobotAPI/Particle.o \
./Src/RobotAPI/Robot.o \
./Src/RobotAPI/SlamManager.o 

CPP_DEPS += \
./Src/RobotAPI/Helper.d \
./Src/RobotAPI/Location.d \
./Src/RobotAPI/Manager.d \
./Src/RobotAPI/Map.d \
./Src/RobotAPI/Particle.d \
./Src/RobotAPI/Robot.d \
./Src/RobotAPI/SlamManager.d 


# Each subdirectory must supply rules for building sources it contributes
Src/RobotAPI/%.o: ../Src/RobotAPI/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/local/include/player-2.0/ -I/usr/local/include/player-2.0 -I/usr/local/include/ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


