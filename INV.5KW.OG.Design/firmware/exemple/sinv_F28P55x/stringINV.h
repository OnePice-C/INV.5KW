//##############################################################################
//
// FILE:  stringINV.h
//
// TITLE: Solution header file for the string inverter
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

#ifndef STRINGINV_H_
#define STRINGINV_H_

#include "stdint.h"
#include "rampgen.h"
#include "dlog_4ch.h"
#include <stringINV_settings.h>
#include <stringINV_dcdc_mppt.h>

#include "spll_1ph_sogi.h"
#include "DCLF32.h"
#include "power_meas_sine_analyzer.h"

//Definition of the function in C
void stringINV_PeripheralInit();
void stringINV_test();
void stringINV_globalVariablesInit(void);


//TBPRD ACDC
//#define DCAC_PWM_PRD DCAC1_TBPRD //unipolar // defined in SysConfig
#define DCAC_PWM_PRD DCAC1_TBPRD //bipolar & HERIC // defined in SysConfig

//TBPRD BOOST
#define BOOST_PWM_PRD BOOST_TBPRD // defined in SysConfig

//TBPRD DCDC
#define BIDIRECTIONAL_PWM_PRD Bidirectional1_TBPRD // defined in SysConfig

typedef struct stringINV_FAULTS_t{
    int32_t stringINV_ADC_fault_OC_Boost;
    int32_t stringINV_ADC_fault_OC_Bidirectional1;
    int32_t stringINV_ADC_fault_OC_Bidirectional2;
    int32_t stringINV_ADC_fault_OC_DCAC1;
    int32_t stringINV_ADC_fault_OC_DCAC2;
    int32_t stringINV_ADC_fault_Overvoltage;
    int32_t stringINV_ADC_fault_Undervoltage;
    int32_t stringINV_ADC_fault_ACOvervoltage;
    int32_t stringINV_ADC_fault_ACUndervoltage;
    int32_t stringINV_DC_OverTemp;
    int32_t stringINV_AC_OverTemp;
}stringINV_FAULTS_t;

extern stringINV_FAULTS_t stringINV_FAULT_FLAGS;

//Ramp Generator parameters String Inverter
extern RAMPGEN stringINV_ACDC_rgen;
extern float32_t stringINV_ACDC_Index_Modulation;
extern float32_t stringINV_ACDC_Amplitude;

extern float32_t Boost_S1_Duty_Cycle;
extern float32_t Boost_S2_Duty_Cycle;
extern float32_t Batt1_Duty_Cycle;
extern float32_t Batt2_Duty_Cycle;

//ACDC Settings

//Date Logger
extern DLOG_4CH stringINV_ACDC_dLog1;
extern DLOG_4CH stringINV_ACDC_dLog2;
extern float32_t stringINV_ACDC_dBuff1[stringINV_ACDC_DLOG_SIZE];
extern float32_t stringINV_ACDC_dBuff2[stringINV_ACDC_DLOG_SIZE];
extern float32_t stringINV_ACDC_dBuff3[stringINV_ACDC_DLOG_SIZE];
extern float32_t stringINV_ACDC_dBuff4[stringINV_ACDC_DLOG_SIZE];
extern float32_t stringINV_ACDC_dBuff5[stringINV_ACDC_DLOG_SIZE];
extern float32_t stringINV_ACDC_dBuff6[stringINV_ACDC_DLOG_SIZE];
extern float32_t stringINV_ACDC_dBuff7[stringINV_ACDC_DLOG_SIZE];
extern float32_t stringINV_ACDC_dBuff8[stringINV_ACDC_DLOG_SIZE];
extern float32_t stringINV_ACDC_dVal1;
extern float32_t stringINV_ACDC_dVal2;
extern float32_t stringINV_ACDC_dVal3;
extern float32_t stringINV_ACDC_dVal4;
extern float32_t stringINV_ACDC_dVal5;
extern float32_t stringINV_ACDC_dVal6;
extern float32_t stringINV_ACDC_dVal7;
extern float32_t stringINV_ACDC_dVal8;

//Temperature Measurements DC/DC
extern float32_t TEMP_Boost1_Buff_Duty;
extern float32_t TEMP_Boost2_Buff_Duty;
extern float32_t TEMP_Batt_H1_Buff_Duty;
extern float32_t TEMP_Batt_L1_Buff_Duty;
extern float32_t TEMP_Batt_H2_Buff_Duty;
extern float32_t TEMP_Batt_L2_Buff_Duty;
extern float32_t TEMP_Boost1_Buff;
extern float32_t TEMP_Boost2_Buff;
extern float32_t TEMP_Batt_H1_Buff;
extern float32_t TEMP_Batt_L1_Buff;
extern float32_t TEMP_Batt_H2_Buff;
extern float32_t TEMP_Batt_L2_Buff;
extern uint32_t stringINV_GaN_Temp_Counter;

//Temperature Measurements DC/DC LPF
extern  float32_t TEMP_Boost1_FILTER;
extern  float32_t TEMP_Boost2_FILTER;
extern  float32_t TEMP_Batt_H1_FILTER;
extern  float32_t TEMP_Batt_L1_FILTER;
extern  float32_t TEMP_Batt_H2_FILTER;
extern  float32_t TEMP_Batt_L2_FILTER;

//Temperature Measurements AC/DC
extern float32_t TEMP_S1_Duty;
extern float32_t TEMP_S2_Duty;
extern float32_t TEMP_S3_Duty;
extern float32_t TEMP_S4_Duty;
extern float32_t TEMP_S5_Duty;
extern float32_t TEMP_S6_Duty;
extern float32_t TEMP_S1;
extern float32_t TEMP_S2;
extern float32_t TEMP_S3;
extern float32_t TEMP_S4;
extern float32_t TEMP_S5;
extern float32_t TEMP_S6;

//Temperature Measurements AC/DC LPF
extern float32_t TEMP_S1_FILTER;
extern float32_t TEMP_S2_FILTER;
extern float32_t TEMP_S3_FILTER;
extern float32_t TEMP_S4_FILTER;
extern float32_t TEMP_S5_FILTER;
extern float32_t TEMP_S6_FILTER;

extern SPLL_1PH_SOGI stringINV_spll_1ph;
extern int32_t stringINV_reset_PLL;

//Analog Measurements

//String Inverter analog measurements AC/DC PU
extern float32_t stringINV_ACDC_iAC_sensed_pu;
extern float32_t stringINV_ACDC_iAC_REF_sensed_pu;
extern float32_t stringINV_ACDC_vAC_sensed_pu;
extern float32_t stringINV_ACDC_vINV_sensed_pu;
extern float32_t stringINV_ACDC_vDC_sensed_pu;
extern float32_t stringINV_ACDC_iDC_sensed_pu;

//String Inverter analog measurements AC/DC
extern float32_t stringINV_ACDC_iAC_sensed;
extern float32_t stringINV_ACDC_vAC_sensed;
extern float32_t stringINV_ACDC_vINV_sensed;
extern float32_t stringINV_ACDC_vDC_sensed;
extern float32_t stringINV_ACDC_iDC_sensed;

//String Inverter analog measurements DC/DC Boost PU
extern float32_t stringINV_DCDC_CS_Boost1_sensed_pu;
extern float32_t stringINV_DCDC_VS_Boost1_sensed_pu;
extern float32_t stringINV_DCDC_CS_Boost2_sensed_pu;
extern float32_t stringINV_DCDC_VS_Boost2_sensed_pu;

//String Inverter analog measurements DC/DC Boost
extern float32_t stringINV_DCDC_CS_Boost1_sensed;
extern float32_t stringINV_DCDC_VS_Boost1_sensed;
extern float32_t stringINV_DCDC_CS_Boost2_sensed;
extern float32_t stringINV_DCDC_VS_Boost2_sensed;

//Measurements DC/DC DC bus voltage meas
extern float32_t stringINV_DCDC_vDC_sensed_pu;
extern float32_t stringINV_DCDC_vDC_sensed;

//DC Bus voltage filter
extern float32_t stringINV_DCDC_vDC_sensed_FILTER;

//MPPT
extern float32_t stringINV_DCDC_CS_Boost1_sensed_FILTER;
extern float32_t stringINV_DCDC_VS_Boost1_sensed_FILTER;
extern float32_t stringINV_DCDC_CS_Boost2_sensed_FILTER;
extern float32_t stringINV_DCDC_VS_Boost2_sensed_FILTER;
extern float32_t stringINV_DCDC_b1_voltage_ref;
extern float32_t stringINV_DCDC_b2_voltage_ref;

//String Inverter analog measurements DC/DC Bidirectional PU
extern float32_t stringINV_DCDC_CS_Batt1_sensed_pu;
extern float32_t stringINV_DCDC_VS_Batt_sensed_pu;
extern float32_t stringINV_DCDC_CS_Batt2_sensed_pu;

//String Inverter analog measurements DC/DC Bidirectional
extern float32_t stringINV_DCDC_CS_Batt1_sensed;
extern float32_t stringINV_DCDC_VS_Batt_sensed;
extern float32_t stringINV_DCDC_CS_Batt2_sensed;

// Internal conditioning of the measurements String Inverter
extern float32_t stringINV_DCDC_VS_Batt_sensed_FILTER;
extern float32_t stringINV_ACDC_vDC_sensed_FILTER;
extern float32_t stringINV_ACDC_vAC_sensed_FILTER;
extern float32_t stringINV_ACDC_vDC_sensed_NOTCH;
extern float32_t stringINV_ACDC_vAC_RMS_FILTER;

//Control variables bidirectional
extern float32_t stringINV_DCDC_CS_Batt_Ref;
extern float32_t stringINV_DCDC_CS_Batt_Ref_Slewed;
extern float32_t stringINV_DCDC_CS_Batt1_loop_err;
extern float32_t stringINV_DCDC_CS_Batt2_loop_err;

//Control variables boost VDC
extern float32_t stringINV_DCDC_VDCext_Ref;
extern float32_t stringINV_DCDC_VDC_loop_err;
extern float32_t stringINV_DCDC_VDCext_Ref_Slewed;

//PI Control Boost converters
extern float32_t stringINV_DCDC_VBoost1_loop_err;
extern float32_t stringINV_DCDC_VBoost2_loop_err;

//String Inverter MPPT
extern stringINV_dcdc_mppt_t stringINV_DCDC_b1_mppt_incc;
extern stringINV_dcdc_mppt_t stringINV_DCDC_b2_mppt_incc;
extern uint32_t stringINV_DCDC_mppt_counter;

//Control Variables Reference values String Inverter
extern float32_t stringINV_ACDC_iAC_real_Ref; // you control the amplitude of the real part
extern float32_t stringINV_ACDC_iAC_imag_Ref; // you control the amplitude of the imag part
extern float32_t stringINV_ACDC_iAC_Ref; // final results of real and imag together.
extern float32_t stringINV_ACDC_iAC_Ref_slewed;
extern float32_t stringINV_ACDC_iAC_real_Ref; // final results of real and imag together.
extern float32_t stringINV_ACDC_iAC_real_Ref_slewed; // you control the amplitude of the real part
extern float32_t stringINV_ACDC_iAC_imag_Ref_slewed; // you control the amplitude of the imag part
extern float32_t stringINV_ACDC_iAC_amp_Ref; // you will use this one to monitor the peak current.

extern float32_t stringINV_DCDC_vDC_Ref;
extern float32_t stringINV_DCDC_vDC_Ref_Slewed;

extern float32_t stringINV_DCDC_BOOST1PWM_Ref;
extern float32_t stringINV_DCDC_BOOST1PWM_Ref_Slewed;

extern float32_t stringINV_DCDC_BOOST2PWM_Ref;
extern float32_t stringINV_DCDC_BOOST2PWM_Ref_Slewed;

