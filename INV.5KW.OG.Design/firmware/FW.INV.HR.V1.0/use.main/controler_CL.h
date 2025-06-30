#ifndef _CONTROLER_CL_H
#define _CONTROLER_CL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "board.h"
#include "c2000ware_libraries.h"
#include "device.h"
#include "driverlib.h"

#include "DCLF32.h"
#include "Rampgen.h"
#include "dlog_4ch.h"
#include "power_meas_sine_analyzer.h"
#include "spll_1ph_sogi.h"


void INV_globalVariablesInit(void);
void INV_runISR1_lab_DCAC_CL(void);
void INV_runISR1_lab_ACDC_CL(void);
void INV_DCAC_Modulation(void);
void INV_vACVoltageControl_PI(void);
void INV_vACVoltageControl_Basic(void);
void INV_RAMP_VAC(void);
void INV_readCurrentAndVoltageSignals(void);


float32_t kalman_filter(float32_t ADC_Value);


#define AC_FREQ ((float32_t)50.5)                        // // Unit Hz
#define ISR_CONTROL_FREQUENCY_AC ((float32_t)30000.00) // synchronize with ISR

#define DCAC_PWM_PRD 1666

//String Inverter SOGI-PLL coefficients
#define INV_SPLL_COEFF_B0      ((float32_t)166.974338481427)
#define INV_SPLL_COEFF_B1      ((float32_t)-166.26611653716)
// #define INV_SPLL_COEFF_K1     ((float32_t) 0.00188141)
// #define INV_SPLL_COEFF_K2      ((float32_t)-0.99623717)

#define INV_ADC_BIPOLAR_PU_SCALE_FACTOR (0.000030517578125f) // Bipolar (1/65536)*2
#define INV_DCAC_vAC_MAX ((float32_t)311.0f)            // Unit V
#define INV_DCAC_vAC_Offset ((float32_t)-9.7f)          // Unit V

#define INV_AC_FILTERING_CONSTANT_VS_INV     ((float32_t) 0.4665)   // Ts x 2 x pi x fcut Cut off frequency of 2 kHz (e-(50e-6*2*31415*2000))

#define INV_AC_FILTERING_CONSTANT_VS_INV_RMS     ((float32_t) 0.0003)   // Ts x 2 x pi x fcut Cut off frequency of 1 Hz (e-(50e-6*2*31415*1))

#define INV_DCAC_Set_Real_vAC_RMS        ((float32_t)230.0f)     // RMS voltage value setting
#define INV_DCAC_vAC_Real_RMS_Offset     ((float32_t)-0.2f)      // RMS value offset

#define Soft_Start                  ((float32_t)20.0000f)   // Soft start and voltage regulation

#define INV_DCAC_vAC_Conv_Offset    ((float32_t)0.0f)
#define INV_DCAC_iAC_Conv_Offset    ((float32_t)-0.1418f)

//Slew Rate Control Boost Duty Cycle
#define ISR_CONTROL_FREQUENCY_AC_INVERSE 1.0 /ISR_CONTROL_FREQUENCY_AC

//Slew Rate Control DC Bus Voltage
#define INV_VOLTS_PER_SECOND_SLEW ((float32_t)25.0)// V/s
// Power meas library

//PI Controller ACDC Voltage
#define gv_ACDC_pi_KP ((float32_t)0.0504)
#define gv_ACDC_pi_KI ((float32_t)0.00005)
#define gv_ACDC_pi_MAX ((float32_t)5)
#define gv_ACDC_pi_MIN ((float32_t)-5)

// voltage control mode: 1 - PI ; 2 - Basic
#define SINV_CTL_VOL 2
// control mode: 1 - mode AC to DC ; 2 - mode - DC to AC
#define MODE_ACDC_DCAC 2

extern float32_t INV_DCAC_Index_Modulation;
extern float32_t INV_DCAC_Amplitude;
extern RAMPGEN INV_DCAC_rgen;

extern volatile float32_t INV_DCAC_vAC_Heric_Sensor;
extern volatile float32_t INV_DCAC_vAC_Heric_Sensor_1;

extern POWER_MEAS_SINE_ANALYZER INV_mains_L1;


#ifdef __cplusplus
}
#endif // extern "C"

#endif 

/* end of file */
