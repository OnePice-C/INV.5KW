//##############################################################################
//
// FILE:  stringINV_settings.h
//
// TITLE: Settings for the string inverter
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

#ifndef STRINGINV_SETTINGS_H_
#define STRINGINV_SETTINGS_H_
//

#define CLK_FREQ        (150000000)

///User-defined settings

//Select the test lab to be used
#define SINV_LAB 2

//Select the modulation scheme here : 1 for HERIC, 2 for Bipolar, 3 for Unipolar
#define stringINV_DCAC_Modulation_Scheme 1

//Lab settings
#if SINV_LAB == 1
#define stringINV_DCDC_CS_Batt_Ref_init (0.0f)
#define stringINV_stop_only_DCAC (0)
#endif

#if SINV_LAB == 2
#define stringINV_DCDC_CS_Batt_Ref_init (0.0f)
#define stringINV_stop_only_DCAC (0)
#endif

#if SINV_LAB == 3
#define MPPTEnable (1)
#define stringINV_DCDC_CS_Batt_Ref_init (0.0f)
#define stringINV_stop_only_DCAC (0)
#endif

#if SINV_LAB == 4
#define stringINV_DCDC_CS_Batt_Ref_init (0.0f)
#define stringINV_stop_only_DCAC (0)
#endif

#if SINV_LAB == 5
#define stringINV_DCDC_CS_Batt_Ref_init (0.5f)
#define stringINV_stop_only_DCAC (0)
#endif

#if SINV_LAB == 6
#define stringINV_DCDC_CS_Batt_Ref_init (0.0f)
#define stringINV_stop_only_DCAC (0)
#endif

#if SINV_LAB == 7
#define stringINV_DCDC_CS_Batt_Ref_init (0.0f)
#define stringINV_stop_only_DCAC (0)
#endif

#if SINV_LAB == 8
#define stringINV_DCDC_CS_Batt_Ref_init (0.0f)
#define stringINV_stop_only_DCAC (0)
#endif

#if SINV_LAB == 9
#define stringINV_DCDC_CS_Batt_Ref_init (0.0f)
#define stringINV_stop_only_DCAC (0)
#endif

#if SINV_LAB == 10
#define MPPTEnable (1)
#define stringINV_DCDC_CS_Batt_Ref_init (0.0f)
#define stringINV_stop_only_DCAC (1)
#endif

#if SINV_LAB == 11
#define MPPTEnable (1)
#define stringINV_DCDC_CS_Batt_Ref_init (1.0f)
#define stringINV_stop_only_DCAC (1)
#endif

//Virtual Data Logger
#define stringINV_ACDC_DLOG_SIZE      (100)
#define stringINV_ACDC_DLOG_TRIGGER   ((float32_t)0.01)
#define stringINV_ACDC_DLOG_SCALE     (10)

#define stringINV_ACDC_DLOG_SIZE_OSC2      (100)
#define stringINV_ACDC_DLOG_SCALE_OSC2     (10)
//

// Temperature Measurements String inverter
#define stringINV_GaN_Temp_Scaling      (6000U)   // take a measurements of the duty cycle every 0.00005 seconds.
#define stringINV_GaN_Temp_Coefficient     ((float32_t)162.3)   //
#define stringINV_GaN_Temp_Offset     ((float32_t)20.1)   //

//String inverter scaling of the measurements and setting of the protections
#define stringINV_ADC_UNIPOLAR_PU_SCALE_FACTOR (0.000244140625f) //Unipolar scaling factor
#define stringINV_ADC_BIPOLAR_PU_SCALE_FACTOR (0.00048828125f) //Unipolar scaling factor*2

//AC-DC
#define stringINV_ACDC_vDC_MAX     ((float32_t) 554)   // Unit V
#define stringINV_ACDC_vDC_Offset     ((float32_t) -0.825)   // Unit V

#define stringINV_ACDC_vAC_MAX     ((float32_t) 495) // Unit V
#define stringINV_ACDC_vAC_Offset     ((float32_t) 0.0) // Unit V

#define stringINV_ACDC_vINV_MAX     ((float32_t) 495)   // Unit V
#define stringINV_ACDC_vINV_Offset     ((float32_t) 0.0) // Unit V

#define stringINV_ACDC_iAC_MAX     ((float32_t) 62)  // Unit A //TMCS1123B1
#define stringINV_ACDC_iAC_Offset     ((float32_t) 0.0)

//DC-DC
#define stringINV_DCDC_CS_Boost1_MAX     ((float32_t) 22) // Unit A
#define stringINV_DCDC_CS_Boost1_Offset     ((float32_t) -0.016) // Unit A

#define stringINV_DCDC_VS_Boost1_MAX     ((float32_t) 554) // Unit V
#define stringINV_DCDC_VS_Boost1_Offset     ((float32_t) -0.33) // Unit V