extern float32_t stringINV_DCDC_IDC_Ref;
extern float32_t stringINV_DCDC_IDC_Ref_Slewed;

extern float32_t stringINV_Boost1_Duty_Ref;
extern float32_t stringINV_Boost1_Duty_Ref_Slewed;

extern float32_t stringINV_Boost2_Duty_Ref;
extern float32_t stringINV_Boost2_Duty_Ref_Slewed;

extern float32_t stringINV_IDCAC_Ref;
extern float32_t stringINV_IDCAC_Ref_Slewed;

//Control Variables Error String Inverter
extern float32_t stringINV_ACDC_iAC_loop_err; // you control the amplitude of the real part
extern float32_t stringINV_ACDC_vDC_loop_err;
extern float32_t stringINV_ACDC_iAC_real_Ref_OUT_PI;


extern float32_t stringINV_ACDC_iAC_loop_out_PI;
extern float32_t stringINV_ACDC_iAC_loop_out_PR1;
extern float32_t stringINV_ACDC_iAC_loop_out_PR3;
extern float32_t stringINV_ACDC_iAC_loop_out_PR5;
extern float32_t stringINV_ACDC_iAC_loop_out_PR7;
extern float32_t stringINV_ACDC_iAC_loop_out_PR9;
extern float32_t stringINV_ACDC_iAC_loop_out_PR11;
extern float32_t stringINV_ACDC_iAC_loop_out_PR13;
extern float32_t stringINV_ACDC_iAC_loop_out_PR15;
extern float32_t stringINV_ACDC_iAC_loop_out_PR17;
extern float32_t stringINV_ACDC_iAC_loop_out_SUM;

extern DCL_DF22 gi_r1;
extern DCL_DF22 gi_r3;
extern DCL_DF22 gi_r5;
extern DCL_DF22 gi_r7;
extern DCL_DF22 gi_r9;
extern DCL_DF22 gi_r11;
extern DCL_DF22 gi_r13;
extern DCL_DF22 gi_r15;
extern DCL_DF22 gi_r17;

extern DCL_DF22 VDC_NOTCH_FILTER_2_Fe;

extern float32_t kpI_1H;
extern float32_t kiI_1H, kiI_3H, kiI_5H, kiI_7H, kiI_9H, kiI_11H, kiI_13H, kiI_15H, kiI_17H;
extern float32_t woI_1H, woI_3H, woI_5H, woI_7H, woI_9H, woI_11H, woI_13H, woI_15H, woI_17H;
extern float32_t wrcI_1H, wrcI_3H, wrcI_5H, wrcI_7H, wrcI_9H, wrcI_11H, wrcI_13H, wrcI_15H, wrcI_17H;

extern DCL_PI gi_ACDC_pi;

extern DCL_PI gv_ACDC_pi;

extern DCL_PI gi_Batt_pi_1;
extern DCL_PI gi_Batt_pi_2;

extern DCL_PI gv_VBoost_pi_1;

extern DCL_PI gv_VBoost_pi_2;

//State Machines
extern int32_t stringINV_ADC_fault;
extern int32_t stringINV_stop;

extern uint16_t stringINV_enableDCRelay;
extern uint16_t stringINV_enableACRelay;

extern POWER_MEAS_SINE_ANALYZER stringINV_mains_L1;

extern uint16_t stringINV_clearPWMTrip;
extern uint16_t stringINV_updateDuty;
extern uint16_t stringINV_clearPWMTripBoost;
extern uint16_t stringINV_updateDutyBoost;
extern uint16_t stringINV_clearPWMTripDCDC;
extern uint16_t stringINV_updateDutyDCDC;
extern uint16_t stringINV_clearPWMTripDCAC;
extern uint16_t stringINV_updateDutyDCAC;
extern uint16_t stringINV_enableUVFaults;

//FFW for ACDC Voltage control loop
extern int32_t stringINV_DCAC_Counter_Disable_FFW;

//Counter faults
extern int32_t stringINV_Counter_Faults;

//ADC Measurements Faults
extern int32_t stringINV_fault_read_start;
extern int32_t stringINV_fault_read_completed;
extern float32_t stringINV_DCDC_CS_Batt1_fault;
extern float32_t stringINV_DCDC_CS_Batt2_fault;
extern float32_t stringINV_DCDC_VS_Batt_fault;
extern float32_t stringINV_DCDC_CS_Boost1_fault;
extern float32_t stringINV_DCDC_VS_Boost1_fault;
extern float32_t stringINV_DCDC_CS_Boost2_fault;
extern float32_t stringINV_DCDC_VS_Boost2_fault;
extern float32_t stringINV_ACDC_iAC_fault;
extern float32_t stringINV_ACDC_vAC_fault;
extern float32_t stringINV_ACDC_vAC_RMS_fault;
extern float32_t stringINV_ACDC_vDC_fault;
extern float32_t stringINV_ACDC_iDC_fault;
extern float32_t stringINV_Boost1_Duty_Ref_fault;
extern float32_t stringINV_Boost2_Duty_Ref_fault;
extern float32_t stringINV_Boost1_Duty_Ref_Slewed_fault;
extern float32_t stringINV_Boost2_Duty_Ref_Slewed_fault;
extern float32_t Batt1_Duty_Cycle_fault;
extern float32_t Batt2_Duty_Cycle_fault;
extern float32_t stringINV_ACDC_Index_Modulation_fault;

extern float32_t TEMP_Boost1_FILTER_fault;
extern float32_t TEMP_Boost2_FILTER_fault;
extern float32_t TEMP_Batt_H1_FILTER_fault;
extern float32_t TEMP_Batt_L1_FILTER_fault;
extern float32_t TEMP_Batt_H2_FILTER_fault;
extern float32_t TEMP_Batt_L2_FILTER_fault;
extern float32_t TEMP_S1_FILTER_fault;
extern float32_t TEMP_S2_FILTER_fault;
extern float32_t TEMP_S3_FILTER_fault;
extern float32_t TEMP_S4_FILTER_fault;
extern float32_t TEMP_S5_FILTER_fault;
extern float32_t TEMP_S6_FILTER_fault;

extern uint16_t stringINV_Counter;

//Definition of the function in C
void computeDF22_NotchFltrCoeff(DCL_DF22 *v, float32_t sampling_freq,
                                float32_t notch_freq, float32_t c1, float32_t c2);
void computeDF22_PRcontrollerCoeff(DCL_DF22 *v, float32_t kp, float32_t ki, float32_t wo,
                                   float32_t fs, float32_t wrc);
//Definition of the function in C

