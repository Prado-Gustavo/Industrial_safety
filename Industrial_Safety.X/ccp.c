/*
 * File:   ccp.c
 * Author: 21193444
 *
 * Created on 25 de Agosto de 2022, 09:19
 */


#include <xc.h>
#include "ccp.h"

struct captura_t * ccp_ptr;

void ccp1_init( struct captura_t * ptr )
{
    INTCONbits.GIE    =  0;
    T1CONbits.TMR1CS  =  1;
    T1CONbits.T1OSCEN =  0;
    T1CONbits.T1CKPS1 =  0;
    T1CONbits.TMR1GE  =  0;
    T1CONbits.T1GINV  =  0;
    INTCONbits.PEIE   =  1;   
    ccp_ptr = ptr;
    INTCONbits.GIE    =  1;
}

void ccp_rise (void)
{
    CCP1CONbits.CCP1M = 5;
}

void ccp_fall (void)
{
    CCP1CONbits.CCP1M = 4;
}

void ccp_load( unsigned char hi, unsigned char lo )
{
    int ccp;
    ccp = hi;
    ccp <<= 8;
    ccp |= lo;
    
    if( CCP1CONbits.CCP1M == 5 )
    {
        CCP1CONbits.CCP1M = 4;
        ccp_ptr->captura1 = ccp;
    }
    else
    {
        CCP1CONbits.CCP1M = 5;
        ccp_ptr->captura2 = ccp;
        ccp_ptr->super_captura = ccp_ptr->captura2 - ccp_ptr->captura1;
    }
}

