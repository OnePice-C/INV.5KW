################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcrc -O4 --opt_for_speed=2 --fp_mode=relaxed --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x/device" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x/device/driverlib" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x/libraries/DCL" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x/libraries/power_measurement" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x/libraries/sfra" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x/libraries/spll" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x/libraries/utilities/dlog" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x/libraries/utilities/rampgen" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x/libraries/FPUfastRTS" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=DEBUG --define=RAM --float_operations_allowed=32 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x/RELEASE/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1119981777: ../stringINV.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/ccs2011/ccs/utils/sysconfig_1.23.0/sysconfig_cli.bat" --script "D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x/stringINV.syscfg" -o "syscfg" -s "C:/ti/C2000Ware_DigitalPower_SDK_5_05_01_00/c2000ware/.metadata/sdk.json" -d "F28P55x" -p "128PDT" -r "F28P55x_128PDT" --compiler ccs
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/board.c: build-1119981777 ../stringINV.syscfg
syscfg/board.h: build-1119981777
syscfg/board.cmd.genlibs: build-1119981777
syscfg/board.opt: build-1119981777
syscfg/board.json: build-1119981777
syscfg/pinmux.csv: build-1119981777
syscfg/epwm.dot: build-1119981777
syscfg/device.c: build-1119981777
syscfg/device.h: build-1119981777
syscfg/adc.dot: build-1119981777
syscfg/device_cmd.cmd: build-1119981777
syscfg/device_cmd.c: build-1119981777
syscfg/device_cmd.h: build-1119981777
syscfg/device_cmd.opt: build-1119981777
syscfg/device_cmd.cmd.genlibs: build-1119981777
syscfg/c2000ware_libraries.cmd.genlibs: build-1119981777
syscfg/c2000ware_libraries.opt: build-1119981777
syscfg/c2000ware_libraries.c: build-1119981777
syscfg/c2000ware_libraries.h: build-1119981777
syscfg/clocktree.h: build-1119981777
syscfg: build-1119981777

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcrc -O4 --opt_for_speed=2 --fp_mode=relaxed --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x/device" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x/device/driverlib" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x/libraries/DCL" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x/libraries/power_measurement" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x/libraries/sfra" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x/libraries/spll" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x/libraries/utilities/dlog" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x/libraries/utilities/rampgen" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x/libraries/FPUfastRTS" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=DEBUG --define=RAM --float_operations_allowed=32 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x/RELEASE/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

f28p55x_codestartbranch.obj: C:/ti/C2000Ware_DigitalPower_SDK_5_05_01_00/c2000ware/device_support/f28p55x/common/source/f28p55x_codestartbranch.asm $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcrc -O4 --opt_for_speed=2 --fp_mode=relaxed --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x/device" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x/device/driverlib" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x/libraries/DCL" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x/libraries/power_measurement" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x/libraries/sfra" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x/libraries/spll" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x/libraries/utilities/dlog" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x/libraries/utilities/rampgen" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x/libraries/FPUfastRTS" --include_path="C:/ti/ccs2011/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=DEBUG --define=RAM --float_operations_allowed=32 --diag_suppress=10063 --diag_warning=225 --diag_wrap=off --display_error_number --gen_func_subsections=on --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="D:/DTKH.INV.13.OFG/INV.5KW.OG.Design/firmware/exemple/sinv_F28P55x/RELEASE/syscfg" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


