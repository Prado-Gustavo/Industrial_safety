/* 
 * File:   ccp.h
 * Author: 21193444
 *
 * Created on 25 de Agosto de 2022, 09:16
 */

#ifndef CCP_H
#define	CCP_H

struct captura_t
{
    int captura1;
    int captura2;
    int super_captura;
};

void ccp1_init( void );
void ccp_load_rising ( unsigned char hi, unsigned char lo );
void ccp_load_falling( unsigned char hi2, unsigned char lo2 );
unsigned int ccp_capture(void);

unsigned char ccp_cap1( void );
unsigned char ccp_cap2( void );


#endif	/* CCP_H */

