/*
 * File:   prs.c
 * Author: 21193442
 *
 * Created on 19 de Agosto de 2022, 09:23
 */


#include <xc.h>
#include "delay.h"

#define AVISO   PORTCbits.RC0
#define PRS     PORTCbits.RC2

int t_sensor;

void prs_init (void) 
{
    TRISCbits.TRISC2  = 1; // Define a porta RD2 como entrada
    TRISCbits.TRISC0  = 0; // Define a porta RD1 como saida
    t_sensor = 0;
    
    AVISO = 0;
    PRS = 0;

}

void prs_detect (unsigned char s, unsigned char w)
{
 
    PRS = s;
    
    
    if (s == 1)
    {  
        t_sensor = 4500;
        AVISO = 1;
        AVISO = w;
    }
        
    if(s == 0)
    {   
        --t_sensor;        
        __delay_ms(1);           

        if(t_sensor <=0)
        {
            AVISO = 0;
            AVISO = w;
        }
    } 
}


