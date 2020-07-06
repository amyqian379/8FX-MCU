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
// 0 : disabled
// 1 : wait for synch break
// 2 : received synch field
// 3 : received header
// 4 : LIN_Data Tx/Rx
// 5 : Checksum Tx/Rx

#define DATALENGTH 8
#define SLAVESEND 0x7D		//bb 0x7D
#define MASTERSEND 0xFE		//aa 0xFE

unsigned int temp;
unsigned char cnt;

volatile unsigned char LIN_State, Rx_Error, Rx_Data, Master_Send, LIN_Header, LIN_Count, LIN_Checksum;
volatile unsigned char LIN_Data[DATALENGTH];

volatile unsigned char ICU_State;
volatile unsigned char counter;
/*--------------------- API Function Declaration ----------------------------*/
void LIN_Uart_Mode3_Init(void);
void Composite_Timer_Init(void);
void wait(unsigned long j);

/*--------------------- MAIN ROUTINE ----------------------------------------*/
void main(void)
{
	__DI();
	/* system clock setting */
	SYCC = 0xFC;				// Main CR PLL clock mode,Source clock  (no division)
	PLLC = 0x80;				// MCLK: main CR clock *2= 4MHZ*2 = 8MHZ  
	while(!PLLC_MPRDY);			// wait Main CR PLL clock oscillation stabilization
	
	LIN_Uart_Mode3_Init();
	Composite_Timer_Init();
	
	/* IO Port initialization */
	AIDRL = 0xFF;				// P0: Port input enabled
	PDR0 = 0xFF;
	DDR0 = 0x2C;				// P05->LED2, P02(SCK),P03(SOT)
	
	PDR6_P63=1;		//LED4 off
  	DDR6_P63=1;		//output
	
	/* watchdog timer setting */
	WDTC = 0x35;				// Clear watchdog timer
	
	InitIrqLevels();			// initialise Interrupt level register and IRQ vector table
	__set_il(3);				// set global interrupt mask to allow all IRQ levels    
	__EI();
	 
	 	
	Rx_Error = 0;
	LIN_State = 1;
	
	counter = 0;
	
	while (!Rx_Error)
	{
		asm("\tNOP");
		WDTC=0x35;	//Clear watch dog timer
	}

	while(1)		// show error code on 7-seg display
	{
		wait(30000);
		PDR0 = PDR0&0xDF;	//LED2 on
		wait(10000);
		WDTC = 0x35;	//Clear watch dog timer
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
	ESCR = 0x80;		// enable LIN break detection interrupt
}

/*****************************************************************************/
/*Function Name: Composite_Timer_Init                                        */
/*Function description:  8/16-bit composite timer initialization             */
/*****************************************************************************/
void Composite_Timer_Init(void)
{
	// Initialize Composite Timer for LIN-Synch-Field measurement
	TMCR0  = 0x30;
	T00CR0 = 0x0F;
	T00CR1 = 0xA0;
	
	ICU_State = 0;		// State flag
}

/*****************************************************************************/
/*Function Name: wait                                                        */
/*Function description: use this funciton to set delay time                  */
/*****************************************************************************/
void wait(unsigned long j)
{
	while(j--)
	{
		asm("\tNOP");
		WDTC=0x35;	//Clear watch dog timer
	}
}

/*--------------------- INTERRUPT SERVICE ROUTINE ---------------------------*/
__interrupt void LIN_UART_Receive (void)
{
	if (ESCR_LBD)				// LIN Break Detection?
	{
		ESCR = 0x80;			// Clear flag
		
		if (LIN_State == 1)
		{
			SCR = 0x03;		// Enable reception & transmit
			LIN_State = 2;		// ready to receive synch field
			LIN_Checksum = 0;
			LIN_Count = 0;
			
			T00CR1 = 0xA0;       	// Clear possible ICU-IRQ

		if (++counter == 10)
			counter = 0;
			PDR6=PDR6^0x08;			//toggle LED4
		}
		
		else
		{
			Rx_Error = 1;		// Unexpected reception of break
		}
	}
	
	else if (SSR_RDRF)			// Reception?
	{
		Rx_Data = RDR_TDR;			// Get reception data
		
		if (SSR_ORE || SSR_FRE)		// Reception errors?
		{
			Rx_Error = 2;
		}
		
		else if (LIN_State == 2)	// Synch field read?
		{
			T00CR1 = 0x00;		// disable Capture-IRQ

			if (Rx_Data != 0x55)
			{
				Rx_Error = 3;
			}
			
			else
			{
				LIN_State = 3;	// ready to receive header				
			}
		}
		
		else if (LIN_State == 3)	// Header read?
		{
			LIN_Header = Rx_Data;
			
			if (LIN_Header == SLAVESEND)
			{
				RDR_TDR = LIN_Data[LIN_Count];	// Send LIN Data
				LIN_Count++;
			}
			
			LIN_State = 4;
		}
		
		else if (LIN_State == 4)			// LIN Data read / write
		{
			if (LIN_Header == MASTERSEND)		// Master sent data?
			{
				LIN_Checksum = LIN_Checksum + Rx_Data;
				LIN_Data[LIN_Count] = Rx_Data;
				LIN_Count++;
				
				if (LIN_Count == DATALENGTH)	// End of message reached?
				{
					LIN_Count = 0;
					LIN_State = 5;
					LIN_Checksum = LIN_Checksum ^ 0xFF;
				}
			}	
			
			else
			{
				LIN_Checksum = LIN_Checksum + LIN_Data[LIN_Count];
				RDR_TDR = LIN_Data[LIN_Count];	// Send next LIN Data		
				LIN_Count++;
				
				if (LIN_Count == DATALENGTH)	// End of message reached?
				{
					LIN_Count = 0;
					LIN_State = 5;
					LIN_Checksum = LIN_Checksum ^ 0xFF;
				}
			}
		}
		
		else if (LIN_State == 5)			// LIN Checksum read / write
		{
			if (LIN_Header == MASTERSEND)		// Master sent data?
			{
				if (Rx_Data != LIN_Checksum)
				{
					Rx_Error = 4;
				}
			}	
			
			else
			{
				RDR_TDR = LIN_Checksum;		// Send Checksum
			}
			
			SCR_RXE = 0;		    		// disable reception wait for LIN break
			LIN_State = 1;				// (new message)
		}
		

	}
	
	else			// Not recognized interrupt cause
	{
		Rx_Error = 5;	
		SSR_RIE = 0;	// disable reception interrupt
	}	
}


__interrupt void Composite_Timer (void)
{
	if (ICU_State == 0)	// Rising edge detected?
	{
		ICU_State = 1;
	}
	else			// Falling edge (last edge) detected!
	{
		ICU_State = 0;
		temp=T00DR >> 3;
		BGR0 = temp;
		if(cnt<250)
		cnt++;
	}
	if (T00CR1_IF)
		Rx_Error = 6;	

	T00CR1 = 0xA0;		 // clear flag
}
