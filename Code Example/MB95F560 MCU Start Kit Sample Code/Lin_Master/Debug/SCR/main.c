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

// LIN-State
//
// 0 : Waiting (Ready to send synch break)
// 1 : set synch break
// 2 : synch break read back, set synch field
// 3 : send header
// 4 : LIN_Data Tx/Rx
// 5 : Checksum Tx/Rx

#define DATALENGTH 8 
#define SLAVESEND 0x7D
#define MASTERSEND 0xFE

volatile unsigned char LIN_State, Rx_Error, Rx_Data, Master_Send;
volatile unsigned char LIN_Header, LIN_Count, LIN_Checksum;
volatile unsigned char LIN_Data[DATALENGTH];
volatile unsigned char counter;

/*--------------------- API Function Declaration ----------------------------*/
void LIN_Uart_Mode3_Init(void);
void Start_LIN_Message(void);
void wait(unsigned long j);


/*--------------------- MAIN ROUTINE ----------------------------------------*/
void main(void)
{
	__DI();
	/* system clock setting */
	SYCC = 0xFC;				// Main CR PLL clock mode,Source clock  (no division)
	PLLC = 0x80;				// MCLK: main CR clock *2= 4MHZ*2 = 8MHZ  
	while(!PLLC_MPRDY);			// wait Main CR PLL clock oscillation stabilization
	
	/* IO Port initialization */
	AIDRL = 0xFF;				// P0: Port input enabled
	PDR0 = 0xFF;
	DDR0 = 0x2C;				// P05->LED2, P02(SCK),P03(SOT)
	
	
	/* LIN-UART Initialization */
	LIN_Uart_Mode3_Init();
	
	LIN_Data[0] = 0x00;			// LIN data sent by master task
	LIN_Data[1] = 0xAA;
	LIN_Data[2] = 0xED;
	LIN_Data[3] = 0x77;
	LIN_Data[4] = 0xDD;
	LIN_Data[5] = 0x11;
	LIN_Data[6] = 0x88;
	LIN_Data[7] = 0x00;
	
	LIN_State = 0;				// Set waiting
	Rx_Error = 0;

	counter = 0;
	
	/* watchdog timer setting */
	WDTC = 0x35;				// Clear watchdog timer
	
	InitIrqLevels();			// initialise Interrupt level register and IRQ vector table
	__set_il(3);				// set global interrupt mask to allow all IRQ levels    
	__EI();
	
	while (!Rx_Error)
	{
		wait(10000);
		LIN_Header = MASTERSEND;// Master sends data to slave
		Master_Send = 1;
		Start_LIN_Message();

		if (!Rx_Error)
		{
			wait(10000);
			LIN_Header = SLAVESEND;	// Master wants data from slave
			Master_Send = 0;
			Start_LIN_Message();
		}
			
		if (++counter == 10)
			counter = 0;
		PDR0 = PDR0^0x20;		//toggle LED2
		WDTC = 0x35;			//Clear watch dog timer
	}
	
	while(1)
	{
		wait(30000);
		PDR0 = PDR0&0xDF;		   //LED2 on
		wait(10000);
		WDTC=0x35;			//Clear watch dog timer
	}	
}
/*****************************************************************************/
/*Function Name: LIN_Uart_Mode3_Init                                         */
/*Function description: LIN-UART works as the LIN master and the LIN slave.  */
/*                      this function initialize operationg mode 3 of LIN.   */
/*****************************************************************************/
void LIN_Uart_Mode3_Init(void)
{
	// Initialize UART asynchronous LIN mode
	BGR1 = 0x01;
	BGR0 = 0xA0;		// Reloadvalue = 832 (8MHz, 9600Baud)
	SMR  = 0xC5;		// enable SOT, Reset, LIN mode
	SSR  = 0x02;		// enable reception interrupt
	SCR  = 0x01;		// enable transmit
	ESCR = 0x30;		// set LIN break 16 bit times
}

