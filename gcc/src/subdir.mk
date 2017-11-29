################################################################################
# Automatically-generated file. Do not edit!
CPP_SRCS += \
../src/application.cpp \
../src/buffer.cpp \
../src/config.cpp \
../src/func.cpp \
../src/list.cpp \
../src/logger.cpp \
../src/object.cpp \
../src/stream.cpp \
../src/strings.cpp \
../src/utf.cpp \
../src/xmlParser.cpp

OBJS += \
./src/application.o \
./src/buffer.o \
./src/config.o \
./src/func.o \
./src/list.o \
./src/logger.o \
./src/object.o \
./src/stream.o \
./src/strings.o \
./src/utf.o \
./src/xmlParser.o

CPP_DEPS += \
./src/application.d \
./src/buffer.d \
./src/config.d \
./src/func.d \
./src/list.d \
./src/logger.d \
./src/object.d \
./src/stream.d \
./src/strings.d \
./src/utf.d \
./src/xmlParser.d


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -D__GXX_EXPERIMENTAL_CXX0X__ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


