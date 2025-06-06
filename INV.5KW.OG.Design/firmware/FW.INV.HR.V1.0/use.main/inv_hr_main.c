// #############################################################################
//
//  FILE:   empty_driverlib_main.c
//
//! \addtogroup driver_example_list
//! <h1>Empty Project Example</h1>
//!
//! This example is an empty project setup for Driverlib development.
//!
//
// #############################################################################
//
//
//
// C2000Ware v5.04.00.00
//
// Copyright (C) 2024 Texas Instruments Incorporated - http://www.ti.com
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//   Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
//
//   Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the
//   distribution.
//
//   Neither the name of Texas Instruments Incorporated nor the names of
//   its contributors may be used to endorse or promote products derived
//   from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// $
// #############################################################################

//
// Included Files
//
#include "board.h"
#include "c2000ware_libraries.h"
#include "device.h"
#include "driverlib.h"

#include "DCLF32.h"
#include "Rampgen.h"
#include "dlog_4ch.h"
#include "power_meas_sine_analyzer.h"

#define AC_FREQ ((float32_t)50)                        // // Unit Hz
#define ISR_CONTROL_FREQUENCY_AC ((float32_t)30000.00) // synchronize with ISR

#define DCAC_PWM_PRD 1666

#pragma RETAIN(stringINV_ACDC_rgen)
#pragma RETAIN(stringINV_ACDC_Index_Modulation)
RAMPGEN stringINV_ACDC_rgen;
float32_t stringINV_ACDC_Index_Modulation;
float32_t stringINV_ACDC_Amplitude;

__interrupt void INT_myADC0_1_ISR(void);

void stringINV_globalVariablesInit(void);
void stringInverter_runISR1_lab_DCAC_OL(void);
void stringINV_DCAC_Modulation(void);
void string_vACVoltageControl(void);
void stringINV_RAMP_VAC(void);

uint16_t stringINV_clearPWMTripDCAC = 1U;
uint16_t stringINV_updateDutyDCAC = 0U;
float32_t zero_sine = 0.0000f;

volatile uint16_t myADC0Results = 0;
volatile uint16_t ADC_Current = 0;


/*****************************************************************/

#pragma RETAIN(stringINV_ACDC_vAC_sensed_pu)
float32_t stringINV_ACDC_vAC_sensed_pu;

#pragma RETAIN(stringINV_ACDC_vAC_sensed)
float32_t stringINV_ACDC_vAC_sensed;

#pragma RETAIN(stringINV_ACDC_vAC_sensed_FILTER)
float32_t stringINV_ACDC_vAC_sensed_FILTER;

#pragma RETAIN(stringINV_ACDC_vAC_RMS_FILTER)
float32_t stringINV_ACDC_vAC_RMS_FILTER;

#pragma RETAIN(stringINV_ACDC_iAC_sensed)
float32_t stringINV_ACDC_iAC_sensed;

#pragma RETAIN(stringINV_DCDC_vAC_loop_err)
#pragma RETAIN (stringINV_ACDC_vAC_real_Ref_OUT_PI)
#pragma RETAIN(stringINV_DCDC_VDCext_Ref)
#pragma RETAIN(stringINV_DCDC_VDCext_Ref_Slewed)

float32_t stringINV_DCDC_vAC_loop_err;
float32_t stringINV_ACDC_vAC_real_Ref_OUT_PI;
float32_t stringINV_DCDC_VDCext_Ref;
float32_t stringINV_DCDC_VDCext_Ref_Slewed;

// Slewed Reference and Outputs
#pragma RETAIN(stringINV_DCDC_vDC_Ref)
#pragma RETAIN(stringINV_DCDC_vDC_Ref_Slewed)

float32_t stringINV_DCDC_vDC_Ref;
float32_t stringINV_DCDC_vDC_Ref_Slewed;

void stringINV_readCurrentAndVoltageSignals(void);

#define stringINV_ADC_BIPOLAR_PU_SCALE_FACTOR (3.0518509e-5f) // Unipolar
#define stringINV_ACDC_vAC_MAX ((float32_t)395)               // Unit V
#define stringINV_ACDC_vAC_Offset ((float32_t)0.0)            // Unit V

#define stringINV_AC_FILTERING_CONSTANT_VS_INV     ((float32_t) 0.4665)   // Ts x 2 x pi x fcut Cut off frequency of 2 kHz (e-(50e-6*2*31415*2000))

