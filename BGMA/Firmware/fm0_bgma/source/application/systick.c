/***************************************************************************//**
* \file systick.c
* \version 1.00
*
* \brief
* Software timer which used to generate a timeout judgment
*
********************************************************************************
* Copyright 2016-2020, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#include "systick.h"

/* Local time unit ms */
static uint32_t SystemTime = 0;

/*******************************************************************************
* Function Name: SysTick_Handler
****************************************************************************//**
*
* \brief System tick interrupt ISR
*
* \param None
*
* \return None
*
*******************************************************************************/
void SysTick_Handler(void)
{
    SystemTime++;
}

/*******************************************************************************
* Function Name: InitSystick
****************************************************************************//**
*
* \brief Initialize system tick
*
* \param None
*
* \return None
*
*******************************************************************************/
void InitSystick(void)
{
    SysTick_Config(__HCLK/1000);          // Configure and start SysTick timer to fire every msec
}

/*******************************************************************************
* Function Name: TimerOverTimeMs
****************************************************************************//**
*
* \brief This function is used by software timer.
* \      And check for timeover occurance in mili-seconds
*
* \param pTimer Pointer of timer counter
*
* \param TimeOutVal The value is used to compare whether the timeout is happened
* \                 And 0 means clear this counter
*
* \return uint8_t 0 mean not timetut, others mean timeout
*
*******************************************************************************/
uint8_t TimerOverTimeMs(uint32_t *pTimer, uint32_t TimeOutVal)
{
    uint32_t CurrentTime;
    uint32_t ElapseTime;
    
    /* Store current system time */
    CurrentTime = SystemTime;
    /* Reset setting */
    if ( 0 == TimeOutVal ) 
    {
        *pTimer = CurrentTime; 
        return 0u;
    }
    /* Over a round */
    if ( (*pTimer) > CurrentTime )
    {
        ElapseTime = 0xFFFFFFFF - (*pTimer) + CurrentTime + 1;
    }
    else
    {
        ElapseTime = CurrentTime - (*pTimer);
    }
    
    /* Check if timeout or not */
    if ( ElapseTime >= TimeOutVal )
    {
        *pTimer += TimeOutVal;
        return 1u;
    }
    return 0u;
}
 
/*******************************************************************************
* Function Name: Delay_ms
****************************************************************************//**
*
* \brief Delay function
*
* \param time delay time
*
* \return None
*
*******************************************************************************/
void Delay_ms(uint32_t time)
{
    uint32_t cnt;
    TimerOverTimeMs(&cnt, 0);
    while (1)
    {
        if ( TimerOverTimeMs(&cnt, time) )
            break;
    }
}


/* [] END OF FILE */
