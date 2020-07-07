/******************************************************************************/
/* File Name      : epcs_vendor.h                                             */
/* Project        : BGM Adapter                                               */
/* Module Function: vendor command process                                    */
/* Author         : lijiale                                                   */
/* Version        : 1.0                                                       */
/* Date           : 2010/03/15                                                */
/* History        : 2010/03/15  create                                        */
/*                  Copyright 2010 FUJITSU ELECTRONICS INC.  LIMITED          */
/******************************************************************************/
#ifndef __EPCS_VENDOR_INC__
#define __EPCS_VENDOR_INC__

/******************************************************************************/
/*  Headers                                                                   */
/******************************************************************************/
#include "usb.h"
#include "config.h"

/******************************************************************************/
/*  Constant Definition                                                       */
/******************************************************************************/
#define VENDOR_GREEN_LED_INIT()    Gpio1pin_InitOut(GPIO1PIN_P3B, Gpio1pin_InitPullup(0u))
#define VENDOR_RED_LED_INIT()      Gpio1pin_InitOut(GPIO1PIN_P3C, Gpio1pin_InitPullup(0u))
#define VENDOR_GREEN_LED_ON()      Gpio1pin_Put(GPIO1PIN_P3B, (1))
#define VENDOR_GREEN_LED_OFF()     Gpio1pin_Put(GPIO1PIN_P3B, (0))
#define VENDOR_RED_LED_ON()        Gpio1pin_Put(GPIO1PIN_P3C, (1))
#define VENDOR_RED_LED_OFF()       Gpio1pin_Put(GPIO1PIN_P3C, (0))

/******************************************************************************/
/*  Global Variable Definition                                                */
/******************************************************************************/

/******************************************************************************/
/*  Register Redefinition                                                     */
/******************************************************************************/

/******************************************************************************/
/*  Global Function Prototypes                                                */
/******************************************************************************/
/* vendor command process */
extern void VENDOR_CommandProcess(stc_usbn_t* pstcUsb, stc_usb_request_t* setup_info);

#endif
