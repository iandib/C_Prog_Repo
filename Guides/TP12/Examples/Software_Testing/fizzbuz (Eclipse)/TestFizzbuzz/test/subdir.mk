################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../test/test_fizzbuzz.c 

C_DEPS += \
./test/test_fizzbuzz.d 

OBJS += \
./test/test_fizzbuzz.o 


# Each subdirectory must supply rules for building sources it contributes
test/%.o: ../test/%.c test/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-test

clean-test:
	-$(RM) ./test/test_fizzbuzz.d ./test/test_fizzbuzz.o

.PHONY: clean-test

