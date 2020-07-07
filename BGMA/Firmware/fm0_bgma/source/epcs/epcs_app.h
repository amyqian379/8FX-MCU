/******************************************************************************/
/* File Name      : epcs_app.h                                                */
/* Project        : BGM Adapter                                               */
/* Module Function: application of epcs module                                */
/* Author         : lijiale                                                   */
/* Version        : 1.0                                                       */
/* Date           : 2010/03/15                                                */
/* History        : 2010/03/15  create                                        */
/*                  Copyright 2010 FUJITSU ELECTRONICS INC.  LIMITED          */
/******************************************************************************/

#ifndef __EPCS_APP_INC__
#define __EPCS_APP_INC__

/******************************************************************************/
/*  Headers                                                                   */
/******************************************************************************/
#include "epcs_common.h"

/******************************************************************************/
/*  Constant Definition                                                       */
/******************************************************************************/
#define EPCS_SELECT_DEFAULT_APP    (0x00)  /* select default application */
#define EPCS_SELECT_APPOINTED_APP  (0x01)  /* select appointed application */
#define EPCS_SELECT_DUMMY_APP      (0x02)  /* select dummy application */

#define EPCS_DEFAULT_HEADER_START_ADDR      (0x0F0000)
#define EPCS_DEFAULT_HEADER_END_ADDR        (0x0F000C)

/******************************************************************************/
/*  Global Variable Definition                                                */
/******************************************************************************/
extern const uint32_t g_EpcsDefaultHeader[4];
extern uint32_t g_EpcsFROMFailedAddr;   /* address of failed operation at FlashROM */

/******************************************************************************/
/*  Register Redefinition                                                     */
/******************************************************************************/

/******************************************************************************/
/*  Global Function Prototypes                                                */
/******************************************************************************/
void EPCS_APP_Main(void);
void EPCS_APP_GetBgmaInfo(uint8_t* info, uint8_t* size);

#endif
