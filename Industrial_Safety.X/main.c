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

int num ;

char aviso;
char prs;

void main (void) 
{
    num = 0;
    prs = 0;
    
    lcd_init();
    prs_init();
    
    while(1)
    {    
         
        prs_detect( prs, aviso);
        
        if( prs == 1)
        {  
         lcd_print(0, 1, "aviso" );
        }
    }
}
