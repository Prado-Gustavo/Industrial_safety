/*
 * File:   ccp.c
 * Author: 21193444
 *
 * Created on 25 de Agosto de 2022, 09:19
 */


#include <xc.h>
#include "ccp.h"

void tmr1_init (void)
{
    TMR1CS        =  1;
    T1OSCEN       =  0;
    T1CKPS1       =  0;
    TMR1GE        =  0;
    T1GINV        =  0;
    GIE           =  1;
    PEIE          =  1;   
}

void ccp_rise (void)
{
    CCP1M0 = 1;
    CCP1M1 = 0;
    CCP1M2 = 1;
    CCP1M3 = 0;
}

void ccp_fall (void)
{
    CCP1M0 = 0;
    CCP1M1 = 0;
    CCP1M2 = 1;
    CCP1M3 = 0;
}

