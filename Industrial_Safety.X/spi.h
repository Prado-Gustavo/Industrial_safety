#ifndef SPI_H
#define SPI_H

void spiSoftClk(void);  						// Gera pulso de clock para o SPI.

void spiSoftIniciar(void);						// Inicializa o SPI.

void spiSoftTxDat(char dado);                   // Envia um Byte na SPI

char spiSoftRxDat(void);                        // Le um dado na SPI

#endif