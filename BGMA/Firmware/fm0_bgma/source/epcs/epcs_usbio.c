/******************************************************************************/
/* File Name      : epcs_usbio.c                                              */
/* Project        : BGM Adapter                                               */
/* Module Function: Basic USB I/O                                             */
/* Author         : lijiale                                                   */
/* Version        : 1.0                                                       */
/* Date           : 2010/03/15                                                */
/* History        : 2010/03/15  create                                        */
/*                  Copyright 2010 FUJITSU ELECTRONICS INC.  LIMITED          */
/******************************************************************************/

/******************************************************************************/
/*  Headers                                                                   */
/******************************************************************************/
#include "epcs_common.h"
#include "epcs_usbio.h"
#include "usb.h"
#include "usbdevice.h"
#include "UsbDeviceVendor.h"
#include "epcs_app.h"
#include "epcs_vendor.h"

/******************************************************************************/
/*  Global Variable Definition                                                */
/******************************************************************************/

/******************************************************************************/
/*  Constant Definition                                                       */
/******************************************************************************/
#define  USBIO_BULK_OUT_BUFFER_SIZE   (1088)  /* buffer size for BULK OUT transfer */
#define  USBIO_BULK_IN_BUFFER_SIZE    (1088)  /* buffer size for BULK IN transfer */

#define  USB_TRANS_SUCCESS     (1)     /* USB transfer is successfully complete  */
#define  USB_TRANS_UNSUCCESS   (0)     /* USB transfer is unsuccessfully complete */

/******************************************************************************/
/*  Static Variable Definition                                                */
/******************************************************************************/
/* information for BULK OUT transfer */
static struct {
    uint16_t ReceiveSize;
    uint8_t  ReceiveState;
    uint8_t  ReceivingFlag;
    uint8_t  Buffer[USBIO_BULK_OUT_BUFFER_SIZE];
}s_BulkOut;

/* information for BULK IN transfer */
static struct {
    uint16_t SendSize;
    uint8_t  SendState;
    uint8_t  SendingFlag;
    uint8_t  Buffer[USBIO_BULK_IN_BUFFER_SIZE];
}s_BulkIn;

/******************************************************************************/
/*  Local Function Prototypes                                                 */
/******************************************************************************/
/* callback funcation for USB driver */
static void cb_usb_out_ep_trans_complete(stc_usbn_t* pstcUsb, const uint8_t* buf, uint32_t len);
static void cb_usb_in_ep_trans_complete(stc_usbn_t* pstcUsb, const uint8_t* buf, uint32_t len);
static void cb_usb_device_conf(stc_usbn_t* pstcUsb, boolean_t configured);

/******************************************************************************/
/*  Functions                                                                 */
/******************************************************************************/


/******************************************************************************/
/* Func Name      :   epcs_initialize                                         */
/* Parameters     :   none                                                    */
/* Return Value   :   none                                                    */
/* Description    :   initialize epcs module                                  */
/******************************************************************************/
int32_t epcs_initialize(void)
{
    EPCS_APP_Main();
    
    /* Initialize usb */
    UsbConfig_UsbInit();
    UsbDeviceVendor_SetVendorRequestCallback(VENDOR_CommandProcess);
    UsbConfig_SwitchMode();
    
    /* abort IN/OUT transfer */
    if (s_BulkIn.SendingFlag == TRUE) {
        //USBF_AbortTrans(USBIO_BULK_IN_EP);
    }
    if (s_BulkOut.ReceivingFlag == TRUE) {
        //USBF_AbortTrans(USBIO_BULK_OUT_EP);
    }

    /* initialize transfer information */
    s_BulkOut.ReceiveSize = 0;
    s_BulkOut.ReceiveState = USB_TRANS_SUCCESS;
    s_BulkOut.ReceivingFlag = FALSE;
    memset(s_BulkOut.Buffer, 0, USBIO_BULK_OUT_BUFFER_SIZE);
    s_BulkIn.SendSize = 0;
    s_BulkIn.SendState = USB_TRANS_SUCCESS;
    s_BulkIn.SendingFlag = FALSE;
    memset(s_BulkIn.Buffer, 0, USBIO_BULK_IN_BUFFER_SIZE);

    /* register callback function */
    UsbDeviceVendor_SetConfCallback(cb_usb_device_conf);
    
    return 0;
}

/******************************************************************************/
/* Func Name      :   epcs_check_read                                         */
/* Parameters     :   none                                                    */
/* Return Value   :   > 0: size of received data                              */
/*                    = 0: received no data                                   */
/*                    < 0: error                                              */
/* Description    :   check if received data                                  */
/******************************************************************************/
int32_t epcs_check_read(void)
{
    int32_t ret;  /* return value */

    /* usb function is not in the config status or transfer is unsuccessful */
    if((FALSE == UsbDeviceVendor_IsReady()) || (s_BulkOut.ReceiveState == USB_TRANS_UNSUCCESS)) {
        /* error */
        return -1;
    } else if (s_BulkOut.ReceivingFlag == TRUE) {
        /* is in transferring */
        ret = 0;
    } else {
        /* return the received data size */
        ret = s_BulkOut.ReceiveSize;
    }
    return (ret);
}

