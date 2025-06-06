//##############################################################################
//
// FILE:  stringINV.c
//
// TITLE:  Solution file for the string inverter
//
//##############################################################################
// $TI Release: TIDA_010938 v2.01.00.00 $
// $Release Date: Tue May  6 00:20:46 CDT 2025 $
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
//
// ALL RIGHTS RESERVED
// $
//##############################################################################

#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "c2000ware_libraries.h"

#include <stringINV_settings.h>
#include "stringINV.h"
#include <stringINV_dcdc_mppt.h>
#include "spll_1ph_sogi.h"
#include "DCLF32.h"
#include "stdint.h"
#include "rampgen.h"
#include "dlog_4ch.h"
#include "power_meas_sine_analyzer.h"


/////////////////////////ACDC Settings//////////////////////////

 //Ramp Generator parameters String Inverter
#pragma RETAIN (stringINV_ACDC_rgen)
#pragma RETAIN (stringINV_ACDC_Index_Modulation)
RAMPGEN stringINV_ACDC_rgen;
float32_t stringINV_ACDC_Index_Modulation;
float32_t stringINV_ACDC_Amplitude;

//DC/DC duty cycle
#pragma RETAIN (Boost_S1_Duty_Cycle)
#pragma RETAIN (Boost_S2_Duty_Cycle)
#pragma RETAIN (Batt1_Duty_Cycle)
#pragma RETAIN (Batt2_Duty_Cycle)
float32_t Boost_S1_Duty_Cycle;
float32_t Boost_S2_Duty_Cycle;
float32_t Batt1_Duty_Cycle;
float32_t Batt2_Duty_Cycle;

/////////////////////////ACDC Settings//////////////////////////

 //Date Logger
DLOG_4CH stringINV_ACDC_dLog1;
DLOG_4CH stringINV_ACDC_dLog2;
float32_t stringINV_ACDC_dBuff1[stringINV_ACDC_DLOG_SIZE];
float32_t stringINV_ACDC_dBuff2[stringINV_ACDC_DLOG_SIZE];
float32_t stringINV_ACDC_dBuff3[stringINV_ACDC_DLOG_SIZE];
float32_t stringINV_ACDC_dBuff4[stringINV_ACDC_DLOG_SIZE];
float32_t stringINV_ACDC_dBuff5[stringINV_ACDC_DLOG_SIZE_OSC2 ];
float32_t stringINV_ACDC_dBuff6[stringINV_ACDC_DLOG_SIZE_OSC2 ];
float32_t stringINV_ACDC_dBuff7[stringINV_ACDC_DLOG_SIZE_OSC2 ];
float32_t stringINV_ACDC_dBuff8[stringINV_ACDC_DLOG_SIZE_OSC2 ];
float32_t stringINV_ACDC_dVal1;
float32_t stringINV_ACDC_dVal2;
float32_t stringINV_ACDC_dVal3;
float32_t stringINV_ACDC_dVal4;
float32_t stringINV_ACDC_dVal5;
float32_t stringINV_ACDC_dVal6;
float32_t stringINV_ACDC_dVal7;
float32_t stringINV_ACDC_dVal8;
//

//Temperature Measurements DC/DC
#pragma RETAIN (TEMP_Boost1_Buff_Duty)
#pragma RETAIN (TEMP_Boost2_Buff_Duty)
#pragma RETAIN (TEMP_Batt_H1_Buff_Duty)
#pragma RETAIN (TEMP_Batt_L1_Buff_Duty)
#pragma RETAIN (TEMP_Batt_H2_Buff_Duty)
#pragma RETAIN (TEMP_Batt_L2_Buff_Duty)
#pragma RETAIN (TEMP_Boost1_Buff)
#pragma RETAIN (TEMP_Boost2_Buff)
#pragma RETAIN (TEMP_Batt_H1_Buff)
#pragma RETAIN (TEMP_Batt_L1_Buff)
#pragma RETAIN (TEMP_Batt_H2_Buff)
#pragma RETAIN (TEMP_Batt_L2_Buff)
#pragma RETAIN (stringINV_GaN_Temp_Counter)

float32_t TEMP_Boost1_Buff_Duty;
float32_t TEMP_Boost2_Buff_Duty;
float32_t TEMP_Batt_H1_Buff_Duty;
float32_t TEMP_Batt_L1_Buff_Duty;
float32_t TEMP_Batt_H2_Buff_Duty;
float32_t TEMP_Batt_L2_Buff_Duty;
float32_t TEMP_Boost1_Buff;
float32_t TEMP_Boost2_Buff;
float32_t TEMP_Batt_H1_Buff;
float32_t TEMP_Batt_L1_Buff;
float32_t TEMP_Batt_H2_Buff;
float32_t TEMP_Batt_L2_Buff;
uint32_t stringINV_GaN_Temp_Counter;
//

//LPF Temperature measurements DC/DC
#pragma RETAIN (TEMP_Boost1_FILTER)
#pragma RETAIN (TEMP_Boost2_FILTER)
#pragma RETAIN (TEMP_Batt_H1_FILTER)
#pragma RETAIN (TEMP_Batt_L1_FILTER)
#pragma RETAIN (TEMP_Batt_H2_FILTER)
#pragma RETAIN (TEMP_Batt_L2_FILTER)

float32_t TEMP_Boost1_FILTER;
float32_t TEMP_Boost2_FILTER;
float32_t TEMP_Batt_H1_FILTER;
float32_t TEMP_Batt_L1_FILTER;
float32_t TEMP_Batt_H2_FILTER;
float32_t TEMP_Batt_L2_FILTER;

//Temperature Measurements AC/DC
#pragma RETAIN (TEMP_S1_Duty)
#pragma RETAIN (TEMP_S2_Duty)
#pragma RETAIN (TEMP_S3_Duty)
#pragma RETAIN (TEMP_S4_Duty)
#pragma RETAIN (TEMP_S5_Duty)
#pragma RETAIN (TEMP_S6_Duty)
#pragma RETAIN (TEMP_S1)
#pragma RETAIN (TEMP_S2)
#pragma RETAIN (TEMP_S3)
#pragma RETAIN (TEMP_S4)
#pragma RETAIN (TEMP_S5)
#pragma RETAIN (TEMP_S6)

float32_t TEMP_S1_Duty;
float32_t TEMP_S2_Duty;
float32_t TEMP_S3_Duty;
float32_t TEMP_S4_Duty;
float32_t TEMP_S5_Duty;
float32_t TEMP_S6_Duty;
float32_t TEMP_S1;
float32_t TEMP_S2;
float32_t TEMP_S3;
float32_t TEMP_S4;
float32_t TEMP_S5;
float32_t TEMP_S6;

