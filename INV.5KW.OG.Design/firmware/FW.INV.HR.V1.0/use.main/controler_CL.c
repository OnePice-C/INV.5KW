/*
    date: 16/06/2025

    file Closed-loop control 

    Mode AC to DC and DC to AC

*/

#include "controler_CL.h"


#pragma RETAIN(INV_DCAC_vAC_sensed_pu)
float32_t INV_DCAC_vAC_sensed_pu;

#pragma RETAIN(INV_DCAC_vAC_Conv)
float32_t INV_DCAC_vAC_Conv;

#pragma RETAIN(INV_DCAC_vAC_sensed_FILTER)
float32_t INV_DCAC_vAC_sensed_FILTER;

#pragma RETAIN(INV_DCAC_vAC_RMS_FILTER)
float32_t INV_DCAC_vAC_RMS_FILTER;

#pragma RETAIN(INV_DCAC_iAC_sensed_pu)
float32_t INV_DCAC_iAC_sensed_pu;

#pragma RETAIN(INV_DCAC_iAC_Conv)
float32_t INV_DCAC_iAC_Conv;

#pragma RETAIN(INV_DCAC_vAC_loop_err)
#pragma RETAIN (INV_DCAC_vAC_OUT_Err)
#pragma RETAIN(INV_DCDC_VDCext_Ref)
#pragma RETAIN(INV_DCDC_VDCext_Ref_Slewed)

float32_t INV_DCAC_vAC_loop_err;
float32_t INV_DCAC_vAC_OUT_Err;
float32_t INV_DCDC_VDCext_Ref;
float32_t INV_DCDC_VDCext_Ref_Slewed;

// Slewed Reference and Outputs
#pragma RETAIN(INV_DCDC_vDC_Ref)
#pragma RETAIN(INV_DCDC_vDC_Ref_Slewed)

float32_t INV_DCDC_vDC_Ref;
float32_t INV_DCDC_vDC_Ref_Slewed;

#pragma RETAIN (INV_DCAC_vDC_sensed_NOTCH)
float32_t INV_DCAC_vDC_sensed_NOTCH;

//PLL
#pragma RETAIN (INV_reset_PLL)
#pragma RETAIN (INV_spll_1ph)

int32_t INV_reset_PLL;
SPLL_1PH_SOGI INV_spll_1ph;


float32_t zero_sine = 0.000f;
uint16_t INV_clearPWMTripDCAC = 1U;
uint16_t INV_updateDutyDCAC = 0U;

uint16_t vAC_Sum_Value = 0;
uint16_t iAC_Sum_Value = 0;
volatile float32_t INV_Sum_vAC_pu = 0;
volatile float32_t INV_Average_vAC_pu = 0;
volatile float32_t INV_Sum_iAC_pu = 0;
volatile float32_t INV_Average_iAC_pu = 0;
float32_t Check_Old_Adc = 0;

/******************Tets variable ****** */



/*********************************** */

// DCL_PI gi_ACDC_pi = PI_DEFAULTS;
DCL_PI gv_ACDC_pi = PI_DEFAULTS;

POWER_MEAS_SINE_ANALYZER INV_mains_L1;

DCL_DF22 VDC_NOTCH_FILTER_2_Fe= DF22_DEFAULTS;


volatile float32_t INV_DCAC_iAC_Heric_Sensor = 0;

//source controler closed-loop

void INV_globalVariablesInit(void) {

    // PI control VDC
    INV_DCDC_VDCext_Ref = 50.0f;
    INV_DCAC_vAC_loop_err = 0;
    INV_DCDC_VDCext_Ref_Slewed = 0;

    // PI controllers parameters used by the DC/AC
    // gi_ACDC_pi.Kp = gi_ACDC_pi_KP;
    // gi_ACDC_pi.Ki = gi_ACDC_pi_KI;
    // gi_ACDC_pi.Umax = gi_ACDC_pi_MAX;
    // gi_ACDC_pi.Umin = gi_ACDC_pi_MIN;

    gv_ACDC_pi.Kp =  gv_ACDC_pi_KP;
    gv_ACDC_pi.Ki = gv_ACDC_pi_KI;
    gv_ACDC_pi.Umax = gv_ACDC_pi_MAX;
    gv_ACDC_pi.Umin = gv_ACDC_pi_MIN;

    // String Inverter DC/AC Portion Open Loop Variables
    INV_DCAC_Index_Modulation = 0.0f;
    INV_DCAC_Amplitude = 0.86636f;
    // Set variables Out PI 
    INV_DCAC_vAC_OUT_Err = 0;

    // It generates a triangular signal for cosphi and sinphi String Inverter

    RAMPGEN_config(&INV_DCAC_rgen, ISR_CONTROL_FREQUENCY_AC, AC_FREQ);

    RAMPGEN_reset(&INV_DCAC_rgen);

    // POWER_MEAS_SINE_ANALYZER_reset(&INV_mains_L1);

    // POWER_MEAS_SINE_ANALYZER_config(&INV_mains_L1,
    //                               ISR_CONTROL_FREQUENCY_AC,
    //                               (float32_t)10.0f,
    //                               (float32_t)55.0f,
    //                               (float32_t)45.0f);

    //Initialization of the variables of the PLL String Inverter

    // INV_reset_PLL=0;

    SPLL_1PH_SOGI_reset(&INV_spll_1ph);

    SPLL_1PH_SOGI_config(&INV_spll_1ph,
                              AC_FREQ,
                              ISR_CONTROL_FREQUENCY_AC,
                              INV_SPLL_COEFF_B0,
                              INV_SPLL_COEFF_B1);

    SPLL_1PH_SOGI_coeff_calc(&INV_spll_1ph);                              

                                
}