/******************************************************************************/
/* Func Name      :   epcs_read_data                                          */
/* Parameters     :   buffer: buffer for transfer data                        */
/*                    offset: data offset in buffer                           */
/*                    length: data size to read                               */
/* Return Value   :   > 0: read data size                                     */
/*                    = 0: no data                                            */
/*                    < 0: error                                              */
/* Description    :   read received data                                      */
/******************************************************************************/
int32_t epcs_read_data(uint8_t* buffer, uint32_t offset, uint32_t length)
{
    int32_t ret;  /* return value */
    uint32_t read_size; /* data size to read */

    /* usb function is not in the config status or offset is unavailable */
    if (FALSE == UsbDeviceVendor_IsReady()) {
        /* error */
        ret = -1;
    } else if (s_BulkOut.ReceiveSize == 0) {
        /* receive data buffer is NULL */
        ret = 0;
    } else if (offset >= s_BulkOut.ReceiveSize) {
        /* error */
        ret = -1;
    } else {
        /* data size to read */
        read_size = ((s_BulkOut.ReceiveSize - offset) < length) ? (s_BulkOut.ReceiveSize - offset) : length;
        /* copy the data */
        memcpy(buffer, &s_BulkOut.Buffer[offset], read_size);
        /* return the data size */
        ret = read_size;
    }

    return (ret);
}

/******************************************************************************/
/* Func Name      :   epcs_clear_read                                         */
/* Parameters     :   none                                                    */
/* Return Value   :   > 0: Reserved                                           */
/*                    = 0: success                                            */
/*                    < 0: error                                              */
/* Description    :   clear received data                                     */
/******************************************************************************/
int32_t epcs_clear_read(void)
{
    int32_t ret;  /* return value */

    /* usb function is not in the config status */
    if (FALSE == UsbDeviceVendor_IsReady()) {
         /* error */
        ret = -1;
    } else {
        /* clear received data size */
        s_BulkOut.ReceiveSize = 0;
        /* set receive state to OK */
        s_BulkOut.ReceiveState = USB_TRANS_SUCCESS;
        /* receive data request */
        if(Ok != UsbDeviceVendor_ReceiveData(s_BulkOut.Buffer, USBIO_BULK_OUT_BUFFER_SIZE, cb_usb_out_ep_trans_complete)) {
            /* error */
            USB_VENDOR_DBG_PRINTF("UsbDeviceVendor_ReceiveData ret failed\r\n");
            ret = -1;
        } else {
            /* success */
            ret = 0;
        }
    }

    return (ret);
}

/******************************************************************************/
/* Func Name      :   epcs_check_write                                        */
/* Parameters     :   none                                                    */
/* Return Value   :   > 0: size of received data                              */
/*                    = 0: ready to send                                      */
/*                    < 0: error                                              */
/* Description    :   check if received data                                  */
/******************************************************************************/
int32_t epcs_check_write(void)
{
    int32_t ret;  /* return value */

    /* usb function is not in the config status or transfer is unsuccessful */
    if ((FALSE == UsbDeviceVendor_IsReady()) || (s_BulkIn.SendState == USB_TRANS_UNSUCCESS)) {
        /* error */
        ret = -1;
    } else if (s_BulkIn.SendingFlag == FALSE) {
        /* is ready to send data */
        ret = 0;
    } else {
        /* unsent data size */
        ret = s_BulkIn.SendSize;
    }

    return (ret);
}

/******************************************************************************/
/* Func Name      :   epcs_write_data                                         */
/* Parameters     :   buffer: buffer for transfer data                        */
/*                    length: data size to write                              */
/* Return Value   :   > 0: read data size                                     */
/*                    = 0: no data                                            */
/*                    < 0: error                                              */
/* Description    :   write send data                                         */
/******************************************************************************/
int32_t epcs_write_data(uint8_t* buffer, uint32_t length)
{
    int32_t ret;  /* return value */
    uint32_t write_size;  /* write data size */

    /* usb function is not in the config status */
    if (FALSE == UsbDeviceVendor_IsReady()) {
        /* error */
        ret = -1;
    } else if (s_BulkIn.SendingFlag == TRUE) {
        /* data is transferring, abort transfer */
        //USBF_AbortTrans(USBIO_BULK_IN_EP);
        /* error */
        ret = -1;
    } else if (length > USBIO_BULK_IN_BUFFER_SIZE) {
        /* write size is unavailable, error */
        ret = -1;
    } else {
        /* send data */
        if (length == 0) {
            /* set sending flag to ture */
            s_BulkIn.SendingFlag = TRUE;
            /* request to send data */
            if(Ok != UsbDeviceVendor_SendData(s_BulkIn.Buffer, s_BulkIn.SendSize, cb_usb_in_ep_trans_complete)) {
                /* set sending flag to false */
                s_BulkIn.SendingFlag = FALSE;
                /* error */
                ret = -1;
            } else {
                /* return send data size */
                ret = s_BulkIn.SendSize;
            }
        } else {
            /* size of write data */
            write_size =  ((USBIO_BULK_IN_BUFFER_SIZE - s_BulkIn.SendSize) < length) ? (USBIO_BULK_IN_BUFFER_SIZE - s_BulkIn.SendSize) : length;
            /* copy write data */
            memcpy(&(s_BulkIn.Buffer[s_BulkIn.SendSize]), buffer, write_size);
            /* updata data size */
            s_BulkIn.SendSize += write_size;
            /* return writen data size */
            ret = write_size;
        }
    }

    return (ret);
}