//LPF Temperature measurements DC/DC
#pragma RETAIN (TEMP_S1_FILTER)
#pragma RETAIN (TEMP_S2_FILTER)
#pragma RETAIN (TEMP_S3_FILTER)
#pragma RETAIN (TEMP_S4_FILTER)
#pragma RETAIN (TEMP_S5_FILTER)
#pragma RETAIN (TEMP_S6_FILTER)

float32_t TEMP_S1_FILTER;
float32_t TEMP_S2_FILTER;
float32_t TEMP_S3_FILTER;
float32_t TEMP_S4_FILTER;
float32_t TEMP_S5_FILTER;
float32_t TEMP_S6_FILTER;

//PLL
#pragma RETAIN (stringINV_reset_PLL)
#pragma RETAIN (stringINV_spll_1ph)

int32_t stringINV_reset_PLL;
SPLL_1PH_SOGI stringINV_spll_1ph;

//Power meas library
POWER_MEAS_SINE_ANALYZER stringINV_mains_L1;

//Analog Measurements

//Analog Measurements String Inverter AC/DC PU
#pragma RETAIN (stringINV_ACDC_iAC_sensed_pu)
#pragma RETAIN (stringINV_ACDC_iAC_REF_sensed_pu)
#pragma RETAIN (stringINV_ACDC_vAC_sensed_pu)
#pragma RETAIN (stringINV_ACDC_vINV_sensed_pu)
#pragma RETAIN (stringINV_ACDC_vDC_sensed_pu)
#pragma RETAIN (stringINV_ACDC_iDC_sensed_pu)

float32_t stringINV_ACDC_iAC_sensed_pu;
float32_t stringINV_ACDC_iAC_REF_sensed_pu;
float32_t stringINV_ACDC_vAC_sensed_pu;
float32_t stringINV_ACDC_vINV_sensed_pu;
float32_t stringINV_ACDC_vDC_sensed_pu;
float32_t stringINV_ACDC_iDC_sensed_pu;

//Analog Measurements String Inverter AC/DC
#pragma RETAIN (stringINV_ACDC_iAC_sensed)
#pragma RETAIN (stringINV_ACDC_vAC_sensed)
#pragma RETAIN (stringINV_ACDC_vINV_sensed)
#pragma RETAIN (stringINV_ACDC_vDC_sensed)
#pragma RETAIN (stringINV_ACDC_iDC_sensed)

float32_t stringINV_ACDC_iAC_sensed;
float32_t stringINV_ACDC_vAC_sensed;
float32_t stringINV_ACDC_vINV_sensed;
float32_t stringINV_ACDC_vDC_sensed;
float32_t stringINV_ACDC_iDC_sensed;

//Analog Measurements String Inverter DC/DC PU
#pragma RETAIN (stringINV_DCDC_CS_Boost1_sensed_pu)
#pragma RETAIN (stringINV_DCDC_VS_Boost1_sensed_pu)
#pragma RETAIN (stringINV_DCDC_CS_Boost2_sensed_pu)
#pragma RETAIN (stringINV_DCDC_VS_Boost2_sensed_pu)
#pragma RETAIN (stringINV_DCDC_CS_Batt1_sensed_pu)
#pragma RETAIN (stringINV_DCDC_VS_Batt_sensed_pu)
#pragma RETAIN (stringINV_DCDC_CS_Batt2_sensed_pu)
#pragma RETAIN (stringINV_DCDC_vDC_sensed_pu)

float32_t stringINV_DCDC_CS_Boost1_sensed_pu;
float32_t stringINV_DCDC_VS_Boost1_sensed_pu;
float32_t stringINV_DCDC_CS_Boost2_sensed_pu;
float32_t stringINV_DCDC_VS_Boost2_sensed_pu;
float32_t stringINV_DCDC_CS_Batt1_sensed_pu;
float32_t stringINV_DCDC_VS_Batt_sensed_pu;
float32_t stringINV_DCDC_CS_Batt2_sensed_pu;
float32_t stringINV_DCDC_vDC_sensed_pu;

//Analog Measurements String Inverter DC/DC
#pragma RETAIN (stringINV_DCDC_CS_Boost1_sensed)
#pragma RETAIN (stringINV_DCDC_VS_Boost1_sensed)
#pragma RETAIN (stringINV_DCDC_CS_Boost2_sensed)
#pragma RETAIN (stringINV_DCDC_VS_Boost2_sensed)
#pragma RETAIN (stringINV_DCDC_CS_Batt1_sensed)
#pragma RETAIN (stringINV_DCDC_VS_Batt_sensed)
#pragma RETAIN (stringINV_DCDC_CS_Batt2_sensed)
#pragma RETAIN (stringINV_DCDC_vDC_sensed)

float32_t stringINV_DCDC_CS_Boost1_sensed;
float32_t stringINV_DCDC_VS_Boost1_sensed;
float32_t stringINV_DCDC_CS_Boost2_sensed;
float32_t stringINV_DCDC_VS_Boost2_sensed;
float32_t stringINV_DCDC_CS_Batt1_sensed;
float32_t stringINV_DCDC_VS_Batt_sensed;
float32_t stringINV_DCDC_CS_Batt2_sensed;
float32_t stringINV_DCDC_vDC_sensed;


#pragma RETAIN (stringINV_DCDC_CS_Boost1_sensed_FILTER)
#pragma RETAIN (stringINV_DCDC_VS_Boost1_sensed_FILTER)
#pragma RETAIN (stringINV_DCDC_CS_Boost2_sensed_FILTER)
#pragma RETAIN (stringINV_DCDC_VS_Boost2_sensed_FILTER)
#pragma RETAIN (stringINV_DCDC_vDC_sensed_FILTER)
#pragma RETAIN (stringINV_DCDC_b1_voltage_ref)
#pragma RETAIN (stringINV_DCDC_b2_voltage_ref)

float32_t stringINV_DCDC_CS_Boost1_sensed_FILTER;
float32_t stringINV_DCDC_VS_Boost1_sensed_FILTER;
float32_t stringINV_DCDC_CS_Boost2_sensed_FILTER;
float32_t stringINV_DCDC_VS_Boost2_sensed_FILTER;
float32_t stringINV_DCDC_vDC_sensed_FILTER;
float32_t stringINV_DCDC_b1_voltage_ref;
float32_t stringINV_DCDC_b2_voltage_ref;

//MPPT
#pragma RETAIN (stringINV_DCDC_mppt_counter)
uint32_t stringINV_DCDC_mppt_counter;

#pragma RETAIN (stringINV_DCDC_b1_mppt_incc)
#pragma RETAIN (stringINV_DCDC_b2_mppt_incc)
stringINV_dcdc_mppt_t stringINV_DCDC_b1_mppt_incc;
stringINV_dcdc_mppt_t stringINV_DCDC_b2_mppt_incc;

