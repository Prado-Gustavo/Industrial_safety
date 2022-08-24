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
    TRISCbits.TRISC2  = 1; // Define a porta RC2 como entrada
    TRISCbits.TRISC0  = 0; // Define a porta RC0 como saida
    t_sensor = 0;
    
    AVISO = 0;
    PRS = 0;

}

unsigned char prs_detect( void )
{
    return( AVISO = PRS );
}


//void prs_detect (unsigned char s, unsigned char w)
//{
//    s = PRS;
// 
//    if (s == 1)
//    {  
//        t_sensor = 4500;
//        w = 1;
//        w = AVISO;
//    }
//        
//    if(s == 0)
//    {   
//        --t_sensor;        
//        delay_ms(1);           
//
//        if(t_sensor <=0)
//        {
//            w = 0;
//            w = AVISO;
//        }
//    } 
//}


