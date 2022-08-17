/*
 * File:   inputs.c
 * Author: 21193442
 *
 * Created on 17 de Agosto de 2022, 08:13
 */


#include <xc.h>
#include "delay.h"

#define US_ECHO    PORTDbits.RD0
#define US_TRIGGER PORTDbits.RD1
#define PIR_OUT    PORTDbits.RC2

void in_init (void)
{
    TRISDbits.TRISD0 = 1;
    TRISDbits.TRISD1 = 0;
    TRISCbits.TRISC2 = 0;
}

void us_trigger (void)
{
        US_TRIGGER = 1;
        delay(1);
        US_TRIGGER = 0;
}

int us_distance ()
{
    if(US_ECHO == 1)
    {
        
    }
    
    
}



