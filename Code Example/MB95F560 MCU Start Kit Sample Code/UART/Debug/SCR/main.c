/*---------------------------------------------------------------------------*/
/* THIS SAMPLE CODE IS PROVIDED AS IS AND IS SUBJECT TO ALTERATIONS. FUJITSU */
/* MICROELECTRONICS ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR */
/* ELIGIBILITY FOR ANY PURPOSES.                                             */
/*         (C) Fujitsu Semiconductor Design (Chengdu) Co., LTD.              */
/*---------------------------------------------------------------------------
  MAIN.C
  - description
  - See README.TXT for project description and disclaimer.
-----------------------------------------------------------------------------*/

#include"mb95560.h"

#define TX_BYTE_NUM 68
#define RX_BYTE_NUM 1

unsigned char tx_data[TX_BYTE_NUM]={"\nWelcome to the LIN-UART (asynchronous mode) of MB95560 series (8FX)"};
unsigned char tx_num;
unsigned char rx_num;

/*--------------------- API Function Declaration ----------------------------*/
void MCU_Initialization(void);



/*--------------------- MAIN ROUTINE ----------------------------------------*/
void main(void)
{
	MCU_Initialization();
	
	rx_num = TX_BYTE_NUM;
	SSR_TIE = 1;				// enable transmit interrupt
	while(1)
	{
		
		WDTC = 0x35;			// Clear watchdog timer
	}
}

/*****************************************************************************/
/*Function Name: MCU_Initialization                                          */
/*Function description:   Initialise MCU: Clock                              */
/*                                        IO PORT                            */
/*                                        LIN-UART                           */
/*                                        watchdog timer                     */
/*****************************************************************************/
void MCU_Initialization(void)
{
	__DI();
	/* system clock setting */
	SYCC = 0xD8;			// Main CR: 4MHZ  
	
	/* IO Port initialization */
	AIDRL = 0xFF;			// P0: Port input enabled
	
	/* LIN-UART Initialization */
	SMR = 0x05;				// Asynchronous (Normal mode),LIN-UART serial data output pin
	BGR1 = 0x01;
	BGR0 = 0xA0;			// Reloadvalue = 832 (8MHz, 9600Baud)
	SCR = 0x15;				// 8bit data, enable transmission
	SSR = 0x00;				
	
	/* watchdog timer setting */
	WDTC = 0x35;			// Clear watchdog timer
	
	InitIrqLevels();		// initialise Interrupt level register and IRQ vector table
	__EI();
}

/*--------------------- INTERRUPT SERVICE ROUTINE ---------------------------*/
__interrupt void LIN_UART_Transmit (void)
{
	if(SSR_TDRE)
	{
		if(tx_num >= rx_num)
		{
			tx_num = 0;
			rx_num = 0;
			SCR_RXE = 1;
			SSR_TIE = 0;
			SSR_RIE = 1;
		}
		else
		{
			RDR_TDR = tx_data[tx_num];
			tx_num++;
		}
	}
}
__interrupt void LIN_UART_Receive (void)
{
	SCR_CRE = 1;
	if(SSR_RDRF)
	{
		tx_data[rx_num] = RDR_TDR;
		rx_num++;
		if(rx_num >= RX_BYTE_NUM)
		{
			SCR_TXE = 1;
			SSR_TIE = 1;
			SSR_RIE = 0;
		}
	}
}
