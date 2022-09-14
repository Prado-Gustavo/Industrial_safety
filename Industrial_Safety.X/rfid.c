///*
// * File:   rfid.c
// * Author: 21193444
// *
// * Created on 17 de Agosto de 2022, 09:57
// */
//
//
//#include <xc.h>
//
//#define RFID_NSS        PORTCbits.RC4
//#define RFID_SCK        PORTCbits.RC3
//
//#define RFID_MISO       PORTCbits.RC4
//#define RFID_MOSI       PORTCbits.RC5
//
//
//#define IDLE            0x00          
////Cancela comandos atuais e coloca o MFCR em estado de repouso
////Cancel current command and puts MFCR in idle state
//#define MEMORY          0x01
////Armazena 25 bytes no buffer interno
////Stores 25 bytes into the internal buffer
//#define RNG             0x02
////Gera um n�mero de ID aleat�rio com 10 bytes
////Generates a random number ID with 10 bytes
//#define CALC_CRC        0x03
////Realiza checagem para verificar corrup��o de dados
////Do a data check in to verify curruption
//#define DATA_TRANSFER   0x04
///*Transmite dados do buffer FIFO imediatamente ap�s sua execu��o, o comando �
//terminado quando o FIFO fica vazio*/
///*The FIFO buffer content is immediately transmitted after starting this command.
//This command automatically terminates when the FIFO buffer is empty.*/
//#define NO_CMD_CHANGE   0x07
///*Esse comando n�o influencia outros em execu��o, � capaz de manipular qualquer
//bit com excess�o de CommandReg register*/
///*This command does not influence any running command in the CommandReg register. It
//can be used to manipulate any bit except the CommandReg register*/
//#define RECEIVE         0x08
//
//#define TRANSCEIVE      0x0C
//#define MF_AUTHENT      0x0E
//#define SOFT_RESET      0x0F

#include <xc.h>
#include "spi.h"
#include "delay.h"

/* MFRC522 */
// Page 0: Command and Status
#define RESERVED00				0x00			// 
#define COMMANDREG				0x01			// 
#define COMMIENREG				0x02			// 
#define DIVLENREG				0x03			// 
#define COMMIRQREG				0x04			// 
#define DIVIRQREG				0x05			// 
#define ERRORREG				0x06			// 
#define STATUS1REG				0x07			// 
#define STATUS2REG				0x08			// 
#define FIFODATAREG				0x09			// 
#define FIFOLEVELREG			0x0A			// 
#define WATERLEVELREG			0x0B			// 
#define CONTROLREG				0x0C			// 
#define BITFRAMINGREG			0x0D			// 
#define COLLREG					0x0E			// 
#define RESERVED01				0x0F			// 

// PAGE 1: Command
#define RESERVED10				0x10			// 
#define MODEREG					0x11			// 
#define TXMODEREG				0x12			// 
#define RXMODEREG				0x13			// 
#define TXCONTROLREG			0x14			// 
#define TXAUTOREG				0x15			// 
#define TXSELREG				0x16			// 
#define RXSELREG				0x17			// 
#define RXTHRESHOLDREG			0x18			// 
#define DEMODREG				0x19			// 
#define RESERVED11				0x1A			// 
#define RESERVED12				0x1B			// 
#define MIFAREREG				0x1C			// 
#define RESERVED13				0x1D			// 
#define RESERVED14				0x1E			// 
#define SERIALSPEEDREG			0x1F			// 
// PAGE 2: CFG
#define RESERVED20				0x20			// 
#define CRCRESULTREGM			0x21			// 
#define CRCRESULTREGL			0x22			// 
#define RESERVED21				0x23			// 
#define MODWIDTHREG				0x24			// 
#define RESERVED22				0x25			// 
#define RFCFGREG				0x26			// 
#define GSNREG					0x27			// 
#define CWGSPREG				0x28			// 
#define MODGSPREG				0x29			// 
#define TMODEREG				0x2A			// 
#define TPRESCALERREG			0x2B			// 
#define TRELOADREGH				0x2C			// 
#define TRELOADREGL				0x2D			// 
#define TCOUNTERVALUEREGH		0x2E			// 
#define TCOUNTERVALUEREGL		0x2F			// 

