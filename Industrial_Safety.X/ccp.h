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

void ccp1_init( struct captura_t * ptr );
void ccp_rise(void);
void ccp_fall(void);

void ccp_load( unsigned char hi, unsigned char lo );

#endif	/* CCP_H */

