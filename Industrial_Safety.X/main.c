/*
 * File:   main.c
 * Author: 21193444
 *
 * Created on 16 de Agosto de 2022, 10:42
 */


#include <xc.h>
#include "config.h"
#include "delay.h"
#include "lcd.h"
#include "prs.h"
#include "timer.h"

void main (void) 
{
    unsigned seg = 0;
    lcd_init();
    prs_init();
    T0_init();

    T0_start( 1000 );
    lcd_num(1,0, (int)seg, 2 );
    
    lcd_print(0, 1, "Pronto" );

    while(1)
    {
        if( T0_status() == 0 )
        {
            T0_start( 1000 );
            seg = ++seg % 60;
            lcd_num(1,0, seg, 2 );
        }
        if (seg == 60)
        {
            PORTCbits.RC0 = 0;
        }
        
    }    

}
