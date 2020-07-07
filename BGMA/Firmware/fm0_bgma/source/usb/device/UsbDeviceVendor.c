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
/** \file UsbDeviceVendor.c
 **
 ** USB vendor device class
 **
 ** History:
 **   - 2020-03-30    0.1  KOZU  Create the file.
 *****************************************************************************/

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "UsbDeviceVendor.h"

#if ((FM_PERIPHERAL_USB_DEVICE_ENABLED == ON) && (USBDEVICEVENDOR_ENABLED == ON))
/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/
volatile boolean_t bVendorReady = FALSE;
static stc_usbn_t* pstcUsbHandle = NULL;
usbdevice_setuprequest_func_ptr_t pfnVendorRequestCallback = NULL;
usb_conf_func_ptr_t pfnDeviceConfCallback = NULL;
static stc_usbn_endpoint_data_t* pstcEndpoint0 = NULL;

/* endpoint 0 receive variables */
static uint8_t *pu8Ep0RecBuf = NULL, *pu8Ep0OutBuf;
static uint32_t u32Ep0RecLen = 0, u32Ep0OutLen;
static trans_com_func_ptr_t pstnEp0RecFunc = NULL;

/* IN endpoint */
static stc_usbn_endpoint_data_t* pstcEndpointIN = NULL;
static stc_usbn_endpoint_buffer_t stcEndpointBufferIN;
static trans_com_func_ptr_t pstnEndpointInTransComFunc = NULL;

/* OUT endpoint */
static stc_usbn_endpoint_data_t* pstcEndpointOUT = NULL;
static stc_usbn_endpoint_buffer_t stcEndpointBufferOUT;
static trans_com_func_ptr_t pstnEndpointOutTransComFunc = NULL;

/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/
static void ConfCallback(stc_usbn_t* pstcUsb);
static void VendorRequestCallback(stc_usbn_t* pstcUsb, stc_usb_request_t* pstcSetup);
static void InEpCallback(stc_usbn_t* pstcUsb, struct stc_usbn_endpoint_data* pstcEndpoint);
static void OutEpCallback(stc_usbn_t* pstcUsb, struct stc_usbn_endpoint_data* pstcEndpoint);

/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/**
 ******************************************************************************
 ** Is called to initialize this class (usally in UsbConfig.c)
 **
 ** \param pstcUsb      USB Handle
 *****************************************************************************/
void UsbDeviceVendor_Init(stc_usbn_t* pstcUsb)
{
    stc_usbdevice_class_config_t stcUsbClassConfig;
    stc_usbdevice_endpoint_config_t stcEndpointConfig;
    uint8_t* pu8Interface = NULL;
    uint8_t u8InterfaceLength = 0;
    uint8_t i = 0;
    
    bVendorReady = FALSE;
    pfnDeviceConfCallback = NULL;
    pstnEndpointInTransComFunc = NULL;
    pstnEndpointOutTransComFunc = NULL;
    pstcUsbHandle = pstcUsb;
    stcUsbClassConfig.u8InterfaceNumber        = 0xFF; // Do not use fix interface number, choose by class, subclass, protocol
    stcUsbClassConfig.u8InterfaceClass         = 0xFF;
    stcUsbClassConfig.u8InterfaceSubClass      = 0xFF;
    stcUsbClassConfig.u8InterfaceProtocoll     = 0xFF;
    stcUsbClassConfig.pfnSetupRequestCallback  = NULL; // No setup request callback handled
    stcUsbClassConfig.pfnConnectionCallback    = NULL; // No connection callback handled
    stcUsbClassConfig.pfnDisconnectionCallback = NULL; // No disconnection callback handled
    stcUsbClassConfig.pfnConfCallback          = ConfCallback; // Callback for configuration set
    stcUsbClassConfig.pfnVendorRequestCallback = VendorRequestCallback; // Callback for vendor request
    UsbDevice_RegisterVendorClass(pstcUsb, &stcUsbClassConfig, &pu8Interface, &u8InterfaceLength);
    
    for(i = 0;i < u8InterfaceLength;) {
        if (USBDESCR_ENDPOINT == pu8Interface[i + 1]) {
            stcEndpointConfig.u8EndpointAddress = pu8Interface[i + 2];
            // OUT endpoint
            if(((stcEndpointConfig.u8EndpointAddress) & 0x80) == 0) {
                stcEndpointConfig.pfnRxTxCallback = OutEpCallback;
                stcEndpointConfig.pstcEndpointBuffer = &stcEndpointBufferOUT;
                pstcEndpointOUT = UsbDevice_SetupEndpoint(pstcUsb, &stcEndpointConfig);
                //UsbDevice_ReceiveData(pstcUsb, pstcEndpointOUT, au8EndpointBufferOUT, BUFFER_SIZE_ENDPOINTOUT, UsbIRQ);
            } else  { // IN endpoint
                stcEndpointConfig.pfnRxTxCallback = InEpCallback;
                stcEndpointConfig.pstcEndpointBuffer = &stcEndpointBufferIN;
                pstcEndpointIN = UsbDevice_SetupEndpoint(pstcUsb, &stcEndpointConfig);
                pstcEndpointIN->bAutomaticNullTermination = TRUE;
            }
        }
        i += pu8Interface[i];
    }
}

