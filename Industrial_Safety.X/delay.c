/*
 * File:   delay.c
 * Author: josewrpereira
 *
 * Created on 19 April 2021, 22:04
 */


#include <xc.h>
#include "delay.h"

void delay_ms( unsigned int t )
{
    while( t )
    {
        __delay_ms( 1 );
        --t;
    }
}

void delay_us( unsigned int tus )
{
    while( tus )
    {
        __delay_us( 1 );
        --tus;
    }
}