//Temperature measurement of the String Inverter
#pragma FUNC_ALWAYS_INLINE(stringINV_GaN_temp)
static inline void stringINV_GaN_temp() {

    //Code for temperature measurements DC/DC and then AC/DC in each loop
    stringINV_GaN_Temp_Counter= stringINV_GaN_Temp_Counter+1;
    DEVICE_DELAY_US(250);

    //Sectioning out the logic statements into 6 intervals
    if(stringINV_GaN_Temp_Counter<=(stringINV_GaN_Temp_Scaling/6))
    {
        //Code for acquiring the temperatures
        //we calculate duty cycle, then ECAP counter is reset, write on the MUX, then rearm ECAP
        TEMP_Boost1_Buff_Duty= ((float)ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_3) - (float)ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_2)) / (ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_3) - ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_1));
        TEMP_Boost1_Buff=stringINV_GaN_Temp_Coefficient*TEMP_Boost1_Buff_Duty+stringINV_GaN_Temp_Offset;
        // ECAP_selectECAPInput(myECAP0_BASE,ECAP_INPUT_INPUTXBAR1);
        ECAP_resetCounters(myECAP0_BASE);

        if((TEMP_Boost1_Buff-TEMP_Boost1_FILTER)>30.0) {TEMP_Boost1_Buff=TEMP_Boost1_FILTER;} // To remove unknown spikes, if any exist

        TEMP_Boost1_FILTER=stringINV_TEMP_FILTERING_CONSTANT*(-TEMP_Boost1_FILTER+TEMP_Boost1_Buff)+TEMP_Boost1_FILTER;

        ECAP_reArm(myECAP0_BASE);

        TEMP_S1_Duty= ((float)ECAP_getEventTimeStamp(myECAP1_BASE, ECAP_EVENT_3) - (float)ECAP_getEventTimeStamp(myECAP1_BASE, ECAP_EVENT_2)) / (ECAP_getEventTimeStamp(myECAP1_BASE, ECAP_EVENT_3) - ECAP_getEventTimeStamp(myECAP1_BASE, ECAP_EVENT_1));
        TEMP_S1=stringINV_GaN_Temp_Coefficient*TEMP_S1_Duty+stringINV_GaN_Temp_Offset;
        ECAP_resetCounters(myECAP1_BASE);


        if((TEMP_S1-TEMP_S1_FILTER)>30.0) {TEMP_S1=TEMP_S1_FILTER;} // To remove unknown spikes, if any exist

        TEMP_S1_FILTER=stringINV_TEMP_FILTERING_CONSTANT*(-TEMP_S1_FILTER+TEMP_S1)+TEMP_S1_FILTER;

        ECAP_reArm(myECAP1_BASE);

        GPIO_writePin(TEMP_MUX_A, 0);
        GPIO_writePin(TEMP_MUX_B, 0);
        GPIO_writePin(TEMP_MUX_C, 0);


        GPIO_writePin(LED_HEARTBEAT,1);
    }

    else if((stringINV_GaN_Temp_Counter>(stringINV_GaN_Temp_Scaling/6)) && (stringINV_GaN_Temp_Counter<=(stringINV_GaN_Temp_Scaling/3)))
    {
        //Code for acquiring the temperatures
        TEMP_Boost2_Buff_Duty= ((float)ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_3) - (float)ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_2)) / (ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_3) - ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_1));
        TEMP_Boost2_Buff=stringINV_GaN_Temp_Coefficient*TEMP_Boost2_Buff_Duty+stringINV_GaN_Temp_Offset;
        //ECAP_selectECAPInput(myECAP0_BASE,ECAP_INPUT_INPUTXBAR1);
        ECAP_resetCounters(myECAP0_BASE);

        GPIO_writePin(TEMP_MUX_A, 1);
        GPIO_writePin(TEMP_MUX_B, 0);
        GPIO_writePin(TEMP_MUX_C, 0);

        if((TEMP_Boost2_Buff-TEMP_Boost2_FILTER)>30.0) {TEMP_Boost2_Buff=TEMP_Boost2_FILTER;} // To remove unknown spikes, if any exist

        TEMP_Boost2_FILTER=stringINV_TEMP_FILTERING_CONSTANT*(-TEMP_Boost2_FILTER+TEMP_Boost2_Buff)+TEMP_Boost2_FILTER;

        ECAP_reArm(myECAP0_BASE);
        TEMP_S2_Duty= ((float)ECAP_getEventTimeStamp(myECAP1_BASE, ECAP_EVENT_3) - (float)ECAP_getEventTimeStamp(myECAP1_BASE, ECAP_EVENT_2)) / (ECAP_getEventTimeStamp(myECAP1_BASE, ECAP_EVENT_3) - ECAP_getEventTimeStamp(myECAP1_BASE, ECAP_EVENT_1));
        TEMP_S2=stringINV_GaN_Temp_Coefficient*TEMP_S2_Duty+stringINV_GaN_Temp_Offset;
        ECAP_resetCounters(myECAP1_BASE);

        if((TEMP_S2-TEMP_S2_FILTER)>30.0) {TEMP_S2=TEMP_S2_FILTER;} // To remove unknown spikes, if any exist

        TEMP_S2_FILTER=stringINV_TEMP_FILTERING_CONSTANT*(-TEMP_S2_FILTER+TEMP_S2)+TEMP_S2_FILTER;
        ECAP_reArm(myECAP1_BASE);
        GPIO_writePin(LED_HEARTBEAT,0);
    }

    else if((stringINV_GaN_Temp_Counter>(stringINV_GaN_Temp_Scaling/3)) && stringINV_GaN_Temp_Counter<=(stringINV_GaN_Temp_Scaling/2))
    {
        //Code for acquiring the temperatures
        TEMP_Batt_H1_Buff_Duty= ((float)ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_3) - (float)ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_2)) / (ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_3) - ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_1));
        TEMP_Batt_H1_Buff=stringINV_GaN_Temp_Coefficient*TEMP_Batt_H1_Buff_Duty+stringINV_GaN_Temp_Offset;
        //ECAP_selectECAPInput(myECAP0_BASE,ECAP_INPUT_INPUTXBAR1);
        ECAP_resetCounters(myECAP0_BASE);

        GPIO_writePin(TEMP_MUX_A, 0);
        GPIO_writePin(TEMP_MUX_B, 1);
        GPIO_writePin(TEMP_MUX_C, 0);

        if((TEMP_Batt_H1_Buff-TEMP_Batt_H1_FILTER)>30.0) {TEMP_Batt_H1_Buff=TEMP_Batt_H1_FILTER;} // To remove unknown spikes, if any exist

        TEMP_Batt_H1_FILTER=stringINV_TEMP_FILTERING_CONSTANT*(-TEMP_Batt_H1_FILTER+TEMP_Batt_H1_Buff)+TEMP_Batt_H1_FILTER;

        ECAP_reArm(myECAP0_BASE);
        TEMP_S3_Duty= ((float)ECAP_getEventTimeStamp(myECAP1_BASE, ECAP_EVENT_3) - (float)ECAP_getEventTimeStamp(myECAP1_BASE, ECAP_EVENT_2)) / (ECAP_getEventTimeStamp(myECAP1_BASE, ECAP_EVENT_3) - ECAP_getEventTimeStamp(myECAP1_BASE, ECAP_EVENT_1));
        TEMP_S3=stringINV_GaN_Temp_Coefficient*TEMP_S3_Duty+stringINV_GaN_Temp_Offset;
        //ECAP_selectECAPInput(myECAP0_BASE,ECAP_INPUT_INPUTXBAR1);
        ECAP_resetCounters(myECAP1_BASE);

        if((TEMP_S3-TEMP_S3_FILTER)>30.0) {TEMP_S3=TEMP_S3_FILTER;} // To remove unknown spikes, if any exist

        TEMP_S3_FILTER=stringINV_TEMP_FILTERING_CONSTANT*(-TEMP_S3_FILTER+TEMP_S3)+TEMP_S3_FILTER;
        ECAP_reArm(myECAP1_BASE);
        GPIO_writePin(LED_HEARTBEAT,1);
    }

    else if((stringINV_GaN_Temp_Counter>(stringINV_GaN_Temp_Scaling/2)) && stringINV_GaN_Temp_Counter<=(stringINV_GaN_Temp_Scaling*2/3))
    {
        //Code for acquiring the temperatures
        TEMP_Batt_L1_Buff_Duty= ((float)ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_3) - (float)ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_2)) / (ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_3) - ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_1));
        TEMP_Batt_L1_Buff=stringINV_GaN_Temp_Coefficient*TEMP_Batt_L1_Buff_Duty+stringINV_GaN_Temp_Offset;
        //ECAP_selectECAPInput(myECAP0_BASE,ECAP_INPUT_INPUTXBAR1);
        ECAP_resetCounters(myECAP0_BASE);

        GPIO_writePin(TEMP_MUX_A, 1);
        GPIO_writePin(TEMP_MUX_B, 1);
        GPIO_writePin(TEMP_MUX_C, 0);

        if((TEMP_Batt_L1_Buff-TEMP_Batt_L1_FILTER)>30.0) {TEMP_Batt_L1_Buff=TEMP_Batt_L1_FILTER;} // To remove unknown spikes, if any exist

        TEMP_Batt_L1_FILTER=stringINV_TEMP_FILTERING_CONSTANT*(-TEMP_Batt_L1_FILTER+TEMP_Batt_L1_Buff)+TEMP_Batt_L1_FILTER;

        ECAP_reArm(myECAP0_BASE);
        TEMP_S4_Duty= ((float)ECAP_getEventTimeStamp(myECAP1_BASE, ECAP_EVENT_3) - (float)ECAP_getEventTimeStamp(myECAP1_BASE, ECAP_EVENT_2)) / (ECAP_getEventTimeStamp(myECAP1_BASE, ECAP_EVENT_3) - ECAP_getEventTimeStamp(myECAP1_BASE, ECAP_EVENT_1));
        TEMP_S4=stringINV_GaN_Temp_Coefficient*TEMP_S4_Duty+stringINV_GaN_Temp_Offset;
        ECAP_resetCounters(myECAP1_BASE);

        if((TEMP_S4-TEMP_S4_FILTER)>30.0) {TEMP_S4=TEMP_S4_FILTER;} // To remove unknown spikes, if any exist

        TEMP_S4_FILTER=stringINV_TEMP_FILTERING_CONSTANT*(-TEMP_S4_FILTER+TEMP_S4)+TEMP_S4_FILTER;
        ECAP_reArm(myECAP1_BASE);
        GPIO_writePin(LED_HEARTBEAT,0);
    }

    else if((stringINV_GaN_Temp_Counter>(stringINV_GaN_Temp_Scaling*2/3)) && stringINV_GaN_Temp_Counter<=(stringINV_GaN_Temp_Scaling*5/6))
    {
        //Code for acquiring the temperatures
        TEMP_Batt_H2_Buff_Duty= ((float)ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_3) - (float)ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_2)) / (ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_3) - ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_1));
        TEMP_Batt_H2_Buff=stringINV_GaN_Temp_Coefficient*TEMP_Batt_H2_Buff_Duty+stringINV_GaN_Temp_Offset;
        //ECAP_selectECAPInput(myECAP0_BASE,ECAP_INPUT_INPUTXBAR1);
        ECAP_resetCounters(myECAP0_BASE);
        GPIO_writePin(TEMP_MUX_A, 0);
        GPIO_writePin(TEMP_MUX_B, 0);
        GPIO_writePin(TEMP_MUX_C, 1);

        if((TEMP_Batt_H2_Buff-TEMP_Batt_H2_FILTER)>30.0) {TEMP_Batt_H2_Buff=TEMP_Batt_H2_FILTER;} // To remove unknown spikes, if any exist

        TEMP_Batt_H2_FILTER=stringINV_TEMP_FILTERING_CONSTANT*(-TEMP_Batt_H2_FILTER+TEMP_Batt_H2_Buff)+TEMP_Batt_H2_FILTER;

        ECAP_reArm(myECAP0_BASE);
        TEMP_S5_Duty= ((float)ECAP_getEventTimeStamp(myECAP1_BASE, ECAP_EVENT_3) - (float)ECAP_getEventTimeStamp(myECAP1_BASE, ECAP_EVENT_2)) / (ECAP_getEventTimeStamp(myECAP1_BASE, ECAP_EVENT_3) - ECAP_getEventTimeStamp(myECAP1_BASE, ECAP_EVENT_1));
        TEMP_S5=stringINV_GaN_Temp_Coefficient*TEMP_S5_Duty+stringINV_GaN_Temp_Offset;
        ECAP_resetCounters(myECAP1_BASE);

        if((TEMP_S5-TEMP_S5_FILTER)>30.0) {TEMP_S5=TEMP_S5_FILTER;} // To remove unknown spikes, if any exist

        TEMP_S5_FILTER=stringINV_TEMP_FILTERING_CONSTANT*(-TEMP_S5_FILTER+TEMP_S5)+TEMP_S5_FILTER;
        ECAP_reArm(myECAP1_BASE);
        GPIO_writePin(LED_HEARTBEAT,1);
    }

    else if((stringINV_GaN_Temp_Counter>(stringINV_GaN_Temp_Scaling*5/6)) && stringINV_GaN_Temp_Counter<(stringINV_GaN_Temp_Scaling))
    {
        //Code for acquiring the temperatures
        TEMP_Batt_L2_Buff_Duty= ((float)ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_3) - (float)ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_2)) / (ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_3) - ECAP_getEventTimeStamp(myECAP0_BASE, ECAP_EVENT_1));
        TEMP_Batt_L2_Buff=stringINV_GaN_Temp_Coefficient*TEMP_Batt_L2_Buff_Duty+stringINV_GaN_Temp_Offset;
        //ECAP_selectECAPInput(myECAP0_BASE,ECAP_INPUT_INPUTXBAR1);
        ECAP_resetCounters(myECAP0_BASE);

        GPIO_writePin(TEMP_MUX_A, 1);
        GPIO_writePin(TEMP_MUX_B, 0);
        GPIO_writePin(TEMP_MUX_C, 1);

        if((TEMP_Batt_L2_Buff-TEMP_Batt_L2_FILTER)>30.0) {TEMP_Batt_L2_Buff=TEMP_Batt_L2_FILTER;} // To remove unknown spikes, if any exist

        TEMP_Batt_L2_FILTER=stringINV_TEMP_FILTERING_CONSTANT*(-TEMP_Batt_L2_FILTER+TEMP_Batt_L2_Buff)+TEMP_Batt_L2_FILTER;

        ECAP_reArm(myECAP0_BASE);

        TEMP_S6_Duty= ((float)ECAP_getEventTimeStamp(myECAP1_BASE, ECAP_EVENT_3) - (float)ECAP_getEventTimeStamp(myECAP1_BASE, ECAP_EVENT_2)) / (ECAP_getEventTimeStamp(myECAP1_BASE, ECAP_EVENT_3) - ECAP_getEventTimeStamp(myECAP1_BASE, ECAP_EVENT_1));
        TEMP_S6=stringINV_GaN_Temp_Coefficient*TEMP_S6_Duty+stringINV_GaN_Temp_Offset;
        ECAP_resetCounters(myECAP1_BASE);

        if((TEMP_S6-TEMP_S6_FILTER)>30.0) {TEMP_S6=TEMP_S6_FILTER;} // To remove unknown spikes, if any exist

        TEMP_S6_FILTER=stringINV_TEMP_FILTERING_CONSTANT*(-TEMP_S6_FILTER+TEMP_S6)+TEMP_S6_FILTER;
        ECAP_reArm(myECAP1_BASE);
        GPIO_writePin(LED_HEARTBEAT,0);
    }

    else if(stringINV_GaN_Temp_Counter==(stringINV_GaN_Temp_Scaling))
    {

        stringINV_GaN_Temp_Counter=0;
    }

    else
    {
        // do nothing
    }
}

//MPPT Initialization
void init_boost_mppt(stringINV_dcdc_mppt_t *incc) {
        stringINV_dcdc_mppt_init(incc);
    incc->MaxVolt = stringINV_DCDC_MPPT_DCDC_PNO_MAX_V;
    incc->MinVolt = stringINV_DCDC_MPPT_DCDC_PNO_MIN_V;
    incc->Stepsize = stringINV_DCDC_MPPT_DCDC_PNO_STEPSIZE;
    incc->DeltaPmin = stringINV_DCDC_MPPT_DCDC_PNO_DELTAPMIN;
    incc->mppt_enable = 1;
}

