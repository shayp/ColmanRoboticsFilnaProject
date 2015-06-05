################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Libs/PngLoader/lodepng.cpp \
../Libs/PngLoader/pngUtil.cpp 

OBJS += \
./Libs/PngLoader/lodepng.o \
./Libs/PngLoader/pngUtil.o 

CPP_DEPS += \
./Libs/PngLoader/lodepng.d \
./Libs/PngLoader/pngUtil.d 


# Each subdirectory must supply rules for building sources it contributes
Libs/PngLoader/%.o: ../Libs/PngLoader/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I/usr/local/include/player-2.0/ -I/usr/local/include/player-2.0 -I/usr/local/include/ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