#define stringINV_AC_FILTERING_CONSTANT_VS_INV_RMS     ((float32_t) 0.0003)   // Ts x 2 x pi x fcut Cut off frequency of 1 Hz (e-(50e-6*2*31415*1))
                     
//Slew Rate Control Boost Duty Cycle
#define ISR_CONTROL_FREQUENCY_AC_INVERSE 1.0 /ISR_CONTROL_FREQUENCY_AC

//Slew Rate Control DC Bus Voltage
#define stringINV_VOLTS_PER_SECOND_SLEW ((float32_t)10.0)// V/s
// Power meas library

//PI Controller ACDC Voltage
#define gv_ACDC_pi_KP ((float32_t)0.1)
#define gv_ACDC_pi_KI ((float32_t)0.00001)
#define gv_ACDC_pi_MAX ((float32_t)3)
#define gv_ACDC_pi_MIN ((float32_t)-3)

// DCL_PI gi_ACDC_pi = PI_DEFAULTS;
DCL_PI gv_ACDC_pi = PI_DEFAULTS;

POWER_MEAS_SINE_ANALYZER stringINV_mains_L1;

/*****************************************************************/

void sine_wave(void);
void PID_sine(void);

uint32_t Check_clock = 0;
uint16_t val_table_sine = 0;
uint8_t flag_table_sine = 0;
float32_t val_amp_sine = 0.8f;
uint16_t mesure_adc = 0;
/*
uint16_t table_sine[300] = {60,70,81,90, 100, 110, 120, 130, 140, 160, 176, 192,
208, 224, 240, 256, 271, 287, 303, 319, 334, 350, 365, 381, 397, 412, 428, 443,
458, 474, 489, 504, 519, 535, 550, 565, 580, 595, 609, 624, 639, 654, 668, 683,
697, 712, 726, 740, 754, 769, 783, 797, 810, 824, 838, 851, 865, 878, 892, 905,
918, 931, 944, 957, 970, 982, 995, 1007, 1020, 1032, 1044, 1056, 1068, 1080,
1091, 1103, 1114, 1126, 1137, 1148, 1159, 1170, 1180, 1191, 1201, 1212, 1222,
1232, 1242, 1252, 1261, 1271, 1280, 1290, 1299, 1308, 1317, 1325, 1334, 1342,
1351, 1359, 1367, 1375, 1382, 1390, 1397, 1404, 1411, 1418, 1425, 1432, 1438,
1445, 1451, 1457, 1463, 1468, 1474, 1479, 1485, 1490, 1495, 1499, 1504, 1508,
1513, 1517, 1521, 1524, 1528, 1531, 1535, 1538, 1541, 1543, 1546, 1548, 1551,
1553, 1555, 1557, 1558, 1560, 1561, 1562, 1563, 1564, 1564, 1565, 1565, 1565,
1565, 1565, 1564, 1564, 1563, 1562, 1561, 1560, 1558, 1557, 1555, 1553, 1551,
1548, 1546, 1543, 1541, 1538, 1535, 1531, 1528, 1524, 1521, 1517, 1513, 1508,
1504, 1499, 1495, 1490, 1485, 1479, 1474, 1468, 1463, 1457, 1451, 1445, 1438,
1432, 1425, 1418, 1411, 1404, 1397, 1390, 1382, 1375, 1367, 1359, 1351, 1342,
1334, 1325, 1317, 1308, 1299, 1290, 1280, 1271, 1261, 1252, 1242, 1232, 1222,
1212, 1201, 1191, 1180, 1170, 1159, 1148, 1137, 1126, 1114, 1103, 1091, 1080,
1068, 1056, 1044, 1032, 1020, 1007, 995, 982, 970, 957, 944, 931, 918, 905, 892,
878, 865, 851, 838, 824, 810, 797, 783, 769, 754, 740, 726, 712, 697, 683, 668,
654, 639, 624, 609, 595, 580, 565, 550, 535, 519, 504, 489, 474, 458, 443, 428,
412, 397, 381, 365, 350, 334, 319, 303, 287, 271, 256, 240, 224, 208, 192, 176,
160, 145, 129, 113, 97, 81,70};
*/

