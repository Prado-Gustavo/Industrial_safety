#ifndef SPI_H
#define SPI_H

#define pinSda_		PORTAbits.RA5
#define pinSck_		PORTCbits.RC3
#define pinMosi		PORTCbits.RC5
#define pinMiso		PORTCbits.RC4
#define pinRst		PORTBbits.RB0

#define pinSdaCfg	TRISAbits.TRISA5
#define pinSckCfg	TRISCbits.TRISC3
#define pinMosiCfg	TRISCbits.TRISC5
#define pinMisoCfg	TRISCbits.TRISC4
#define pinRstCfg	TRISBbits.TRISB0

void spiSoftClk(void);  						// Gera pulso de clock para o SPI.

void spiSoftIniciar(void);						// Inicializa o SPI.

void spiSoftTxDat(char dado);                   // Envia um Byte na SPI

void spiSoftTxCmd(char end, char oper);         // Envio de um Comando SPI

char spiSoftRxDat(void);                        // Le um dado na SPI

#endif