// PAGE 3: TEST REGISTER
#define RESERVED30				0x30			// 
#define TESTSEL1REG				0x31			// 
#define TESTSEL2REG				0x32			// 
#define TESTPINENREG			        0x33			// 
#define TESTPINVALUEREG			        0x34			// 
#define TESTBUSREG			 	0x35			// 
#define AUTOTESTREG				0x36			// 
#define VERSIONREG				0x37			// 
#define ANALOGTESTREG		         	0x38			// 
#define TESTDAC1REG				0x39			// 
#define TESTDAC2REG				0x3A			// 
#define TESTADCREG				0x3B			// 
#define RESERVED31				0x3C			// 
#define RESERVED32				0x3D			// 
#define RESERVED33				0x3E			// 
#define RESERVED34				0x3F			// 

// PAGE 4: MF522 Command word
#define PCD_IDLE				0x00			// NO action; Cancel the current command
#define PCD_AUTHENT				0x0E			// Authentication Key
#define PCD_RECEIVE				0x08			// Receive Data
#define PCD_TRANSMIT			0x04			// Transmit data
#define PCD_TRANSCEIVE			0x0C			// Transmit and receive data,
#define PCD_RESETPHASE			0x0F			// Reset
#define PCD_CALCCRC				0x03			// CRC Calculate

// PAGE 5: Mifare_One card command word
#define PICC_REQIDL				0x26			// Find the antenna area does not enter hibernation
#define PICC_REQALL				0x52			// Find all the cards antenna area
#define PICC_ANTICOLL			0x93			// Anti-collision
#define PICC_SElECTTAG			0x93			// Election card
#define PICC_AUTHENT1A			0x60			// Authentication key A
#define PICC_AUTHENT1B			0x61			// Authentication key B
#define PICC_READ				0x30			// Read Block
#define PICC_WRITE				0xA0			// Write block
#define PICC_DECREMENT			0xC0			// Debit
#define PICC_INCREMENT			0xC1			// Recharge
#define PICC_RESTORE			0xC2			// Transfer block data to the buffer
#define PICC_TRANSFER			0xB0			// Save the data in the buffer
#define PICC_HALT				0x50			// Sleep

/* Geral */
#define LED_LIGADO			0		// valor para acionamento do led
#define LED_DESLIGADO		1
#define RELE_LIGADO			1		// valor para acionamento do rele
#define RELE_DESLIGADO		0
#define MODO_PROG			1		// valor para modo de programacao
#define MODO_NORMAL			0		// valor para modo normal
#define TAGMESTREGRAVADA	170		// um numero qualquer para indicar a condicao
#define POSICAO_TAGMESTRE	2		// localizado tag mestre no endere�o 2 da eeprom
#define TAGDESCONHECIDA		0x7E	// tag ainda nao foi gravada na eeprom
#define ESCREVER			0		// escrever dados
#define LER					1		// ler dados
#define APAGAR_EEPROM		0		// Apagar todas as tags da eeprom.
#define APAGAR_TAG_MESTRE	1		// Apagar a tag mestre da eeprom.
#define DESLOCAMENTO		2		// indica deslocamento na posicao inicial da eeprom

//MFRC-522 Codigos de erros da comunicacao
#define MI_OK				0		// Sem erros.
#define MI_NOTAGERR			1		// Nao existe tag proximo ao leitor.
#define MI_ERR				2		// Erro na comunicacao.
#define MAX_LEN				16		// Tamanho maximo .

/* Hardware */
#define rele		PORTCbits.RC2
#define led_vm		PORTCbits.RC6
#define led_vd		PORTCbits.RC1
#define led_az		PORTCbits.RC7
#define sw_del		PORTCbits.RC5

#define MFRC522_Rst				PORTBbits.RB4									//at RD3_Bit;
#define MFRC522_CS				PORTBbits.RB0									// at RD4_Bit;
#define MFRC522_Rst_Direction	TRISBbits.TRISB4								//at TRISD3_Bit;
#define MFRC522_CS_Direction	TRISBbits.TRISB0							//at TRISD4_Bit;

char b, find, c; // Uso geral.
char f_mp = 0; // Flag modo de programacao.
char dados_tag[] = {"________________"}; // Matriz de envio/recepcao de dados.

/* Geral */
void delay_piscal(void)							// Rotina de delay de 200 ms.
{
	__delay_ms(200);
}

void delay_1seg(void)							// Rotina de delay de 1 segundo.
{
	__delay_ms(1000);
}

/* MFRC522 */
void mfrc522ClrBit(char end, char mascara) // Limpa um bit .
{
	char lido;
	spiSoftTxCmd(end, LER); // Le o registrador.
	lido = spiSoftRxDat(); // Recebe byte.
	pinSda_ = 1;
	lido = lido & (~mascara); // Limpa o bit.
	spiSoftTxCmd(end, ESCREVER); // Escreve registrador.
	spiSoftTxDat(lido); // Escreve registrador com bit zerado.
	pinSda_ = 1;
}