/******************************************************************************/
/* Func Name      :   epcs_clear_write                                        */
/* Parameters     :   none                                                    */
/* Return Value   :   > 0: Reserved                                           */
/*                    = 0: success                                            */
/*                    < 0: error                                              */
/* Description    :   clear received data                                     */
/******************************************************************************/
int32_t epcs_clear_write(void)
{
    int32_t ret;  /* return value */

    /* usb function is not in the config status */
    if(FALSE == UsbDeviceVendor_IsReady()) {
        /* error */
        ret = -1;
    } else {
        /* is in transferring */
        if (s_BulkIn.SendingFlag == TRUE) {
            /* abort transfer */
            //USBF_AbortTrans(USBIO_BULK_IN_EP);
        }
        /* clear sending flag */
        s_BulkIn.SendingFlag = FALSE;
        /* clear send data size */
        s_BulkIn.SendSize = 0;
        /* set send state to success */
        s_BulkIn.SendState = USB_TRANS_SUCCESS;
        /* success */
        ret = 0;
    }

    return (ret);
}

/******************************************************************************/
/* Func Name      :   epcs_reset                                               */
/* Parameters     :   none                                                    */
/* Return Value   :   none                                                    */
/* Description    :   USB reset process                                       */
/******************************************************************************/
int32_t epcs_reset(void)
{
    /* initialize USB function */
    epcs_initialize();
    return 0;
}

/******************************************************************************/
/* Func Name      :   cb_usb_out_ep_trans_complete                            */
/* Return Value   :   none                                                    */
/* Description    :   USB OUT EP transfe complete callback function           */
/******************************************************************************/
static void cb_usb_out_ep_trans_complete(stc_usbn_t* pstcUsb, const uint8_t* buf, uint32_t len)
{
    (void)pstcUsb;
    (void)buf;
    /* set received data size */
    s_BulkOut.ReceiveSize = len;
    /* set receiving flag to false */
    s_BulkOut.ReceivingFlag = FALSE;
}

/******************************************************************************/
/* Func Name      :   cb_usb_in_ep_trans_complete                             */
/* Return Value   :   none                                                    */
/* Description    :   USB IN EP transfe complete callback function            */
/******************************************************************************/
static void cb_usb_in_ep_trans_complete(stc_usbn_t* pstcUsb, const uint8_t* buf, uint32_t len)
{
    (void)pstcUsb;
    (void)buf;
    /* usb device have send the zero packet, do not send zero packet */
    if ((len > 0) && (len % BUFFER_SIZE_ENDPOINTOUT == 0)) {
        //USBF_Send(USBIO_BULK_IN_EP, s_BulkIn.Buffer, 0);
    }
    /* clear send data size */
    s_BulkIn.SendSize = 0;
    /* set sending flag to false */
    s_BulkIn.SendingFlag = FALSE;
}

/******************************************************************************/
/* Func Name      :   cb_usb_device_conf                                      */
/* Return Value   :   none                                                    */
/* Description    :   USB device configuration callback function              */
/******************************************************************************/
static void cb_usb_device_conf(stc_usbn_t* pstcUsb, boolean_t configured)
{
    (void)pstcUsb;
    if(configured == TRUE) {
        //
    }
}

/******************************************************************************/
/* Func Name      :   epcs_test                                               */
/* Return Value   :   none                                                    */
/* Description    :   USB IO test                                             */
/******************************************************************************/
#if (USB_IO_TEST_ENABLED)
void epcs_test(void)
{
    int32_t ret = 0;
    uint16_t size = 0;
    uint8_t buffer[USBIO_BULK_OUT_BUFFER_SIZE];
    
    /* initialize USB function */
    epcs_initialize();
    /* Wait for the usb device configure */
    while(epcs_clear_read() < 0);
    /* infinite loop */
    while(1) {
        ret = epcs_check_read();
        if(ret > 0){
            size = (ret < USBIO_BULK_OUT_BUFFER_SIZE) ? ret : USBIO_BULK_OUT_BUFFER_SIZE;
            ret = epcs_read_data(buffer, 0, size);
            size = ret;
            epcs_clear_read();
            if (ret > 0) {
                ret = epcs_clear_write();
                if (ret == 0) {
                    ret = epcs_write_data(buffer, size);
                    if (ret == size) {
                        epcs_write_data(buffer, 0);
                    }
                }
            }
        }
    }
}
#endif


