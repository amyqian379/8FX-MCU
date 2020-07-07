/***************************************************************************//**
* \file     systick.h
* \version  1.00
*
* \brief
* Software timer which used to generate a timeout judgment
*
********************************************************************************
* \copyright
* Copyright 2016-2020, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#ifndef __BGMA_SYSTICK__
#define __BGMA_SYSTICK__

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "mcu.h"
#include <stdbool.h>

#define ClrTimeOut(pTimer)         ( TimerOverTimeMs(pTimer, 0) )
#define IsTimeOut(pTimer, value)   ( TimerOverTimeMs(pTimer, value) )

#ifdef __cplusplus
extern "C" {
#endif

void    InitSystick(void);
uint8_t TimerOverTimeMs(uint32_t *pTimer, uint32_t TimeOutVal);
void    Delay_ms(uint32_t time);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __BGMA_SYSTICK__ */

/* [] END OF FILE */