void mfrc522SetBit(char end, char mascara) // Ativa um bit no registro
{
	char lido;
	spiSoftTxCmd(end, LER); // Le o registrador.
	lido = spiSoftRxDat(); // Recebe byte.
	pinSda_ = 1;
	lido = lido | mascara; // Ativa o bit.
	spiSoftTxCmd(end, ESCREVER); // Escreve registrador.
	spiSoftTxDat(lido); // Escreve registrador com bit ativo.
	pinSda_ = 1;
}

void mfrc522AntOn(void) // Liga a antena.
{
	mfrc522SetBit(TXCONTROLREG, 0x03); // TxControlReg ? era 0x14
}

void mfrc522AntOff(void) // Desliga a antena.
{
	mfrc522ClrBit(TXCONTROLREG, 0x03); // TxControlReg ? era 0x14
}

void mfrc522Rst(void) // Reset por software.
{
	spiSoftTxCmd(COMMANDREG, ESCREVER); // Escrever 'CommandReg'.
	spiSoftTxDat(PCD_RESETPHASE); // Reset. Era 0x0F
	pinSda_ = 1;
}

void mfrc522Iniciar(void) // Inicializa o MFRC522.
{
	mfrc522Rst(); // Reset do MFRC522.

	spiSoftTxCmd(TMODEREG, ESCREVER); // Escrever 'TModeReg'.
	spiSoftTxDat(0x8D); // Tauto=1; f(timer)=6.78Mhz/tpresc.
	pinSda_ = 1;

	spiSoftTxCmd(TPRESCALERREG, ESCREVER); // Escrever 'TModeReg'.
	spiSoftTxDat(0x3E); // Tmode[3...1]+TPrescallerReg.
	pinSda_ = 1;

	spiSoftTxCmd(TRELOADREGL, ESCREVER); //
	spiSoftTxDat(30); //
	pinSda_ = 1;

	spiSoftTxCmd(TRELOADREGH, ESCREVER); //
	spiSoftTxDat(0); //
	pinSda_ = 1;

	spiSoftTxCmd(TXAUTOREG, ESCREVER); // 100%ASK
	spiSoftTxDat(0x40); //
	pinSda_ = 1;

	spiSoftTxCmd(MODEREG, ESCREVER); // CRC valor inicial=0x6363
	spiSoftTxDat(0x3D); //
	pinSda_ = 1;

	mfrc522AntOn(); // Ligar antena.
}

/* EEPROM */
void eepromEscrever(char Address, char Data) // Grava um dado no endereco da EEprom.
{
	while (EECON1bits.WR); // Waits Until Last Attempt To Write Is Finished
	EEADR = Address; // Writes The Addres To Which We'll Wite Our Data
	EEDATA = Data; // Write The Data To Be Saved
	EECON1bits.EEPGD = 0; // Cleared To Point To EEPROM Not The Program Memory
	EECON1bits.WREN = 1; // Enable The Operation !
	INTCONbits.GIE = 0; // Disable All Interrupts Untill Writting Data Is Done
	EECON2 = 0x55; // Part Of Writing Mechanism..
	EECON2 = 0xAA; // Part Of Writing Mechanism..
	EECON1bits.WR = 1; // Part Of Writing Mechanism..
	INTCONbits.GIE = 1; // Re-Enable Interrupts
	EECON1bits.WREN = 0; // Disable The Operation
	EECON1bits.WR = 0; // Ready For Next Writting Operation
}

char eepromLer(char Address) // Le um dado no endereco da EEprom.
{
	char Data;
	EEADR = Address; // Write The Address From Which We Wonna Get Data
	EECON1bits.EEPGD = 0; // Cleared To Point To EEPROM Not The Program Memory
	EECON1bits.RD = 1; // Start The Read Operation
	Data = EEDATA; // Read The Data
	__delay_ms(1);
	return Data;
}

void eepromApagar(void) // Apaga a EEprom.
{
	char a;
	for (a = 0; a < 128; a++)
	{
		eepromEscrever(a, 0XFF); //zera eeprom do pic
	}
}

