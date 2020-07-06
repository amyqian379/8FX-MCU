/*---------------------------------------------------------------------------*/
/* THIS SAMPLE CODE IS PROVIDED AS IS AND IS SUBJECT TO ALTERATIONS. FUJITSU */
/* MICROELECTRONICS ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR */
/* ELIGIBILITY FOR ANY PURPOSES.                                             */
/*         (C) Fujitsu Semiconductor Design (Chengdu) Co., LTD.              */
/*---------------------------------------------------------------------------
  VECTORS.C
  - Interrupt level (priority) setting
  - Interrupt vector definition
-----------------------------------------------------------------------------*/

#include "MB95560.h"

/*---------------------------------------------------------------------------
   InitIrqLevels()

   This function  pre-sets all interrupt control registers. It can be used
   to set all interrupt priorities in static applications. If this file
   contains assignments to dedicated resources, verify  that the
   appropriate controller is used.

   NOTE: value 0xFF disables the interrupt and value 0 sets highest priority.
   NOTE: For all resource interrupts exists 3 Interrupt level registers (ILRx).
         Each register sets the level for 4 different resources (IRQx).
   NOTE: This list is prepared for the 8FX-emulation chip MB95FV100 'Horn'.
         Not all resources will be supported by all 8FX-devices
-----------------------------------------------------------------------------*/

void InitIrqLevels(void)
{
/*  ILRx                  IRQs defined by ILRx */

    ILR0 = 0xFF;      //  IRQ0:  external interrupt ch4 
                      //  IRQ1:  external interrupt ch5 
                      //  IRQ2:  external interrupt ch2 | ch6
                      //  IRQ3:  external interrupt ch3 | ch7

    ILR1 = 0xFF;      //  IRQ4:   -
                      //  IRQ5:  8/16-bit timer ch0 (lower)
                      //  IRQ6:  8/16-bit timer ch0 (upper)
                      //  IRQ7:  LIN-UART (reception)

    ILR2 = 0xFF;      //  IRQ8:  LIN-UART (transmission)
                      //  IRQ9:   -
                      //  IRQ10:  -
                      //  IRQ11:  -

    ILR3 = 0xFF;      //  IRQ12:  -
                      //  IRQ13:  -
                      //  IRQ14: 8/16-bit timer ch1 (upper)
                      //  IRQ15:  -
                          
    ILR4 = 0xFF;      //  IRQ16:  -
                      //  IRQ17:  -
                      //  IRQ18: 8/10-bit A/D-converter
                      //  IRQ19: Timebase timer
                          
    ILR5 = 0xFF;      //  IRQ20: Watch prescaler
                      //  IRQ21: -
                      //  IRQ22: 8/16-bit composite timer ch1 (lower)
                      //  IRQ23: Flash memory                              
}

/*---------------------------------------------------------------------------
   Prototypes
   
   Add your own prototypes here. Each vector definition needs is proto-
   type. Either do it here or include a header file containing them.
-----------------------------------------------------------------------------*/

__interrupt void DefaultIRQHandler (void);

/*---------------------------------------------------------------------------
   Vector definiton

   Use following statements to define vectors. 
   All resource related vectors are predefined. 
   Remaining software interrupts can be added hereas well.
-----------------------------------------------------------------------------*/
#pragma intvect DefaultIRQHandler	0   //  IRQ0:  external interrupt ch4 
#pragma intvect DefaultIRQHandler	1   //  IRQ1:  external interrupt ch5  
#pragma intvect DefaultIRQHandler	2   //  IRQ2:  external interrupt ch2 | ch6 
#pragma intvect DefaultIRQHandler	3   //  IRQ3:  external interrupt ch3 | ch7 
                                      
#pragma intvect DefaultIRQHandler 	4   //  IRQ4:  -
#pragma intvect DefaultIRQHandler 	5   //  IRQ5:  8/16-bit timer ch0 (lower) 
#pragma intvect DefaultIRQHandler 	6   //  IRQ6:  8/16-bit timer ch0 (upper) 
#pragma intvect DefaultIRQHandler 	7   //  IRQ7:  LIN-UART (reception) 
                                      
#pragma intvect DefaultIRQHandler 	8   //  IRQ8:  LIN-UART (transmission) 	     
#pragma intvect DefaultIRQHandler 	9   //  IRQ9:   -
#pragma intvect DefaultIRQHandler 	10  //  IRQ10:  -
#pragma intvect DefaultIRQHandler 	11  //  IRQ11:  -
                                      
#pragma intvect DefaultIRQHandler 	12  //  IRQ12:  -
#pragma intvect DefaultIRQHandler 	13  //  IRQ13:  -
#pragma intvect DefaultIRQHandler 	14  //  IRQ14: 8/16-bit composite timer ch1 (upper) 
#pragma intvect DefaultIRQHandler 	15  //  IRQ15:  -
                                          
#pragma intvect DefaultIRQHandler 	16  //  IRQ16:  -
#pragma intvect DefaultIRQHandler 	17  //  IRQ17:  -
#pragma intvect DefaultIRQHandler 	18  //  IRQ18: 8/10-bit A/D-converter 
#pragma intvect DefaultIRQHandler 	19  //  IRQ19: Timebase timer 
                                          
#pragma intvect DefaultIRQHandler 	20  //  IRQ20: Watch prescaler 
#pragma intvect DefaultIRQHandler 	21  //  IRQ21:  -
#pragma intvect DefaultIRQHandler 	22  //  IRQ22: 8/16-bit composite timer ch1 (lower)
#pragma intvect DefaultIRQHandler 	23  //  IRQ23: Flash memory    
 	
/*---------------------------------------------------------------------------
   DefaultIRQHandler()

   This function is a placeholder for all vector definitions. 
   Either use your own placeholder or add necessary code here 
   (the real used resource interrupt handlers should be defined in the main.c). 
-----------------------------------------------------------------------------*/
__interrupt void DefaultIRQHandler (void)
{
	__DI();						// disable interrupts
	while(1)
		__wait_nop();				// halt system
}