//Run MPPT
#pragma FUNC_ALWAYS_INLINE(stringINV_MPPT)
static inline void stringINV_MPPT() {

    stringINV_DCDC_mppt_counter++;
    if(stringINV_DCDC_mppt_counter == stringINV_DCDC_MPPT_COUNTER_THR-2) {
        stringINV_DCDC_b1_mppt_incc.Ipv = stringINV_DCDC_CS_Boost1_sensed_FILTER;
        stringINV_DCDC_b1_mppt_incc.Vpv = stringINV_DCDC_VS_Boost1_sensed_FILTER;
        stringINV_dcdc_mppt_run(&stringINV_DCDC_b1_mppt_incc);
        stringINV_DCDC_b1_voltage_ref = stringINV_DCDC_b1_mppt_incc.VmppOut;

        }
    if(stringINV_DCDC_mppt_counter == stringINV_DCDC_MPPT_COUNTER_THR-1) {
        stringINV_DCDC_b2_mppt_incc.Ipv = stringINV_DCDC_CS_Boost2_sensed_FILTER;
        stringINV_DCDC_b2_mppt_incc.Vpv = stringINV_DCDC_VS_Boost2_sensed_FILTER;
        stringINV_dcdc_mppt_run(&stringINV_DCDC_b2_mppt_incc);
        stringINV_DCDC_b2_voltage_ref = stringINV_DCDC_b2_mppt_incc.VmppOut;
        }
    if(stringINV_DCDC_mppt_counter == stringINV_DCDC_MPPT_COUNTER_THR) {
        stringINV_DCDC_mppt_counter = 0;
        }
}

//Current control Bidirectional Converters
void string_DCDC_CurrentControl() {


    //PI control loops bidirectional 1 & 2
    stringINV_DCDC_CS_Batt1_loop_err=stringINV_DCDC_CS_Batt_Ref_Slewed+stringINV_DCDC_CS_Batt1_sensed;
    Batt1_Duty_Cycle = ((DCL_runPI_C2(&gi_Batt_pi_1,stringINV_DCDC_CS_Batt1_loop_err,0)+stringINV_DCDC_VS_Batt_sensed_FILTER)/(stringINV_ACDC_vDC_sensed_FILTER+3.0f));

    stringINV_DCDC_CS_Batt2_loop_err=stringINV_DCDC_CS_Batt_Ref_Slewed+stringINV_DCDC_CS_Batt2_sensed;
    Batt2_Duty_Cycle = ((DCL_runPI_C2(&gi_Batt_pi_2,stringINV_DCDC_CS_Batt2_loop_err,0)+stringINV_DCDC_VS_Batt_sensed_FILTER)/(stringINV_ACDC_vDC_sensed_FILTER+3.0f));

    //Set boundary conditions
    Batt1_Duty_Cycle= (Batt1_Duty_Cycle > 1.0f) ? 1.0f : Batt1_Duty_Cycle;
    Batt1_Duty_Cycle = (Batt1_Duty_Cycle < 0.0f) ? 0.0f : Batt1_Duty_Cycle;

    Batt2_Duty_Cycle= (Batt2_Duty_Cycle > 1.0f) ? 1.0f : Batt2_Duty_Cycle;
    Batt2_Duty_Cycle = (Batt2_Duty_Cycle < 0.0f) ? 0.0f : Batt2_Duty_Cycle;
}

//Current control AC/DC Converter
void string_ACDC_CurrentControl()
{
    stringINV_ACDC_iAC_loop_err=stringINV_ACDC_iAC_Ref_slewed-stringINV_ACDC_iAC_sensed;

        stringINV_ACDC_iAC_loop_out_PR1= DCL_runDF22_C1(&gi_r1, stringINV_ACDC_iAC_loop_err);
        stringINV_ACDC_iAC_loop_out_PR3= DCL_runDF22_C1(&gi_r3, stringINV_ACDC_iAC_loop_err);
        stringINV_ACDC_iAC_loop_out_PR5= DCL_runDF22_C1(&gi_r5, stringINV_ACDC_iAC_loop_err);
        stringINV_ACDC_iAC_loop_out_PR7= DCL_runDF22_C1(&gi_r7, stringINV_ACDC_iAC_loop_err);
        stringINV_ACDC_iAC_loop_out_PR9= DCL_runDF22_C1(&gi_r9, stringINV_ACDC_iAC_loop_err);
        stringINV_ACDC_iAC_loop_out_PR11= DCL_runDF22_C1(&gi_r11, stringINV_ACDC_iAC_loop_err);
        stringINV_ACDC_iAC_loop_out_PR13= DCL_runDF22_C1(&gi_r13, stringINV_ACDC_iAC_loop_err);
        stringINV_ACDC_iAC_loop_out_PR15= DCL_runDF22_C1(&gi_r15, stringINV_ACDC_iAC_loop_err);
        stringINV_ACDC_iAC_loop_out_PR17= DCL_runDF22_C1(&gi_r17, stringINV_ACDC_iAC_loop_err);

        stringINV_ACDC_Index_Modulation = (DCL_runPI_C2(&gi_ACDC_pi,stringINV_ACDC_iAC_loop_err,0)+(stringINV_ACDC_vAC_RMS_FILTER*1.4142*(stringINV_spll_1ph.sine))+stringINV_ACDC_iAC_loop_out_PR1+stringINV_ACDC_iAC_loop_out_PR3+stringINV_ACDC_iAC_loop_out_PR5+stringINV_ACDC_iAC_loop_out_PR7+stringINV_ACDC_iAC_loop_out_PR9+stringINV_ACDC_iAC_loop_out_PR11+stringINV_ACDC_iAC_loop_out_PR13+stringINV_ACDC_iAC_loop_out_PR15+stringINV_ACDC_iAC_loop_out_PR17)/(stringINV_ACDC_vDC_sensed_FILTER+5.0f);
        //Index modulation calculation based on closed-loop control with PR controller, FB and FF
      }

//DC Bus Voltage control
void string_DCBusVoltageControl() {
    stringINV_ACDC_vDC_loop_err=stringINV_DCDC_VDCext_Ref_Slewed-stringINV_ACDC_vDC_sensed_NOTCH;
    stringINV_ACDC_iAC_real_Ref_OUT_PI= -DCL_runPI_C2(&gv_ACDC_pi,stringINV_ACDC_vDC_loop_err,0);
    stringINV_ACDC_iAC_Ref_slewed = stringINV_ACDC_iAC_real_Ref_OUT_PI*(stringINV_spll_1ph.sine)+stringINV_ACDC_iAC_imag_Ref*(stringINV_spll_1ph.cosine);
}

void stringINV_Converter_Stop()
{
    GPIO_writePin(RY_ACPreCharge, 0);
    GPIO_writePin(RY_DCPreCharge, 0);
    EPWM_forceTripZoneEvent(BOOST_BASE, EPWM_TZ_FORCE_EVENT_OST);
    EPWM_forceTripZoneEvent(Bidirectional1_BASE, EPWM_TZ_FORCE_EVENT_OST);
    EPWM_forceTripZoneEvent(Bidirectional2_BASE, EPWM_TZ_FORCE_EVENT_OST);
    EPWM_forceTripZoneEvent(DCAC1_BASE, EPWM_TZ_FORCE_EVENT_OST);
    EPWM_forceTripZoneEvent(DCAC2_BASE, EPWM_TZ_FORCE_EVENT_OST);
}

void stringINV_Fault_Read()
{
    //Overcurrent Protection
    if((EPWM_getTripZoneFlagStatus(BOOST_BASE) & EPWM_TZ_FLAG_DCBEVT1)==EPWM_TZ_FLAG_DCBEVT1) {stringINV_ADC_fault=1; stringINV_FAULT_FLAGS.stringINV_ADC_fault_OC_Boost=1;}
    if((EPWM_getTripZoneFlagStatus(Bidirectional1_BASE) & EPWM_TZ_FLAG_DCBEVT1)==EPWM_TZ_FLAG_DCBEVT1) {stringINV_ADC_fault=1; stringINV_FAULT_FLAGS.stringINV_ADC_fault_OC_Bidirectional1=1;}
    if((EPWM_getTripZoneFlagStatus(Bidirectional2_BASE) & EPWM_TZ_FLAG_DCBEVT1)==EPWM_TZ_FLAG_DCBEVT1) {stringINV_ADC_fault=1; stringINV_FAULT_FLAGS.stringINV_ADC_fault_OC_Bidirectional2=1;}
    if((EPWM_getTripZoneFlagStatus(DCAC1_BASE) & EPWM_TZ_FLAG_DCBEVT1)==EPWM_TZ_FLAG_DCBEVT1) {stringINV_ADC_fault=1; stringINV_FAULT_FLAGS.stringINV_ADC_fault_OC_DCAC1=1;}
    if((EPWM_getTripZoneFlagStatus(DCAC2_BASE) & EPWM_TZ_FLAG_DCBEVT1)==EPWM_TZ_FLAG_DCBEVT1) {stringINV_ADC_fault=1; stringINV_FAULT_FLAGS.stringINV_ADC_fault_OC_DCAC2=1;}

    //Overvoltage Protection
    if((stringINV_ACDC_vDC_sensed > stringINV_ACDC_vDC_TRIP_LIMIT_V)||(stringINV_DCDC_vDC_sensed > stringINV_ACDC_vDC_TRIP_LIMIT_V))
    {
        stringINV_ADC_fault=1;
        stringINV_FAULT_FLAGS.stringINV_ADC_fault_Overvoltage=1;
    }

    //Undervoltage Protection
    if((stringINV_enableUVFaults==1) && (stringINV_ACDC_vDC_sensed < stringINV_ACDC_vDC_TRIP_MIN_V))
    {
        stringINV_ADC_fault=1;
        stringINV_FAULT_FLAGS.stringINV_ADC_fault_Undervoltage=1;
    }

    //Overvoltage Protection Grid
    if((stringINV_enableUVFaults==1) && (stringINV_mains_L1.vRms > stringINV_ACDC_vAC_TRIP_MAX_V ))
    {
        stringINV_ADC_fault=1;
        stringINV_FAULT_FLAGS.stringINV_ADC_fault_ACOvervoltage=1;
    }

    //Undervoltage Protection Grid

    if((stringINV_enableUVFaults==1) && (stringINV_mains_L1.vRms < stringINV_ACDC_vAC_TRIP_MIN_V))
    {
        stringINV_ADC_fault=1;
        stringINV_FAULT_FLAGS.stringINV_ADC_fault_ACUndervoltage=1;

    }

    //Overtermperature Protection
    if((TEMP_Boost1_FILTER > stringINV_TempLimit)||(TEMP_Boost2_FILTER > stringINV_TempLimit)||(TEMP_Batt_H1_FILTER > stringINV_TempLimit)||(TEMP_Batt_L1_FILTER > stringINV_TempLimit)||(TEMP_Batt_H2_FILTER > stringINV_TempLimit)||(TEMP_Batt_L2_FILTER > stringINV_TempLimit))
    {
        stringINV_ADC_fault=1;
        stringINV_FAULT_FLAGS.stringINV_DC_OverTemp=1;
        TEMP_Boost1_FILTER_fault=TEMP_Boost1_FILTER;
        TEMP_Boost2_FILTER_fault=TEMP_Boost2_FILTER;
        TEMP_Batt_H1_FILTER_fault=TEMP_Batt_H1_FILTER;
        TEMP_Batt_L1_FILTER_fault=TEMP_Batt_L1_FILTER;
        TEMP_Batt_H2_FILTER_fault=TEMP_Batt_H2_FILTER;
        TEMP_Batt_L2_FILTER_fault=TEMP_Batt_L2_FILTER;
          }
     if((TEMP_S1_FILTER > stringINV_TempLimit)||(TEMP_S2_FILTER > stringINV_TempLimit)||(TEMP_S3_FILTER > stringINV_TempLimit)||(TEMP_S4_FILTER > stringINV_TempLimit)||(TEMP_S5_FILTER > stringINV_TempLimit)||(TEMP_S6_FILTER > stringINV_TempLimit))
     {
         stringINV_ADC_fault=1;
         stringINV_FAULT_FLAGS.stringINV_AC_OverTemp=1;
         TEMP_S1_FILTER_fault=TEMP_S1_FILTER;
         TEMP_S2_FILTER_fault=TEMP_S2_FILTER;
         TEMP_S3_FILTER_fault=TEMP_S3_FILTER;
         TEMP_S4_FILTER_fault=TEMP_S4_FILTER;
         TEMP_S5_FILTER_fault=TEMP_S5_FILTER;
         TEMP_S6_FILTER_fault=TEMP_S6_FILTER;
      }

     if(stringINV_ADC_fault==1)
     {
         stringINV_fault_read_start=1;
         stringINV_Converter_Stop();
         GPIO_writePin(LED_FAULT,1);
     }

     if(stringINV_fault_read_start==1 & stringINV_fault_read_completed==1)
     {
         stringINV_DCDC_CS_Boost1_fault=stringINV_DCDC_CS_Boost1_sensed;
         stringINV_DCDC_VS_Boost1_fault=stringINV_DCDC_VS_Boost1_sensed;
         stringINV_DCDC_CS_Boost2_fault=stringINV_DCDC_CS_Boost2_sensed;
         stringINV_DCDC_VS_Boost2_fault=stringINV_DCDC_VS_Boost2_sensed;
         stringINV_Boost1_Duty_Ref_Slewed_fault=stringINV_Boost1_Duty_Ref_Slewed;
         stringINV_Boost2_Duty_Ref_Slewed_fault=stringINV_Boost2_Duty_Ref_Slewed;
         stringINV_Boost1_Duty_Ref_fault=stringINV_Boost1_Duty_Ref;
         stringINV_Boost2_Duty_Ref_fault=stringINV_Boost2_Duty_Ref;

         stringINV_DCDC_CS_Batt1_fault=stringINV_DCDC_CS_Batt1_sensed;
         stringINV_DCDC_CS_Batt2_fault=stringINV_DCDC_CS_Batt2_sensed;
         stringINV_DCDC_VS_Batt_fault=stringINV_DCDC_VS_Batt_sensed;
         Batt1_Duty_Cycle_fault=Batt1_Duty_Cycle;
         Batt2_Duty_Cycle_fault=Batt2_Duty_Cycle;

         stringINV_ACDC_vDC_fault=stringINV_ACDC_vDC_sensed;
         stringINV_ACDC_iAC_fault=stringINV_ACDC_iAC_sensed;
         stringINV_ACDC_vAC_fault=stringINV_ACDC_vAC_sensed;
         stringINV_ACDC_vAC_RMS_fault=stringINV_mains_L1.vRms;
         stringINV_ACDC_Index_Modulation_fault=stringINV_ACDC_Index_Modulation;

         stringINV_fault_read_completed=0;
     }
}