/*****************************************************************************/
/*Function Name: Start_LIN_Message                                           */
/*Function description: invoke this funciton to start LIN message            */
/*****************************************************************************/
void Start_LIN_Message(void)
{
	ESCR_LBD = 0;		// clear possible LIN-Break detection
	ESCR_LBIE = 1;		// enable LIN Break detection (for read back)
	
	ECCR = 0x40;		// Genarte LIN-Break
	
	LIN_State = 1;
}	

/*****************************************************************************/
/*Function Name: wait                                                        */
/*Function description: use this funciton to set delay time                  */
/*****************************************************************************/
void wait(unsigned long j)
{
  	while(j--)
  	{	asm("\tNOP");
		WDTC=0x35;	//Clear watch dog timer
	}
}

/*--------------------- INTERRUPT SERVICE ROUTINE ---------------------------*/

__interrupt void LIN_UART_Recive (void)
{
	if (ESCR_LBD)				// LIN Break Detection (Read back)?
	{
		ESCR_LBD = 0;			// Clear flag
		
		if (LIN_State == 1)
		{
			SCR_RXE = 1;		// Enable reception
			RDR_TDR = 0x55;			// Send Synchfield
			LIN_State = 2;
			LIN_Checksum = 0;
		}
		
		else
		{
			Rx_Error = 1;		// Unexpected reception of break
		}
	}
	
	else if (SSR_RDRF)			// Reception?
	{
		Rx_Data = RDR_TDR;			// Get reception data
		
		if (SSR_ORE || SSR_FRE)	// Reception errors?
		{
			Rx_Error = 2;
		}
		
		else if (LIN_State == 2)	// Synch field read back?
		{
			if (Rx_Data != 0x55)
			{
				Rx_Error = 3;
			}
			
			else
			{
				RDR_TDR = LIN_Header;			// Send LIN_Header
				LIN_State = 3;
			}
		}
		
		else if (LIN_State == 3)				// Header read back?
		{
			if (Rx_Data != LIN_Header)
			{
				Rx_Error = 4;
			}
			
			else
			{
				if (Master_Send)			// Master wants to send?
				{
					RDR_TDR = LIN_Data[LIN_Count];	// Send LIN Data
					LIN_Checksum = LIN_Data[LIN_Count];
				}
				
				LIN_State = 4;
			}
		}
		
		else if (LIN_State == 4)				// LIN Data read back / Slave Data
		{
			if (Master_Send)				// Master sent data?
			{
				if (Rx_Data != LIN_Data[LIN_Count])
				{
					Rx_Error = 5;
				}
				
				LIN_Count++;
				
				if (LIN_Count == DATALENGTH)		// End of message reached?
				{
					LIN_Count = 0;
					LIN_State = 5;
					LIN_Checksum = LIN_Checksum ^ 0xFF;
					RDR_TDR = LIN_Checksum;
				}
				
				else
				{
					RDR_TDR = LIN_Data[LIN_Count];	// Send next LIN Data
					LIN_Checksum = LIN_Checksum + LIN_Data[LIN_Count];
				}
			}
			
			else						// Receive Data from Slave
			{
				LIN_Data[LIN_Count] = Rx_Data;
				LIN_Checksum = LIN_Checksum + Rx_Data;
				
				LIN_Count++;
				
				if (LIN_Count == DATALENGTH)		// End of message reached?
				{
					LIN_Count = 0;
					LIN_State = 5;
					LIN_Checksum = LIN_Checksum ^ 0xFF;
				}
			}
		}
		
		else if (LIN_State == 5)				// LIN Checksum read back / Slave Checksum
		{
			if (Rx_Data != LIN_Checksum)
			{
				Rx_Error = 6;
			}
			
			SCR_RXE = 0;
			LIN_State = 0;
		}		
	}
	
	else					// Not recognized interrupt cause
	{
		Rx_Error = 7;	
		SSR_RIE = 0;			// disable reception interrupt
	}	
}



