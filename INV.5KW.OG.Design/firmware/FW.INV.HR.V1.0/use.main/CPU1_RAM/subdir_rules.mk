################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
build-1312403247: ../c2000.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs2011/ccs/utils/sysconfig_1.24.0/sysconfig_cli.bat" --script "D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main/c2000.syscfg" -o "syscfg" -s "C:/ti/C2000Ware_5_04_00_00/.metadata/sdk.json" -d "F28P65x" -p "100PZP" -r "F28P65x_100PZP" --context "CPU1" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/board.c: build-1312403247 ../c2000.syscfg
syscfg/board.h: build-1312403247
syscfg/board.cmd.genlibs: build-1312403247
syscfg/board.opt: build-1312403247
syscfg/board.json: build-1312403247
syscfg/pinmux.csv: build-1312403247
syscfg/epwm.dot: build-1312403247
syscfg/adc.dot: build-1312403247
syscfg/c2000ware_libraries.cmd.genlibs: build-1312403247
syscfg/c2000ware_libraries.opt: build-1312403247
syscfg/c2000ware_libraries.c: build-1312403247
syscfg/c2000ware_libraries.h: build-1312403247
syscfg/clocktree.h: build-1312403247
syscfg: build-1312403247

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu64 --tmu_support=tmu1 --vcu_support=vcrc -Ooff --fp_mode=relaxed --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main" --include_path="C:/ti/C2000Ware_5_04_00_00" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main/device" --include_path="C:/ti/C2000Ware_5_04_00_00/driverlib/f28p65x/driverlib/" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main/libraries/utilities/dlog" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main/libraries/sfra" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main/libraries/power_measurement" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main/libraries/FPUfastRTS" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main/libraries/spll" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main/libraries/DCL" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main/libraries/utilities/rampgen" --define=RAM --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main/CPU1_RAM/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

controler_CL.obj: ../controler_CL.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu64 --tmu_support=tmu1 --vcu_support=vcrc -Ooff --fp_mode=relaxed --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main" --include_path="C:/ti/C2000Ware_5_04_00_00" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main/device" --include_path="C:/ti/C2000Ware_5_04_00_00/driverlib/f28p65x/driverlib/" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main/libraries/utilities/dlog" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main/libraries/sfra" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main/libraries/power_measurement" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main/libraries/FPUfastRTS" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main/libraries/spll" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main/libraries/DCL" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main/libraries/utilities/rampgen" --define=RAM --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main/CPU1_RAM/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

inv_hr_main.obj: ../inv_hr_main.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu64 --tmu_support=tmu1 --vcu_support=vcrc -Ooff --fp_mode=relaxed --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main" --include_path="C:/ti/C2000Ware_5_04_00_00" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main/device" --include_path="C:/ti/C2000Ware_5_04_00_00/driverlib/f28p65x/driverlib/" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main/libraries/utilities/dlog" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main/libraries/sfra" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main/libraries/power_measurement" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main/libraries/FPUfastRTS" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main/libraries/spll" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main/libraries/DCL" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main/libraries/utilities/rampgen" --define=RAM --define=DEBUG --define=CPU1 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/FW.INV.HR.V1.0/use.main/CPU1_RAM/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


