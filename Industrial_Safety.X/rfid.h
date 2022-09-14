#ifndef MFRC522_V01_H
#define MFRC522_V01_H


void delay_piscal(void);				    // Rotina de delay de 200 ms.

void mfrc522ClrBit(char end, char mascara); // Limpa um bit .

void mfrc522SetBit(char end, char mascara); // Ativa um bit no registro

void mfrc522AntOn(void);                    // Liga a antena.

void mfrc522AntOff(void);                   // Desliga a antena.

void mfrc522Rst(void);                      // Reset por software.

void mfrc522Iniciar(void);                  // Inicializa o MFRC522.

/* EEPROM */
void eepromEscrever(char Address, char Data); // Grava um dado no endereco da EEprom.

char eepromLer(char Address);                 // Le um dado no endereco da EEprom.

void eepromApagar(void);                      // Apaga a EEprom.
 
/*   TAG   */
char tagTxCmd(char cmd, char *data, char dlen, char *result, char *rlen);

char tagLocalizar(void);                              // Busca UID gravada na Eeprom.

void tagMasterWr(void);                               // Grava a UID de Tag mestre na Eeprom.

void tagSlaverWr(void);                               // Grava a UID de Tag escrava na Eeprom.

char procura_tag(char modo, char *data);

char anti_colisao(char *mBuf);

char get_UID(void);                                   // Obter UID da tag no campo do leitor.

char mfrc522Uid(char *vlrAsc);

void testa_botao_del(char modo);

static void MFRC522_Wr(char addr, char value);

static char MFRC522_Rd(char addr);

static void MFRC522_Clear_Bit(char addr, char mask);

static void MFRC522_Set_Bit(char addr, char mask);

void MFRC522_Reset(void);

void MFRC522_AntennaOn(void);

void MFRC522_AntennaOff(void);

/* Nao */
void MFRC522_Init();

char MFRC522_ToCard(char command, char *sendData, char sendLen, char *backData, char *backLen);

char MFRC522_Request(char reqMode, char *TagType);

void MFRC522_CRC(char *dataIn, char length, char *dataOut);

char MFRC522_SelectTag(char *serNum);

void MFRC522_Halt(); //hibernacao

char MFRC522_Auth(char authMode, char BlockAddr, char *Sectorkey, char *serNum);

char MFRC522_Write(char blockAddr, char *writeData);

char MFRC522_Read(char blockAddr, char *recvData);

char MFRC522_AntiColl(char *serNum);

//0x0044 = Mifare_UltraLight
//0x0004 = Mifare_One (S50)
//0x0002 = Mifare_One (S70)
//0x0008 = Mifare_Pro (X)
//0x0344 = Mifare_DESFire

char MFRC522_isCard(char *TagType);

char MFRC522_ReadCardSerial(char *str);

void hex2Ascii(char *strIn, char *strOut, char cntDig);

char matEeprom[]=;

void eepromLoad(void);

char tagSearch(char *tagVlr);	// Procura TAG na E2PROM

#endif