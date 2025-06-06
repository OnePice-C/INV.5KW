//##############################################################################
//
// FILE:  stringINV_dcdc_mppt.h
//
// TITLE:  Solution header file for the MPPT stage
//
//#############################################################################
// $TI Release: TIDA_010938 v2.01.00.00 $
// $Release Date: Tue May  6 00:20:46 CDT 2025 $
// $Copyright:
// Copyright (C) 2025 Texas Instruments Incorporated - http://www.ti.com/
//
// ALL RIGHTS RESERVED
// $
//#############################################################################

#ifndef STRINGINV_DCDC_MPPT_H_
#define STRINGINV_DCDC_MPPT_H_

typedef struct {
    float32_t  Ipv;
    float32_t  Vpv;
    float32_t  DeltaPmin;
    float32_t  MaxVolt;
    float32_t  MinVolt;
    float32_t  Stepsize;
    float32_t  VmppOut;
    float32_t  DeltaP;
    float32_t  PanelPower;
    float32_t  PanelPower_Prev;
    int16_t mppt_enable;
    int16_t mppt_first;
} stringINV_dcdc_mppt_t;

static void stringINV_dcdc_mppt_init(stringINV_dcdc_mppt_t *v) {
    v->mppt_first = 1;
}

#pragma FUNC_ALWAYS_INLINE(stringINV_dcdc_mppt_run)
static void stringINV_dcdc_mppt_run(stringINV_dcdc_mppt_t *v) {
    v->PanelPower = v->Vpv*v->Ipv;

    if (v->mppt_enable!=1) { return; }

        if (v->mppt_first == 1)
        {
            v->VmppOut= v->Vpv -10;
            v->mppt_first=0;
            v->PanelPower_Prev=v->PanelPower;
        }
        else
        {
            v->PanelPower= (v->Vpv*v->Ipv);
            v->DeltaP=v->PanelPower-v->PanelPower_Prev;
            if (v->DeltaP > v->DeltaPmin)
            {
                v->VmppOut=v->Vpv+v->Stepsize;
            }
            else if (v->DeltaP < -v->DeltaPmin)
                {
                    v->Stepsize=-v->Stepsize;
                    v->VmppOut=v->Vpv+v->Stepsize;
                }
            v->PanelPower_Prev = v->PanelPower;
        }
        if(v->VmppOut< v->MinVolt) v->VmppOut = v->MinVolt;
        if(v->VmppOut> v->MaxVolt) v->VmppOut= v->MaxVolt;
}

#endif /* STRINGINV_DCDC_MPPT_H_ */