//Filtering of the measurements String Inverter
#pragma RETAIN (stringINV_DCDC_VS_Batt_sensed_FILTER)
#pragma RETAIN (stringINV_ACDC_vDC_sensed_FILTER)
#pragma RETAIN (stringINV_ACDC_vDC_sensed_NOTCH)
#pragma RETAIN (stringINV_ACDC_vAC_sensed_FILTER)
#pragma RETAIN (stringINV_ACDC_vAC_RMS_FILTER)

float32_t stringINV_DCDC_VS_Batt_sensed_FILTER;
float32_t stringINV_ACDC_vDC_sensed_FILTER;
float32_t stringINV_ACDC_vDC_sensed_NOTCH;
float32_t stringINV_ACDC_vAC_sensed_FILTER;
float32_t stringINV_ACDC_vAC_RMS_FILTER;

//State Machines
#pragma RETAIN (stringINV_ADC_fault)
#pragma RETAIN (stringINV_stop)
int32_t stringINV_ADC_fault;
int32_t stringINV_stop;

//FFW for ACDC Voltage control loop
int32_t stringINV_DCAC_Counter_Disable_FFW;

//Counter for faults
int32_t stringINV_Counter_Faults;

#pragma RETAIN (stringINV_FAULT_FLAGS)
stringINV_FAULTS_t stringINV_FAULT_FLAGS;

//ADC Measurements Fault Analog Measurements
#pragma RETAIN (stringINV_fault_read_start)
#pragma RETAIN (stringINV_fault_read_completed)
#pragma RETAIN (stringINV_DCDC_CS_Batt1_fault)
#pragma RETAIN (stringINV_DCDC_CS_Batt2_fault)
#pragma RETAIN (stringINV_DCDC_VS_Batt_fault)
#pragma RETAIN (stringINV_DCDC_CS_Boost1_fault)
#pragma RETAIN (stringINV_DCDC_VS_Boost1_fault)
#pragma RETAIN (stringINV_DCDC_CS_Boost2_fault)
#pragma RETAIN (stringINV_DCDC_VS_Boost2_fault)
#pragma RETAIN (stringINV_ACDC_iAC_fault)
#pragma RETAIN (stringINV_ACDC_vAC_fault)
#pragma RETAIN (stringINV_ACDC_vAC_RMS_fault)
#pragma RETAIN (stringINV_ACDC_vDC_fault)
#pragma RETAIN (stringINV_ACDC_iDC_fault)
#pragma RETAIN (stringINV_Boost1_Duty_Ref_fault)
#pragma RETAIN (stringINV_Boost2_Duty_Ref_fault)
#pragma RETAIN (stringINV_Boost1_Duty_Ref_Slewed_fault)
#pragma RETAIN (stringINV_Boost2_Duty_Ref_Slewed_fault)
#pragma RETAIN (Batt1_Duty_Cycle_fault)
#pragma RETAIN (Batt2_Duty_Cycle_fault)
#pragma RETAIN (stringINV_ACDC_Index_Modulation_fault)

int32_t stringINV_fault_read_start;
int32_t stringINV_fault_read_completed;
float32_t stringINV_DCDC_CS_Batt1_fault;
float32_t stringINV_DCDC_CS_Batt2_fault;
float32_t stringINV_DCDC_VS_Batt_fault;
float32_t stringINV_DCDC_CS_Boost1_fault;
float32_t stringINV_DCDC_VS_Boost1_fault;
float32_t stringINV_DCDC_CS_Boost2_fault;
float32_t stringINV_DCDC_VS_Boost2_fault;
float32_t stringINV_ACDC_iAC_fault;
float32_t stringINV_ACDC_vAC_fault;
float32_t stringINV_ACDC_vAC_RMS_fault;
float32_t stringINV_ACDC_vDC_fault;
float32_t stringINV_ACDC_iDC_fault;
float32_t stringINV_Boost1_Duty_Ref_fault;
float32_t stringINV_Boost2_Duty_Ref_fault;
float32_t stringINV_Boost1_Duty_Ref_Slewed_fault;
float32_t stringINV_Boost2_Duty_Ref_Slewed_fault;
float32_t Batt1_Duty_Cycle_fault;
float32_t Batt2_Duty_Cycle_fault;
float32_t stringINV_ACDC_Index_Modulation_fault;

#pragma RETAIN (TEMP_Boost1_FILTER_fault)
#pragma RETAIN (TEMP_Boost2_FILTER_fault)
#pragma RETAIN (TEMP_Batt_H1_FILTER_fault)
#pragma RETAIN (TEMP_Batt_L1_FILTER_fault)
#pragma RETAIN (TEMP_Batt_H2_FILTER_fault)
#pragma RETAIN (TEMP_Batt_L2_FILTER_fault)
#pragma RETAIN (TEMP_S1_FILTER_fault)
#pragma RETAIN (TEMP_S2_FILTER_fault)
#pragma RETAIN (TEMP_S3_FILTER_fault)
#pragma RETAIN (TEMP_S4_FILTER_fault)
#pragma RETAIN (TEMP_S5_FILTER_fault)
#pragma RETAIN (TEMP_S6_FILTER_fault)

float32_t TEMP_Boost1_FILTER_fault;
float32_t TEMP_Boost2_FILTER_fault;
float32_t TEMP_Batt_H1_FILTER_fault;
float32_t TEMP_Batt_L1_FILTER_fault;
float32_t TEMP_Batt_H2_FILTER_fault;
float32_t TEMP_Batt_L2_FILTER_fault;
float32_t TEMP_S1_FILTER_fault;
float32_t TEMP_S2_FILTER_fault;
float32_t TEMP_S3_FILTER_fault;
float32_t TEMP_S4_FILTER_fault;
float32_t TEMP_S5_FILTER_fault;
float32_t TEMP_S6_FILTER_fault;

//Control Variables Reference values String Inverter
#pragma RETAIN (stringINV_ACDC_iAC_real_Ref)
#pragma RETAIN (stringINV_ACDC_iAC_imag_Ref)
#pragma RETAIN (stringINV_ACDC_iAC_Ref)
#pragma RETAIN (stringINV_ACDC_iAC_Ref_slewed)
#pragma RETAIN (stringINV_ACDC_iAC_real_Ref)
#pragma RETAIN (stringINV_ACDC_iAC_real_Ref_slewed)
#pragma RETAIN (stringINV_ACDC_iAC_imag_Ref_slewed)
#pragma RETAIN (stringINV_ACDC_iAC_amp_Ref)

