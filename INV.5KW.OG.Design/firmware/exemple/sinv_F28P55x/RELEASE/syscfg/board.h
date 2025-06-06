/*
 * Copyright (c) 2020 Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef BOARD_H
#define BOARD_H

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//
// Included Files
//

#include "driverlib.h"
#include "device.h"

//*****************************************************************************
//
// PinMux Configurations
//
//*****************************************************************************

//
// ANALOG -> myANALOGPinMux0 Pinmux
//

//
// EPWM4 -> BOOST Pinmux
//
//
// EPWM4_A - GPIO Settings
//
#define GPIO_PIN_EPWM4_A 6
#define BOOST_EPWMA_GPIO 6
#define BOOST_EPWMA_PIN_CONFIG GPIO_6_EPWM4_A
//
// EPWM4_B - GPIO Settings
//
#define GPIO_PIN_EPWM4_B 23
#define BOOST_EPWMB_GPIO 23
#define BOOST_EPWMB_PIN_CONFIG GPIO_23_EPWM4_B

//
// EPWM1 -> DCAC1 Pinmux
//
//
// EPWM1_A - GPIO Settings
//
#define GPIO_PIN_EPWM1_A 0
#define DCAC1_EPWMA_GPIO 0
#define DCAC1_EPWMA_PIN_CONFIG GPIO_0_EPWM1_A
//
// EPWM1_B - GPIO Settings
//
#define GPIO_PIN_EPWM1_B 1
#define DCAC1_EPWMB_GPIO 1
#define DCAC1_EPWMB_PIN_CONFIG GPIO_1_EPWM1_B

//
// EPWM2 -> DCAC2 Pinmux
//
//
// EPWM2_A - GPIO Settings
//
#define GPIO_PIN_EPWM2_A 2
#define DCAC2_EPWMA_GPIO 2
#define DCAC2_EPWMA_PIN_CONFIG GPIO_2_EPWM2_A
//
// EPWM2_B - GPIO Settings
//
#define GPIO_PIN_EPWM2_B 3
#define DCAC2_EPWMB_GPIO 3
#define DCAC2_EPWMB_PIN_CONFIG GPIO_3_EPWM2_B

//
// EPWM5 -> Bidirectional1 Pinmux
//
//
// EPWM5_A - GPIO Settings
//
#define GPIO_PIN_EPWM5_A 8
#define Bidirectional1_EPWMA_GPIO 8
#define Bidirectional1_EPWMA_PIN_CONFIG GPIO_8_EPWM5_A
//
// EPWM5_B - GPIO Settings
//
#define GPIO_PIN_EPWM5_B 9
#define Bidirectional1_EPWMB_GPIO 9
#define Bidirectional1_EPWMB_PIN_CONFIG GPIO_9_EPWM5_B

//
// EPWM6 -> Bidirectional2 Pinmux
//
//
// EPWM6_A - GPIO Settings
//
#define GPIO_PIN_EPWM6_A 10
#define Bidirectional2_EPWMA_GPIO 10
#define Bidirectional2_EPWMA_PIN_CONFIG GPIO_10_EPWM6_A
//
// EPWM6_B - GPIO Settings
//
#define GPIO_PIN_EPWM6_B 11
#define Bidirectional2_EPWMB_GPIO 11
#define Bidirectional2_EPWMB_PIN_CONFIG GPIO_11_EPWM6_B
//
// GPIO62 - GPIO Settings
//
#define RY_ACPreCharge_GPIO_PIN_CONFIG GPIO_62_GPIO62
//
// GPIO57 - GPIO Settings
//
#define RY_DCPreCharge_GPIO_PIN_CONFIG GPIO_57_GPIO57
//
// GPIO56 - GPIO Settings
//
#define Enable_Buffer_ACDC_GPIO_PIN_CONFIG GPIO_56_GPIO56
//
// GPIO55 - GPIO Settings
//
#define Enable_Buffer_DCDC_GPIO_PIN_CONFIG GPIO_55_GPIO55
//
// GPIO58 - GPIO Settings
//
#define Enable_CAN_GPIO_PIN_CONFIG GPIO_58_GPIO58
//
// GPIO61 - GPIO Settings
//
#define Enable_RS485_GPIO_PIN_CONFIG GPIO_61_GPIO61
//
// GPIO34 - GPIO Settings
//
#define TEMP_MUX_A_GPIO_PIN_CONFIG GPIO_34_GPIO34
//
// GPIO40 - GPIO Settings
//
#define TEMP_MUX_B_GPIO_PIN_CONFIG GPIO_40_GPIO40
//
// GPIO44 - GPIO Settings
//
#define TEMP_MUX_C_GPIO_PIN_CONFIG GPIO_44_GPIO44
//
// GPIO60 - GPIO Settings
//
#define TPGPIO24_GPIO_PIN_CONFIG GPIO_60_GPIO60
//
// GPIO52 - GPIO Settings
//
#define LED_FAULT_GPIO_PIN_CONFIG GPIO_52_GPIO52
//
// GPIO53 - GPIO Settings
//
#define LED_HEARTBEAT_GPIO_PIN_CONFIG GPIO_53_GPIO53

//*****************************************************************************
//
// ADC Configurations
//
//*****************************************************************************
#define ADC_A_BASE ADCA_BASE
#define ADC_A_RESULT_BASE ADCARESULT_BASE
#define SOC_CS_Batt2 ADC_SOC_NUMBER0
#define SOC_CS_Batt2_FORCE ADC_FORCE_SOC0
#define SOC_CS_Batt2_ADC_BASE ADCA_BASE
#define SOC_CS_Batt2_RESULT_BASE ADCARESULT_BASE
#define SOC_CS_Batt2_SAMPLE_WINDOW 100
#define SOC_CS_Batt2_TRIGGER_SOURCE ADC_TRIGGER_EPWM5_SOCA
#define SOC_CS_Batt2_CHANNEL ADC_CH_ADCIN3
#define SOC_CS_Boost1 ADC_SOC_NUMBER1
#define SOC_CS_Boost1_FORCE ADC_FORCE_SOC1
#define SOC_CS_Boost1_ADC_BASE ADCA_BASE
#define SOC_CS_Boost1_RESULT_BASE ADCARESULT_BASE
#define SOC_CS_Boost1_SAMPLE_WINDOW 100
#define SOC_CS_Boost1_TRIGGER_SOURCE ADC_TRIGGER_EPWM5_SOCA
#define SOC_CS_Boost1_CHANNEL ADC_CH_ADCIN11
#define SOC_VS_Boost2 ADC_SOC_NUMBER2
#define SOC_VS_Boost2_FORCE ADC_FORCE_SOC2
#define SOC_VS_Boost2_ADC_BASE ADCA_BASE
#define SOC_VS_Boost2_RESULT_BASE ADCARESULT_BASE
#define SOC_VS_Boost2_SAMPLE_WINDOW 100
#define SOC_VS_Boost2_TRIGGER_SOURCE ADC_TRIGGER_EPWM5_SOCA
#define SOC_VS_Boost2_CHANNEL ADC_CH_ADCIN27
#define SOC_VS_Batt ADC_SOC_NUMBER3
#define SOC_VS_Batt_FORCE ADC_FORCE_SOC3
#define SOC_VS_Batt_ADC_BASE ADCA_BASE
#define SOC_VS_Batt_RESULT_BASE ADCARESULT_BASE
#define SOC_VS_Batt_SAMPLE_WINDOW 100
#define SOC_VS_Batt_TRIGGER_SOURCE ADC_TRIGGER_EPWM5_SOCA
#define SOC_VS_Batt_CHANNEL ADC_CH_ADCIN6
#define SOC_VS_Boost1 ADC_SOC_NUMBER4
#define SOC_VS_Boost1_FORCE ADC_FORCE_SOC4
#define SOC_VS_Boost1_ADC_BASE ADCA_BASE
#define SOC_VS_Boost1_RESULT_BASE ADCARESULT_BASE
#define SOC_VS_Boost1_SAMPLE_WINDOW 100
#define SOC_VS_Boost1_TRIGGER_SOURCE ADC_TRIGGER_EPWM5_SOCA
#define SOC_VS_Boost1_CHANNEL ADC_CH_ADCIN9
#define SOC_Vbus_DCDC ADC_SOC_NUMBER5
#define SOC_Vbus_DCDC_FORCE ADC_FORCE_SOC5
#define SOC_Vbus_DCDC_ADC_BASE ADCA_BASE
#define SOC_Vbus_DCDC_RESULT_BASE ADCARESULT_BASE
#define SOC_Vbus_DCDC_SAMPLE_WINDOW 100
#define SOC_Vbus_DCDC_TRIGGER_SOURCE ADC_TRIGGER_EPWM5_SOCA
#define SOC_Vbus_DCDC_CHANNEL ADC_CH_ADCIN28
void ADC_A_init();

#define ADC_B_BASE ADCB_BASE
#define ADC_B_RESULT_BASE ADCBRESULT_BASE
#define SOC_IAC ADC_SOC_NUMBER0
#define SOC_IAC_FORCE ADC_FORCE_SOC0
#define SOC_IAC_ADC_BASE ADCB_BASE
#define SOC_IAC_RESULT_BASE ADCBRESULT_BASE
#define SOC_IAC_SAMPLE_WINDOW 100
#define SOC_IAC_TRIGGER_SOURCE ADC_TRIGGER_EPWM5_SOCA
#define SOC_IAC_CHANNEL ADC_CH_ADCIN8
#define SOC_Vbus ADC_SOC_NUMBER1
#define SOC_Vbus_FORCE ADC_FORCE_SOC1
#define SOC_Vbus_ADC_BASE ADCB_BASE
#define SOC_Vbus_RESULT_BASE ADCBRESULT_BASE
#define SOC_Vbus_SAMPLE_WINDOW 100
#define SOC_Vbus_TRIGGER_SOURCE ADC_TRIGGER_EPWM5_SOCA
#define SOC_Vbus_CHANNEL ADC_CH_ADCIN26
void ADC_B_init();

#define ADC_C_BASE ADCC_BASE
#define ADC_C_RESULT_BASE ADCCRESULT_BASE
#define SOC_CS_Batt1 ADC_SOC_NUMBER0
#define SOC_CS_Batt1_FORCE ADC_FORCE_SOC0
#define SOC_CS_Batt1_ADC_BASE ADCC_BASE
#define SOC_CS_Batt1_RESULT_BASE ADCCRESULT_BASE
#define SOC_CS_Batt1_SAMPLE_WINDOW 100
#define SOC_CS_Batt1_TRIGGER_SOURCE ADC_TRIGGER_EPWM5_SOCA
#define SOC_CS_Batt1_CHANNEL ADC_CH_ADCIN1
#define SOC_VAC ADC_SOC_NUMBER1
#define SOC_VAC_FORCE ADC_FORCE_SOC1
#define SOC_VAC_ADC_BASE ADCC_BASE
#define SOC_VAC_RESULT_BASE ADCCRESULT_BASE
#define SOC_VAC_SAMPLE_WINDOW 100
#define SOC_VAC_TRIGGER_SOURCE ADC_TRIGGER_EPWM5_SOCA
#define SOC_VAC_CHANNEL ADC_CH_ADCIN6
void ADC_C_init();

#define ADC_D_BASE ADCD_BASE
#define ADC_D_RESULT_BASE ADCDRESULT_BASE
#define SOC_CS_Boost2 ADC_SOC_NUMBER0
#define SOC_CS_Boost2_FORCE ADC_FORCE_SOC0
#define SOC_CS_Boost2_ADC_BASE ADCD_BASE
#define SOC_CS_Boost2_RESULT_BASE ADCDRESULT_BASE
#define SOC_CS_Boost2_SAMPLE_WINDOW 100
#define SOC_CS_Boost2_TRIGGER_SOURCE ADC_TRIGGER_EPWM5_SOCA
#define SOC_CS_Boost2_CHANNEL ADC_CH_ADCIN15
void ADC_D_init();


//*****************************************************************************
//
// ASYSCTL Configurations
//
//*****************************************************************************

//*****************************************************************************
//
// CMPSS Configurations
//
//*****************************************************************************
#define myCMPSS_DCAC_BASE CMPSS2_BASE
#define myCMPSS_DCAC_HIGH_COMP_BASE CMPSS2_BASE    
#define myCMPSS_DCAC_LOW_COMP_BASE CMPSS2_BASE    
void myCMPSS_DCAC_init();
#define myCMPSS_Boost_BASE CMPSS1_BASE
#define myCMPSS_Boost_HIGH_COMP_BASE CMPSS1_BASE    
#define myCMPSS_Boost_LOW_COMP_BASE CMPSS1_BASE    
void myCMPSS_Boost_init();
#define myCMPSS_Bidir1_BASE CMPSS4_BASE
#define myCMPSS_Bidir1_HIGH_COMP_BASE CMPSS4_BASE    
#define myCMPSS_Bidir1_LOW_COMP_BASE CMPSS4_BASE    
void myCMPSS_Bidir1_init();
#define myCMPSS_Bidir2_BASE CMPSS3_BASE
#define myCMPSS_Bidir2_HIGH_COMP_BASE CMPSS3_BASE    
#define myCMPSS_Bidir2_LOW_COMP_BASE CMPSS3_BASE    
void myCMPSS_Bidir2_init();

//*****************************************************************************
//
// ECAP Configurations
//
//*****************************************************************************
#define myECAP0_BASE ECAP1_BASE
#define myECAP0_SIGNAL_MUNIT_BASE ECAP1SIGNALMONITORING_BASE
void myECAP0_init();
#define myECAP1_BASE ECAP2_BASE
#define myECAP1_SIGNAL_MUNIT_BASE ECAP2SIGNALMONITORING_BASE
void myECAP1_init();

//*****************************************************************************
//
// EPWM Configurations
//
//*****************************************************************************
#define BOOST_BASE EPWM4_BASE
#define BOOST_TBPRD 560
#define BOOST_COUNTER_MODE EPWM_COUNTER_MODE_UP_DOWN
#define BOOST_TBPHS 0
#define BOOST_CMPA 0
#define BOOST_CMPB 0
#define BOOST_CMPC 0
#define BOOST_CMPD 0
#define BOOST_DBRED 6
#define BOOST_DBFED 6
#define BOOST_TZA_ACTION EPWM_TZ_ACTION_HIGH_Z
#define BOOST_TZB_ACTION EPWM_TZ_ACTION_HIGH_Z
#define BOOST_INTERRUPT_SOURCE EPWM_INT_TBCTR_DISABLED
#define DCAC1_BASE EPWM1_BASE
#define DCAC1_TBPRD 840
#define DCAC1_COUNTER_MODE EPWM_COUNTER_MODE_UP_DOWN
#define DCAC1_TBPHS 0
#define DCAC1_CMPA 0
#define DCAC1_CMPB 0
#define DCAC1_CMPC 0
#define DCAC1_CMPD 0
#define DCAC1_DBRED 23
#define DCAC1_DBFED 23
#define DCAC1_TZA_ACTION EPWM_TZ_ACTION_HIGH_Z
#define DCAC1_TZB_ACTION EPWM_TZ_ACTION_HIGH_Z
#define DCAC1_INTERRUPT_SOURCE EPWM_INT_TBCTR_DISABLED
#define DCAC2_BASE EPWM2_BASE
#define DCAC2_TBPRD 840
#define DCAC2_COUNTER_MODE EPWM_COUNTER_MODE_UP_DOWN
#define DCAC2_TBPHS 0
#define DCAC2_CMPA 0
#define DCAC2_CMPB 0
#define DCAC2_CMPC 0
#define DCAC2_CMPD 0
#define DCAC2_DBRED 23
#define DCAC2_DBFED 23
#define DCAC2_TZA_ACTION EPWM_TZ_ACTION_HIGH_Z
#define DCAC2_TZB_ACTION EPWM_TZ_ACTION_HIGH_Z
#define DCAC2_INTERRUPT_SOURCE EPWM_INT_TBCTR_DISABLED
#define Bidirectional1_BASE EPWM5_BASE
#define Bidirectional1_TBPRD 1120
#define Bidirectional1_COUNTER_MODE EPWM_COUNTER_MODE_UP_DOWN
#define Bidirectional1_TBPHS 0
#define Bidirectional1_CMPA 0
#define Bidirectional1_CMPB 0
#define Bidirectional1_CMPC 0
#define Bidirectional1_CMPD 0
#define Bidirectional1_DBRED 21
#define Bidirectional1_DBFED 21
#define Bidirectional1_TZA_ACTION EPWM_TZ_ACTION_HIGH_Z
#define Bidirectional1_TZB_ACTION EPWM_TZ_ACTION_HIGH_Z
#define Bidirectional1_INTERRUPT_SOURCE EPWM_INT_TBCTR_DISABLED
#define Bidirectional2_BASE EPWM6_BASE
#define Bidirectional2_TBPRD 1120
#define Bidirectional2_COUNTER_MODE EPWM_COUNTER_MODE_UP_DOWN
#define Bidirectional2_TBPHS 1118
#define Bidirectional2_CMPA 0
#define Bidirectional2_CMPB 0
#define Bidirectional2_CMPC 0
#define Bidirectional2_CMPD 0
#define Bidirectional2_DBRED 21
#define Bidirectional2_DBFED 21
#define Bidirectional2_TZA_ACTION EPWM_TZ_ACTION_HIGH_Z
#define Bidirectional2_TZB_ACTION EPWM_TZ_ACTION_HIGH_Z
#define Bidirectional2_INTERRUPT_SOURCE EPWM_INT_TBCTR_DISABLED

//*****************************************************************************
//
// EPWMXBAR Configurations
//
//*****************************************************************************
void myEPWMXBAR0_init();
#define myEPWMXBAR0 XBAR_TRIP5
#define myEPWMXBAR0_ENABLED_MUXES (XBAR_MUX00)
void myEPWMXBAR1_init();
#define myEPWMXBAR1 XBAR_TRIP10
#define myEPWMXBAR1_ENABLED_MUXES (XBAR_MUX04 | XBAR_MUX06)
void myEPWMXBAR2_init();
#define myEPWMXBAR2 XBAR_TRIP12
#define myEPWMXBAR2_ENABLED_MUXES (XBAR_MUX02)

//*****************************************************************************
//
// GPIO Configurations
//
//*****************************************************************************
#define RY_ACPreCharge 62
void RY_ACPreCharge_init();
#define RY_DCPreCharge 57
void RY_DCPreCharge_init();
#define Enable_Buffer_ACDC 56
void Enable_Buffer_ACDC_init();
#define Enable_Buffer_DCDC 55
void Enable_Buffer_DCDC_init();
#define Enable_CAN 58
void Enable_CAN_init();
#define Enable_RS485 61
void Enable_RS485_init();
#define TEMP_MUX_A 34
void TEMP_MUX_A_init();
#define TEMP_MUX_B 40
void TEMP_MUX_B_init();
#define TEMP_MUX_C 44
void TEMP_MUX_C_init();
#define TPGPIO24 60
void TPGPIO24_init();
#define LED_FAULT 52
void LED_FAULT_init();
#define LED_HEARTBEAT 53
void LED_HEARTBEAT_init();

//*****************************************************************************
//
// INPUTXBAR Configurations
//
//*****************************************************************************
#define myINPUTXBARINPUT0_SOURCE 51
#define myINPUTXBARINPUT0_INPUT XBAR_INPUT1
void myINPUTXBARINPUT0_init();
#define myINPUTXBARINPUT1_SOURCE 58
#define myINPUTXBARINPUT1_INPUT XBAR_INPUT2
void myINPUTXBARINPUT1_init();
#define myINPUTXBARINPUT2_SOURCE 46
#define myINPUTXBARINPUT2_INPUT XBAR_INPUT7
void myINPUTXBARINPUT2_init();

//*****************************************************************************
//
// INTERRUPT Configurations
//
//*****************************************************************************

// Interrupt Settings for INT_ADC_A_1
// ISR need to be defined for the registered interrupts
#define INT_ADC_A_1 INT_ADCA1
#define INT_ADC_A_1_INTERRUPT_ACK_GROUP INTERRUPT_ACK_GROUP1
extern __interrupt void INT_ADC_A_1_ISR(void);

//*****************************************************************************
//
// SYNC Scheme Configurations
//
//*****************************************************************************

//*****************************************************************************
//
// SYSCTL Configurations
//
//*****************************************************************************

//*****************************************************************************
//
// Board Configurations
//
//*****************************************************************************
void	Board_init();
void	ADC_init();
void	ASYSCTL_init();
void	CMPSS_init();
void	ECAP_init();
void	EPWM_init();
void	EPWMXBAR_init();
void	GPIO_init();
void	INPUTXBAR_init();
void	INTERRUPT_init();
void	SYNC_init();
void	SYSCTL_init();
void	PinMux_init();

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif  // end of BOARD_H definition
