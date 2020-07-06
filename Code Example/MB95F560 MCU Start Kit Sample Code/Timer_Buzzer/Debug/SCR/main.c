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


/*--------------------- API Function Declaration ----------------------------*/
void PWM_Init(void);


/*****************************************************************************/
/*Function Name: main                                                        */
/*Function description:  Initialise MCU: Clock                               */
/*                                        External Interrupt                 */
/*                                        8/16-bit Composite Timer           */
/*                                        watchdog timer                     */
/*                                        Interrupt level setting            */
/*						 push key-press S1(INT07) to drive the buzzer        */
/*                       push key-press S2(INT06) to stop the buzzer         */
/*****************************************************************************/
void main(void)
{
	__DI();
	/* system clock setting */
	SYCC = 0xDB;			// source clock: 4MHZ/16  
	
	/* External Interrupt Initialization */
	EIC30 = 0x55;			// INT07: Falling edge,Enables output of interrupt request
							// INT06: Falling edge,Enables output of interrupt request
							
							
	/* watchdog timer setting */
	WDTC = 0x35;			// Clear watchdog timer
	
	/* 8/16-bit Composite Timer setting: PWM mode*/
	PWM_Init();				// 8/16-bit Composite Timer to generate PWM signal to drive buzzer
	
	
	InitIrqLevels();		// initialise Interrupt level register and IRQ vector table
	__set_il(3);			// set global interrupt mask to allow all IRQ levels
	__EI();
	
	
	while(1)
	{
		
		WDTC = 0x35;			// Clear watchdog timer
	}
}

/*****************************************************************************/
/*Function Name: PWM_Init                                                    */
/*Function description: use 8/16-bit Composite Timer module to generate      */
/*                      a fixed-cycle PWM signal, PWM signal with "H" pulse  */
/*                      can drive the buzzer                                 */
/*****************************************************************************/
void PWM_Init(void)
{
	/* 8/16-bit Composite Timer Initialization*/
	T10CR0 = 0x03;			//  PWM timer (fixed-cycle mode),1MCLK
	T10CR1 = 0x07;			//  Enables timer output, Timer initial value "1"
	TMCR1 = 0x20;			//	selects the internal signal (TII0) as signal input for timer 10
	T10DR = 250;			// 250/((1/4M)*(1/32))=32ms
	
}


/*--------------------- INTERRUPT SERVICE ROUTINE ---------------------------*/
__interrupt void External_INT06 (void)
{
	EIC30_EIR0 = 0;			// clear External interrupt request flag
	T10CR1_STA = 0;		//  Enables timer
}

__interrupt void External_INT07 (void)
{
	EIC30_EIR1 = 0;			// clear External interrupt request flag
	T10CR1_STA = 1;		//  Enables timer
}