/*   TAG   */
char tagTxCmd(char cmd, char *data, char dlen, char *result, char *rlen)
{
	char status = MI_ERR;
	char irqEn = 0x00;
	char waitIRq = 0x00;
	char lastBits, n;
	char i, a;

	switch (cmd)
	{
		case PCD_AUTHENT:
			irqEn = 0x12;
			waitIRq = 0x10;
			break;
		case PCD_TRANSCEIVE:
			irqEn = 0x77;
			waitIRq = 0x30;
			break;
		default:
			break;
	}

	spiSoftTxCmd(COMMIENREG, ESCREVER); // requisicao de interrupcao
	spiSoftTxDat(irqEn | 0x80);
	pinSda_ = 1;

	mfrc522ClrBit(COMMIRQREG, 0x80); //apaga bits de interrupcoes

	mfrc522SetBit(FIFOLEVELREG, 0x80); // FlushBuffer=1, Inicializacao da FIFO.

	spiSoftTxCmd(COMMANDREG, ESCREVER); // Nenhuma acao, cancela comandos.
	spiSoftTxDat(PCD_IDLE); //
	pinSda_ = 1;

	//escreve para a FIFO
	for (i = 0; i < dlen; i++)
	{
		spiSoftTxCmd(FIFODATAREG, ESCREVER);
		spiSoftTxDat(data[i]); //
		pinSda_ = 1;
	}

	//Envia um comando
	spiSoftTxCmd(COMMANDREG, ESCREVER); //
	spiSoftTxDat(cmd); //
	pinSda_ = 1;

	if (cmd == PCD_TRANSCEIVE) mfrc522SetBit(BITFRAMINGREG, 0x80);				// StartSend=1, inicia transmissao
	
	// Aguarda o comando ser executado e depois ler a FIFO.
	i = 250; // Tempo max. de espera 25ms.
	do
	{
		__delay_us(100);														// Aguarda 100us
		spiSoftTxCmd(COMMIRQREG, LER);											//
		n = spiSoftRxDat();
		pinSda_ = 1;															//finaliza comunicacao
		i--;
	} while ((i != 0) && !(n & 0x01) && !(n & waitIRq));

	mfrc522ClrBit(BITFRAMINGREG, 0x80);											// StartSend=0, termina comunicacao

	if (i != 0)
	{ // Confere se nao houve time out.
		spiSoftTxCmd(ERRORREG, LER); ////BufferOvfl Collerr CRCErr ProtecolErr
		a = spiSoftRxDat();
		pinSda_ = 1;															//finaliza comunicacao
		a = a & 0x1B;															//mascara de bits a serem considerados

		if (!a)
		{
			status = MI_OK;
			if (n & irqEn & 0x01) status = MI_NOTAGERR;							//nao existe tag

			if (cmd == PCD_TRANSCEIVE)
			{
				spiSoftTxCmd(FIFOLEVELREG, LER);								//
				n = spiSoftRxDat();
				pinSda_ = 1;													//finaliza comunicacao

				spiSoftTxCmd(CONTROLREG, LER);									//
				lastBits = spiSoftRxDat();
				pinSda_ = 1;													//finaliza comunicacao

				lastBits = lastBits & 0x07;
				
				if (lastBits) *rlen = (n - 1) * 8 + lastBits;
				else *rlen = n * 8;

				if (n == 0) n = 1;
				if (n > MAX_LEN) n = MAX_LEN;

				for (i = 0; i < n; i++)											// Obter o streamming da FIFO.
				{
					spiSoftTxCmd(FIFODATAREG, LER);
					result[i] = spiSoftRxDat();
					pinSda_ = 1;												//finaliza comunicacao
				}
				result[i] = 0;
			}
		} 
		else status = MI_ERR;
	}
	return (status);
}

char tagLocalizar(void) // Busca UID gravada na Eeprom.
{
	char i, y;

	for (i = DESLOCAMENTO; i < 126; i = i + 4)
	{
		for (y = 0; y < 4; y++)
		{
			if (dados_tag[y] != eepromLer(y + i))break;
			//			if (dados_tag[y] != R(y + i))break;
		}
		if (y == 4)return i; //pega o endere�o inicial do UID encontrado
	}
	return i; //se i=126 (0x7e) entao nao encontrou
}

void tagMasterWr(void) // Grava a UID de Tag mestre na Eeprom.
{
	char i;
	for (i = 0; i < 4; i++)
	{
		eepromEscrever(i + DESLOCAMENTO, dados_tag[i]);
	}
	eepromEscrever(1, TAGMESTREGRAVADA);
	f_mp = 0; //desliga modo de programacao
}

