/*
 * File:   interrupt.c
 * Author: 21193442
 *
 * Created on 23 de Agosto de 2022, 08:47
 */


#include <xc.h>
#include "timer.h"
#include "ccp.h"
#include "lcd.h"
#include "delay.h"

int ccp1;
int ccp2;
int ccps;

void __interrupt() isr(void)
{
    if( INTCONbits.T0IF && INTCONbits.T0IE )
    {
        INTCONbits.T0IF = 0;
        T0_int();
    }
//    if( PIR1bits.TMR1IF )
//    {
//        PIR1bits.TMR1IF = 0;
//        T1_int();
//    }
    if( PIR1bits.TMR2IF && PIE1bits.TMR2IE )
    {
        PIR1bits.TMR2IF = 0;
        T2_int();
    }
    if( PIR1bits.CCP1IF && PIE1bits.CCP1IE )
    {
        PIR1bits.CCP1IF = 0;
        PORTAbits.RA0 = !PORTAbits.RA0;
        ccp_load( CCPR1H, CCPR1L );
        T1CONbits.TMR1ON = 1;
        PIE1bits.CCP1IE = 1;
    }
}
