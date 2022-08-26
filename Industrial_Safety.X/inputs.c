/*
 * File:   inputs.c
 * Author: 21193442
 *
 * Created on 17 de Agosto de 2022, 08:13
 */


#include <xc.h>
#include "delay.h"
#include "ccp.h"
#include "inputs.h"

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

//void echo_time (int t1, int t2, struct captura_t *ptr)
//{
//    ccp_rise();
//    
//    while (UTS_ECHO)
//    {
//        TMR1ON = 1;
//        t1 = CCPR1H;
//        t1<<=8;
//        t1 |= CCPR1L;
//        ccp_fall();
//        ptr->captura1 = t1;
//    }
//    while (!UTS_ECHO)
//    {
//        TMR1ON = 0;
//        t2 = CCPR1H;
//        t2<<=8;
//        t2 |= CCPR1L;
//        ptr->captura2 = t2;
//    }
//    ptr->super_captura = (ptr->captura2 - ptr->captura1);
//}