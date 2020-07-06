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

union
{
	unsigned char byte;
	struct
	{
		unsigned char b00:1;
		unsigned char b01:1;
		unsigned char b02:1;
		unsigned char b03:1;
		unsigned char b04:1;
		unsigned char b05:1;
		unsigned char b06:1;
		unsigned char b07:1;
	}bit;
}flag;

unsigned char toggle_status;

#define flag_key1_int07	flag.bit.b07
#define flag_key2_int06	flag.bit.b06

/*--------------------- API Function Declaration ----------------------------*/
void MCU_Initialization(void);
void Key_Function(void);


/*--------------------- MAIN ROUTINE ----------------------------------------*/
void main(void)
{
	MCU_Initialization();
	
	while(1)
	{
		Key_Function();
		WDTC = 0x35;			// Clear watchdog timer	
	}
}

/*****************************************************************************/
/*Function Name: MCU_Initialization                                          */
/*Function description:   Initialise MCU: Clock                              */
/*                                        IO PORT                            */
/*                                        External Interrupt                 */
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
	
	/* External Interrupt Initialization */
	EIC30 = 0x55;			// INT07: Falling edge,Enables output of interrupt request
							// INT06: Falling edge,Enables output of interrupt request
	
	/* watchdog timer setting */
	WDTC = 0x35;			// Clear watchdog timer
	
	InitIrqLevels();		// initialise Interrupt level register and IRQ vector table
	__set_il(3);			// set global interrupt mask to allow all IRQ levels
	__EI();
}


/*****************************************************************************/
/*Function Name: Key_Function                                                */
/*Function description:   Key1(INT07) : ...LED2 -> LED3 -> LED4...           */
/*                        Key2(INT06) : ...LED4 -> LED3 -> LED2...           */
/*****************************************************************************/
void Key_Function(void)
{
	if(flag_key1_int07)
	{
		
		if(PDR0_P07)			//release active
		{
			flag_key1_int07 = 0;// clear flag
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
	}
	else if(flag_key2_int06)
	{
		
		if(PDR0_P06)			//release active
		{
			flag_key2_int06 = 0;// clear flag
			switch(toggle_status)
			{
				case 0:
				{
					/* LED2 display */
					PDR0_P05 = 1;			// P05 -> LED2: OFF	
					PDR6_P64 = 1;			// P64 -> LED3: OFF	
					PDR6_P63 = 0;			// P63 -> LED4: ON
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
					PDR0_P05 = 0;			// P05 -> LED2: ON	
					PDR6_P64 = 1;			// P64 -> LED3: OFF	
					PDR6_P63 = 1;			// P63 -> LED4: OFF
					toggle_status=0;
					break;
				}
			}
		}
	}
}


/*--------------------- INTERRUPT SERVICE ROUTINE ---------------------------*/
__interrupt void External_INT06 (void)
{
	EIC30_EIR0 = 0;			// clear External interrupt request flag
	flag_key2_int06 = 1;	// the flag of key down
}

__interrupt void External_INT07 (void)
{
	EIC30_EIR1 = 0;			// clear External interrupt request flag
	flag_key1_int07 = 1;	// the flag of key down
}

