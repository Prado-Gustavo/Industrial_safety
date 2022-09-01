/*
 * File:   ccp.c
 * Author: 21193444
 *
 * Created on 25 de Agosto de 2022, 09:19
 */


#include <xc.h>
#include "ccp.h"

#define CCP_RISING_EDGE     5
#define CCP_FALLING_EDGE    4

struct captura_t * ccp;

void ccp1_init( void )
{
    INTCONbits.GIE    =  0;
    T1CONbits.TMR1CS  =  0;
    T1CONbits.TMR1GE  =  0;
    T1CONbits.T1CKPS =  0;
    T1CONbits.TMR1ON = 1;
    CCP1CONbits.CCP1M = CCP_RISING_EDGE;
    TRISCbits.TRISC2 = 1;
    PIE1bits.CCP1IE = 1;
    INTCONbits.PEIE   =  1; 
    INTCONbits.GIE    =  1;
}

void ccp_load( unsigned char hi, unsigned char lo )
{
    int ccpaux;
    ccpaux = hi;
    ccpaux <<= 8;
    ccpaux = lo;
    
    if( CCP1CONbits.CCP1M == 5 )
    {
        ccp->captura1 = ccpaux;
        CCP1CONbits.CCP1M = CCP_FALLING_EDGE;
    }
    else
    {
        ccp->captura2 = ccpaux;
        ccp->super_captura = ccp->captura2 - ccp->captura1;
        CCP1CONbits.CCP1M = CCP_RISING_EDGE;
    }
}

unsigned int ccp_capture(void)
{
    return( ccp->super_captura );
}


unsigned char ccp_cap1( void )
{
    return( ccp->captura1 );
}

unsigned char ccp_cap2( void )
{
    return( ccp->captura2 );
}