void stringINV_DCAC_Modulation()
{
#if(stringINV_DCAC_Modulation_Scheme==1) //HERIC
    {
        if(stringINV_ACDC_Index_Modulation >= 0.02f)  //
                {
                    EPWM_setCounterCompareValue(DCAC1_BASE, EPWM_COUNTER_COMPARE_A, stringINV_ACDC_Index_Modulation*DCAC_PWM_PRD);
                    EPWM_setCounterCompareValue(DCAC2_BASE, EPWM_COUNTER_COMPARE_A, 0);
                }
                else if(stringINV_ACDC_Index_Modulation < 0.02f && stringINV_ACDC_Index_Modulation >=  -0.02f) // Between 2 % and -2%
                {
                    EPWM_setCounterCompareValue(DCAC1_BASE, EPWM_COUNTER_COMPARE_A, 0); //
                    EPWM_setCounterCompareValue(DCAC2_BASE, EPWM_COUNTER_COMPARE_A, 0);

                    if(stringINV_stop==1)
                    {
                        stringINV_Converter_Stop();
                    }
                }
                else
                {
                    EPWM_setCounterCompareValue(DCAC1_BASE, EPWM_COUNTER_COMPARE_A, 0);
                    EPWM_setCounterCompareValue(DCAC2_BASE, EPWM_COUNTER_COMPARE_A, -stringINV_ACDC_Index_Modulation*DCAC_PWM_PRD);
                }
    }
#endif
#if (stringINV_DCAC_Modulation_Scheme==2) //Bipolar
    {
        EPWM_setCounterCompareValue(DCAC1_BASE, EPWM_COUNTER_COMPARE_A, ((stringINV_ACDC_Index_Modulation+1.0f)*0.5f)*DCAC_PWM_PRD);

        if(stringINV_ACDC_Index_Modulation < 0.02f && stringINV_ACDC_Index_Modulation >=  -0.02f) // Between 2 % and -2 %
                    {
                    if(stringINV_stop==1)
                    {
                        stringINV_Converter_Stop();
                    }
          }
    }
#endif
#if(stringINV_DCAC_Modulation_Scheme==3) //Unipolar
    {
        EPWM_setCounterCompareValue(DCAC1_BASE, EPWM_COUNTER_COMPARE_A, ((stringINV_ACDC_Index_Modulation+1.0f)*0.5f)*DCAC_PWM_PRD);
        EPWM_setCounterCompareValue(DCAC2_BASE, EPWM_COUNTER_COMPARE_A, ((-stringINV_ACDC_Index_Modulation+1.0f)*0.5f)*DCAC_PWM_PRD);

        if(stringINV_ACDC_Index_Modulation < 0.02f && stringINV_ACDC_Index_Modulation >=  -0.02f) // Between 2 % and -2 %
        {
                    if(stringINV_stop==1)
                    {
                        stringINV_Converter_Stop();
                    }
        }
    }
#endif
}

#pragma FUNC_ALWAYS_INLINE(stringINV_readCurrentAndVoltageSignals)
static inline void stringINV_readCurrentAndVoltageSignals()
{
    //DC-DC PU Measurements
    stringINV_DCDC_CS_Boost1_sensed_pu =  ADC_readResult(SOC_CS_Boost1_RESULT_BASE, SOC_CS_Boost1)*stringINV_ADC_UNIPOLAR_PU_SCALE_FACTOR; //Unipolar Measurement
    stringINV_DCDC_VS_Boost1_sensed_pu =  ADC_readResult(SOC_VS_Boost1_RESULT_BASE, SOC_VS_Boost1)*stringINV_ADC_UNIPOLAR_PU_SCALE_FACTOR; //Unipolar Measurement
    stringINV_DCDC_CS_Boost2_sensed_pu =  ADC_readResult(SOC_CS_Boost2_RESULT_BASE, SOC_CS_Boost2)*stringINV_ADC_UNIPOLAR_PU_SCALE_FACTOR; //Unipolar Measurement
    stringINV_DCDC_VS_Boost2_sensed_pu =  ADC_readResult(SOC_VS_Boost2_RESULT_BASE, SOC_VS_Boost2)*stringINV_ADC_UNIPOLAR_PU_SCALE_FACTOR; //Unipolar Measurement
    stringINV_DCDC_CS_Batt1_sensed_pu =  ADC_readResult(SOC_CS_Batt1_RESULT_BASE, SOC_CS_Batt1)*stringINV_ADC_BIPOLAR_PU_SCALE_FACTOR-1.0f; //Bipolar Measurement
    stringINV_DCDC_VS_Batt_sensed_pu =  ADC_readResult(SOC_VS_Batt_RESULT_BASE, SOC_VS_Batt)*stringINV_ADC_UNIPOLAR_PU_SCALE_FACTOR; //Unipolar Measurement
    stringINV_DCDC_CS_Batt2_sensed_pu =  ADC_readResult(SOC_CS_Batt2_RESULT_BASE, SOC_CS_Batt2)*stringINV_ADC_BIPOLAR_PU_SCALE_FACTOR-1.0f; //Bipolar Measurement
    stringINV_DCDC_vDC_sensed_pu=  ADC_readResult(SOC_Vbus_DCDC_RESULT_BASE, SOC_Vbus_DCDC)*stringINV_ADC_UNIPOLAR_PU_SCALE_FACTOR; //Unipolar Measurement

    //DC-AC PU Measurements
    stringINV_ACDC_vDC_sensed_pu=  ADC_readResult(SOC_Vbus_RESULT_BASE, SOC_Vbus)*stringINV_ADC_UNIPOLAR_PU_SCALE_FACTOR; //Unipolar Measurement
    stringINV_ACDC_iAC_sensed_pu=  ADC_readResult(SOC_IAC_RESULT_BASE, SOC_IAC)*stringINV_ADC_BIPOLAR_PU_SCALE_FACTOR-1.0f; //Bipolar Measurement
    stringINV_ACDC_vAC_sensed_pu=  ADC_readResult(SOC_VAC_RESULT_BASE, SOC_VAC)*stringINV_ADC_BIPOLAR_PU_SCALE_FACTOR-1.0f; //Bipolar Measurement

    //DC-DC Scaled Measurements
    stringINV_DCDC_CS_Boost1_sensed = stringINV_DCDC_CS_Boost1_sensed_pu*stringINV_DCDC_CS_Boost1_MAX + stringINV_DCDC_CS_Boost1_Offset;
    stringINV_DCDC_VS_Boost1_sensed = stringINV_DCDC_VS_Boost1_sensed_pu*stringINV_DCDC_VS_Boost1_MAX + stringINV_DCDC_VS_Boost1_Offset;
    stringINV_DCDC_CS_Boost2_sensed = stringINV_DCDC_CS_Boost2_sensed_pu*stringINV_DCDC_CS_Boost2_MAX + stringINV_DCDC_CS_Boost2_Offset;
    stringINV_DCDC_VS_Boost2_sensed = stringINV_DCDC_VS_Boost2_sensed_pu*stringINV_DCDC_VS_Boost2_MAX + stringINV_DCDC_VS_Boost2_Offset;
    stringINV_DCDC_CS_Batt1_sensed = stringINV_DCDC_CS_Batt1_sensed_pu*stringINV_DCDC_CS_Batt1_MAX + stringINV_DCDC_CS_Batt1_Offset;
    stringINV_DCDC_VS_Batt_sensed = stringINV_DCDC_VS_Batt_sensed_pu*stringINV_DCDC_VS_Batt_MAX + stringINV_DCDC_VS_Batt_Offset;
    stringINV_DCDC_CS_Batt2_sensed = stringINV_DCDC_CS_Batt2_sensed_pu*stringINV_DCDC_CS_Batt2_MAX + stringINV_DCDC_CS_Batt2_Offset;
    stringINV_DCDC_vDC_sensed = stringINV_DCDC_vDC_sensed_pu*stringINV_DCDC_vDC_MAX + stringINV_DCDC_vDC_Offset;


    //DC-AC Scaled Measurements
    stringINV_ACDC_vDC_sensed = stringINV_ACDC_vDC_sensed_pu*stringINV_ACDC_vDC_MAX + stringINV_ACDC_vDC_Offset;
    stringINV_ACDC_iAC_sensed = stringINV_ACDC_iAC_sensed_pu*stringINV_ACDC_iAC_MAX + stringINV_ACDC_iAC_Offset;
    stringINV_ACDC_vAC_sensed = stringINV_ACDC_vAC_sensed_pu*stringINV_ACDC_vAC_MAX + stringINV_ACDC_vAC_Offset;


    //DC-DC Low Pass Filtering of analog measurements
    stringINV_DCDC_VS_Batt_sensed_FILTER=stringINV_DC_FILTERING_CONSTANT_VS_BATT*(-stringINV_DCDC_VS_Batt_sensed_FILTER+stringINV_DCDC_VS_Batt_sensed)+stringINV_DCDC_VS_Batt_sensed_FILTER;
    stringINV_DCDC_CS_Boost1_sensed_FILTER=stringINV_DC_FILTERING_CONSTANT_CS_BOOST*(-stringINV_DCDC_CS_Boost1_sensed_FILTER+stringINV_DCDC_CS_Boost1_sensed)+stringINV_DCDC_CS_Boost1_sensed_FILTER;
    stringINV_DCDC_VS_Boost1_sensed_FILTER=stringINV_DC_FILTERING_CONSTANT_VS_BOOST*(-stringINV_DCDC_VS_Boost1_sensed_FILTER+stringINV_DCDC_VS_Boost1_sensed)+stringINV_DCDC_VS_Boost1_sensed_FILTER;
    stringINV_DCDC_CS_Boost2_sensed_FILTER=stringINV_DC_FILTERING_CONSTANT_CS_BOOST*(-stringINV_DCDC_CS_Boost2_sensed_FILTER+stringINV_DCDC_CS_Boost2_sensed)+stringINV_DCDC_CS_Boost2_sensed_FILTER;
    stringINV_DCDC_VS_Boost2_sensed_FILTER=stringINV_DC_FILTERING_CONSTANT_VS_BOOST*(-stringINV_DCDC_VS_Boost2_sensed_FILTER+stringINV_DCDC_VS_Boost2_sensed)+stringINV_DCDC_VS_Boost2_sensed_FILTER;
    stringINV_DCDC_vDC_sensed_FILTER=stringINV_DC_FILTERING_CONSTANT_VDC*(-stringINV_DCDC_vDC_sensed_FILTER+stringINV_DCDC_vDC_sensed)+stringINV_DCDC_vDC_sensed_FILTER;

    //AC-DC Low Pass Filtering of analog measurements
    stringINV_ACDC_vDC_sensed_FILTER=stringINV_DC_FILTERING_CONSTANT_VDC*(-stringINV_ACDC_vDC_sensed_FILTER+stringINV_ACDC_vDC_sensed)+stringINV_ACDC_vDC_sensed_FILTER;
    stringINV_ACDC_vAC_sensed_FILTER=stringINV_AC_FILTERING_CONSTANT_VS_INV*(-stringINV_ACDC_vAC_sensed_FILTER+stringINV_ACDC_vAC_sensed)+stringINV_ACDC_vAC_sensed_FILTER;
    stringINV_ACDC_vAC_RMS_FILTER=stringINV_AC_FILTERING_CONSTANT_VS_INV_RMS*(-stringINV_ACDC_vAC_RMS_FILTER+stringINV_mains_L1.vRms)+stringINV_ACDC_vAC_RMS_FILTER;

    //Notch Filtering
    stringINV_ACDC_vDC_sensed_NOTCH = DCL_runDF22_C4(&VDC_NOTCH_FILTER_2_Fe, stringINV_ACDC_vDC_sensed_FILTER);

    //Power measurement library
    stringINV_mains_L1.v = stringINV_ACDC_vAC_sensed;
    stringINV_mains_L1.i = stringINV_ACDC_iAC_sensed;
}

