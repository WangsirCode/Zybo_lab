################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../audio_demo.c \
../display_ctrl.c \
../display_demo.c \
../main.c \
../timer_ps.c 

OBJS += \
./audio_demo.o \
./display_ctrl.o \
./display_demo.o \
./main.o \
./timer_ps.o 

C_DEPS += \
./audio_demo.d \
./display_ctrl.d \
./display_demo.d \
./main.d \
./timer_ps.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -I../../lab10part2_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