void INV_readCurrentAndVoltageSignals(void) {

#if MODE_ACDC_DCAC == 1

    INV_DCAC_vAC_Heric_Sensor = ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER0);

    INV_DCAC_vAC_sensed_pu = 
    (INV_DCAC_vAC_Heric_Sensor * INV_ADC_BIPOLAR_PU_SCALE_FACTOR - 1.00f); // Bipolar Measurement


#elif MODE_ACDC_DCAC == 2

    // Read Current
    //
    if((__sinpuf32(INV_DCAC_rgen.out)) >= 0.0000f) {
    
        if(Check_Old_Adc < 0.0000f){

            INV_Average_iAC_pu = sqrtf(INV_Sum_iAC_pu / iAC_Sum_Value);
            INV_DCAC_iAC_Conv = ((INV_Average_iAC_pu * 25.0000f*1.1311f) + INV_DCAC_iAC_Conv_Offset);

            if(INV_Average_iAC_pu > 10.0f){

                // Over current Protection
            }

            iAC_Sum_Value = 0;
            INV_Sum_iAC_pu = 0;

        }
    }

    INV_DCAC_iAC_Heric_Sensor = (ADC_readResult(ADCCRESULT_BASE, ADC_SOC_NUMBER1));
    // (kalman_filter(ADC_readResult(ADCCRESULT_BASE, ADC_SOC_NUMBER1))*0.00003051756f - 1.0f);
    INV_DCAC_iAC_sensed_pu = ((INV_DCAC_iAC_Heric_Sensor * INV_ADC_BIPOLAR_PU_SCALE_FACTOR) - 1.0f);

    INV_Sum_iAC_pu += ((INV_DCAC_iAC_sensed_pu * INV_DCAC_iAC_sensed_pu));
    iAC_Sum_Value++;


    // Read Voltage AC
    //
    if((__sinpuf32(INV_DCAC_rgen.out)) >= 0.000f) {

        if(Check_Old_Adc < 0.000f){
            
            INV_Average_vAC_pu = (sqrtf(INV_Sum_vAC_pu / vAC_Sum_Value));
            INV_DCAC_vAC_Conv = (INV_Average_vAC_pu * 435.7840f) + INV_DCAC_vAC_Conv_Offset;
            
            if(INV_DCAC_vAC_Conv >= 260){

                // Over voltage protection
            }

            INV_Sum_vAC_pu = 0;
            vAC_Sum_Value = 0;
        }
    }

    INV_DCAC_vAC_Heric_Sensor = ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER0);
    // INV_DCAC_vAC_Heric_Sensor_1 = kalman_filter(ADC_readResult(ADCBRESULT_BASE, ADC_SOC_NUMBER0));  
    INV_DCAC_vAC_sensed_pu = INV_DCAC_vAC_Heric_Sensor * INV_ADC_BIPOLAR_PU_SCALE_FACTOR - 1.0f; // Bipolar Measurement

    // Sum Voltage and Current
    //
    vAC_Sum_Value++;
    INV_Sum_vAC_pu += (INV_DCAC_vAC_sensed_pu * INV_DCAC_vAC_sensed_pu);

#else
#error undefine MODE_ACDC_DCAC
#endif

    // INV_DCAC_vAC_sensed =
    //     INV_DCAC_vAC_sensed_pu * INV_DCAC_vAC_MAX + INV_DCAC_vAC_Offset;

    // INV_DCAC_vAC_sensed_FILTER =
    //     INV_AC_FILTERING_CONSTANT_VS_INV * (-INV_DCAC_vAC_sensed_FILTER + INV_DCAC_vAC_sensed) +INV_DCAC_vAC_sensed_FILTER;

    // INV_DCAC_vAC_RMS_FILTER =
    //     INV_AC_FILTERING_CONSTANT_VS_INV_RMS * (-INV_DCAC_vAC_RMS_FILTER + INV_mains_L1.vRms) +
    //           INV_DCAC_vAC_RMS_FILTER;
          
    // INV_DCAC_vDC_sensed_NOTCH =
    //     DCL_runDF22_C4(&VDC_NOTCH_FILTER_2_Fe,
    //     INV_DCAC_vAC_RMS_FILTER);

    // Power measurement library
    //
    // INV_mains_L1.v = INV_DCAC_vAC_sensed; 
    // INV_mains_L1.i = INV_DCAC_iAC_sensed_pu;
}

