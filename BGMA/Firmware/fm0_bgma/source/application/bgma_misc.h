/***************************************************************************//**
* \file     bgma_misc.h
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
#ifndef __BGMA_MISC__
#define __BGMA_MISC__

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "mcu.h"
#include "systick.h"
#include "LPCdef.h"
#include "UARTio.h"

#ifdef __cplusplus
extern "C" {
#endif

void bgma_io_initial(void);
void enable_uvccm_int(void);
void enable_rstmx_int(void);
void enable_poutflx_int(void);
void power_on_init(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __BGMA_MISC__ */

/* [] END OF FILE */
