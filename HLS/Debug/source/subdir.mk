################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../hamming_original.cpp 

OBJS += \
./source/hamming_original.o 

CPP_DEPS += \
./source/hamming_original.d 


# Each subdirectory must supply rules for building sources it contributes
source/hamming_original.o: /home/anders/master/MFCC/hamming_original.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DAESL_TB -D__llvm__ -D__llvm__ -I/tools/Xilinx/Vivado/2018.3/lnx64/tools/systemc/include -I/tools/Xilinx/Vivado/2018.3/lnx64/tools/auto_cc/include -I/home/anders/master -I/tools/Xilinx/Vivado/2018.3/include -I/tools/Xilinx/Vivado/2018.3/include/ap_sysc -I/tools/Xilinx/Vivado/2018.3/include/etc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


