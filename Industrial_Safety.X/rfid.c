/*
 * File:   rfid.c
 * Author: 21193444
 *
 * Created on 17 de Agosto de 2022, 09:57
 */


#include <xc.h>

#define RFID_NSS        PORTCbits.RC4
#define RFID_SCK        PORTCbits.RC3

#define RFID_MISO       PORTCbits.RC4
#define RFID_MOSI       PORTCbits.RC5


#define IDLE            0x00          
//Cancela comandos atuais e coloca o MFCR em estado de repouso
//Cancel current command and puts MFCR in idle state
#define MEMORY          0x01
//Armazena 25 bytes no buffer interno
//Stores 25 bytes into the internal buffer
#define RNG             0x02
//Gera um número de ID aleatório com 10 bytes
//Generates a random number ID with 10 bytes
#define CALC_CRC        0x03
//Realiza checagem para verificar corrupção de dados
//Do a data check in to verify curruption
#define DATA_TRANSFER   0x04
/*Transmite dados do buffer FIFO imediatamente após sua execução, o comando é
terminado quando o FIFO fica vazio*/
/*The FIFO buffer content is immediately transmitted after starting this command.
This command automatically terminates when the FIFO buffer is empty.*/
#define NO_CMD_CHANGE   0x07
/*Esse comando não influencia outros em execução, é capaz de manipular qualquer
bit com excessão de CommandReg register*/
/*This command does not influence any running command in the CommandReg register. It
can be used to manipulate any bit except the CommandReg register*/
#define RECEIVE         0x08

#define TRANSCEIVE      0x0C
#define MF_AUTHENT      0x0E
#define SOFT_RESET      0x0F


void idle_command (void)
{
    RFID_MOSI == IDLE;
}