//Function for DC Bus Voltage ramp
#pragma FUNC_ALWAYS_INLINE(stringINV_RAMP_VDC)
static inline void stringINV_RAMP_VDC()
{
    if((stringINV_DCDC_vDC_Ref - stringINV_DCDC_vDC_Ref_Slewed) > (2 * stringINV_VOLTS_PER_SECOND_SLEW) *
            (ISR_CONTROL_FREQUENCY_AC_INVERSE))
    {
        stringINV_DCDC_vDC_Ref_Slewed =  stringINV_DCDC_vDC_Ref_Slewed + (stringINV_VOLTS_PER_SECOND_SLEW) *
                (ISR_CONTROL_FREQUENCY_AC_INVERSE);
    }
    else if((stringINV_DCDC_vDC_Ref - stringINV_DCDC_vDC_Ref_Slewed) <
            - (2 * stringINV_VOLTS_PER_SECOND_SLEW) *
            (ISR_CONTROL_FREQUENCY_AC_INVERSE))
    {
        stringINV_DCDC_vDC_Ref_Slewed =  stringINV_DCDC_vDC_Ref_Slewed - (stringINV_VOLTS_PER_SECOND_SLEW) *
                (ISR_CONTROL_FREQUENCY_AC_INVERSE);
    }
    else
    {
        stringINV_DCDC_vDC_Ref_Slewed =  stringINV_DCDC_vDC_Ref;
    }


}

//Function for Boost 1 Duty Cycle ramp
#pragma FUNC_ALWAYS_INLINE(stringINV_RAMP_BOOST1PWM)
static inline void stringINV_RAMP_BOOST1PWM()
{
    if((stringINV_DCDC_BOOST1PWM_Ref - stringINV_DCDC_BOOST1PWM_Ref_Slewed) > (2 * stringINV_D_PER_SECOND_SLEW) *
            (ISR_CONTROL_FREQUENCY_AC_INVERSE))
    {
        stringINV_DCDC_BOOST1PWM_Ref_Slewed =  stringINV_DCDC_BOOST1PWM_Ref_Slewed + (stringINV_D_PER_SECOND_SLEW) *
                (ISR_CONTROL_FREQUENCY_AC_INVERSE);
    }
    else if((stringINV_DCDC_BOOST1PWM_Ref - stringINV_DCDC_BOOST1PWM_Ref_Slewed) <
            - (2 * stringINV_D_PER_SECOND_SLEW) *
            (ISR_CONTROL_FREQUENCY_AC_INVERSE))
    {
        stringINV_DCDC_BOOST1PWM_Ref_Slewed =  stringINV_DCDC_BOOST1PWM_Ref_Slewed - (stringINV_D_PER_SECOND_SLEW) *
                (ISR_CONTROL_FREQUENCY_AC_INVERSE);
    }
    else
    {
        stringINV_DCDC_BOOST1PWM_Ref_Slewed =  stringINV_DCDC_BOOST1PWM_Ref;
    }
}

//Function for Boost 2 Duty Cycle ramp
#pragma FUNC_ALWAYS_INLINE(stringINV_RAMP_BOOST2PWM)
static inline void stringINV_RAMP_BOOST2PWM()
{
    if((stringINV_DCDC_BOOST2PWM_Ref - stringINV_DCDC_BOOST2PWM_Ref_Slewed) > (2 * stringINV_D_PER_SECOND_SLEW) *
            (ISR_CONTROL_FREQUENCY_AC_INVERSE))
    {
        stringINV_DCDC_BOOST2PWM_Ref_Slewed =  stringINV_DCDC_BOOST2PWM_Ref_Slewed + (stringINV_D_PER_SECOND_SLEW) *
                (ISR_CONTROL_FREQUENCY_AC_INVERSE);
    }
    else if((stringINV_DCDC_BOOST2PWM_Ref - stringINV_DCDC_BOOST2PWM_Ref_Slewed) <
            - (2 * stringINV_D_PER_SECOND_SLEW) *
            (ISR_CONTROL_FREQUENCY_AC_INVERSE))
    {
        stringINV_DCDC_BOOST2PWM_Ref_Slewed =  stringINV_DCDC_BOOST2PWM_Ref_Slewed - (stringINV_D_PER_SECOND_SLEW) *
                (ISR_CONTROL_FREQUENCY_AC_INVERSE);
    }
    else
    {
        stringINV_DCDC_BOOST2PWM_Ref_Slewed =  stringINV_DCDC_BOOST2PWM_Ref;
    }
}

//Function for Bidirectional Current ramp
#pragma FUNC_ALWAYS_INLINE(stringINV_RAMP_IBATT)
static inline void stringINV_RAMP_IBATT()
{
    if((stringINV_DCDC_IDC_Ref - stringINV_DCDC_IDC_Ref_Slewed) > (2 * stringINV_AMPS_PER_SECOND_SLEW) *
            (ISR_CONTROL_FREQUENCY_AC_INVERSE))
    {
        stringINV_DCDC_IDC_Ref_Slewed =  stringINV_DCDC_IDC_Ref_Slewed + (stringINV_AMPS_PER_SECOND_SLEW) *
                (ISR_CONTROL_FREQUENCY_AC_INVERSE);
    }
    else if((stringINV_DCDC_IDC_Ref - stringINV_DCDC_IDC_Ref_Slewed) <
            - (2 * stringINV_AMPS_PER_SECOND_SLEW) *
            (ISR_CONTROL_FREQUENCY_AC_INVERSE))
    {
        stringINV_DCDC_IDC_Ref_Slewed =  stringINV_DCDC_IDC_Ref_Slewed - (stringINV_AMPS_PER_SECOND_SLEW) *
                (ISR_CONTROL_FREQUENCY_AC_INVERSE);
    }
    else
    {
        stringINV_DCDC_IDC_Ref_Slewed =  stringINV_DCDC_IDC_Ref;
    }
}

//Function for ACDC Current ramp
#pragma FUNC_ALWAYS_INLINE(stringINV_RAMP_IDCACREF)
static inline void stringINV_RAMP_IDCACREF()
{
    if((stringINV_IDCAC_Ref - stringINV_IDCAC_Ref_Slewed) > (2 * stringINV_AMPS_PER_SECOND_SLEW) *
            (ISR_CONTROL_FREQUENCY_AC_INVERSE))
    {
        stringINV_IDCAC_Ref_Slewed =  stringINV_IDCAC_Ref_Slewed + (stringINV_AMPS_PER_SECOND_SLEW) *
                (ISR_CONTROL_FREQUENCY_AC_INVERSE);
    }
    else if((stringINV_IDCAC_Ref - stringINV_IDCAC_Ref_Slewed) <
            - (2 * stringINV_AMPS_PER_SECOND_SLEW) *
            (ISR_CONTROL_FREQUENCY_AC_INVERSE))
    {
        stringINV_IDCAC_Ref_Slewed =  stringINV_IDCAC_Ref_Slewed - (stringINV_AMPS_PER_SECOND_SLEW) *
                (ISR_CONTROL_FREQUENCY_AC_INVERSE);
    }
    else
    {
        stringINV_IDCAC_Ref_Slewed =  stringINV_IDCAC_Ref;
    }
}

#pragma FUNC_ALWAYS_INLINE(stringInverter_runISR1_lab_ADC_PWM) //LAB 1: ADC & PWM Check
static inline void stringInverter_runISR1_lab_ADC_PWM()
{

    RAMPGEN_run(&stringINV_ACDC_rgen);

    stringINV_ACDC_Index_Modulation = stringINV_ACDC_Amplitude*(__sinpuf32(stringINV_ACDC_rgen.out));

    if(stringINV_clearPWMTrip == 1U)
    {
        stringINV_clearPWMTrip = 0;
        stringINV_updateDuty=1;
        EPWM_clearTripZoneFlag(BOOST_BASE, EPWM_TZ_INTERRUPT |EPWM_TZ_FLAG_OST);
        EPWM_clearTripZoneFlag(Bidirectional1_BASE, EPWM_TZ_INTERRUPT |EPWM_TZ_FLAG_OST);
        EPWM_clearTripZoneFlag(Bidirectional2_BASE, EPWM_TZ_INTERRUPT |EPWM_TZ_FLAG_OST);
        EPWM_clearTripZoneFlag(DCAC1_BASE, EPWM_TZ_INTERRUPT |EPWM_TZ_FLAG_OST);
        EPWM_clearTripZoneFlag(DCAC2_BASE, EPWM_TZ_INTERRUPT |EPWM_TZ_FLAG_OST);
    }

    if(stringINV_updateDuty == 1U)
    {
        //Boost Converters
        EPWM_setCounterCompareValue(BOOST_BASE, EPWM_COUNTER_COMPARE_A, (1-stringINV_Boost1_Duty_Ref)*BOOST_PWM_PRD); //Boost S1 Duty Cycle
        EPWM_setCounterCompareValue(BOOST_BASE, EPWM_COUNTER_COMPARE_B, (1-stringINV_Boost2_Duty_Ref)*BOOST_PWM_PRD); //Boost S2 Duty Cycle

        //Bidirectional DC/DC Converter
        EPWM_setCounterCompareValue(Bidirectional1_BASE, EPWM_COUNTER_COMPARE_A, (Batt1_Duty_Cycle)*BIDIRECTIONAL_PWM_PRD); //Bidirectional 1 Duty Cycle
        EPWM_setCounterCompareValue(Bidirectional2_BASE, EPWM_COUNTER_COMPARE_A, (Batt2_Duty_Cycle)*BIDIRECTIONAL_PWM_PRD); //Bidirectional 2 Duty Cycle

        //AC/DC Converter
        if(stringINV_ACDC_Index_Modulation >= 0.02f)  //
        {
            EPWM_setCounterCompareValue(DCAC1_BASE, EPWM_COUNTER_COMPARE_A, stringINV_ACDC_Index_Modulation*DCAC_PWM_PRD);
            EPWM_setCounterCompareValue(DCAC2_BASE, EPWM_COUNTER_COMPARE_A, 0);
        }
      else if(stringINV_ACDC_Index_Modulation < 0.02f && stringINV_ACDC_Index_Modulation >=  -0.02f) // Between 2 % and -2%
        {
            EPWM_setCounterCompareValue(DCAC1_BASE, EPWM_COUNTER_COMPARE_A, 0); //
            EPWM_setCounterCompareValue(DCAC2_BASE, EPWM_COUNTER_COMPARE_A, 0);
        }
        else
        {
            EPWM_setCounterCompareValue(DCAC1_BASE, EPWM_COUNTER_COMPARE_A, 0);
            EPWM_setCounterCompareValue(DCAC2_BASE, EPWM_COUNTER_COMPARE_A, -stringINV_ACDC_Index_Modulation*DCAC_PWM_PRD);
        }
    }
}