float32_t stringINV_ACDC_iAC_real_Ref; // you control the amplitude of the real part
float32_t stringINV_ACDC_iAC_imag_Ref; // you control the amplitude of the imag part
float32_t stringINV_ACDC_iAC_Ref; // final results of real and imag together.
float32_t stringINV_ACDC_iAC_Ref_slewed; //Ramped value
float32_t stringINV_ACDC_iAC_real_Ref; // real current reference
float32_t stringINV_ACDC_iAC_real_Ref_slewed; //Ramped value
float32_t stringINV_ACDC_iAC_imag_Ref_slewed; // you control the amplitude of the imag part
float32_t stringINV_ACDC_iAC_amp_Ref; // you will use this one to monitor the peak current.

//PI control battery
#pragma RETAIN (stringINV_DCDC_CS_Batt_Ref)
#pragma RETAIN (stringINV_DCDC_CS_Batt_Ref_Slewed)

float32_t stringINV_DCDC_CS_Batt_Ref; //DC-DC current ref
float32_t stringINV_DCDC_CS_Batt_Ref_Slewed;

#pragma RETAIN (stringINV_DCDC_CS_Batt1_loop_err)
#pragma RETAIN (stringINV_DCDC_CS_Batt2_loop_err)

float32_t stringINV_DCDC_CS_Batt1_loop_err;
float32_t stringINV_DCDC_CS_Batt2_loop_err;

//PI control DC Bus voltage
#pragma RETAIN (stringINV_DCDC_VDC_loop_err)
#pragma RETAIN (stringINV_DCDC_VDCext_Ref)
#pragma RETAIN (stringINV_DCDC_VDCext_Ref_Slewed)

float32_t stringINV_DCDC_VDC_loop_err;
float32_t stringINV_DCDC_VDCext_Ref;
float32_t stringINV_DCDC_VDCext_Ref_Slewed;

//PI Control Boost converters
#pragma RETAIN (stringINV_DCDC_VBoost1_loop_err)
#pragma RETAIN (stringINV_DCDC_VBoost2_loop_err)

float32_t stringINV_DCDC_VBoost1_loop_err;
float32_t stringINV_DCDC_VBoost2_loop_err;

DCL_PI gi_Batt_pi_1 = PI_DEFAULTS;
DCL_PI gi_Batt_pi_2 = PI_DEFAULTS;
DCL_PI gv_VBoost_pi_1 = PI_DEFAULTS;
DCL_PI gv_VBoost_pi_2 = PI_DEFAULTS;

//Slewed Reference and Outputs
#pragma RETAIN (stringINV_DCDC_vDC_Ref)
#pragma RETAIN (stringINV_DCDC_vDC_Ref_Slewed)

float32_t stringINV_DCDC_vDC_Ref;
float32_t stringINV_DCDC_vDC_Ref_Slewed;

#pragma RETAIN (stringINV_DCDC_BOOST1PWM_Ref)
#pragma RETAIN (stringINV_DCDC_BOOST1PWM_Ref_Slewed)

float32_t stringINV_DCDC_BOOST1PWM_Ref;
float32_t stringINV_DCDC_BOOST1PWM_Ref_Slewed;

#pragma RETAIN (stringINV_DCDC_BOOST2PWM_Ref)
#pragma RETAIN (stringINV_DCDC_BOOST2PWM_Ref_Slewed)

float32_t stringINV_DCDC_BOOST2PWM_Ref;
float32_t stringINV_DCDC_BOOST2PWM_Ref_Slewed;

#pragma RETAIN (stringINV_DCDC_IDC_Ref)
#pragma RETAIN (stringINV_DCDC_IDC_Ref_Slewed)

float32_t stringINV_DCDC_IDC_Ref;
float32_t stringINV_DCDC_IDC_Ref_Slewed;

#pragma RETAIN (stringINV_Boost1_Duty_Ref)
#pragma RETAIN (stringINV_Boost1_Duty_Ref_Slewed)

float32_t stringINV_Boost1_Duty_Ref;
float32_t stringINV_Boost1_Duty_Ref_Slewed;

#pragma RETAIN (stringINV_Boost2_Duty_Ref)
#pragma RETAIN (stringINV_Boost2_Duty_Ref_Slewed)

float32_t stringINV_Boost2_Duty_Ref;
float32_t stringINV_Boost2_Duty_Ref_Slewed;

#pragma RETAIN (stringINV_IDCAC_Ref)
#pragma RETAIN (stringINV_IDCAC_Ref_Slewed)

float32_t stringINV_IDCAC_Ref;
float32_t stringINV_IDCAC_Ref_Slewed;

//Control Variables Error String Inverter
#pragma RETAIN (stringINV_ACDC_iAC_loop_err)
#pragma RETAIN (stringINV_ACDC_vDC_loop_err)
#pragma RETAIN (stringINV_ACDC_iAC_real_Ref_OUT_PI)

float32_t stringINV_ACDC_iAC_loop_err;
float32_t stringINV_ACDC_vDC_loop_err;
float32_t stringINV_ACDC_iAC_real_Ref_OUT_PI;

#pragma RETAIN (stringINV_ACDC_iAC_loop_out_PI)
#pragma RETAIN (stringINV_ACDC_iAC_loop_out_PR1)
#pragma RETAIN (stringINV_ACDC_iAC_loop_out_PR3)
#pragma RETAIN (stringINV_ACDC_iAC_loop_out_PR5)
#pragma RETAIN (stringINV_ACDC_iAC_loop_out_PR7)
#pragma RETAIN (stringINV_ACDC_iAC_loop_out_PR9)
#pragma RETAIN (stringINV_ACDC_iAC_loop_out_PR11)
#pragma RETAIN (stringINV_ACDC_iAC_loop_out_PR13)
#pragma RETAIN (stringINV_ACDC_iAC_loop_out_PR15)
#pragma RETAIN (stringINV_ACDC_iAC_loop_out_PR17)
#pragma RETAIN (stringINV_ACDC_iAC_loop_out_SUM)

float32_t stringINV_ACDC_iAC_loop_out_PI;
float32_t stringINV_ACDC_iAC_loop_out_PR1;
float32_t stringINV_ACDC_iAC_loop_out_PR3;
float32_t stringINV_ACDC_iAC_loop_out_PR5;
float32_t stringINV_ACDC_iAC_loop_out_PR7;
float32_t stringINV_ACDC_iAC_loop_out_PR9;
float32_t stringINV_ACDC_iAC_loop_out_PR11;
float32_t stringINV_ACDC_iAC_loop_out_PR13;
float32_t stringINV_ACDC_iAC_loop_out_PR15;
float32_t stringINV_ACDC_iAC_loop_out_PR17;
float32_t stringINV_ACDC_iAC_loop_out_SUM;

