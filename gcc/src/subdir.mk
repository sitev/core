################################################################################
# Automatically-generated file. Do not edit!
CPP_SRCS += \
../src/application.cpp \
../src/logger.cpp \
../src/object.cpp \
../src/config.cpp \
../src/stream.cpp 

OBJS += \
./src/application.o \
./src/logger.o \
./src/object.o \
./src/config.o \
./src/stream.o 

CPP_DEPS += \
./src/application.d \
./src/logger.d \
./src/object.d \
./src/config.d \
./src/stream.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