void tagSlaverWr(void) // Grava a UID de Tag escrava na Eeprom.
{
	char a, b;

	if (f_mp == MODO_PROG)
	{
		for (a = DESLOCAMENTO + 4; a < 126; a = a + 4) //localiza posicao vazia e grava UID da tag
		{
			for (b = 0; b < 4; b++)
			{
				if (eepromLer(a + b) != 0xFF)break; //sai do la�o secund�rio
			}
			if (b == 4)
			{//grava UID a partir da posicao do registrador 'a'
				for (b = 0; b < 4; b++)
				{
					eepromEscrever(a + b, dados_tag[b]); //grava UID na posicao vazia
				}
				led_vm = LED_DESLIGADO;
				led_vd = LED_LIGADO;
				delay_1seg();
				led_vd = LED_DESLIGADO;
				break; //sai do la�o prim�rio
			}
		}
	}
	else //indica tag rejeitada
	{
		led_vd = LED_DESLIGADO;
		led_vm = LED_LIGADO;
		delay_1seg();
		led_vm = LED_DESLIGADO;
	}
}

char procura_tag(char modo, char *data)											// 
{
	char status, len;															// 

	spiSoftTxCmd(BITFRAMINGREG, ESCREVER);										// Carrega o 'BitFramingReg'.
	spiSoftTxDat(0x07);															// TxLastBists = BitFramingReg[2..0]
	pinSda_ = 1;
	data[0] = modo;
	status = tagTxCmd(PCD_TRANSCEIVE, data, 1, data, &len);						// 
	if ((status != MI_OK) || (len != 0x10)) status = MI_ERR;					// 
	return (status);
}

char anti_colisao(char *mBuf)
{
	char status, i, len;
	char checksum = 0x00;
#define str_len   2

	spiSoftTxCmd(BITFRAMINGREG, ESCREVER); // Carrega o registrador.
	spiSoftTxDat(0x00); //
	pinSda_ = 1;

	mBuf[0] = PICC_ANTICOLL; // Comando anticolisao.
	mBuf[1] = 0x20;

	status = tagTxCmd(PCD_TRANSCEIVE, mBuf, str_len, mBuf, &len);

	if (status == MI_OK)
	{
		for (i = 0; i < 4; i++) checksum ^= mBuf[i]; // Checksum= 0x00^mBuf[0]^mBuf[1]^mBuf[2]^mBuf[3] - XOR de todos os bytes.
		if (checksum != mBuf[4]) status = MI_ERR; // Checksum tem que ser igual ao 5� byte da tag, diferente gera erro.
	}

	return status;
}

char get_UID(void) // Obter UID da tag no campo do leitor.
{
	char a;
	a = anti_colisao(dados_tag);
	return a;
}

char mfrc522Uid(char *vlrAsc)
{
	char a;
	a = anti_colisao(vlrAsc);
	return a;
}

void testa_botao_del(char modo)
{
	char t = 0; // Variavel para timeout e contador.
	//	while (!sw_del)																// Enquanto o botao 'Del' 
	while (sw_del) // Enquanto o botao 'Del' 
	{
		led_vd = LED_DESLIGADO; // Desliga o led. Fechadura desligada.
		led_vm = LED_LIGADO; // Liga o led. Modo apagar.
		__delay_ms(100); // Aguardar...
		t++;
		if (t >= 100)
		{
			if (modo == APAGAR_EEPROM)
			{
				eepromApagar(); // Apagar a eeprom.
				t = 3; // Variavel para 3 vezes.
				while (t) // Laco para piscar o led 3 vezes.
				{
					delay_piscal(); // Aguardar...
					led_vm = LED_LIGADO; // Liga o led.
					delay_piscal(); // Aguardar...
					led_vm = LED_DESLIGADO; // Desliga o led.
					t--; // Decrementa a variavel.
				}
			} else
			{
				eepromEscrever(1, 0XFF);
				for (t = 0; t < 4; t++)
				{
					eepromEscrever(t + DESLOCAMENTO, 0XFF);
				}
				t = 5; // Pisca led vm 5 vezes para indicar apagamento da EEprom.
				while (t) // Laco para piscar o led 5 vezes.
				{
					delay_piscal(); // Aguardar...
					led_vm = LED_LIGADO; // Liga o led.
					delay_piscal(); // Aguardar...
					led_vm = LED_DESLIGADO; // Desliga o led.
					t--; // Decrementa a variavel.
				}
			}
			f_mp = MODO_PROG; // Modo de programacao automatico.
		}
	}
	while (!sw_del); // Aguarda soltar botao
	led_vm = LED_DESLIGADO; // Desliga o led.
}

