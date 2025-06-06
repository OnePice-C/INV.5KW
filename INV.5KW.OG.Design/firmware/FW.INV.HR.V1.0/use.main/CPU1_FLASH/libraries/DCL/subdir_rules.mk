################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
libraries/DCL/%.obj: ../libraries/DCL/%.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu64 --tmu_support=tmu1 --vcu_support=vcrc -Ooff --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main" --include_path="C:/ti/C2000Ware_5_04_00_00" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main/device" --include_path="C:/ti/C2000Ware_5_04_00_00/driverlib/f28p65x/driverlib/" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=_FLASH --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="libraries/DCL/$(basename $(<F)).d_raw" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main/CPU1_FLASH/syscfg" --obj_directory="libraries/DCL" --cmd_file="syscfg/board.opt" --cmd_file="syscfg/c2000ware_libraries.opt" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