#define stringINV_DCDC_CS_Boost2_MAX     ((float32_t) 22) // Unit A
#define stringINV_DCDC_CS_Boost2_Offset     ((float32_t) -0.016) // Unit A

#define stringINV_DCDC_VS_Boost2_MAX     ((float32_t) 554) // Unit V
#define stringINV_DCDC_VS_Boost2_Offset     ((float32_t) -0.165) // Unit V

#define stringINV_DCDC_CS_Batt1_MAX     ((float32_t) 26.83) // Unit A
#define stringINV_DCDC_CS_Batt1_Offset     ((float32_t) 0.0) // Unit A

#define stringINV_DCDC_CS_Batt2_MAX     ((float32_t) 26.83) // Unit A
#define stringINV_DCDC_CS_Batt2_Offset     ((float32_t) 0.0) // Unit A

#define stringINV_DCDC_VS_Batt_MAX     ((float32_t) 554) // Unit A
#define stringINV_DCDC_VS_Batt_Offset     ((float32_t) 0.0) // Unit A

#define stringINV_DCDC_vDC_MAX     ((float32_t) 554)   // Unit V
#define stringINV_DCDC_vDC_Offset     ((float32_t) 0.0)   // Unit V

#define stringINV_ACDC_vDC_TRIP_LIMIT_V    ((float32_t) 520.0 )  // Unit V
#define stringINV_ACDC_vDC_TRIP_MIN_V    ((float32_t) 340.0)  // Unit V

#define stringINV_ACDC_vAC_TRIP_MAX_V    ((float32_t) 250.0)  // Unit V
#define stringINV_ACDC_vAC_TRIP_MIN_V    ((float32_t) 180.0)  // Unit V

#define stringINV_TempLimit ((float32_t) 125 )  // Unit deg. C

#define stringINV_ACDC_iAC_TRIP_AMPS    ((float32_t) 35)  // Unit A
#define stringINV_ACDC_iAC_TRIP_AMPS_POS    ((int16_t)(2048+abs(2048*stringINV_ACDC_iAC_TRIP_AMPS/stringINV_ACDC_iAC_MAX)))  // Unit A
#define stringINV_ACDC_iAC_TRIP_AMPS_NEG    ((int16_t)(2048-abs(2048*stringINV_ACDC_iAC_TRIP_AMPS/stringINV_ACDC_iAC_MAX)))  // Unit A

#define stringINV_ACDC_CS_Batt_TRIP_AMPS    ((float32_t) 25)  // Unit A
#define stringINV_ACDC_CS_Batt_TRIP_AMPS_POS    ((int16_t)(2048+abs(2048*stringINV_ACDC_CS_Batt_TRIP_AMPS/stringINV_DCDC_CS_Batt1_MAX)))  // Unit A
#define stringINV_ACDC_CS_Batt_TRIP_AMPS_NEG    ((int16_t)(2048-abs(2048*stringINV_ACDC_CS_Batt_TRIP_AMPS/stringINV_DCDC_CS_Batt1_MAX)))  // Unit A

#define stringINV_ACDC_CS_Boost_TRIP_AMPS    ((float32_t) 20)  // Unit A
#define stringINV_ACDC_CS_Boost_TRIP_AMPS_HIGH    ((int16_t)(abs(4096*stringINV_ACDC_CS_Boost_TRIP_AMPS/stringINV_DCDC_CS_Boost1_MAX)))  // Unit A
#define stringINV_ACDC_CS_Boost_TRIP_AMPS_LOW    ((int16_t)(abs(4096*stringINV_ACDC_CS_Boost_TRIP_AMPS/stringINV_DCDC_CS_Boost1_MAX)))  // Unit A

//Filter constants
#define stringINV_TEMP_FILTERING_CONSTANT     ((float32_t) 0.0309)   // Ts x 2 x pi x fcut Cut off frequency

#define stringINV_DC_FILTERING_CONSTANT_VS_BOOST     ((float32_t) 0.4665)   // Ts x 2 x pi x fcut Cut off frequency of 2 kHz (e-(50e-6*2*3.1415*2000))
#define stringINV_DC_FILTERING_CONSTANT_VS_BATT     ((float32_t) 0.0309)   // Ts x 2 x pi x fcut Cut off frequency of 2 kHz (e-(50e-6*2*3.1415*2000))
#define stringINV_DC_FILTERING_CONSTANT_VDC     ((float32_t) 0.4665)   // Ts x 2 x pi x fcut Cut off frequency of 2 kHz (e-(50e-6*2*3.1415*2000))

#define stringINV_DC_FILTERING_CONSTANT_CS_BOOST     ((float32_t) 0.4665)   // Ts x 2 x pi x fcut Cut off frequency of 2 kHz (e-(50e-6*2*3.1415*2000))

#define stringINV_AC_FILTERING_CONSTANT_VS_INV     ((float32_t) 0.4665)   // Ts x 2 x pi x fcut Cut off frequency of 2 kHz (e-(50e-6*2*3.1415*2000))

