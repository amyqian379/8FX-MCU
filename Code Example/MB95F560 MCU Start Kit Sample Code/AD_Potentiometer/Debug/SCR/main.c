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


#define AD_CNT 8

unsigned char AD_result;

/*--------------------- API Function Declaration ----------------------------*/
void MCU_Initialization(void);
void AD_Function(void);

/*--------------------- MAIN ROUTINE ----------------------------------------*/
void main(void)
{
	MCU_Initialization();
	
	while(1)
	{
		AD_Function();
		WDTC = 0x35;			// Clear watchdog timer	
	}
}
/*****************************************************************************/
/*Function Name: MCU_Initialization                                          */
/*Function description:   Initialise MCU: Clock                              */
/*                                        IO PORT                            */
/*                                        AD converter                       */
/*                                        watchdog timer                     */
/*****************************************************************************/
void MCU_Initialization(void)
{
	__DI();
	/* system clock setting */
	SYCC = 0xD8;			// Main CR: 4MHZ  
	
	/* IO Port initialization */
	AIDRL = 0xFC;			// P00,P01 Analog input enabled
	
	PDR0_P05 = 1;
	DDR0_P05 = 1;			// P05 -> LED2
	
	PDR6_P64 = 1;
	DDR6_P64 = 1;			// P64 -> LED3
	
	PDR6_P63 = 1;
	DDR6_P63 = 1;			// P63 -> LED4
	
	/* AD converter Initialization */
	ADC1 = 0x00;			// AN00 pin
	ADC2 = 0x80;			// 8-bit precision,
	
	 
	/* watchdog timer setting */
	WDTC = 0x35;			// Clear watchdog timer
	
	InitIrqLevels();		// initialise Interrupt level register and IRQ vector table
	__EI();
}

/*****************************************************************************/
/*Function Name: AD_Function                                          		 */
/*Function description: when turn the AD potentiometer on target board,      */
/*                      different LED twinkle indicates AD convert result    */
/*                      for different range.                                 */
/*****************************************************************************/
void AD_Function(void)
{
	unsigned char i;
	unsigned char j = 0;
	unsigned int temp = 0;
	
	for(i=0; i< AD_CNT; i++)
	{
		ADC1_AD = 1;		// start AD converter
		while(!ADC1_ADI&&j<250)
		{
			j++;			//prevent AD halting in dead loop
		}
		temp += ADD_ADDL;
	}
	AD_result = temp/AD_CNT; 
	if(AD_result > 196)
	{
		PDR6_P63=1;			//LED4 OFF
		PDR6_P64=1;			//LED3 OFF
		PDR0_P05=1;			//LED2 OFF
	}
	else if(AD_result > 128)
	{
		PDR6_P63=0;			// LED4 ON
		PDR6_P64=1;
		PDR0_P05=1;
	}
	else if(AD_result > 64)
	{
		PDR6_P63=0;			// LED4 ON
		PDR6_P64=0;			// LED3 ON
		PDR0_P05=1;
	}
	else
	{
		PDR6_P63=0;			// LED4 ON
		PDR6_P64=0;			// LED3 ON
		PDR0_P05=0;			// LED2 ON
	}
}

