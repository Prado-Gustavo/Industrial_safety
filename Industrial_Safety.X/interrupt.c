/*
 * File:   interrupt.c
 * Author: 21193442
 *
 * Created on 23 de Agosto de 2022, 08:47
 */


#include <xc.h>
#include "timer.h"


void __interrupt() ilsr(void)
{
    if( INTCONbits.T0IF )
    {
        INTCONbits.T0IF = 0;
        T0_int();
    }
    if( PIR1bits.TMR1IF )
    {
        PIR1bits.TMR1IF = 0;
        T1_int();
    }
    if( PIR1bits.TMR2IF )
    {
        PIR1bits.TMR2IF = 0;
        T2_int();
    }
}
