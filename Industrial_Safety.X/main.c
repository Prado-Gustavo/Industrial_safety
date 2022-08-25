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
#include "ccp.h"
#include "inputs.h"

void main (void) 
{
    unsigned seg = 0;
    unsigned block = 0;
    int psr_ant = 0;
    
    TRISCbits.TRISC0 = 0;
    
    
    lcd_init();
    prs_init();
    T0_init();
    tmr1_init();
    
    T0_start( 1000 );
    lcd_num(1,0, (int)seg, 2 );
    
    lcd_print(0, 1, "Pronto" );

    while(1)
    {
        
        uts_trigger(0, 0);
        echo_time(0, 0);
        
        lcd_num( 0,0, t1, 3 );
        lcd_num( 0,8, t2, 3 );
        lcd_num( 1,8, ( t2 - t1 ), 3);
//        if( T0_status() == 0 && block == 0 )
//        {
//            PORTCbits.RC0 = 0;
//            T0_start( 1000 );
//            seg = ++seg % 60;
//            lcd_print(0, 1, "Pronto   " );
//            lcd_num(1,0, seg, 2 );
//            
//        }    
        
//        prs_detect();

        
//        if( prs_detect() )
//        {
//             lcd_print(0, 1, "BLOQUEADO");
//             block = 1;
//        }
//        else
//        {
//            if( block == 0 )
//            {
//                lcd_print(0, 1, "LIVRE     ");
//            }
//            else
//            {
//                T0_start(1000);
//                block = ++block % 60;
//                lcd_print(0, 1, "BLOQUEADO");
//                lcd_num(1,0, block - 1, 2 );
//                while( T0_status() )
//                    ;
//                if(block >= 4)
//                {
//                    block = 0;
//                }
//            }
//        }
        
        
//        if(prs_detect() == 0 && block == 0)
//        {
//            lcd_print(0, 1, "LIVRE     ");
//        }
//        
//        if ( prs_detect() == 0 && block > 0 )
//        {
//            T0_start(1000);
//            block = ++block % 60;
//            lcd_print(0, 1, "BLOQUEADO");
//            lcd_num(1,0, block - 1, 2 );
//            
//            if(block == 4)
//            {
//             block = 0;
//            }
//        }
        
    }    

}