//PI ACDC
DCL_PI gi_ACDC_pi = PI_DEFAULTS;
DCL_PI gv_ACDC_pi = PI_DEFAULTS;

DCL_DF22 gi_r1 = DF22_DEFAULTS;
DCL_DF22 gi_r3 = DF22_DEFAULTS;
DCL_DF22 gi_r5 = DF22_DEFAULTS;
DCL_DF22 gi_r7 = DF22_DEFAULTS;
DCL_DF22 gi_r9 = DF22_DEFAULTS;
DCL_DF22 gi_r11 = DF22_DEFAULTS;
DCL_DF22 gi_r13 = DF22_DEFAULTS;
DCL_DF22 gi_r15 = DF22_DEFAULTS;
DCL_DF22 gi_r17 = DF22_DEFAULTS;

//For tuning PR and R controllers
float32_t kpI_1H;
float32_t kiI_1H, kiI_3H, kiI_5H, kiI_7H, kiI_9H, kiI_11H, kiI_13H, kiI_15H, kiI_17H;
float32_t woI_1H, woI_3H, woI_5H, woI_7H, woI_9H, woI_11H, woI_13H, woI_15H, woI_17H;
float32_t wrcI_1H, wrcI_3H, wrcI_5H, wrcI_7H, wrcI_9H, wrcI_11H, wrcI_13H, wrcI_15H, wrcI_17H;

DCL_DF22 VDC_NOTCH_FILTER_2_Fe= DF22_DEFAULTS;

#pragma RETAIN (stringINV_clearPWMTrip)
#pragma RETAIN (stringINV_updateDuty)
#pragma RETAIN (stringINV_clearPWMTripBoost)
#pragma RETAIN (stringINV_updateDutyBoost)
#pragma RETAIN (stringINV_clearPWMTripDCDC)
#pragma RETAIN (stringINV_updateDutyDCDC)
#pragma RETAIN (stringINV_clearPWMTripDCAC)
#pragma RETAIN (stringINV_updateDutyDCAC)
#pragma RETAIN (stringINV_enableUVFaults)

uint16_t stringINV_clearPWMTrip;
uint16_t stringINV_updateDuty;
uint16_t stringINV_clearPWMTripBoost;
uint16_t stringINV_updateDutyBoost;
uint16_t stringINV_clearPWMTripDCDC;
uint16_t stringINV_updateDutyDCDC;
uint16_t stringINV_clearPWMTripDCAC;
uint16_t stringINV_updateDutyDCAC;
uint16_t stringINV_enableUVFaults;

#pragma RETAIN (stringINV_enableDCRelay)
#pragma RETAIN (stringINV_enableACRelay)

uint16_t stringINV_enableDCRelay;
uint16_t stringINV_enableACRelay;

//debugging
#pragma RETAIN (stringINV_Counter)
uint16_t stringINV_Counter;