/**
 ******************************************************************************
 ** \brief Configuration change callback, used to see if configuration is set
 **        or cleared (USB Set Configuration request received)
 **
 ** \param pstcUsb Pointer to USB instance
 ******************************************************************************/
static void ConfCallback(stc_usbn_t* pstcUsb)
{
    if(UsbDevice_GetStatus(pstcUsb) == UsbConfigured) {
        bVendorReady = TRUE;
        pstnEndpointInTransComFunc = NULL;
        pstnEndpointOutTransComFunc = NULL;
        pstcEndpoint0 = Usb_GetEndpointPtr(pstcUsb, 0x00);
        USB_VENDOR_DBG_PRINTF("Set_Conf request received\r\n");
        if(pfnDeviceConfCallback != NULL) {
            pfnDeviceConfCallback(pstcUsb, TRUE);
        }
    } else {
        bVendorReady = FALSE;
        pstnEndpointInTransComFunc = NULL;
        pstnEndpointOutTransComFunc = NULL;
    }
}

/**
 ******************************************************************************
 ** Vendor Request handling
 **
 ** \param pstcUsb   USB handle
 ** \param pstcSetup Received Setup
 *****************************************************************************/
static void VendorRequestCallback(stc_usbn_t* pstcUsb, stc_usb_request_t* pstcSetup)
{
    if(NULL != pfnVendorRequestCallback) {
        pfnVendorRequestCallback(pstcUsb, pstcSetup);
    }
}

/**
 ******************************************************************************
 ** \brief control receive callback function
 **
 ** \param pstcUsb      USB handle
 ** \param pstcEndpoint Endpoint handle
 ******************************************************************************/
static void Endpoint0RxCallback(stc_usbn_t* pstcUsb, stc_usbn_endpoint_data_t* pstcEndpoint)
{
    uint32_t size = pstcEndpoint->pstcEndpointBuffer->u32DataSize;
    
    if(u32Ep0RecLen < size) {
        size = u32Ep0RecLen;
    }
    USB_VENDOR_DBG_PRINTF("0R:%d\r\n", (int)size);
    memcpy(pu8Ep0RecBuf, pstcEndpoint->pstcEndpointBuffer->pu8Buffer, size);
    pu8Ep0RecBuf += size;
    u32Ep0RecLen -= size;
    u32Ep0OutLen += size;
    if(1 < u32Ep0RecLen) {
        UsbDevice_ReceiveDataControl(pstcUsb, Endpoint0RxCallback);
    } else {
        if(NULL != pstnEp0RecFunc)  {
            pstnEp0RecFunc(pstcUsb, pu8Ep0OutBuf, u32Ep0OutLen);
            pstnEp0RecFunc = NULL;
        }
    }
}

/**
 ******************************************************************************
 ** \brief IN endpoint callback function
 **
 ** \param pstcUsb      USB handle
 ** \param pstcEndpoint Endpoint handle
 ******************************************************************************/
static void InEpCallback(stc_usbn_t* pstcUsb, struct stc_usbn_endpoint_data* pstcEndpoint)
{
    if((NULL == pstcUsb) || (NULL == pstcEndpoint)) {
       return;
    }
    USB_VENDOR_DBG_PRINTF("I:%d\r\n", (int)(pstcEndpoint->pstcEndpointBuffer->u32DataSize));
    if(NULL != pstnEndpointInTransComFunc) {
        pstnEndpointInTransComFunc(pstcUsb, pstcEndpoint->pstcEndpointBuffer->pu8Buffer, pstcEndpoint->pstcEndpointBuffer->u32DataSize);
        pstnEndpointInTransComFunc = NULL;
    }
}

