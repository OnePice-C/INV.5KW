//#############################################################################
//
// FILE:   stringINV_main.c
//
// TITLE: Main file for the solution
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
//
// Included Files
//
#include "driverlib.h"
#include "device.h"
#include "board.h"
#include "c2000ware_libraries.h"

#include <stringINV_settings.h>
#include "stringINV.h"

#include "DCLF32.h"
//

//
// Variable declarations for state machine
//
void (*Alpha_State_Ptr)(void);  // Base States pointer
void (*A_Task_Ptr)(void);       // State pointer A branch
void (*B_Task_Ptr)(void);       // State pointer B branch

//
// State Machine function prototypes
//------------------------------------
// Alpha states
//
void A0(void);  //state A0
void B0(void);  //state B0

//
// A branch states
//
void A1(void);  //state A1

//
// B branch states
//
void B1(void);  //state B1
void B2(void);  //state B2
void B3(void);  //state B3

//
// Main
//
void main(void)
{
    //
    // Initialize device clock and peripherals
    //
    Device_init();

    //
    // Disable pin locks and enable internal pull-ups.
    //
    Device_initGPIO();
    //
    // Tasks State-machine init
    //
    Alpha_State_Ptr = &A0;
    A_Task_Ptr = &A1;
    B_Task_Ptr = &B1;

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
    // Disable sync(Freeze clock to PWM as well). GTBCLKSYNC is applicable
    // only for multiple core devices. Uncomment the below statement if
    // applicable.
    //
    // SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_GTBCLKSYNC);
    SysCtl_disablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    DEVICE_DELAY_US(200000);
    //
    // PinMux and Peripheral Initialization
    //
    Board_init();

    stringINV_globalVariablesInit();

    stringINV_PeripheralInit();

    //
    // C2000Ware Library initialization
    //
    C2000Ware_libraries_init();

    // Enable sync and clock to PWM
    //
    SysCtl_enablePeripheral(SYSCTL_PERIPH_CLK_TBCLKSYNC);

    //
    // Enable Global Interrupt (INTM) and real time interrupt (DBGM)
    //
    EINT;
    ERTM;

    while(1)
    {
        //
        // State machine entry & exit point
        //
        (*Alpha_State_Ptr)();   // jump to an Alpha state (A0,B0,...)
    }
}

// Interrupt
__attribute__((ramfunc))
interrupt void INT_ADC_A_1_ISR(void)
{
    GPIO_writePin(TPGPIO24,1); //PIN SPI MISO Pin 4 of the control card
    ADC_clearInterruptStatus(ADC_A_BASE, ADC_INT_NUMBER1);

    stringINV_readCurrentAndVoltageSignals(); //Function to read analog measurements
    stringINV_Fault_Read(); //Function to read faults

    //Run labs for string inverter here
#if SINV_LAB == 1

    stringInverter_runISR1_lab_ADC_PWM();
    //
    //Run this to check PWMs
    //
#elif SINV_LAB == 2
    //
    //Run this to operate boost converters open-loop
    //
    stringInverter_runISR1_lab_Boost_OL();

#elif SINV_LAB == 3
    //
    //Run this to operate boost converters with MPPT
    //
    stringInverter_runISR1_lab_Boost_MPPT();

    #elif SINV_LAB == 4
    //
    //Run this to operate DC/DC in current- control close-loop
    //
    stringInverter_runISR1_lab_DCDC_CL();

#elif SINV_LAB == 5
    //
    //Run this to operate load on DC bus, supplying current internally through
    //both boosts open-loop and DC/DC in current- control close-loop
    //
    stringInverter_runISR1_lab_Boost_OL_DCDC_CL();

#elif SINV_LAB == 6
    //
    //Run this to operate DC/AC converter in H-Bride unipolar/ bipolar or HERIC
    //Open Loop
    //
    stringInverter_runISR1_lab_DCAC_OL();

#elif SINV_LAB == 7
    //
    //Run this to operate DC/AC converter in H-Bride unipolar/ bipolar or HERIC
    //close-loop
    //
    stringInverter_runISR1_lab_DCAC_CL();

#elif SINV_LAB == 8
    //
    //Run this to operate DC/AC converter in H-Bride unipolar/ bipolar or HERIC
    //closed Loop with PLL, connected to grid
    //
    stringInverter_runISR1_lab_DCAC_CL_PLLandGrid();

#elif SINV_LAB == 9
    //
    //Run this to operate DC/AC converter with DC Bus Voltage loop
    //closed Loop with pll
    //
    stringInverter_runISR1_lab_DCAC_VoltageControl();

#elif SINV_LAB == 10
    //
    //Run this to operate DC/AC converter with DC Bus Voltage loop and Boosts with MPPT
    //closed Loop with pll
    //

    stringInverter_runISR1_lab_DCAC_VoltageControl();
    stringInverter_runISR1_lab_Boost_MPPT();

#elif SINV_LAB == 11
    //
    //Run this to operate DC/AC converter with DC Bus Voltage loop, Boosts with MPPT and DC/DC in current- control close-loop
    //system running: 26.9% : 40MIPS
    //close-loop with PLL
    //
    stringInverter_runISR1_lab_DCAC_VoltageControl();
    stringInverter_runISR1_lab_Boost_MPPT();
    stringInverter_runISR1_lab_DCDC_CL();

#else
#error undefined lab
#endif

    POWER_MEAS_SINE_ANALYZER_run(&stringINV_mains_L1);


    GPIO_writePin(TPGPIO24,0); //PIN SPI MISO Pin 4 of the control card
    Interrupt_clearACKGroup(INT_ADC_A_1_INTERRUPT_ACK_GROUP);
}

//
//  STATE-MACHINE SEQUENCING AND SYNCRONIZATION FOR SLOW BACKGROUND TASKS
//
//
//--------------------------------- FRAME WORK --------------------------------
//
void A0(void)
{
    //
    // loop rate synchronizer for A-tasks
    //
    (*A_Task_Ptr)();        // jump to an A Task (A1,A2,A3,...)
    Alpha_State_Ptr = &B0;      // Comment out to allow only A tasks
}

void B0(void)
{
    //
    // loop rate synchronizer for B-tasks
    //
    (*B_Task_Ptr)();        // jump to a B Task (B1,B2,B3,...)
    Alpha_State_Ptr = &A0;      // Allow C state tasks
}

//
//  A - TASKS (executed in every 1 msec)
//
void A1(void)
{
    stringINV_test();
    A_Task_Ptr = &A1;
}

//
//  B - TASKS
//
void B1(void)
{
    // Low priority updates of frequencies and parameters for debug

    B_Task_Ptr = &B2;
}


void B2(void)
{
    // Low priority temp updates

    B_Task_Ptr = &B3;
}

void B3(void)
{
    B_Task_Ptr = &B1;
}

//
// End of File
//
