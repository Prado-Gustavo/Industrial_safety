/*
 * File:   inputs.c
 * Author: 21193442
 *
 * Created on 17 de Agosto de 2022, 08:13
 */


#include <xc.h>
#include "delay.h"

#define UTS_ECHO    PORTDbits.RD0
#define UTS_TRIGGER PORTDbits.RD1
#define PIR_OUT    PORTDbits.RC2

int modo ; 

void in_init (void)
{
    TRISDbits.TRISD0 = 1;
    TRISDbits.TRISD1 = 0;
    TRISCbits.TRISC2 = 0;
}

void uts_trigger (void)
{
        UTS_TRIGGER = 1;
        __delay_us(10);
        UTS_TRIGGER = 0;
        __delay_us(10);
        
}