#pragma FUNC_ALWAYS_INLINE(stringInverter_runISR1_lab_Boost_OL) //LAB 2: Boost Open-Loop
static inline void stringInverter_runISR1_lab_Boost_OL()
{
    //Start the machine
    if(stringINV_clearPWMTripBoost == 1U)
    {
        stringINV_clearPWMTripBoost = 0;
        stringINV_updateDutyBoost=1;
        EPWM_clearTripZoneFlag(BOOST_BASE, EPWM_TZ_INTERRUPT |EPWM_TZ_FLAG_OST);
    }

    if(stringINV_updateDutyBoost == 1U)
    {
        //Ramp generation for duty cycles
        stringINV_DCDC_BOOST1PWM_Ref=stringINV_Boost1_Duty_Ref;
        stringINV_RAMP_BOOST1PWM();
        stringINV_Boost1_Duty_Ref_Slewed=stringINV_DCDC_BOOST1PWM_Ref_Slewed; //Ramp boost1 duty cycle

        stringINV_DCDC_BOOST2PWM_Ref=stringINV_Boost2_Duty_Ref;
        stringINV_RAMP_BOOST2PWM();
        stringINV_Boost2_Duty_Ref_Slewed=stringINV_DCDC_BOOST2PWM_Ref_Slewed; //Ramp boost2 duty cycle


        stringINV_Boost1_Duty_Ref= (stringINV_Boost1_Duty_Ref > 1.0f) ? 1.0f : stringINV_Boost1_Duty_Ref;
        stringINV_Boost1_Duty_Ref = (stringINV_Boost1_Duty_Ref < 0.0f) ? 0.0f : stringINV_Boost1_Duty_Ref;

        stringINV_Boost2_Duty_Ref= (stringINV_Boost2_Duty_Ref > 1.0f) ? 1.0f : stringINV_Boost2_Duty_Ref;
        stringINV_Boost2_Duty_Ref = (stringINV_Boost2_Duty_Ref < 0.0f) ? 0.0f : stringINV_Boost2_Duty_Ref;


        //Configuration to start with open circuit on both Boosts
        EPWM_setCounterCompareValue(BOOST_BASE, EPWM_COUNTER_COMPARE_A, (stringINV_Boost1_Duty_Ref_Slewed)*BOOST_PWM_PRD); //Boost S1 Duty Cycle
        EPWM_setCounterCompareValue(BOOST_BASE, EPWM_COUNTER_COMPARE_B, (stringINV_Boost2_Duty_Ref_Slewed)*BOOST_PWM_PRD); //Boost S2 Duty Cycle

     }

    if(stringINV_stop==1)
    {
        stringINV_Converter_Stop();
    }
}

#pragma FUNC_ALWAYS_INLINE(stringInverter_runISR1_lab_Boost_MPPT) //LAB 3: Boost Close-Loop with MPPT
static inline void stringInverter_runISR1_lab_Boost_MPPT()
{

     //Start the machine
    if(stringINV_clearPWMTripBoost == 1U)
    {
        stringINV_clearPWMTripBoost = 0;
        stringINV_updateDutyBoost=1;
        EPWM_clearTripZoneFlag(BOOST_BASE, EPWM_TZ_INTERRUPT |EPWM_TZ_FLAG_OST);
    }

    if(stringINV_updateDutyBoost == 1U)
    {

        //PI control loop for voltage control
        stringINV_DCDC_VBoost1_loop_err=-stringINV_DCDC_b1_voltage_ref+stringINV_DCDC_VS_Boost1_sensed_FILTER;
        stringINV_Boost1_Duty_Ref = (DCL_runPI_C2(&gv_VBoost_pi_1,stringINV_DCDC_VBoost1_loop_err,0));

        stringINV_DCDC_VBoost2_loop_err=-stringINV_DCDC_b2_voltage_ref+stringINV_DCDC_VS_Boost2_sensed_FILTER;
        stringINV_Boost2_Duty_Ref = (DCL_runPI_C2(&gv_VBoost_pi_2,stringINV_DCDC_VBoost2_loop_err,0));

        //Set boundary conditions
        stringINV_Boost1_Duty_Ref= (stringINV_Boost1_Duty_Ref > 1.0f) ? 1.0f : stringINV_Boost1_Duty_Ref;
        stringINV_Boost1_Duty_Ref = (stringINV_Boost1_Duty_Ref < 0.0f) ? 0.0f : stringINV_Boost1_Duty_Ref;

        stringINV_Boost2_Duty_Ref= (stringINV_Boost2_Duty_Ref > 1.0f) ? 1.0f : stringINV_Boost2_Duty_Ref;
        stringINV_Boost2_Duty_Ref = (stringINV_Boost2_Duty_Ref < 0.0f) ? 0.0f : stringINV_Boost2_Duty_Ref;

        //Configuration to start with Boost 1 & 2 in open circuit
        EPWM_setCounterCompareValue(BOOST_BASE, EPWM_COUNTER_COMPARE_A, (stringINV_Boost1_Duty_Ref)*BOOST_PWM_PRD); //Boost S1 Duty Cycle
        EPWM_setCounterCompareValue(BOOST_BASE, EPWM_COUNTER_COMPARE_B, (stringINV_Boost2_Duty_Ref)*BOOST_PWM_PRD); //Boost S2 Duty Cycle
    }


    if(stringINV_stop_only_DCAC==1){}

    else
    {
    if(stringINV_stop==1)
    {
        stringINV_Converter_Stop();
    }
    }

}

#pragma FUNC_ALWAYS_INLINE(stringInverter_runISR1_lab_DCDC_CL) //LAB 4: Bidirectional 1&2 Close-Loop with Current Control
static inline void stringInverter_runISR1_lab_DCDC_CL()
{

    // Start the machine
    if(stringINV_clearPWMTripDCDC == 1U)
    {
// First Duty Cycle Calculation to avoid overcurrent from battery

        stringINV_clearPWMTripDCDC = 0;
        stringINV_updateDutyDCDC=1;
        EPWM_clearTripZoneFlag(Bidirectional1_BASE, EPWM_TZ_INTERRUPT |EPWM_TZ_FLAG_OST);
        EPWM_clearTripZoneFlag(Bidirectional2_BASE, EPWM_TZ_INTERRUPT |EPWM_TZ_FLAG_OST);

    }

    if(stringINV_updateDutyDCDC == 1U)
    {
        //Ramp current reference batt 1 & 2
        stringINV_DCDC_IDC_Ref=stringINV_DCDC_CS_Batt_Ref;
        stringINV_RAMP_IBATT();
        stringINV_DCDC_CS_Batt_Ref_Slewed=stringINV_DCDC_IDC_Ref_Slewed;

        string_DCDC_CurrentControl();

        EPWM_setCounterCompareValue(Bidirectional1_BASE, EPWM_COUNTER_COMPARE_A, (Batt1_Duty_Cycle)*BIDIRECTIONAL_PWM_PRD); //Bidirectional 1 Duty Cycle
        EPWM_setCounterCompareValue(Bidirectional2_BASE, EPWM_COUNTER_COMPARE_A, (Batt2_Duty_Cycle)*BIDIRECTIONAL_PWM_PRD); //Bidirectional 2 Duty Cycle
    }
    else
    {
        // First Duty Cycle Calculation to avoid overcurrent from battery
        EPWM_setCounterCompareValue(Bidirectional1_BASE, EPWM_COUNTER_COMPARE_A, (stringINV_DCDC_VS_Batt_sensed_FILTER)/(stringINV_ACDC_vDC_sensed_FILTER+3.0f)*BIDIRECTIONAL_PWM_PRD); //Bidirectional 1 Duty Cycle
        EPWM_setCounterCompareValue(Bidirectional2_BASE, EPWM_COUNTER_COMPARE_A, (stringINV_DCDC_VS_Batt_sensed_FILTER)/(stringINV_ACDC_vDC_sensed_FILTER+3.0f)*BIDIRECTIONAL_PWM_PRD); //Bidirectional 2 Duty Cycle
        Batt1_Duty_Cycle= (Batt1_Duty_Cycle > 1.0f) ? 1.0f : Batt1_Duty_Cycle;
        Batt1_Duty_Cycle = (Batt1_Duty_Cycle < 0.0f) ? 0.0f : Batt1_Duty_Cycle;
        Batt2_Duty_Cycle= (Batt2_Duty_Cycle > 1.0f) ? 1.0f : Batt2_Duty_Cycle;
        Batt2_Duty_Cycle = (Batt2_Duty_Cycle < 0.0f) ? 0.0f : Batt2_Duty_Cycle;
    }

    if(stringINV_stop_only_DCAC==1){}

    else
    {
    if(stringINV_stop==1)
    {
        stringINV_Converter_Stop();
    }
    }
}