static void MFRC522_Wr(char addr, char value)
{
	MFRC522_CS = 0;
	spiSoftTxDat((addr << 1) & 0x7E);
	spiSoftTxDat(value);
	MFRC522_CS = 1;
}

static char MFRC522_Rd(char addr)
{
	char value;
	MFRC522_CS = 0;
	spiSoftTxDat(((addr << 1) & 0x7E) | 0x80);
	//	value = Soft_SPI_Read( 0x00 );
//	value = Soft_SPI_Read();
	value = spiSoftRxDat();
	MFRC522_CS = 1;
	return value;
}

static void MFRC522_Clear_Bit(char addr, char mask)
{
	MFRC522_Wr(addr, MFRC522_Rd(addr) & (~mask));
}

static void MFRC522_Set_Bit(char addr, char mask)
{
	MFRC522_Wr(addr, MFRC522_Rd(addr) | mask);
}

void MFRC522_Reset(void)
{
	MFRC522_Wr(COMMANDREG, PCD_RESETPHASE);
}

void MFRC522_AntennaOn(void)
{
	MFRC522_Set_Bit(TXCONTROLREG, 0x03);
}

void MFRC522_AntennaOff(void)
{
	MFRC522_Clear_Bit(TXCONTROLREG, 0x03);
}

/* Nao */
void MFRC522_Init()
{
	MFRC522_CS_Direction = 0;
	MFRC522_Rst_Direction = 0;
	MFRC522_CS = 1;
	MFRC522_Rst = 1;

	MFRC522_Reset();

	MFRC522_Wr(TMODEREG, 0x8D); //Tauto=1; f(Timer) = 6.78MHz/TPreScaler
	MFRC522_Wr(TPRESCALERREG, 0x3E); //TModeReg[3..0] + TPrescalerReg
	MFRC522_Wr(TRELOADREGL, 30);
	MFRC522_Wr(TRELOADREGH, 0);

	MFRC522_Wr(TXAUTOREG, 0x40); //100%ASK
	MFRC522_Wr(MODEREG, 0x3D); // CRC valor inicial de 0x6363

	//MFRC522_Clear_Bit( STATUS2REG, 0x08 );//MFCrypto1On=0
	//MFRC522_Wr( RXSELREG, 0x86 );      //RxWait = RxSelReg[5..0]
	//MFRC522_Wr( RFCFGREG, 0x7F );     //RxGain = 48dB

	MFRC522_AntennaOn();
}

char MFRC522_ToCard(char command, char *sendData, char sendLen, char *backData, char *backLen)
{
	char _status = MI_ERR;
	char irqEn = 0x00;
	char waitIRq = 0x00;
	char lastBits;
	char n;
	unsigned int i;

	switch (command)
	{
		case PCD_AUTHENT:		// Fecha/envia a Certificacao do cartao
		{
			irqEn = 0x12;
			waitIRq = 0x10;
			break;
		}
		case PCD_TRANSCEIVE:	// Transmite os dados da FIFO
		{
			irqEn = 0x77;
			waitIRq = 0x30;
			break;
		}
		default:
			break;
	}

	// Escreve os dados na FIFO
	for (i = 0; i < sendLen; i++) MFRC522_Wr(FIFODATAREG, sendData[i]);

	//Executa o comando
	MFRC522_Wr(COMMANDREG, command);

	//StartSend=1, Inicia a transmissao dos dados
	if (command == PCD_TRANSCEIVE) MFRC522_Set_Bit(BITFRAMINGREG, 0x80);

	// Aguarda o recebimento completo dos dados.
	// i: de acordo com o ajuste da frequencia do clock, o tempo maximo de espera do cartao M1 = 25ms?
	i = 0xFFFF;
	do
	{
		//CommIrqReg[7..0]
		//Set1 TxIRq RxIRq IdleIRq HiAlerIRq LoAlertIRq ErrIRq TimerIRq
		n = MFRC522_Rd(COMMIRQREG);
		i--;
	} while (i && !(n & 0x01) && !(n & waitIRq));

	MFRC522_Clear_Bit(BITFRAMINGREG, 0x80); //StartSend=0

	if (i != 0)
	{
		if (!(MFRC522_Rd(ERRORREG) & 0x1B)) //BufferOvfl Collerr CRCErr ProtecolErr
		{
			_status = MI_OK;
			if (n & irqEn & 0x01) _status = MI_NOTAGERR; //??

			if (command == PCD_TRANSCEIVE)
			{
				n = MFRC522_Rd(FIFOLEVELREG);
				lastBits = MFRC522_Rd(CONTROLREG) & 0x07;
				
				if (lastBits) *backLen = (n - 1) * 8 + lastBits;
				else *backLen = n * 8;

				if (n == 0) n = 1;
				if (n > 16) n = 16;

				//Lendo os dados recebidos na FIFO
				for (i = 0; i < n; i++) backData[i] = MFRC522_Rd(FIFODATAREG);
				backData[i] = 0;
			}
		} else _status = MI_ERR;
	}

	//MFRC522_Set_Bit( CONTROLREG, 0x80 );
	//MFRC522_Wr( COMMANDREG, PCD_IDLE );

	return (_status);
}

