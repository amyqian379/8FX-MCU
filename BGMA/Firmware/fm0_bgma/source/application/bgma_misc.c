/***************************************************************************//**
* \file bgma_misc.c
* \version 1.00
*
* \brief
* initialize the GPIO, external interrupt and ADC etc.
*
********************************************************************************
* Copyright 2016-2020, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#include "bgma_misc.h"

/******************************************************************************/
/* Func Name      :   bgma_io_initial                                         */
/* Description    :   implement BGMA IO initialization                        */
/* Parameters     :   none                                                    */
/* Return Value   :   none                                                    */
/******************************************************************************/
void bgma_io_initial(void)
{
    /* Initialize Red/Green LEDs */
    Gpio1pin_InitOut( GPIO1PIN_P3B, Gpio1pin_InitVal( 0u ) );   // Red LED
    Gpio1pin_InitOut( GPIO1PIN_P3C, Gpio1pin_InitVal( 0u ) );   // Green LED 
         
    /* Set POUTFLX (over-current detection) as input port*/
    Gpio1pin_InitIn ( GPIO1PIN_P4E, Gpio1pin_InitPullup( 0u ) );  // P4E
    // SetPinFunc_INT06_2(0u); 	                  // P4E
    // Gpio1pin_InitIn ( GPIO1PIN_P4E, Gpio1pin_InitPullup(1u));  // Pull-up    
    
    /* Set RSTX (reset MCU) as output port*/
    Gpio1pin_InitOut( GPIO1PIN_P52, Gpio1pin_InitVal( 1u ) );     // P52
    Gpio1pin_Put( GPIO1PIN_P52, 1);   // Output 'H'
      
    /* Set RSTMX as input port*/
    /* Monitor reset accessed by reset button in user board */
    SetPinFunc_INT00_0(0u); 	                  // P50
    // Gpio1pin_InitIn ( GPIO1PIN_P50, Gpio1pin_InitPullup(1u));  // Pull-up
    
    /* Set UVCCM as input port */
    /* Monitor UVCC of LPC, if BGM find power fall, an interrupt will be happened */
    SetPinFunc_INT01_0(0u); 	                  // P51
    Gpio1pin_InitIn ( GPIO1PIN_P51, Gpio1pin_InitPullup(1u));  // Pull-up
    
    /* Set OE as output pin */
    /* Controls the voltage of 1-line UART. When power on, we will control this pin to pull down DBG line*/
    Gpio1pin_InitOut( GPIO1PIN_P53, Gpio1pin_InitVal( 1u ) );     // P53
    Gpio1pin_Put( GPIO1PIN_P53, 1);   // Output 'H'
    
    /* Set POUTEN as output port */
    /* Control to power on/off LPC */
    bFM0P_GPIO_ADE_AN00 = 0;  // Disable pin ADC function
    Gpio1pin_InitOut( GPIO1PIN_P10, Gpio1pin_InitVal( 0u ) );     // P10
    Gpio1pin_Put( GPIO1PIN_P10, 0);   // Output 'L'
    
    /* Set Write ( reserve function ) as input port */
    bFM0P_GPIO_ADE_AN04 = 0;  // Disable pin ADC function
    Gpio1pin_InitIn ( GPIO1PIN_P14, Gpio1pin_InitPullup( 0u ) );  // P14
}

/******************************************************************************/
/* Func Name      :   enable_uvccm_int                                        */
/* Description    :   enable UVCCM pin external interrupt, INT01_0[P51]       */
/* Parameters     :   none                                                    */
/* Return Value   :   none                                                    */
/******************************************************************************/
void enable_uvccm_int(void)
{
    FM0P_GPIO_PFR5 |= 0x2;
    bFM0P_EXTI_ENIR_EN1  = 0;  // Disable external interrupt
    bFM0P_EXTI_EICL_ECL1 = 0;  // Clear external interrupt factor
    bFM0P_EXTI_ELVR_LA1  = 1;
    bFM0P_EXTI_ELVR_LB1  = 1;  // Detects the falling edge
    bFM0P_EXTI_ENIR_EN1  = 1;  // Enable external interrupt
    
    NVIC_ClearPendingIRQ(EXINT0_1_IRQn); 
    NVIC_SetPriority(EXINT0_1_IRQn, 3);
    NVIC_EnableIRQ(EXINT0_1_IRQn); 
}

/******************************************************************************/
/* Func Name      :   enable_rtsmx_int                                        */
/* Description    :   enable reset in pin external interrupt, INT00_0[P50]    */
/* Parameters     :   none                                                    */
/* Return Value   :   none                                                    */
/******************************************************************************/
void enable_rstmx_int(void)
{
    FM0P_GPIO_PFR5 |= 0x1;
    bFM0P_EXTI_ENIR_EN0  = 0;  // Disable external interrupt
    bFM0P_EXTI_EICL_ECL0 = 0;  // Clear external interrupt factor
    bFM0P_EXTI_ELVR_LA0  = 1;
    bFM0P_EXTI_ELVR_LB0  = 1;  // Detects the falling edge
    bFM0P_EXTI_ENIR_EN0  = 1;  // Enable external interrupt
    
    NVIC_ClearPendingIRQ(EXINT0_1_IRQn); 
    NVIC_SetPriority(EXINT0_1_IRQn, 3);
    NVIC_EnableIRQ(EXINT0_1_IRQn); 
}