/**
 ******************************************************************************
 ** \brief OUT endpoint callback function
 **
 ** \param pstcUsb      USB handle
 ** \param pstcEndpoint Endpoint handle
 ******************************************************************************/
static void OutEpCallback(stc_usbn_t* pstcUsb, struct stc_usbn_endpoint_data* pstcEndpoint)
{
    if((NULL == pstcUsb) || (NULL == pstcEndpoint)) {
       return;
    }
    USB_VENDOR_DBG_PRINTF("O:%d\r\n", (int)(pstcEndpoint->pstcEndpointBuffer->u32DataSize));
    if(NULL != pstnEndpointOutTransComFunc) {
        pstnEndpointOutTransComFunc(pstcUsb, pstcEndpoint->pstcEndpointBuffer->pu8Buffer, pstcEndpoint->pstcEndpointBuffer->u32DataSize);
        pstnEndpointOutTransComFunc = NULL;
    }
}


/**
 ******************************************************************************
 ** \brief Get the vendor class status
 **
 ** \return status
 ******************************************************************************/
boolean_t UsbDeviceVendor_IsReady(void)
{
    return bVendorReady;
}

/**
 ******************************************************************************
 ** Set device configuration callback
 *****************************************************************************/
void UsbDeviceVendor_SetConfCallback(usb_conf_func_ptr_t cb)
{
    pfnDeviceConfCallback = cb;
}

/**
 ******************************************************************************
 ** Set vendor requst callback
 *****************************************************************************/
void UsbDeviceVendor_SetVendorRequestCallback(usbdevice_setuprequest_func_ptr_t cb)
{
    pfnVendorRequestCallback = cb;
}

/**
 ******************************************************************************
 ** \brief Initiate endpoint0 receiving data (OUT direction)
 **
 ** \param pstcUsb Pointer to USB instance
 ** \param pu8Buffer Pointer to data buffer
 ** \param u32DataSize Size of data to be received
 **
 ** \return none
 ******************************************************************************/
void UsbDeviceVendor_ReceiveDataControl(stc_usbn_t* pstcUsb, uint8_t* pu8Buf, uint32_t u32Len, trans_com_func_ptr_t cb)
{
    pu8Ep0RecBuf = pu8Buf;
    u32Ep0RecLen = u32Len;
    pu8Ep0OutBuf = pu8Buf;
    u32Ep0OutLen = 0;
    pstnEp0RecFunc = cb;
    UsbDevice_ReceiveDataControl(pstcUsb, Endpoint0RxCallback);
}

/**
 ******************************************************************************
 ** \brief Initiate IN endpoint
 **
 ** \param pu8Buf Pointer to data buffer
 ** \param u32Len Size of data to be received
 **
 ** \return result
 ******************************************************************************/
en_result_t UsbDeviceVendor_SendData(uint8_t* pu8Buf, uint32_t u32Len, trans_com_func_ptr_t cb)
{
    if(bVendorReady == FALSE) {
        return Error;
    }
    pstnEndpointInTransComFunc = cb;
    return UsbDevice_SendData(pstcUsbHandle, pstcEndpointIN, pu8Buf, u32Len, UsbIRQ);
}

/**
 ******************************************************************************
 ** \brief Initialize OUT endpoint to receive data
 **
 ** \return result
 ******************************************************************************/
en_result_t UsbDeviceVendor_ReceiveData(uint8_t* pu8Buf, uint32_t u32Len, trans_com_func_ptr_t cb)
{
    if(bVendorReady == FALSE) {
        return Error;
    }
    pstnEndpointOutTransComFunc = cb;
    return UsbDevice_ReceiveData(pstcUsbHandle, pstcEndpointOUT, pu8Buf, u32Len, UsbIRQ);
}

/**
 ******************************************************************************
 ** \brief Stall control endpoint
 **
 ** \return result
 ******************************************************************************/
en_result_t UsbDeviceVendor_StallControlEndpoint(void)
{
    return Usb_HalStallEndpoint(pstcEndpoint0);
}

/**
 ******************************************************************************
 ** \brief Stall vendor in endpoint
 **
 ** \return result
 ******************************************************************************/
en_result_t UsbDeviceVendor_StallInEndpoint(void)
{
    return Usb_HalStallEndpoint(pstcEndpointIN);
}

/**
 ******************************************************************************
 ** \brief Stall vendor out endpoint
 **
 ** \return result
 ******************************************************************************/
en_result_t UsbDeviceVendor_StallOutEndpoint(void)
{
    return Usb_HalStallEndpoint(pstcEndpointOUT);
}

#endif
/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/

