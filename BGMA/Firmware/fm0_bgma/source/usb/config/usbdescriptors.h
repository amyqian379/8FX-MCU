/*******************************************************************************
* Copyright (C) 2013-2016, Cypress Semiconductor Corporation or a              *
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
/** \file UsbDescriptors.h
 **
 ** USB Descriptors File
 **
 ** History:
 **   - 2020-03-20  1.0  KOZU  New file for BGMA
 *****************************************************************************/
#ifndef __USBDESCRIPTORS_H__
#define __USBDESCRIPTORS_H__

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "usb.h"

/*****************************************************************************/
/* Global pre-processor symbols/macros ('#define')                           */
/*****************************************************************************/
/* get lower 1 byte of 16 bit data */
#define LOBYTE(hw)          ((uint8_t) ((uint16_t) (hw) & 0x00FF))
/* get upper 1 byte of 16 bit data */
#define HIBYTE(hw)          ((uint8_t) ((uint16_t) (hw) >> 8))

/*------------ USB descriptor configuration-----------------------------------*/
#define USB_VENDOR_ID       (0x04C5)   /* Vendor ID(fujitsu) */
#define USB_PRODUCT_ID      (0x2024)   /* Product ID */
#define USB_BCD_DEVICE      (0x0200)   /* USB Specification Release Number in Binary-Coded Decimal */

/*****************************************************************************/
/* Global type definitions ('typedef')                                       */
/*****************************************************************************/
#define USBDESCRIPTORS_STRINGDESCRIPTOR_COUNT (uint32_t)(sizeof(pstcStringDescriptors) / sizeof(pstcStringDescriptors[0]))


/*****************************************************************************/
/* Global variable declarations ('extern', definition in C source)           */
/*****************************************************************************/
const uint8_t au8DeviceDescriptor[18] = 
{
    ///DEVICE DESCRIPTOR
    0x12,    ///bLength: Length of this descriptor
    0x01,    ///bDescriptorType: Device Descriptor Type
    0x00,    ///bcdUSB: USB Version
    0x02,    ///bcdUSB: USB Version
    0xFF,    ///bDeviceClass: Class Code: VENDOR_SPECIFIC
    0xFF,    ///bDeviceSubClass: Sub Class Code
    0xFF,    ///bDeviceProtocol: Protocol Code
    0x40,    ///bMaxPacketSize0: Maximum size of endpoint 0
    LOBYTE(USB_VENDOR_ID),    ///idVendor: Vendor ID
    HIBYTE(USB_VENDOR_ID),    ///idVendor: Vendor ID
    LOBYTE(USB_PRODUCT_ID),    ///idProduct: Product ID
    HIBYTE(USB_PRODUCT_ID),    ///idProduct: Product ID
    LOBYTE(USB_BCD_DEVICE),    ///bcdDevice: Release Number
    HIBYTE(USB_BCD_DEVICE),    ///bcdDevice: Release Number
    0x01,    ///iManufacture: String-Index of Manufacture
    0x02,    ///iProduct: String-Index of Product
    0x03,    ///iSerialNumber: String-Index of Serial Number
    0x01     ///bNumConfigurations: Number of possible configurations
};

const uint8_t au8ConfigDescriptor[32] =
{        ///CONFIG DESCRIPTOR(1)
        0x09,    ///bLength: Length of this descriptor
        0x02,    ///bDescriptorType: Config Descriptor Type
        32,      ///wTotalLength: Total Length with all interface- and endpoint descriptors
        0x00,    ///wTotalLength: Total Length with all interface- and endpoint descriptors
        0x01,    ///bNumInterfaces: Number of interfaces
        0x01,    ///iConfigurationValue: Number of this configuration
        0x04,    ///iConfiguration: String index of this configuration
        0x80,    ///bmAttributes: Remote-Wakeup not supported
        0xFA,    ///MaxPower: (in 2mA)
            ///INTERFACE DESCRIPTOR(0)
            0x09,    ///bLength: Length of this descriptor
            0x04,    ///bDescriptorType: Interface Descriptor Type
            0x00,    ///bInterfaceNumber: Interface Number
            0x00,    ///bAlternateSetting: Alternate setting for this interface
            0x02,    ///bNumEndpoints: Number of endpoints in this interface excluding endpoint 0
            0xFF,    ///iInterfaceClass: Class Code: VENDOR_SPECIFIC
            0xFF,    ///iInterfaceSubClass: SubClass Code
            0xFF,    ///bInterfaceProtocol: Protocol Code
            0x00,    ///iInterface: String index
                ///ENDPOINT DESCRIPTOR(1)
                0x07,    ///bLength: Length of this descriptor
                0x05,    ///bDescriptorType: Endpoint Descriptor Type
                0x82,    ///bEndpointAddress: Endpoint address (IN,EP2)
                0x02,    ///bmAttributes: Transfer Type: BULK_TRANSFER
                0x40,    ///wMaxPacketSize: Endpoint Size
                0x00,    ///wMaxPacketSize: Endpoint Size
                0x00,    ///bIntervall: Polling Intervall
                ///ENDPOINT DESCRIPTOR(0)
                0x07,    ///bLength: Length of this descriptor
                0x05,    ///bDescriptorType: Endpoint Descriptor Type
                0x01,    ///bEndpointAddress: Endpoint address (OUT,EP1)
                0x02,    ///bmAttributes: Transfer Type: BULK_TRANSFER
                0x40,    ///wMaxPacketSize: Endpoint Size
                0x00,    ///wMaxPacketSize: Endpoint Size
                0x00     ///bIntervall: Polling Intervall
};

const stc_usbdevice_stringdescriptor_t pstcStringDescriptors[] =
{
    {"FUJITSU SEMICONDUCTOR LIMITED",NULL},     //Manufacturer String
    {"MB2146-07-E",NULL},                       //Product String
    {"100331125959001",NULL},                   //Serial Number String
    {"Full-Speed", NULL},                       //iConfiguration
};

const uint8_t au8ReportDescriptor0[1]; // Not used
const uint8_t au8ReportDescriptor1[1]; // Not used
const uint8_t au8ReportDescriptor2[1]; // Not used

const stc_usbdevice_reportdescriptor_t astcReportDescriptors[3] =
{
    {(uint8_t*)au8ReportDescriptor0,sizeof(au8ReportDescriptor0)},
    {(uint8_t*)au8ReportDescriptor1,sizeof(au8ReportDescriptor1)},
    {(uint8_t*)au8ReportDescriptor2,sizeof(au8ReportDescriptor2)},
};

const stc_usbdevice_reportdescriptor_t astcHIDDescriptors[3] =
{
    {NULL,0},
    {NULL,0},
    {NULL,0},
};

/*****************************************************************************/
/* Global function prototypes ('extern', definition in C source)             */
/*****************************************************************************/


#endif /* __USBDESCRIPTORS_H__ */
