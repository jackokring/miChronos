################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
main.obj: ../main.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"/home/jacko/ti/ccsv5/tools/compiler/msp430_4.1.1/bin/cl430" -vmspx -g -O4 --opt_for_speed=0 --define=__CCE__ --define=ISM_EU --include_path="/home/jacko/ti/ccsv5/ccs_base/msp430/include" --include_path="/home/jacko/ti/ccsv5/tools/compiler/msp430_4.1.1/include" --include_path="/home/jacko/ti/ccsv5/msp430/include" --include_path="/home/jacko/ChronosSource/ez430_chronos/include" --include_path="/home/jacko/ChronosSource/ez430_chronos/driver" --include_path="/home/jacko/ChronosSource/ez430_chronos/logic" --include_path="/home/jacko/ChronosSource/ez430_chronos/bluerobin" --include_path="/home/jacko/ChronosSource/ez430_chronos/simpliciti" --diag_warning=225 --call_assumptions=2 --auto_inline=0 --gen_opt_info=2 --printf_support=minimal --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: $<'
	@echo ' '