/******************************************************************************/
/* Func Name      :   enable_poutflx_int                                      */
/* Description    :   enable power monitor pin interrupt, INT06_2[P4E]        */
/* Parameters     :   none                                                    */
/* Return Value   :   none                                                    */
/******************************************************************************/
void enable_poutflx_int(void)
{
    FM0P_GPIO_PFR6 |= 0x4000;
    bFM0P_EXTI_ENIR_EN6  = 0;  // Disable external interrupt
    bFM0P_EXTI_EICL_ECL6 = 0;  // Clear external interrupt factor
    bFM0P_EXTI_ELVR_LA6  = 1;
    bFM0P_EXTI_ELVR_LB6  = 1;  // Detects the falling edge
    bFM0P_EXTI_ENIR_EN6  = 1;  // Enable external interrupt
    
    NVIC_ClearPendingIRQ(EXINT6_7_IRQn); 
    NVIC_SetPriority(EXINT6_7_IRQn, 3);
    NVIC_EnableIRQ(EXINT6_7_IRQn); 
}

/******************************************************************************/
/* Func Name      :   EXINT0_1_IRQHandler                                     */
/* Description    :   UVCCM, RSTMX interrupt subroutin                        */
/* Parameters     :   none                                                    */
/* Return Value   :   none                                                    */
/******************************************************************************/
void EXINT0_1_IRQHandler(void)
{   
    /* RSTMX interrupt, target MCU reset */
    if ( (1u==bFM0P_EXTI_EIRR_ER0) && (0u==IO_RSTMX) )
    {
        power_state |= USER_RST;
        bFM0P_EXTI_ENIR_EN0 = 0u;  // Disable this external interrupt
    }
    /* UVCCM interrupt, target MCU power off */
    if ( (1u==bFM0P_EXTI_EIRR_ER1) && (0u==IO_UVCCM) )
    {
        /* leak currentfor HV125 chip not compitable, UART_Rxd pin */
        Gpio1pin_InitOut( GPIO1PIN_P11, Gpio1pin_InitVal( 0u ) );     // P11, SI
        Gpio1pin_Put( GPIO1PIN_P11, 0);   // Output 'L'
        bFM0P_EXTI_ENIR_EN1 = 0u;  // Disable this external interrupt
        /* ”–“…Œ £ø*/
        /* RSTMX (P50), output 'L' ??? */
        //Gpio1pin_InitOut( GPIO1PIN_P50, Gpio1pin_InitVal( 0u ) );     // P50
        //Gpio1pin_Put( GPIO1PIN_P50, 0);   // Output 'L'
        
        /* Re-configurate system status */
        power_state |= LOW_POWER;
        monitor_state &= ~(CR_FINE|TRIMMING|BRTUP_ON);
        
        /* Re-configurate SIN1_1, SOT1_1 as gpio function */
        Gpio1pin_InitOut( GPIO1PIN_P12, Gpio1pin_InitVal( 0u ) );     // P12
        Gpio1pin_Put( GPIO1PIN_P12, 1);   // Output 'L'
        Gpio1pin_InitIn ( GPIO1PIN_P11, Gpio1pin_InitPullup( 0u ) );  // P11 input
        bFM0P_GPIO_ADE_AN01 = 0;  // Disable pin ADC function
        bFM0P_GPIO_ADE_AN02 = 0;  // Disable pin ADC function 
    }
    bFM0P_EXTI_EICL_ECL0 = 0u;  // Clear interrupt flag
    bFM0P_EXTI_EICL_ECL1 = 0u;  // Clear interrupt flag
    /* Clear the interrupt flag */
    NVIC_ClearPendingIRQ(EXINT0_1_IRQn); 
}

/******************************************************************************/
/* Func Name      :   EXINT6_7_IRQHandler                                     */
/* Description    :   POUTFLX (over-current detection) extern interrupt       */
/* Parameters     :   none                                                    */
/* Return Value   :   none                                                    */
/******************************************************************************/
void EXINT6_7_IRQHandler(void)
{
    if ( 0u == IO_POUTFLX )
    {
        power_state |= OVER_CURRENT;    
        /* Control to power off LPC, P10 [POUTEN] */
        Gpio1pin_Put( GPIO1PIN_P10, 0);   // Output 'L'
        bFM0P_EXTI_ENIR_EN6  = 0;  // Disable external interrupt
    }

    bFM0P_EXTI_EICL_ECL6 = 0u;  // Clear interrupt flag
    NVIC_ClearPendingIRQ(EXINT6_7_IRQn); 
}

/******************************************************************************/
/* Func Name      :   power_on_init                                           */
/* Description    :   implement power on initialization                       */
/* Parameters     :   none                                                    */
/* Return Value   :   none                                                    */
/******************************************************************************/
void power_on_init(void)
{
    power_state &= ~LOW_POWER;     /* clear LOW_POWER flag */
    power_state &= ~OVER_CURRENT;  /* clear OVER_CURRENT flag */
    monitor_state &= ~MCU_RUN;     /* clear MCU_RUN flag,set MCU_BREAK flag */
    Delay_ms(1000);                /* 1000ms, wait 1500*700us */
    uart_init(UART_BAUD_RATE_62500); /* initial UART */
    enable_uvccm_int();             
    enable_rstmx_int();
    enable_poutflx_int();
    monitor_state |= TRIMMING;         /* doing trim after power on */
    retry_counter = 0;
    if ((monitor_state & MON_START) == MON_START){
        monitor_state &= ~MON_START; /* exit monitor mode */
        power_state |= LOWPOWERIDT;  /* need indicate power off during in monitor mode */
        power_state &= ~RST_ERROR;   /* clear RST error flag after exit monitor mode */
    }
}

/* [] END OF FILE */