uint16_t table_sine[300] = {
    60,   77,   94,   110,  127,  144,  161,  178,  194,  211,  228,  244,
    261,  278,  294,  311,  328,  344,  361,  377,  394,  410,  427,  443,
    459,  475,  492,  508,  524,  540,  556,  572,  588,  604,  619,  635,
    651,  666,  682,  697,  713,  728,  743,  759,  774,  789,  804,  818,
    833,  848,  863,  877,  891,  906,  920,  934,  948,  962,  976,  990,
    1003, 1017, 1030, 1044, 1057, 1070, 1083, 1096, 1109, 1121, 1134, 1146,
    1159, 1171, 1183, 1195, 1207, 1218, 1230, 1241, 1253, 1264, 1275, 1286,
    1297, 1307, 1318, 1328, 1338, 1349, 1358, 1368, 1378, 1387, 1397, 1406,
    1415, 1424, 1433, 1441, 1450, 1458, 1466, 1474, 1482, 1490, 1498, 1505,
    1512, 1519, 1526, 1533, 1540, 1546, 1552, 1558, 1564, 1570, 1576, 1581,
    1586, 1592, 1596, 1601, 1606, 1610, 1615, 1619, 1623, 1626, 1630, 1633,
    1637, 1640, 1643, 1645, 1648, 1650, 1652, 1654, 1656, 1658, 1659, 1661,
    1662, 1663, 1664, 1664, 1665, 1665, 1665, 1665, 1665, 1664, 1664, 1663,
    1662, 1661, 1659, 1658, 1656, 1654, 1652, 1650, 1648, 1645, 1643, 1640,
    1637, 1633, 1630, 1626, 1623, 1619, 1615, 1610, 1606, 1601, 1596, 1592,
    1586, 1581, 1576, 1570, 1564, 1558, 1552, 1546, 1540, 1533, 1526, 1519,
    1512, 1505, 1498, 1490, 1482, 1474, 1466, 1458, 1450, 1441, 1433, 1424,
    1415, 1406, 1397, 1387, 1378, 1368, 1358, 1349, 1338, 1328, 1318, 1307,
    1297, 1286, 1275, 1264, 1253, 1241, 1230, 1218, 1207, 1195, 1183, 1171,
    1159, 1146, 1134, 1121, 1109, 1096, 1083, 1070, 1057, 1044, 1030, 1017,
    1003, 990,  976,  962,  948,  934,  920,  906,  891,  877,  862,  848,
    833,  818,  804,  789,  774,  759,  743,  728,  713,  697,  682,  666,
    651,  635,  619,  604,  588,  572,  556,  540,  524,  508,  492,  475,
    459,  443,  427,  410,  394,  377,  361,  344,  328,  311,  294,  278,
    261,  244,  228,  211,  194,  178,  161,  144,  127,  110,  94,   77};

//
// Main
//
void main(void) {

  //
  // Initialize device clock and peripherals
  //
  Device_init();
  Check_clock = SysCtl_getClock(DEVICE_OSCSRC_FREQ);
  //
  // Disable pin locks and enable internal pull-ups.
  //
  Device_initGPIO();

  //
  // Initialize PIE and clear PIE registers. Disables CPU interrupts.
  //
  Interrupt_initModule();

  //
  // Initialize the PIE vector table with pointers to the shell Interrupt
  // Service Routines (ISR).
  //
  Interrupt_initVectorTable();

  //
  // PinMux and Peripheral Initialization
  //
  Board_init();

  //
  // C2000Ware Library initialization
  //
  C2000Ware_libraries_init();

  //
  // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
  //
  // config Global
  stringINV_globalVariablesInit();

  /*****************************************************************************
   *  DEAD_BAND = 800ns = 1/(200Mhz/1/1) * 80(valua set) * 2(DBRED:80, DBFED:80)
   **
   ****************************************************************************/

  EINT;
  ERTM;

  while (1) {
    GPIO_togglePin(41);
    DEVICE_DELAY_US(500000);
  }
}

__interrupt void INT_myADC0_1_ISR(void) {

  GPIO_togglePin(58);
  // if (stringINV_ACDC_Index_Modulation >= (stringINV_ACDC_Amplitude - 0.005f))
  // {
  //   myADC0Results = ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER0);

  //   ADC_Current = ADC_readResult(ADCCRESULT_BASE, ADC_SOC_NUMBER1);
  // }
  // PID_sine();
  // sine_wave();

  stringINV_readCurrentAndVoltageSignals();

  stringInverter_runISR1_lab_DCAC_OL();

  ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1);

  if (true == ADC_getInterruptOverflowStatus(myADC0_BASE, ADC_INT_NUMBER1)) {

    ADC_clearInterruptOverflowStatus(myADC0_BASE, ADC_INT_NUMBER1);
    ADC_clearInterruptStatus(myADC0_BASE, ADC_INT_NUMBER1);
  }

  Interrupt_clearACKGroup(INT_myADC0_1_INTERRUPT_ACK_GROUP);
}

