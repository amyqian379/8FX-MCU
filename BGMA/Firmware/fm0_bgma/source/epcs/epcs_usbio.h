/******************************************************************************/
/* File Name      : epcs_usbio.h                                              */
/* Project        : BGM Adapter                                               */
/* Module Function: Basic USB I/O                                             */
/* Author         : lijiale                                                   */
/* Version        : 1.0                                                       */
/* Date           : 2010/03/15                                                */
/* History        : 2010/03/15  create                                        */
/*                  Copyright 2010 FUJITSU ELECTRONICS INC.  LIMITED          */
/******************************************************************************/

#ifndef __EPCS_USBIO_INC__
#define __EPCS_USBIO_INC__

/******************************************************************************/
/*  Headers                                                                   */
/******************************************************************************/
#include "epcs_common.h"

/******************************************************************************/
/*  Constant Definition                                                       */
/******************************************************************************/
/* Enable or disable the USB IO test, 1-enable, 0-disable */
#define USB_IO_TEST_ENABLED         0

/******************************************************************************/
/*  Global Variable Definition                                                */
/******************************************************************************/

/******************************************************************************/
/*  Register Redefinition                                                     */
/******************************************************************************/

/******************************************************************************/
/*  Global Function Prototypes                                                */
/******************************************************************************/
int32_t epcs_initialize(void);
int32_t epcs_check_read(void);
int32_t epcs_read_data(uint8_t* buffer, uint32_t offset, uint32_t length);
int32_t epcs_clear_read(void);
int32_t epcs_check_write(void);
int32_t epcs_write_data(uint8_t* buffer, uint32_t length);
int32_t epcs_clear_write(void);
int32_t epcs_reset(void);

#if (USB_IO_TEST_ENABLED)
void epcs_test(void);
#endif

#endif