void stringINV_PeripheralInit() {


    GPIO_writePin(Enable_CAN, 0);
    GPIO_writePin(Enable_RS485, 0);

    GPIO_writePin(Enable_Buffer_ACDC, 0); // Enables DC/AC Buffer
    GPIO_writePin(Enable_Buffer_DCDC, 0); // Enables DC/DC Buffer

    //Overcurrent Fault Setting

    // Trigger event when DCBH is high
    EPWM_setTripZoneDigitalCompareEventCondition(BOOST_BASE,
                                                 EPWM_TZ_DC_OUTPUT_B1,
                                                 EPWM_TZ_EVENT_DCXH_HIGH);

    EPWM_setTripZoneDigitalCompareEventCondition(Bidirectional1_BASE,
                                                 EPWM_TZ_DC_OUTPUT_B1,
                                                 EPWM_TZ_EVENT_DCXH_HIGH);

    EPWM_setTripZoneDigitalCompareEventCondition(Bidirectional2_BASE,
                                                 EPWM_TZ_DC_OUTPUT_B1,
                                                 EPWM_TZ_EVENT_DCXH_HIGH);


    EPWM_setTripZoneDigitalCompareEventCondition(DCAC1_BASE,
                                                 EPWM_TZ_DC_OUTPUT_B1,
                                                 EPWM_TZ_EVENT_DCXH_HIGH);

    EPWM_setTripZoneDigitalCompareEventCondition(DCAC2_BASE,
                                                 EPWM_TZ_DC_OUTPUT_B1,
                                                 EPWM_TZ_EVENT_DCXH_HIGH);



    // Configure DCBH to use TRIPs as an input
    EPWM_enableDigitalCompareTripCombinationInput(BOOST_BASE,
                                                  EPWM_DC_COMBINATIONAL_TRIPIN5,
                                                  EPWM_DC_TYPE_DCBH);


    EPWM_enableDigitalCompareTripCombinationInput(Bidirectional1_BASE,
                                                  EPWM_DC_COMBINATIONAL_TRIPIN10,
                                                  EPWM_DC_TYPE_DCBH);

    EPWM_enableDigitalCompareTripCombinationInput(Bidirectional2_BASE,
                                                  EPWM_DC_COMBINATIONAL_TRIPIN10,
                                                  EPWM_DC_TYPE_DCBH);

    EPWM_enableDigitalCompareTripCombinationInput(DCAC1_BASE,
                                                  EPWM_DC_COMBINATIONAL_TRIPIN12,
                                                  EPWM_DC_TYPE_DCBH);

    EPWM_enableDigitalCompareTripCombinationInput(DCAC2_BASE,
                                                  EPWM_DC_COMBINATIONAL_TRIPIN12,
                                                  EPWM_DC_TYPE_DCBH);


    // Enable DCB as OST
    EPWM_enableTripZoneSignals(BOOST_BASE, EPWM_TZ_SIGNAL_DCBEVT1);

    EPWM_enableTripZoneSignals(Bidirectional1_BASE, EPWM_TZ_SIGNAL_DCBEVT1);

    EPWM_enableTripZoneSignals(Bidirectional2_BASE, EPWM_TZ_SIGNAL_DCBEVT1);

    EPWM_enableTripZoneSignals(DCAC1_BASE, EPWM_TZ_SIGNAL_DCBEVT1);

    EPWM_enableTripZoneSignals(DCAC2_BASE, EPWM_TZ_SIGNAL_DCBEVT1);


    // Configure the DCB path to be unfiltered and asynchronous
    EPWM_setDigitalCompareEventSource(BOOST_BASE,
                                      EPWM_DC_MODULE_B,
                                      EPWM_DC_EVENT_1,
                                      EPWM_DC_EVENT_SOURCE_ORIG_SIGNAL);


    EPWM_setDigitalCompareEventSource(Bidirectional1_BASE,
                                      EPWM_DC_MODULE_B,
                                      EPWM_DC_EVENT_1,
                                      EPWM_DC_EVENT_SOURCE_ORIG_SIGNAL);


    EPWM_setDigitalCompareEventSource(Bidirectional2_BASE,
                                      EPWM_DC_MODULE_B,
                                      EPWM_DC_EVENT_1,
                                      EPWM_DC_EVENT_SOURCE_ORIG_SIGNAL);


    EPWM_setDigitalCompareEventSource(DCAC1_BASE,
                                      EPWM_DC_MODULE_B,
                                      EPWM_DC_EVENT_1,
                                      EPWM_DC_EVENT_SOURCE_ORIG_SIGNAL);


    EPWM_setDigitalCompareEventSource(DCAC2_BASE,
                                      EPWM_DC_MODULE_B,
                                      EPWM_DC_EVENT_1,
                                      EPWM_DC_EVENT_SOURCE_ORIG_SIGNAL);

    EPWM_clearTripZoneFlag(BOOST_BASE, EPWM_TZ_INTERRUPT |EPWM_TZ_FLAG_DCBEVT1);

    EPWM_clearTripZoneFlag(Bidirectional1_BASE, EPWM_TZ_INTERRUPT |EPWM_TZ_FLAG_DCBEVT1);
    EPWM_clearTripZoneFlag(Bidirectional2_BASE, EPWM_TZ_INTERRUPT |EPWM_TZ_FLAG_DCBEVT1);

    EPWM_clearTripZoneFlag(DCAC1_BASE, EPWM_TZ_INTERRUPT |EPWM_TZ_FLAG_DCBEVT1);
    EPWM_clearTripZoneFlag(DCAC2_BASE, EPWM_TZ_INTERRUPT |EPWM_TZ_FLAG_DCBEVT1);


    EPWM_forceTripZoneEvent(BOOST_BASE, EPWM_TZ_FORCE_EVENT_OST);
    EPWM_forceTripZoneEvent(DCAC1_BASE, EPWM_TZ_FORCE_EVENT_OST);
    EPWM_forceTripZoneEvent(DCAC2_BASE, EPWM_TZ_FORCE_EVENT_OST);
    EPWM_forceTripZoneEvent(Bidirectional1_BASE, EPWM_TZ_FORCE_EVENT_OST);
    EPWM_forceTripZoneEvent(Bidirectional2_BASE, EPWM_TZ_FORCE_EVENT_OST);


    //Overcurrent protections
    //Sets the internal DAC high and low values of the comparator

    //IAC
    CMPSS_setDACValueHigh(myCMPSS_DCAC_BASE,stringINV_ACDC_iAC_TRIP_AMPS_POS);
    CMPSS_setDACValueLow(myCMPSS_DCAC_BASE,stringINV_ACDC_iAC_TRIP_AMPS_NEG);

    //Bidirectional
    CMPSS_setDACValueHigh(myCMPSS_Bidir1_BASE,stringINV_ACDC_CS_Batt_TRIP_AMPS_POS);
    CMPSS_setDACValueLow(myCMPSS_Bidir1_BASE,stringINV_ACDC_CS_Batt_TRIP_AMPS_NEG);

    CMPSS_setDACValueHigh(myCMPSS_Bidir2_BASE,stringINV_ACDC_CS_Batt_TRIP_AMPS_POS);
    CMPSS_setDACValueLow(myCMPSS_Bidir2_BASE,stringINV_ACDC_CS_Batt_TRIP_AMPS_NEG);

    //Boost
    CMPSS_setDACValueHigh(myCMPSS_Boost_BASE,stringINV_ACDC_CS_Boost_TRIP_AMPS_HIGH);
    CMPSS_setDACValueLow(myCMPSS_Boost_BASE,stringINV_ACDC_CS_Boost_TRIP_AMPS_LOW);

       }





////////////////Notch filter and PR controllers//////////

void computeDF22_PRcontrollerCoeff(DCL_DF22 *v, float32_t kp, float32_t ki,
                                   float32_t wo, float32_t fs, float32_t wrc)
{
    float32_t temp1, temp2, wo_adjusted;
    wo_adjusted = 2.0f*fs*tanf(wo/(2.0f*fs));

    temp1 = 4.0f*fs*fs+wo_adjusted*wo_adjusted+4.0f*fs*wrc;
    temp2 = 4.0f*ki*wrc*fs/temp1;
    v->b0 = temp2;
    v->b1 = 0;
    v->b2=-temp2;
    v->a1=((-8.0f*fs*fs+2*wo_adjusted*wo_adjusted)/temp1);
    v->a2=((temp1-8.0f*fs*wrc)/temp1);
    v->x1 = 0;
    v->x2 = 0;

    if(kp!=0)
    {
        v->b0+=kp;
        v->b1+=kp*v->a1;
        v->b2+=kp*v->a2;
    }

    v->a1=(v->a1);
    v->a2=(v->a2);
}

//TODO computeDF_22NotchFltrCoeff
void computeDF22_NotchFltrCoeff(DCL_DF22 *v, float32_t Fs, float32_t notch_freq,
                                float32_t c1, float32_t c2)
{
    float32_t temp1;
    float32_t temp2;
    float32_t wn2;
    float32_t Ts;
    Ts = 1.0f/Fs;

    // pre warp the notch frequency
    wn2 = 2.0f*Fs*tanf(notch_freq*CONST_PI_32*Ts);

    temp1= 4.0f*Fs*Fs + 4.0f* wn2 * c2 * Fs + wn2*wn2;
    temp2= 1.0f/ (4.0f*Fs*Fs + 4.0f* wn2 * c1 * Fs + wn2*wn2);

    v->b0 = temp1* temp2;
    v->b1 = (-8.0f*Fs*Fs + 2.0f* wn2* wn2)* temp2;
    v->b2 = (4.0f*Fs*Fs-4*wn2*c2*Fs+wn2*wn2)*temp2;
    v->a1 = (-8.0f*Fs*Fs + 2.0f* wn2* wn2)*temp2;
    v->a2 = (4.0f*Fs*Fs-4.0f*wn2*c1*Fs+wn2*wn2)*temp2;

}

////////////////Notch filter and PR controllers//////////