void INV_RAMP_VAC(void)
{
    if((INV_DCDC_vDC_Ref - INV_DCDC_vDC_Ref_Slewed) > (2 * INV_VOLTS_PER_SECOND_SLEW) *
            (ISR_CONTROL_FREQUENCY_AC_INVERSE))
    {
        INV_DCDC_vDC_Ref_Slewed =  INV_DCDC_vDC_Ref_Slewed + (INV_VOLTS_PER_SECOND_SLEW) *
            (ISR_CONTROL_FREQUENCY_AC_INVERSE);
    }
    else if((INV_DCDC_vDC_Ref - INV_DCDC_vDC_Ref_Slewed) < -(2 * INV_VOLTS_PER_SECOND_SLEW) *
            (ISR_CONTROL_FREQUENCY_AC_INVERSE))
    {
        INV_DCDC_vDC_Ref_Slewed =  INV_DCDC_vDC_Ref_Slewed - (INV_VOLTS_PER_SECOND_SLEW) *
            (ISR_CONTROL_FREQUENCY_AC_INVERSE);
    }
    else
    {
        INV_DCDC_vDC_Ref_Slewed =  INV_DCDC_vDC_Ref;
    }
}


void INV_DCAC_Modulation(void) {
    
    // HERIC
    if(INV_DCAC_Index_Modulation >=0.9400f)  {                 // max: 0.95500f
      
        INV_DCAC_Index_Modulation = 0.9400f;}
    
    else if (INV_DCAC_Index_Modulation <= (-0.9400f))  {       // min: -0.95500f
    
        INV_DCAC_Index_Modulation = -0.9400f;}

    if (INV_DCAC_Index_Modulation >= zero_sine) { // Check cycle sine, set zero == 0
    
        EPWM_setCounterCompareValue(myEPWM2_BASE, EPWM_COUNTER_COMPARE_A,
                                    INV_DCAC_Index_Modulation * DCAC_PWM_PRD);

        EPWM_setCounterCompareValue(myEPWM1_BASE, EPWM_COUNTER_COMPARE_A, 0);
    }

    // else if (INV_DCAC_Index_Modulation < zero_sine &&
    //          INV_DCAC_Index_Modulation >= 0)
    // {
    //   EPWM_setCounterCompareValue(myEPWM1_BASE, EPWM_COUNTER_COMPARE_A, 72);
    //   EPWM_setCounterCompareValue(myEPWM2_BASE, EPWM_COUNTER_COMPARE_A, 0);
    // } else if (INV_DCAC_Index_Modulation >= -zero_sine &&
    //            INV_DCAC_Index_Modulation < 0) {

    //   EPWM_setCounterCompareValue(myEPWM1_BASE, EPWM_COUNTER_COMPARE_A, 0);
    //   EPWM_setCounterCompareValue(myEPWM2_BASE, EPWM_COUNTER_COMPARE_A, 72);
    // }
    // if (INV_stop == 1) {
    //   INV_Converter_Stop();
    // }

    else {

        EPWM_setCounterCompareValue(myEPWM2_BASE, EPWM_COUNTER_COMPARE_A, 0);
        EPWM_setCounterCompareValue(myEPWM1_BASE, EPWM_COUNTER_COMPARE_A,
                                  -INV_DCAC_Index_Modulation * DCAC_PWM_PRD);
    }
}


void INV_runISR1_lab_DCAC_CL(void) {

    RAMPGEN_run(&INV_DCAC_rgen);

    INV_DCAC_Index_Modulation = 0.8 * (__sinpuf32(INV_DCAC_rgen.out));


    //  (INV_DCAC_vAC_OUT_Err/3) * (__sinpuf32(INV_DCAC_rgen.out));
    //  INV_DCAC_Amplitude * (__sinpuf32(INV_DCAC_rgen.out));
    
    /*************** use to Control PI ******************* */ 

    INV_DCDC_vDC_Ref = INV_DCDC_VDCext_Ref;
    INV_RAMP_VAC();
    INV_DCDC_VDCext_Ref_Slewed = INV_DCDC_vDC_Ref_Slewed; // ramp VDC to reference

    /*****************************************************************************/

    if (INV_clearPWMTripDCAC == 1U) {     // Start the machine!
    
        if (INV_DCAC_Index_Modulation < 0.006 && INV_DCAC_Index_Modulation >= -0.006) {   

            INV_clearPWMTripDCAC = 0;
            INV_updateDutyDCAC = 1;
            // EPWM_clearTripZoneFlag(DCAC1_BASE, EPWM_TZ_INTERRUPT
            // |EPWM_TZ_FLAG_OST); EPWM_clearTripZoneFlag(DCAC2_BASE,
            // EPWM_TZ_INTERRUPT |EPWM_TZ_FLAG_OST);
        }
    }

    if (INV_updateDutyDCAC == 1U) {

        INV_DCAC_Modulation();

    }
}

