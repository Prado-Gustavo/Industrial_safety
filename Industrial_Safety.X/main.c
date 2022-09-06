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
//    unsigned seg = 0;
//    unsigned block = 0;
//    int psr_ant = 0;
    int ccp1;
    int ccp2;
    int ccp3; 
    
    
    TRISCbits.TRISC0 = 0;
    
    in_init();
    lcd_init();
    ccp1_init();
ANSEL = 0;
TRISAbits.TRISA0 = 0;
    
//    T0_start( 1000 );
//    lcd_num(1,0, (int)seg, 2 );
//    
//    lcd_print(0, 1, "Pronto" );

    while(1)
    {
///        ccp1 = ccp_cap1();
//        ccp2 = ccp_cap2();
//        ccp3 = ccp_capture();
//        
//        lcd_num( 1, 0,  ccp1, 3);
//        lcd_num( 1, 5,  ccp2, 3);  
//        lcd_num( 1, 10, ccp3, 3);
//
        lcd_num( 0, 13, (int)TMR1H, 3);
        delay_ms(1000);
        
        
        

        
//echo_time(0, 0, &captura);
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
