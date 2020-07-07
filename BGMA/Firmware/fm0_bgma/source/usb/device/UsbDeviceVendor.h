/*******************************************************************************
* Copyright (C) 2013-2020, Cypress Semiconductor Corporation or a              *
* subsidiary of Cypress Semiconductor Corporation.  All rights reserved.       *
*                                                                              *
* This software, including source code, documentation and related              *
* materials ("Software"), is owned by Cypress Semiconductor Corporation or     *
* one of its subsidiaries ("Cypress") and is protected by and subject to       *
* worldwide patent protection (United States and foreign), United States       *
* copyright laws and international treaty provisions. Therefore, you may use   *
* this Software only as provided in the license agreement accompanying the     *
* software package from which you obtained this Software ("EULA").             *
*                                                                              *
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,     *
* non-transferable license to copy, modify, and compile the                    *
* Software source code solely for use in connection with Cypress's             *
* integrated circuit products.  Any reproduction, modification, translation,   *
* compilation, or representation of this Software except as specified          *
* above is prohibited without the express written permission of Cypress.       *
*                                                                              *
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO                         *
* WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING,                         *
* BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED                                 *
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A                              *
* PARTICULAR PURPOSE. Cypress reserves the right to make                       *
* changes to the Software without notice. Cypress does not assume any          *
* liability arising out of the application or use of the Software or any       *
* product or circuit described in the Software. Cypress does not               *
* authorize its products for use in any products where a malfunction or        *
* failure of the Cypress product may reasonably be expected to result in       *
* significant property damage, injury or death ("High Risk Product"). By       *
* including Cypress's product in a High Risk Product, the manufacturer         *
* of such system or application assumes all risk of such use and in doing      *
* so agrees to indemnify Cypress against all liability.                        *
*******************************************************************************/
/******************************************************************************/
/** \file UsbDeviceVendor.h
 **
 ** USB vendor device class
 **
 ** History:
 **   - 2020-03-30    0.1  KOZU  Create the file.
 *****************************************************************************/
#ifndef __USBDEVICEVENDOR_H__
#define __USBDEVICEVENDOR_H__

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "usb.h"
#include <stdio.h>

#ifndef USBDEVICEVENDOR_ENABLED
    #define USBDEVICEVENDOR_ENABLED OFF
#endif

#if ((FM_PERIPHERAL_USB_DEVICE_ENABLED == ON) && (USBDEVICEVENDOR_ENABLED == ON))
#include "usbdevice.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define')                           */
/*****************************************************************************/
#define BUFFER_SIZE_ENDPOINTOUT             64u

/* Enable or disable the debug, 0-disable, 1-enable */
#define USB_VENDOR_CLASS_DEBUG              (0u)
#if (USB_VENDOR_CLASS_DEBUG)
 #define USB_VENDOR_DBG_PRINTF(...)         (printf(__VA_ARGS__))
#else
 #define USB_VENDOR_DBG_PRINTF(...)
#endif

/*****************************************************************************/
/* Global type definitions ('typedef')                                       */
/*****************************************************************************/
/* usb device configuration changed function pointer */
typedef void (*usb_conf_func_ptr_t)(stc_usbn_t* pstcUsb, boolean_t configured);
/* usb data transfer complete function pointer */
typedef void (*trans_com_func_ptr_t)(stc_usbn_t* pstcUsb, const uint8_t* pu8Buf, uint32_t u32Len);

/*****************************************************************************/
/* Global variable declarations ('extern', definition in C source)           */
/*****************************************************************************/
extern volatile boolean_t bVendorReady;

/*****************************************************************************/
/* Global function prototypes ('extern', definition in C source)             */
/*****************************************************************************/
void UsbDeviceVendor_Init(stc_usbn_t* pstcUsb);
boolean_t UsbDeviceVendor_IsReady(void);
void UsbDeviceVendor_SetConfCallback(usb_conf_func_ptr_t cb);
void UsbDeviceVendor_SetVendorRequestCallback(usbdevice_setuprequest_func_ptr_t cb);
void UsbDeviceVendor_ReceiveDataControl(stc_usbn_t* pstcUsb, uint8_t* pu8Buf, uint32_t u32Len, trans_com_func_ptr_t cb);
en_result_t UsbDeviceVendor_SendData(uint8_t* pu8Buf, uint32_t u32Len, trans_com_func_ptr_t cb);
en_result_t UsbDeviceVendor_ReceiveData(uint8_t* pu8Buf, uint32_t u32Len, trans_com_func_ptr_t cb);
en_result_t UsbDeviceVendor_StallControlEndpoint(void);
en_result_t UsbDeviceVendor_StallInEndpoint(void);
en_result_t UsbDeviceVendor_StallOutEndpoint(void);

#ifdef __cplusplus
}
#endif

#else
    #define UsbDeviceVendor_Init(x) ;
#endif
#endif /* __USBDEVICEVENDOR_H__*/