#pragma FUNC_ALWAYS_INLINE(stringInverter_runISR1_lab_Boost_OL_DCDC_CL) ////LAB 5: Boost Open-Loop & Bidirectional Close-Loop
static inline void stringInverter_runISR1_lab_Boost_OL_DCDC_CL()
{
    //Start the machine
    if(stringINV_clearPWMTripBoost == 1U)
    {
        stringINV_clearPWMTripBoost = 0;
        stringINV_updateDutyBoost=1;
        EPWM_clearTripZoneFlag(BOOST_BASE, EPWM_TZ_INTERRUPT |EPWM_TZ_FLAG_OST);
    }

    if(stringINV_updateDutyBoost == 1U)
    {
        //Ramp generation for duty cycles
        stringINV_DCDC_BOOST1PWM_Ref=stringINV_Boost1_Duty_Ref;
        stringINV_RAMP_BOOST1PWM();
        stringINV_Boost1_Duty_Ref_Slewed=stringINV_DCDC_BOOST1PWM_Ref_Slewed;

        //Configuration to start with short on both boost converters, starts with CMP reference = 1
        EPWM_setCounterCompareValue(BOOST_BASE, EPWM_COUNTER_COMPARE_A, (stringINV_Boost1_Duty_Ref_Slewed)*BOOST_PWM_PRD); //Boost S1 Duty Cycle
        EPWM_setCounterCompareValue(BOOST_BASE, EPWM_COUNTER_COMPARE_B, (stringINV_Boost1_Duty_Ref_Slewed)*BOOST_PWM_PRD); //Boost S2 Duty Cycle

        if(stringINV_clearPWMTripDCDC == 1U)
        {
            stringINV_clearPWMTripDCDC = 0;
            stringINV_updateDutyDCDC=1;
            EPWM_clearTripZoneFlag(Bidirectional1_BASE, EPWM_TZ_INTERRUPT |EPWM_TZ_FLAG_OST);
            EPWM_clearTripZoneFlag(Bidirectional2_BASE, EPWM_TZ_INTERRUPT |EPWM_TZ_FLAG_OST);
        }

        if(stringINV_updateDutyDCDC == 1U)
        {
            //Ramp current measurements batt 1 & 2
            stringINV_DCDC_IDC_Ref=stringINV_DCDC_CS_Batt_Ref;
            stringINV_RAMP_IBATT();
            stringINV_DCDC_CS_Batt_Ref_Slewed=stringINV_DCDC_IDC_Ref_Slewed;

            string_DCDC_CurrentControl();

            EPWM_setCounterCompareValue(Bidirectional1_BASE, EPWM_COUNTER_COMPARE_A, (Batt1_Duty_Cycle)*BIDIRECTIONAL_PWM_PRD); //Bidirectional 1 Duty Cycle
            EPWM_setCounterCompareValue(Bidirectional2_BASE, EPWM_COUNTER_COMPARE_A, (Batt2_Duty_Cycle)*BIDIRECTIONAL_PWM_PRD); //Bidirectional 2 Duty Cycle
        }
        else
        {
            // First Duty Cycle Calculation to avoid overcurrent from battery
            EPWM_setCounterCompareValue(Bidirectional1_BASE, EPWM_COUNTER_COMPARE_A, (stringINV_DCDC_VS_Batt_sensed_FILTER)/(stringINV_ACDC_vDC_sensed_FILTER+3.0f)*BIDIRECTIONAL_PWM_PRD); //Bidirectional 1 Duty Cycle
            EPWM_setCounterCompareValue(Bidirectional2_BASE, EPWM_COUNTER_COMPARE_A, (stringINV_DCDC_VS_Batt_sensed_FILTER)/(stringINV_ACDC_vDC_sensed_FILTER+3.0f)*BIDIRECTIONAL_PWM_PRD); //Bidirectional 2 Duty Cycle
            Batt1_Duty_Cycle= (Batt1_Duty_Cycle > 1.0f) ? 1.0f : Batt1_Duty_Cycle;
            Batt1_Duty_Cycle = (Batt1_Duty_Cycle < 0.0f) ? 0.0f : Batt1_Duty_Cycle;
            Batt2_Duty_Cycle= (Batt2_Duty_Cycle > 1.0f) ? 1.0f : Batt2_Duty_Cycle;
            Batt2_Duty_Cycle = (Batt2_Duty_Cycle < 0.0f) ? 0.0f : Batt2_Duty_Cycle;
         }
    }

    if(stringINV_stop==1)
    {
        stringINV_Converter_Stop();
    }
}

#pragma FUNC_ALWAYS_INLINE(stringInverter_runISR1_lab_DCAC_OL) //LAB 6: DCAC Open-Loop
static inline void stringInverter_runISR1_lab_DCAC_OL()
{
    SPLL_1PH_SOGI_run(&stringINV_spll_1ph,
                      stringINV_ACDC_vAC_sensed_pu);

    RAMPGEN_run(&stringINV_ACDC_rgen);

    stringINV_ACDC_Index_Modulation = stringINV_ACDC_Amplitude*(__sinpuf32(stringINV_ACDC_rgen.out));

    if(stringINV_clearPWMTripDCAC == 1U)   // Start the machine!
    {
        if(stringINV_ACDC_Index_Modulation < 0.006 && stringINV_ACDC_Index_Modulation >= -0.006) /////
                {
                    stringINV_clearPWMTripDCAC = 0;
                    stringINV_updateDutyDCAC=1;
                    EPWM_clearTripZoneFlag(DCAC1_BASE, EPWM_TZ_INTERRUPT |EPWM_TZ_FLAG_OST);
                    EPWM_clearTripZoneFlag(DCAC2_BASE, EPWM_TZ_INTERRUPT |EPWM_TZ_FLAG_OST);
                }
            }

    if(stringINV_updateDutyDCAC == 1U)
    {
        stringINV_DCAC_Modulation();
    }

    //Date Logger
    stringINV_ACDC_dVal1 = (stringINV_spll_1ph.sine);
    stringINV_ACDC_dVal2 = stringINV_ACDC_vAC_sensed ;
    stringINV_ACDC_dVal3 = stringINV_ACDC_iAC_sensed;
    stringINV_ACDC_dVal4 = stringINV_ACDC_Index_Modulation;
    DLOG_4CH_run(&stringINV_ACDC_dLog1);
}

#pragma FUNC_ALWAYS_INLINE(stringInverter_runISR1_lab_DCAC_CL) //LAB 7: DCAC Close-Loop
static inline void stringInverter_runISR1_lab_DCAC_CL()
{
    RAMPGEN_run(&stringINV_ACDC_rgen);

    //Ramp current for grid current reference
    stringINV_IDCAC_Ref=stringINV_ACDC_iAC_real_Ref;
    stringINV_RAMP_IDCACREF();
    stringINV_ACDC_iAC_real_Ref_slewed=stringINV_IDCAC_Ref_Slewed;

    stringINV_ACDC_iAC_Ref_slewed =stringINV_ACDC_iAC_real_Ref_slewed*(__sinpuf32(stringINV_ACDC_rgen.out))+stringINV_ACDC_iAC_imag_Ref_slewed*(__cospuf32(stringINV_ACDC_rgen.out));

    if(stringINV_clearPWMTripDCAC == 1U)   // Start the machine!
    {

        if(stringINV_ACDC_iAC_Ref_slewed < 0.006 && stringINV_ACDC_iAC_Ref_slewed >= -0.006) /////
        {
            stringINV_clearPWMTripDCAC = 0;
            stringINV_updateDutyDCAC=1;
            EPWM_clearTripZoneFlag(DCAC1_BASE, EPWM_TZ_INTERRUPT |EPWM_TZ_FLAG_OST);
            EPWM_clearTripZoneFlag(DCAC2_BASE, EPWM_TZ_INTERRUPT |EPWM_TZ_FLAG_OST);
        }
    }

    if(stringINV_updateDutyDCAC == 1U)
    {
        string_ACDC_CurrentControl();
        stringINV_DCAC_Modulation();

    }
    //Date Logger
    stringINV_ACDC_dVal1 = (stringINV_spll_1ph.sine);
    stringINV_ACDC_dVal2 = stringINV_ACDC_vAC_sensed ;
    stringINV_ACDC_dVal3 = stringINV_ACDC_iAC_sensed;
    stringINV_ACDC_dVal4 = stringINV_ACDC_Index_Modulation;
    DLOG_4CH_run(&stringINV_ACDC_dLog1);
}


#pragma FUNC_ALWAYS_INLINE(stringInverter_runISR1_lab_DCAC_CL_PLLandGrid) //LAB 8: DCAC Close-Loop with PLL and Grid connected
static inline void stringInverter_runISR1_lab_DCAC_CL_PLLandGrid()
{
    SPLL_1PH_SOGI_run(&stringINV_spll_1ph,
                      stringINV_ACDC_vAC_sensed_pu);


        //Ramp current for grid current reference
        stringINV_IDCAC_Ref=stringINV_ACDC_iAC_real_Ref;
        stringINV_RAMP_IDCACREF();
        stringINV_ACDC_iAC_real_Ref_slewed=stringINV_IDCAC_Ref_Slewed;

        stringINV_ACDC_iAC_Ref_slewed =stringINV_ACDC_iAC_real_Ref_slewed*(stringINV_spll_1ph.sine)+stringINV_ACDC_iAC_imag_Ref_slewed*(stringINV_spll_1ph.cosine);

     if(stringINV_clearPWMTripDCAC == 1U)   // Start the machine!
            {

        if(stringINV_ACDC_vAC_sensed_FILTER< 2 && stringINV_ACDC_vAC_sensed_FILTER >= -2) //
        {
            stringINV_clearPWMTripDCAC = 0;
            stringINV_Counter=0;
            stringINV_updateDutyDCAC=1;
            EPWM_clearTripZoneFlag(DCAC1_BASE, EPWM_TZ_INTERRUPT |EPWM_TZ_FLAG_OST);
            EPWM_clearTripZoneFlag(DCAC2_BASE, EPWM_TZ_INTERRUPT |EPWM_TZ_FLAG_OST);
        }
     }

    if(stringINV_updateDutyDCAC == 1U)
    {

        string_ACDC_CurrentControl();
        stringINV_DCAC_Modulation();
    }

    //Date Logger
    stringINV_ACDC_dVal1 = (stringINV_spll_1ph.sine);
    stringINV_ACDC_dVal2 = stringINV_ACDC_vAC_sensed ;
    stringINV_ACDC_dVal3 = stringINV_ACDC_iAC_sensed;
    stringINV_ACDC_dVal4 = stringINV_ACDC_Index_Modulation;
    DLOG_4CH_run(&stringINV_ACDC_dLog1);
}

#pragma FUNC_ALWAYS_INLINE(stringInverter_runISR1_lab_DCAC_VoltageControl) //LAB 9: DCAC Close-Loop with PLL, Grid and Voltage control
static inline void stringInverter_runISR1_lab_DCAC_VoltageControl()
{
    SPLL_1PH_SOGI_run(&stringINV_spll_1ph,
                      stringINV_ACDC_vAC_sensed_pu);

        //Ramp generation for DC Bus Voltage reference
        stringINV_DCDC_vDC_Ref=stringINV_DCDC_VDCext_Ref;
        stringINV_RAMP_VDC();
        stringINV_DCDC_VDCext_Ref_Slewed=stringINV_DCDC_vDC_Ref_Slewed; //ramp VDC to reference

        if(stringINV_clearPWMTripDCAC == 1U)   // Start the machine!
            {

        if(stringINV_ACDC_vAC_sensed_FILTER< 2 && stringINV_ACDC_vAC_sensed_FILTER >= -2) //
        {
            stringINV_clearPWMTripDCAC = 0;
            stringINV_Counter=0;
            stringINV_updateDutyDCAC=1;
            EPWM_clearTripZoneFlag(DCAC1_BASE, EPWM_TZ_INTERRUPT |EPWM_TZ_FLAG_OST);
            EPWM_clearTripZoneFlag(DCAC2_BASE, EPWM_TZ_INTERRUPT |EPWM_TZ_FLAG_OST);
        }
            }

    if(stringINV_updateDutyDCAC == 1U)
    {
        string_DCBusVoltageControl();
        string_ACDC_CurrentControl();

        stringINV_DCAC_Modulation();

        //Enable the protections for AC grid and DC bus undervoltage
        if(stringINV_Counter_Faults<20000000)
        {
            stringINV_Counter_Faults++;
        }
        else
        {
            stringINV_enableUVFaults=1;
        }


        if(stringINV_DCAC_Counter_Disable_FFW<20000)
        {
             stringINV_DCAC_Counter_Disable_FFW++;
        }
        else
        {
             gv_ACDC_pi.Umax = 33;
             gv_ACDC_pi.Umin = -33;
        }
    }
    //Date Logger
    stringINV_ACDC_dVal1 = (stringINV_spll_1ph.sine);
    stringINV_ACDC_dVal2 = stringINV_ACDC_vAC_sensed ;
    stringINV_ACDC_dVal3 = stringINV_ACDC_iAC_sensed;
    stringINV_ACDC_dVal4 = stringINV_ACDC_vDC_sensed;
    DLOG_4CH_run(&stringINV_ACDC_dLog1);
}

#endif /* STRINGINV_H_ */