void stringInverter_runISR1_lab_DCAC_OL(void) {
  // SPLL_1PH_SOGI_run(&stringINV_spll_1ph,
  //                   stringINV_ACDC_vAC_sensed_pu);

  stringINV_DCDC_vDC_Ref = stringINV_DCDC_VDCext_Ref;
  stringINV_RAMP_VAC();
  stringINV_DCDC_VDCext_Ref_Slewed =
      stringINV_DCDC_vDC_Ref_Slewed; // ramp VDC to reference

  if (stringINV_clearPWMTripDCAC == 1U) // Start the machine!
  {
    if (stringINV_ACDC_Index_Modulation < 0.006 &&
        stringINV_ACDC_Index_Modulation >= -0.006) /////
    {
      stringINV_clearPWMTripDCAC = 0;
      stringINV_updateDutyDCAC = 1;
      // EPWM_clearTripZoneFlag(DCAC1_BASE, EPWM_TZ_INTERRUPT
      // |EPWM_TZ_FLAG_OST); EPWM_clearTripZoneFlag(DCAC2_BASE,
      // EPWM_TZ_INTERRUPT |EPWM_TZ_FLAG_OST);
    }
  }

  if (stringINV_updateDutyDCAC == 1U) {

    string_vACVoltageControl();
    stringINV_DCAC_Modulation();
  }
}

void stringINV_DCAC_Modulation(void) {
  // HERIC

  if (stringINV_ACDC_Index_Modulation >= zero_sine) //
  {
    EPWM_setCounterCompareValue(myEPWM2_BASE, EPWM_COUNTER_COMPARE_A,
                                stringINV_ACDC_Index_Modulation * DCAC_PWM_PRD);

    EPWM_setCounterCompareValue(myEPWM1_BASE, EPWM_COUNTER_COMPARE_A, 0);
  }

  // else if (stringINV_ACDC_Index_Modulation < zero_sine &&
  //          stringINV_ACDC_Index_Modulation >= 0)
  // {
  //   EPWM_setCounterCompareValue(myEPWM1_BASE, EPWM_COUNTER_COMPARE_A, 72);
  //   EPWM_setCounterCompareValue(myEPWM2_BASE, EPWM_COUNTER_COMPARE_A, 0);
  // } else if (stringINV_ACDC_Index_Modulation >= -zero_sine &&
  //            stringINV_ACDC_Index_Modulation < 0) {

  //   EPWM_setCounterCompareValue(myEPWM1_BASE, EPWM_COUNTER_COMPARE_A, 0);
  //   EPWM_setCounterCompareValue(myEPWM2_BASE, EPWM_COUNTER_COMPARE_A, 72);
  // }
  // if (stringINV_stop == 1) {
  //   stringINV_Converter_Stop();
  // }

  else {
    EPWM_setCounterCompareValue(myEPWM2_BASE, EPWM_COUNTER_COMPARE_A, 0);
    EPWM_setCounterCompareValue(myEPWM1_BASE, EPWM_COUNTER_COMPARE_A,
                                -stringINV_ACDC_Index_Modulation *
                                    DCAC_PWM_PRD);
  }
}

void stringINV_globalVariablesInit(void) {

  // PI control VDC
  stringINV_DCDC_VDCext_Ref = 220.0f;
  stringINV_DCDC_vAC_loop_err = 0;
  stringINV_DCDC_VDCext_Ref_Slewed = 0;

//PI controllers parameters used by the DC/AC
    // gi_ACDC_pi.Kp = gi_ACDC_pi_KP;
    // gi_ACDC_pi.Ki = gi_ACDC_pi_KI;
    // gi_ACDC_pi.Umax = gi_ACDC_pi_MAX;
    // gi_ACDC_pi.Umin = gi_ACDC_pi_MIN;

    gv_ACDC_pi.Kp =  gv_ACDC_pi_KP;
    gv_ACDC_pi.Ki = gv_ACDC_pi_KI;
    gv_ACDC_pi.Umax = gv_ACDC_pi_MAX;
    gv_ACDC_pi.Umin = gv_ACDC_pi_MIN;

  // String Inverter DC/AC Portion Open Loop Variables
  stringINV_ACDC_Index_Modulation = 0.0f;
  stringINV_ACDC_Amplitude = 0.86636f;

  // It generates a triangular signal for cosphi and sinphi String Inverter

  RAMPGEN_config(&stringINV_ACDC_rgen, ISR_CONTROL_FREQUENCY_AC, AC_FREQ);

  RAMPGEN_reset(&stringINV_ACDC_rgen);
}