void INV_runISR1_lab_ACDC_CL(void) {

    SPLL_1PH_SOGI_run(&INV_spll_1ph,
                      INV_DCAC_vAC_sensed_pu);

    INV_DCAC_Index_Modulation = 0.50856f * (INV_spll_1ph.sine);
    
    if (INV_clearPWMTripDCAC == 1U) { // Start the machine!

        if (INV_DCAC_Index_Modulation < 0.006 && INV_DCAC_Index_Modulation >= -0.006) { /////
      
            INV_clearPWMTripDCAC = 0;
            INV_updateDutyDCAC = 1;
            // EPWM_clearTripZoneFlag(DCAC1_BASE, EPWM_TZ_INTERRUPT
            // |EPWM_TZ_FLAG_OST); EPWM_clearTripZoneFlag(DCAC2_BASE,
            // EPWM_TZ_INTERRUPT |EPWM_TZ_FLAG_OST);
        }
    }

    if (INV_updateDutyDCAC == 1U) {

        INV_DCAC_Modulation();
    }
}

void INV_vACVoltageControl_PI() {

    INV_DCAC_vAC_loop_err =
        INV_DCDC_VDCext_Ref_Slewed - INV_DCAC_vAC_sensed_FILTER;

    INV_DCAC_vAC_OUT_Err =
        (DCL_runPI_C2(&gv_ACDC_pi, INV_DCAC_vAC_loop_err, 0))/5;
}

void INV_vACVoltageControl_Basic() {

    if(__sinpuf32(INV_DCAC_rgen.out) < 0.000f) {

         if(Check_Old_Adc >= 0.000f) {

            // 0.4845 ~ 212 VAC, 0.573 ~250VAC            
            INV_DCAC_vAC_loop_err = ((INV_DCAC_Set_Real_vAC_RMS + INV_DCAC_vAC_Real_RMS_Offset)/436.3001f) - INV_Average_vAC_pu; 
            
            // Hysteresis window
            //
            if (INV_DCAC_vAC_loop_err > -0.0010f && INV_DCAC_vAC_loop_err < 0.0010f) {
                INV_DCAC_vAC_OUT_Err = INV_DCAC_vAC_OUT_Err;
            }
            else {
                INV_DCAC_vAC_OUT_Err += (INV_DCAC_vAC_loop_err / Soft_Start); // Result control loop error
            }
            
            // Sine waveform Max-Min Limit
            //
            if(INV_DCAC_vAC_OUT_Err >= 0.9400f) {      // max: 0.9550
                INV_DCAC_vAC_OUT_Err = 0.9400f;
            }
            else if(INV_DCAC_vAC_OUT_Err <= 0.0000f) { 
                INV_DCAC_vAC_OUT_Err = 0.0000f;
            }
        }
    }

    Check_Old_Adc = INV_DCAC_Index_Modulation; // Save the value of sine before updating  the new value
}

float32_t kalman_filter(float32_t ADC_Value) {

	float x_k1_k1, x_k_k1;
//	static float ADC_OLD_Value;
	float Z_k;
	static float P_k1_k1;

	// Q: Nhiễu điều chỉnh, Q tăng, phản ứng động trở nên nhanh hơn và độ ổn định hội tụ trở nên kém hơn
	static float Q = 0.00001;

	// R: Kiểm tra tiếng ồn, R tăng, phản ứng động trở nên chậm hơn, độ ổn định hội tụ trở nên tốt hơn
	static float R = 0.01851;
	static float Kg = 0;
	static float P_k_k1 = 1;

	float kalman_adc;
	static float kalman_adc_old = 0;
	Z_k = ADC_Value;
	x_k1_k1 = kalman_adc_old;

	x_k_k1 = x_k1_k1;
	P_k_k1 = P_k1_k1 + Q;

	Kg = P_k_k1 / (P_k_k1 + R);

	kalman_adc = x_k_k1 + Kg * (Z_k - kalman_adc_old);
	P_k1_k1 = (1 - Kg) * P_k_k1;
	P_k_k1 = P_k1_k1;

//	ADC_OLD_Value = ADC_Value;
	kalman_adc_old = kalman_adc;

	return kalman_adc;
}