char MFRC522_Request(char reqMode, char *TagType)
{
	char _status;
	char backBits; //The received data bits
	MFRC522_Wr(BITFRAMINGREG, 0x07); //TxLastBists = BitFramingReg[2..0]   ???
	TagType[0] = reqMode;
	_status = tagTxCmd(PCD_TRANSCEIVE, TagType, 1, TagType, &backBits);
	if ((_status != MI_OK) || (backBits != 0x10)) _status = MI_ERR;

	return (_status);
}

void MFRC522_CRC(char *dataIn, char length, char *dataOut)
{
	char i, n;
	mfrc522ClrBit(DIVIRQREG, 0x04);
	mfrc522SetBit(FIFOLEVELREG, 0x80);
	//Escreve dados no FIFO        
	for (i = 0; i < length; i++) MFRC522_Wr(FIFODATAREG, *dataIn++);

	MFRC522_Wr(COMMANDREG, PCD_CALCCRC);

	i = 0xFF; //Espera a finalizacao do Calculo do CRC
	do
	{
		n = MFRC522_Rd(DIVIRQREG);
		i--;
	} while (i && !(n & 0x04)); //CRCIrq = 1

	dataOut[0] = MFRC522_Rd(CRCRESULTREGL);
	dataOut[1] = MFRC522_Rd(CRCRESULTREGM);
}

char MFRC522_SelectTag(char *serNum)
{
	char i;
	char _status;
	char size;
	char recvBits;
	char buffer[9];

//	MFRC522_Clear_Bit(STATUS2REG, 0x08);
//	mfrc522ClrBit(STATUS2REG, 0x08);
//	MFRC522_Clear_Bit( STATUS2REG, 0x08 );   //MFCrypto1On=0

	buffer[0] = PICC_SElECTTAG;
	buffer[1] = 0x70;

	for (i = 2; i < 7; i++) buffer[i] = *serNum++;

	MFRC522_CRC(buffer, 7, &buffer[7]);

	_status = tagTxCmd(PCD_TRANSCEIVE, buffer, 9, buffer, &recvBits);

	if ((_status == MI_OK) && (recvBits == 0x18)) size = buffer[0];
	else size = 0;

	return (size);
}

void MFRC522_Halt() //hibernacao
{
	char unLen;
	char buff[4];

	buff[0] = PICC_HALT;
	buff[1] = 0;
	MFRC522_CRC(buff, 2, &buff[2]);

	MFRC522_Clear_Bit(STATUS2REG, 0x80);
	MFRC522_ToCard(PCD_TRANSCEIVE, buff, 4, buff, &unLen);
	MFRC522_Clear_Bit(STATUS2REG, 0x08);
}

char MFRC522_Auth(char authMode, char BlockAddr, char *Sectorkey, char *serNum)
{
	char _status;
	char recvBits;
	char i;
	char buff[12];

	//Verifica o endereco do bloco de comando + setor + senha + numero de serie do cartao
	buff[0] = authMode;
	buff[1] = BlockAddr;

	for (i = 2; i < 8; i++)		buff[i] = Sectorkey[i - 2];
	for (i = 8; i < 12; i++)	buff[i] = serNum[i - 8];

	_status = tagTxCmd(PCD_AUTHENT, buff, 12, buff, &recvBits);
	if ((_status != MI_OK) || !(MFRC522_Rd(STATUS2REG) & 0x08)) _status = MI_ERR;
	return (_status);
}