void sine_wave(void) {

  val_table_sine++;
  if (val_table_sine >= 300) {
    val_table_sine = 0;
    flag_table_sine++;
    if (flag_table_sine >= 2) {
      flag_table_sine = 0;
    }
  }
  switch (flag_table_sine) {

  case 0:
    EPWM_setCounterCompareValue(myEPWM1_BASE, EPWM_COUNTER_COMPARE_A,
                                table_sine[val_table_sine] * val_amp_sine);
    EPWM_setCounterCompareValue(myEPWM2_BASE, EPWM_COUNTER_COMPARE_A, 0);

    break;
  case 1:
    EPWM_setCounterCompareValue(myEPWM2_BASE, EPWM_COUNTER_COMPARE_A,
                                table_sine[val_table_sine] * val_amp_sine);
    EPWM_setCounterCompareValue(myEPWM1_BASE, EPWM_COUNTER_COMPARE_A, 0);
    break;
  }
}

void PID_sine(void) {

  mesure_adc = 1000 + myADC0Results;
  if (mesure_adc < 2145) {
    val_amp_sine = val_amp_sine + 0.000005f;

  } else if (mesure_adc > 2155) {
    val_amp_sine = val_amp_sine - 0.000005f;
  } else {
    val_amp_sine = val_amp_sine;
  }

  if (val_amp_sine > 1.0f) {
    val_amp_sine = 1.0f;
  } else if (val_amp_sine < 0.0f) {
    val_amp_sine = 0.0f;
  } else {
    val_amp_sine = val_amp_sine;
  }
}

void stringINV_readCurrentAndVoltageSignals(void) {

  stringINV_ACDC_vAC_sensed_pu =
      ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER0) *
          stringINV_ADC_BIPOLAR_PU_SCALE_FACTOR -
      1.0f; // Bipolar Measurement
  stringINV_ACDC_vAC_sensed =
      stringINV_ACDC_vAC_sensed_pu * stringINV_ACDC_vAC_MAX +
      stringINV_ACDC_vAC_Offset;

  stringINV_ACDC_vAC_sensed_FILTER =
      stringINV_AC_FILTERING_CONSTANT_VS_INV *
          (-stringINV_ACDC_vAC_sensed_FILTER + stringINV_ACDC_vAC_sensed) +
      stringINV_ACDC_vAC_sensed_FILTER;

  stringINV_ACDC_vAC_RMS_FILTER =
      stringINV_AC_FILTERING_CONSTANT_VS_INV_RMS *
          (-stringINV_ACDC_vAC_RMS_FILTER + stringINV_mains_L1.vRms) +
      stringINV_ACDC_vAC_RMS_FILTER;
  // stringINV_ACDC_vDC_sensed_NOTCH =
  //     DCL_runDF22_C4(&VDC_NOTCH_FILTER_2_Fe,
  //     stringINV_ACDC_vDC_sensed_FILTER);

  // Power measurement library
  stringINV_mains_L1.v = stringINV_ACDC_vAC_sensed;
  stringINV_mains_L1.i = stringINV_ACDC_iAC_sensed;
}

void stringINV_RAMP_VAC(void)
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


void string_vACVoltageControl() {
  stringINV_DCDC_vAC_loop_err =
      stringINV_DCDC_VDCext_Ref_Slewed - stringINV_ACDC_vAC_sensed_FILTER;
  stringINV_ACDC_vAC_real_Ref_OUT_PI =
      DCL_runPI_C2(&gv_ACDC_pi, stringINV_DCDC_vAC_loop_err, 0);
  // stringINV_ACDC_iAC_Ref_slewed =
  //     stringINV_ACDC_vAC_real_Ref_OUT_PI * (stringINV_spll_1ph.sine) +
  //     stringINV_ACDC_iAC_imag_Ref * (stringINV_spll_1ph.cosine);

  RAMPGEN_run(&stringINV_ACDC_rgen);

  stringINV_ACDC_Index_Modulation =
      (stringINV_ACDC_vAC_real_Ref_OUT_PI/3) * (__sinpuf32(stringINV_ACDC_rgen.out));
}

// set
// myGPIO0
//  End of File
//
