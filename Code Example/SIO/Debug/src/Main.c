/* THIS SAMPLE CODE IS PROVIDED AS IS AND IS SUBJECT TO ALTERATIONS. FUJITSU */
/* MICROELECTRONICS ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR */
/* ELIGIBILITY FOR ANY PURPOSES.                                             */
/*            (C) Fujitsu Microelectronics (Shanghai) Co., LTD.              */
/*---------------------------------------------------------------------------
  MAIN.C
  - description
  - See README.TXT for project description and disclaimer.
/*---------------------------------------------------------------------------*/

#include "mb95200.h"

#define TX_side

unsigned char tx_data=0x55;
unsigned char rx_data;

/*----------------------------- SUB ROUTINES --------------------------------*/

void MCU_initialization()
{
	__DI();
	
	/*system clock*/
	SYCC=0x00;		//MCLK = source clock = 8Mhz (Main CR)
	
	/*IO port*/
	AIDRL=0xFF;
	PDR6_P63=1;		//LED4
	DDR6_P63=1;		//Output enable
	PDR0_P05=1;		//LED2
	DDR0_P05=1;		//Output enable

	/*LIN UART configuration*/
	BGR=832;		//9600bps
#ifdef RX_side
	ECCR = 0x20;		//CLK RX side
	SMR=0xB5;		//Synchronous mode, Use external CLK directly, enable SOT, SCK input
#else
	SMR=0x87;		//Synchronous mode, Use reload counter, enable SOT, SCK output
#endif
	SCR=0x13;		//No parity, 1 stop bit, 8bit, enable reception/transmission
	SSR=0x00;		//disable interrupt
	
	WDTC=0x35;		//Clear watch dog timer
	
	InitIrqLevels(); 	// initialize Interrupt level register and IRQ vector table
	__EI();
}

void wait(unsigned long j)
{
  	while(j--)
  	{	asm("\tNOP");
		WDTC=0x35;	//Clear watch dog timer
	}
}

/*----------------------------- MAIN ROUTINE --------------------------------*/

void main()
{	
	MCU_initialization();
	
	while(1)
	{
		while (SSR_TDRE == 0)
		{
			WDTC=0x35;		//Clear watch dog timer;
		}
		TDR=tx_data;			//Start sending
		
		while (SSR_RDRF == 0)
		{
			WDTC=0x35;		//Clear watch dog timer;
		}
		rx_data=RDR;			//transmission finished (via reception)
		
		if(rx_data==0x55)
#ifdef RX_side
			PDR6^=0x08;		//toggle LED4
#else
			PDR0^=0x20;		//toggle LED2
		wait(10000);
#endif		
		WDTC=0x35;			//Clear watch dog timer;

	}
}