void stringINV_globalVariablesInit(void)
{

    //Individual Fault Flags
    stringINV_stop=0;
    stringINV_ADC_fault=0;
    stringINV_FAULT_FLAGS.stringINV_ADC_fault_OC_Boost=0;
    stringINV_FAULT_FLAGS.stringINV_ADC_fault_OC_Bidirectional1=0;
    stringINV_FAULT_FLAGS.stringINV_ADC_fault_OC_Bidirectional2=0;
    stringINV_FAULT_FLAGS.stringINV_ADC_fault_OC_DCAC1=0;
    stringINV_FAULT_FLAGS.stringINV_ADC_fault_OC_DCAC2=0;
    stringINV_FAULT_FLAGS.stringINV_ADC_fault_Overvoltage=0;
    stringINV_FAULT_FLAGS.stringINV_ADC_fault_Undervoltage=0;
    stringINV_FAULT_FLAGS.stringINV_ADC_fault_ACOvervoltage=0;
    stringINV_FAULT_FLAGS.stringINV_ADC_fault_ACUndervoltage=0;
    stringINV_FAULT_FLAGS.stringINV_DC_OverTemp=0;
    stringINV_FAULT_FLAGS.stringINV_AC_OverTemp=0;
    stringINV_fault_read_start=0;
    stringINV_fault_read_completed=1;


    stringINV_clearPWMTripBoost=0;
    stringINV_updateDutyBoost=0;
    stringINV_clearPWMTripDCDC=0;
    stringINV_updateDutyDCDC=0;
    stringINV_clearPWMTripDCAC=0;
    stringINV_updateDutyDCAC=0;
    stringINV_enableUVFaults=0;
    stringINV_enableDCRelay=0;
    stringINV_enableACRelay=0;

    //Boost Converter Variables
    stringINV_DCDC_mppt_counter = 0;

    init_boost_mppt(&stringINV_DCDC_b1_mppt_incc);
    init_boost_mppt(&stringINV_DCDC_b2_mppt_incc);
    stringINV_DCDC_b1_voltage_ref=500;
    stringINV_DCDC_b2_voltage_ref=500;

    stringINV_Boost1_Duty_Ref=0;
    stringINV_Boost1_Duty_Ref_Slewed=0;
    stringINV_Boost2_Duty_Ref_Slewed=0;

    stringINV_DCDC_BOOST1PWM_Ref_Slewed=0;
    stringINV_DCDC_BOOST2PWM_Ref_Slewed=0;

    gv_VBoost_pi_1.Kp = gv_VBoost_pi_KP;
    gv_VBoost_pi_1.Ki = gv_VBoost_pi_KI;
    gv_VBoost_pi_1.Umax = gv_VBoost_pi_MAX;
    gv_VBoost_pi_1.Umin = gv_VBoost_pi_MIN;

    gv_VBoost_pi_2.Kp = gv_VBoost_pi_KP;
    gv_VBoost_pi_2.Ki = gv_VBoost_pi_KI;
    gv_VBoost_pi_2.Umax = gv_VBoost_pi_MAX;
    gv_VBoost_pi_2.Umin = gv_VBoost_pi_MIN;

    //PI Current Control Battery
    stringINV_DCDC_CS_Batt_Ref=stringINV_DCDC_CS_Batt_Ref_init;
    stringINV_DCDC_CS_Batt_Ref_Slewed=0;
    stringINV_DCDC_CS_Batt1_loop_err=0;
    stringINV_DCDC_CS_Batt2_loop_err=0;
    stringINV_DCDC_IDC_Ref_Slewed=0;

    gi_Batt_pi_1.Kp = gi_DCDC_pi_KP;
    gi_Batt_pi_1.Ki = gi_DCDC_pi_KI;
    gi_Batt_pi_1.Umax = gi_DCDC_pi_MAX;
    gi_Batt_pi_1.Umin = gi_DCDC_pi_MIN;

    gi_Batt_pi_2.Kp = gi_DCDC_pi_KP;
    gi_Batt_pi_2.Ki = gi_DCDC_pi_KI;
    gi_Batt_pi_2.Umax = gi_DCDC_pi_MAX;
    gi_Batt_pi_2.Umin = gi_DCDC_pi_MIN;


    //String Inverter DC/AC Portion Open Loop Variables
    stringINV_ACDC_Index_Modulation=0;
    stringINV_ACDC_Amplitude=0.83636f;

    //It generates a triangular signal for cosphi and sinphi String Inverter

    RAMPGEN_config(&stringINV_ACDC_rgen,
                      ISR_CONTROL_FREQUENCY_AC,
                      AC_FREQ);

    RAMPGEN_reset(&stringINV_ACDC_rgen);

    //String Inverter DC/AC Portion Close Loop Variables
    stringINV_ACDC_iAC_real_Ref=0.5;
    stringINV_ACDC_iAC_imag_Ref=0;
    stringINV_ACDC_iAC_imag_Ref_slewed=0;
    stringINV_ACDC_iAC_Ref=0;
    stringINV_ACDC_iAC_amp_Ref=0;
    stringINV_ACDC_iAC_Ref_slewed=0; //Ramped value current
    stringINV_ACDC_iAC_real_Ref_slewed=0; //Ramped value real current
    stringINV_IDCAC_Ref_Slewed=0;


    //Initialization of the variables of the PLL String Inverter

    stringINV_reset_PLL=0;

    SPLL_1PH_SOGI_reset(&stringINV_spll_1ph);

    SPLL_1PH_SOGI_config(&stringINV_spll_1ph,
                             AC_FREQ,
                             ISR_CONTROL_FREQUENCY_AC,
                                 stringINV_SPLL_COEFF_B0,
                                 stringINV_SPLL_COEFF_B1);

    SPLL_1PH_SOGI_coeff_calc(&stringINV_spll_1ph);


    //PI control VDC
    stringINV_DCDC_VDCext_Ref=400.0f;
    stringINV_DCDC_VDC_loop_err=0;
    stringINV_DCDC_VDCext_Ref_Slewed=0;

    stringINV_ACDC_iAC_loop_err=0;

    stringINV_ACDC_iAC_loop_out_PI=0;
    stringINV_ACDC_iAC_loop_out_PR1=0;
    stringINV_ACDC_iAC_loop_out_PR3=0;
    stringINV_ACDC_iAC_loop_out_PR5=0;
    stringINV_ACDC_iAC_loop_out_PR7=0;
    stringINV_ACDC_iAC_loop_out_PR9=0;
    stringINV_ACDC_iAC_loop_out_PR11=0;
    stringINV_ACDC_iAC_loop_out_PR13=0;
    stringINV_ACDC_iAC_loop_out_PR15=0;
    stringINV_ACDC_iAC_loop_out_PR17=0;
    stringINV_ACDC_iAC_loop_out_SUM=0;

    stringINV_DCAC_Counter_Disable_FFW=0;

// Calculation of the Proportional Resonant coefficient
    kpI_1H = KPI_1H;
    kiI_1H = KII_1H;
    wrcI_1H= WRCI_1H;
    woI_1H = 2.0f*CONST_PI_32*AC_FREQ;
    computeDF22_PRcontrollerCoeff(&gi_r1, kpI_1H,kiI_1H,woI_1H,
                                   ISR_CONTROL_FREQUENCY_AC,wrcI_1H);

    kiI_3H = KII_3H;
    wrcI_3H = WRCI_3H;
    woI_3H = 2.0f*CONST_PI_32*AC_FREQ*3;
    computeDF22_PRcontrollerCoeff(&gi_r3, 0,kiI_3H,woI_3H,
                                  ISR_CONTROL_FREQUENCY_AC,wrcI_3H);

    kiI_5H = KII_5H;
    wrcI_5H = WRCI_5H;
    woI_5H = 2.0f*CONST_PI_32*AC_FREQ*5;
    computeDF22_PRcontrollerCoeff(&gi_r5, 0,kiI_5H,woI_5H,
                                  ISR_CONTROL_FREQUENCY_AC,wrcI_5H);

    kiI_7H = KII_7H;
    wrcI_7H = WRCI_7H;
    woI_7H = 2.0f*CONST_PI_32*AC_FREQ*7;
    computeDF22_PRcontrollerCoeff(&gi_r7, 0,kiI_7H,woI_7H,
                                  ISR_CONTROL_FREQUENCY_AC,wrcI_7H);

    kiI_9H = KII_9H;
    wrcI_9H = WRCI_9H;
    woI_9H = 2.0f*CONST_PI_32*AC_FREQ*9;
    computeDF22_PRcontrollerCoeff(&gi_r9, 0,kiI_9H,woI_9H,
                                  ISR_CONTROL_FREQUENCY_AC,wrcI_9H);

    kiI_11H = KII_11H;
    wrcI_11H = WRCI_11H;
    woI_11H = 2.0f*CONST_PI_32*AC_FREQ*11;
    computeDF22_PRcontrollerCoeff(&gi_r11, 0,kiI_11H,woI_11H,
                                  ISR_CONTROL_FREQUENCY_AC,wrcI_11H);


    kiI_13H = KII_13H;
    wrcI_13H = WRCI_13H;
    woI_13H = 2.0f*CONST_PI_32*AC_FREQ*13;
    computeDF22_PRcontrollerCoeff(&gi_r13, 0,kiI_13H,woI_13H,
                                  ISR_CONTROL_FREQUENCY_AC,wrcI_13H);


    kiI_15H = KII_15H;
    wrcI_15H = WRCI_15H;
    woI_15H = 2.0f*CONST_PI_32*AC_FREQ*15;
    computeDF22_PRcontrollerCoeff(&gi_r15, 0,kiI_15H,woI_15H,
                                  ISR_CONTROL_FREQUENCY_AC,wrcI_15H);


    kiI_17H = KII_17H;
    wrcI_17H = WRCI_17H;
    woI_17H = 2.0f*CONST_PI_32*AC_FREQ*17;
    computeDF22_PRcontrollerCoeff(&gi_r17, 0,kiI_17H,woI_17H,
                                  ISR_CONTROL_FREQUENCY_AC,wrcI_17H);



//PI controllers parameters used by the DC/AC
    gi_ACDC_pi.Kp = gi_ACDC_pi_KP;
    gi_ACDC_pi.Ki = gi_ACDC_pi_KI;
    gi_ACDC_pi.Umax = gi_ACDC_pi_MAX;
    gi_ACDC_pi.Umin = gi_ACDC_pi_MIN;

    gv_ACDC_pi.Kp =  gv_ACDC_pi_KP;
    gv_ACDC_pi.Ki = gv_ACDC_pi_KI;
    gv_ACDC_pi.Umax = gv_ACDC_pi_MAX;
    gv_ACDC_pi.Umin = gv_ACDC_pi_MIN;

    computeDF22_NotchFltrCoeff(&VDC_NOTCH_FILTER_2_Fe, (ISR_CONTROL_FREQUENCY_AC), (AC_FREQ*2.0) , 0.25f, 0.00001f);

    //Data logger Init Function
        DLOG_4CH_reset(&stringINV_ACDC_dLog1);
        DLOG_4CH_config(&stringINV_ACDC_dLog1,
                        &stringINV_ACDC_dVal1, &stringINV_ACDC_dVal2, &stringINV_ACDC_dVal3, &stringINV_ACDC_dVal4,
                        stringINV_ACDC_dBuff1, stringINV_ACDC_dBuff2, stringINV_ACDC_dBuff3, stringINV_ACDC_dBuff4,
                        stringINV_ACDC_DLOG_SIZE, stringINV_ACDC_DLOG_TRIGGER, stringINV_ACDC_DLOG_SCALE);


        DLOG_4CH_reset(&stringINV_ACDC_dLog2);
        DLOG_4CH_config(&stringINV_ACDC_dLog2,
                        &stringINV_ACDC_dVal5, &stringINV_ACDC_dVal6, &stringINV_ACDC_dVal7, &stringINV_ACDC_dVal8,
                        stringINV_ACDC_dBuff5, stringINV_ACDC_dBuff6, stringINV_ACDC_dBuff7, stringINV_ACDC_dBuff8,
                        stringINV_ACDC_DLOG_SIZE_OSC2, stringINV_ACDC_DLOG_TRIGGER, stringINV_ACDC_DLOG_SCALE_OSC2);

        //Temperature counter
        stringINV_GaN_Temp_Counter=0;


        POWER_MEAS_SINE_ANALYZER_reset(&stringINV_mains_L1);
        POWER_MEAS_SINE_ANALYZER_config(&stringINV_mains_L1,
                                        ISR_CONTROL_FREQUENCY_AC,
                                        (float32_t)10.0f,
                                        (float32_t)55.0f,
                                        (float32_t)45.0f);

        //Initialization of the variables.
}

void stringINV_test() {

    //Temperature measurement String Inverter
    stringINV_GaN_temp();

    //Reset PLL
    if(stringINV_reset_PLL == 1)
    {
        stringINV_reset_PLL = 0;
        SPLL_1PH_SOGI_reset(&stringINV_spll_1ph);
    }

    //Enable DC-DC relay
    if(stringINV_enableDCRelay == 1U)
    {
        stringINV_enableDCRelay=0;
        GPIO_writePin(RY_DCPreCharge, 1);
    }

    //Enable AC-DC relay
    if(stringINV_enableACRelay == 1U)
    {
        stringINV_enableACRelay=0;
        GPIO_writePin(RY_ACPreCharge, 1);
    }

 //MPPT
#if(MPPTEnable == 1)
    {
        if(stringINV_updateDutyBoost == 1U)
        {
        stringINV_MPPT();
        }
    }
#endif

}

//TODO: Define ADC interrupt routine and do control there