char MFRC522_Write(char blockAddr, char *writeData)
{
	char _status;
	char recvBits;
	char i;
	char buff[18];

	buff[0] = PICC_WRITE;
	buff[1] = blockAddr;

	MFRC522_CRC(buff, 2, &buff[2]);
	_status = tagTxCmd(PCD_TRANSCEIVE, buff, 4, buff, &recvBits);

	if ((_status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A)) _status = MI_ERR;

	if (_status == MI_OK)
	{
		for (i = 0; i < 16; i++) buff[i] = writeData[i];			// Escreve os dados da FIFO (16 Bytes)

		MFRC522_CRC(buff, 16, &buff[16]);
		_status = tagTxCmd(PCD_TRANSCEIVE, buff, 18, buff, &recvBits);
		
		if ((_status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A)) _status = MI_ERR;
	}

	return (_status);
}

char MFRC522_Read(char blockAddr, char *recvData)
{
	char _status;
	char unLen;

	recvData[0] = PICC_READ;
	recvData[1] = blockAddr;

	MFRC522_CRC(recvData, 2, &recvData[2]);
	_status = tagTxCmd(PCD_TRANSCEIVE, recvData, 4, recvData, &unLen);

	if ((_status != MI_OK) || (unLen != 0x90)) _status = MI_ERR;

	return (_status);
}

char MFRC522_AntiColl(char *serNum)
{
	char _status;
	char i;
	char serNumCheck = 0;
	char unLen;

	MFRC522_Wr(BITFRAMINGREG, 0x00); //TxLastBists = BitFramingReg[2..0]

	serNum[0] = PICC_ANTICOLL;
	serNum[1] = 0x20;
	MFRC522_Clear_Bit(STATUS2REG, 0x08);
	_status = MFRC522_ToCard(PCD_TRANSCEIVE, serNum, 2, serNum, &unLen);

	if (_status == MI_OK)
	{
		for (i = 0; i < 4; i++) serNumCheck ^= serNum[i];
		if (serNumCheck != serNum[4])_status = MI_ERR;
	}

	return (_status);
}

//0x0044 = Mifare_UltraLight
//0x0004 = Mifare_One (S50)
//0x0002 = Mifare_One (S70)
//0x0008 = Mifare_Pro (X)
//0x0344 = Mifare_DESFire

char MFRC522_isCard(char *TagType)
{
	if (MFRC522_Request(PICC_REQIDL, TagType) == MI_OK) return (1);
	else return (0);
}

char MFRC522_ReadCardSerial(char *str)
{
	char _status;
	_status = MFRC522_AntiColl(str);
	str[5] = 0;
	if (_status == MI_OK) return (1);
	else return (0);
}

void hex2Ascii(char *strIn, char *strOut, char cntDig)
{
	char a,b,uni,dez;
	for(a=0;a<cntDig;a++)
	{
		b=a*2;
		uni= strIn[a] & 0x0F;
		dez=(strIn[a] & 0xF0)>>4;
		if (uni <10) uni += '0';
		if (uni > 9 && uni < 16) uni += 0x37;
		if (dez <10) dez += '0';
		if (dez > 9 && dez < 16) dez += 0x37;
		strOut[b]=dez;
		strOut[b+1]=uni;
	}
}

char matEeprom[]=
{
	0xFF,0xFF,0xFF,0xFF,0xFF, // 00...04
	0xFF,0xFF,0xFF,0xFF,0xFF, // 05...09
	0xFF,0xFF,0xFF,0xFF,0xFF, // 10...14
	0xFF,0xFF,0xFF,0xFF,0xFF, // 15...19
	0xFF,0xFF,0xFF,0xFF,0xFF, // 20...24
	0xFF,0xFF,0xFF,0xFF,0xFF, // 25...29
	0xFF,0xFF,0xFF,0xFF,0xFF, // 30...34
	0xFF,0xFF,0xFF,0xFF,0xFF, // 35...39
	0xFF,0xFF,0xFF,0xFF,0xFF, // 40...44
	0xFF,0xFF,0xFF,0xFF,0xFF, // 45...49
	0xFF,0xFF,0xFF,0xFF,0xFF  // 50...54
};

void eepromLoad(void)
{
	char x,y;
	for(x=0;x<55;x+=5)
	{
		for(y=0;y<5;y++)matEeprom[x+y]=eepromLer(x+y);
	}
}

char tagSearch(char *tagVlr)	// Procura TAG na E2PROM
{
	char a=0, b=0, c=0;
	while(a<55)
	{
		for(b=0;b<5;b++)
		{
			if(tagVlr[a+b]==matEeprom[a+b])c=1;
			else c=0;
		}
		if(c==1)break;
		a +=5;
	}
	return(a);
}
