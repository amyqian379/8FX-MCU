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


unsigned int t512us;
unsigned char toggle_status;

/*--------------------- API Function Declaration ----------------------------*/
void MCU_Initialization(void);
void LED_Display(void);

/*--------------------- MAIN ROUTINE ----------------------------------------*/
void main(void)
{
	MCU_Initialization();
	
	while(1)
	{
		if(t512us == 0)		// 512us*1000 = 512ms
		{
			t512us = 1000;
			LED_Display();
		}
		
		WDTC=0x35;			//Clear watch dog timer
	}
}


/*****************************************************************************/
/*Function Name: MCU_Initialization                                          */
/*Function description:   Initialise MCU: Clock                              */
/*                                        IO PORT                            */
/*                                        timer-base timer                   */
/*                                        watchdog timer                     */
/*                                        Interrupt level setting            */
/*****************************************************************************/
void MCU_Initialization(void)
{
	__DI();
	/* system clock setting */
	SYCC = 0xD8;			// Main CR: 4MHZ  
	
	/* IO Port initialization */
	PDR0_P05 = 1;
	DDR0_P05 = 1;			// P05 -> LED2
	
	PDR6_P64 = 1;
	DDR6_P64 = 1;			// P64 -> LED3
	
	PDR6_P63 = 1;
	DDR6_P63 = 1;			// P63 -> LED4
	
	t512us = 1000;			// t512us is used as count times of 512us interval time, 512us*1000 =512ms
	
	/* timer-base timer setting */
	TBTC = 0x4B;			// interval time: 512us
	
	/* watchdog timer setting */
	WDTC = 0x35;			// Clear watchdog timer
	
	InitIrqLevels();		// initialise Interrupt level register and IRQ vector table
	__set_il(3);			// set global interrupt mask to allow all IRQ levels
	__EI();
}

/*****************************************************************************/
/*Function Name: LED_Display                                                 */
/*Function description:  display circularly according to the method as below */
/*                       LED2 -> LED3 -> LED4 -> LED2..                      */
/*****************************************************************************/
void LED_Display(void)
{
	
	switch(toggle_status)
	{
		case 0:
		{
			/* LED2 display */
			PDR0_P05 = 0;			// P05 -> LED2: ON	
			PDR6_P64 = 1;			// P64 -> LED3: OFF	
			PDR6_P63 = 1;			// P63 -> LED4: OFF
			toggle_status=1;
			break;
		}
		case 1:
		{
			/* LED3 display */
			PDR0_P05 = 1;			// P05 -> LED2: OFF	
			PDR6_P64 = 0;			// P64 -> LED3: ON	
			PDR6_P63 = 1;			// P63 -> LED4: OFF
			toggle_status=2;
			break;
		}
		case 2:
		{
			/* LED4 display */
			PDR0_P05 = 1;			// P05 -> LED2: OFF	
			PDR6_P64 = 1;			// P64 -> LED3: OFF	
			PDR6_P63 = 0;			// P63 -> LED4: ON
			toggle_status=0;
			break;
		}
	}
	
}

/*--------------------- INTERRUPT SERVICE ROUTINE ---------------------------*/
__interrupt void timerbase_timer (void)
{
	TBTC_TBIF = 0;			// clear Time-base timer interrupt request flag bit
	if(t512us != 0)
	{
		t512us--;
	}
}