#define stringINV_AC_FILTERING_CONSTANT_VS_INV_RMS     ((float32_t) 0.0003)   // Ts x 2 x pi x fcut Cut off frequency of 1 Hz (e-(50e-6*2*3.1415*1))

//Grid and controller parameters
#define AC_FREQ    ((float32_t) 50)   // // Unit Hz
#define ISR_CONTROL_FREQUENCY_AC ((float32_t) 22321.43) //synchronize with ISR to get grid frequency // Unit Hz

//String Inverter SOGI-PLL coefficients
#define stringINV_SPLL_COEFF_B0      ((float32_t)166.974338481427)
#define stringINV_SPLL_COEFF_B1      ((float32_t)-166.26611653716)
#define stringINV_SPLL_COEFF_K1     ((float32_t) 0.00188141)
#define stringINV_SPLL_COEFF_K2      ((float32_t)-0.99623717)

//PI Controller ACDC Current
#define gi_ACDC_pi_KP ((float32_t)2.1865)  //2*pi*2000*(87*2) (10% ISR freq)
#define gi_ACDC_pi_KI ((float32_t)0.001) // Kp*2*pi*2000*0.1/ISR freq steps i.e 20000   0.1374
#define gi_ACDC_pi_MAX ((float32_t)100)  // Updated Values
#define gi_ACDC_pi_MIN ((float32_t)-100)  // Updated Values

//PI Controller ACDC Voltage
#define gv_ACDC_pi_KP ((float32_t)0.1)
#define gv_ACDC_pi_KI ((float32_t)0.00001)
#define gv_ACDC_pi_MAX ((float32_t)3)
#define gv_ACDC_pi_MIN ((float32_t)-3)

//PI Controller Battery 1&2
#define gi_DCDC_pi_KP ((float32_t)1)  //Updated values //update to 1
#define gi_DCDC_pi_KI ((float32_t)0.1) // Updated Values //update to 0.1
#define gi_DCDC_pi_MAX ((float32_t)400)  // Updated Values
#define gi_DCDC_pi_MIN ((float32_t)-400)  // Updated Values

//PI Controller MPPT
#define gv_VBoost_pi_KP ((float32_t)0.001)//
#define gv_VBoost_pi_KI ((float32_t)0.014)//
#define gv_VBoost_pi_MAX ((float32_t)1)  //
#define gv_VBoost_pi_MIN ((float32_t)0)  //

//COEFF PR Controllers Beginning
#define  KPI_1H  ((float32_t)0.5)
#define  KII_1H ((float32_t)3500)
#define  WRCI_1H ((float32_t)0.4)
#define  KII_3H ((float32_t)3500)
#define  WRCI_3H ((float32_t)0.4)
#define  KII_5H ((float32_t)3500)
#define  WRCI_5H ((float32_t)0.4)
#define  KII_7H ((float32_t)3500)
#define  WRCI_7H ((float32_t)0.4)
#define  KII_9H ((float32_t)3500)
#define  WRCI_9H ((float32_t)0.4)
#define  KII_11H ((float32_t)3500)
#define  WRCI_11H ((float32_t)0.4)
#define  KII_13H ((float32_t)3500)
#define  WRCI_13H ((float32_t)0.4)
#define  KII_15H ((float32_t)3500)
#define  WRCI_15H ((float32_t)0.4)
#define  KII_17H ((float32_t)3500)
#define  WRCI_17H ((float32_t)0.4)

//MPPT
#define stringINV_DCDC_MPPT_DCDC_PNO_MAX_V        ((float32_t)500.0f)
#define stringINV_DCDC_MPPT_DCDC_PNO_MIN_V        ((float32_t)2.0f)
#define stringINV_DCDC_MPPT_DCDC_PNO_STEPSIZE     ((float32_t)0.05f)
#define stringINV_DCDC_MPPT_DCDC_PNO_DELTAPMIN    ((float32_t)0.01f)

#define stringINV_DCDC_MPPT_COUNTER_THR ((uint32_t)1000)

//Limitation in the duty cycles
#define  stringINV_Index_Modulation_HIGH_PU 0.98f
#define  stringINV_Index_Modulation_LOW_PU -0.98f

//Slew Rate Control Boost Duty Cycle
#define ISR_CONTROL_FREQUENCY_AC_INVERSE 1.0 /ISR_CONTROL_FREQUENCY_AC

//Slew Rate Control DC Bus Voltage
#define stringINV_VOLTS_PER_SECOND_SLEW ((float32_t)20.0)// V/s

//Slew Rate Control Boost Duty Cycle final
#define stringINV_D_PER_SECOND_SLEW ((float32_t)0.1)// 0.1/s

//Slew Rate Control Current Battery 1 & 2 final
#define stringINV_AMPS_PER_SECOND_SLEW ((float32_t)0.25) // 1A/s

#endif /* STRINGINV_SETTINGS_H_ */
