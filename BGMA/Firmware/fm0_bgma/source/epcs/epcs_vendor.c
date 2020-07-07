/******************************************************************************/
/* File Name      : epcs_vendor.c                                             */
/* Project        : BGM Adapter                                               */
/* Module Function: vendor command process                                    */
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
#include "epcs_vendor.h"
#include "epcs_app.h"
#include "UsbDeviceVendor.h"

/******************************************************************************/
/*  Global Variable Definition                                                */
/******************************************************************************/

/******************************************************************************/
/*  Constant Definition                                                       */
/******************************************************************************/
/* vendor command */
#define  VSET_BMGA_PTR          (0x00)  /* set object address */
#define  VGET_BGMA_DATA         (0x01)  /* get data from object address */
#define  VSET_BGMA_DATA         (0x02)  /* set data to object address */
#define  VSET_BGMA_FER          (0x03)  /* erase FlashROM */
#define  VSET_BGMA_FWR          (0x04)  /* write data into FlashROM */
#define  VSET_LED               (0x10)  /* set LED */
#define  VGET_BGMA_INFO         (0x11)  /* get BGM adapter's information */
#define  VSET_BGMA_RESET        (0x12)  /* reset BGM adapter */
#define  VGET_BGMA_CALL         (0x13)  /* call function in memory */
#define  NO_VENDOR_COMMADN      (0xFF)  /* no command */

#define  VENDOR_BUFFER_SIZE     (64)  /* buffer size for vendor command transfer */

#define  VENDOR_LED_ALL_OFF     (0x0000)  /* comand for set all led to off */
#define  VENDOR_LED_GREEN_ON    (0x0100)  /* comand for set green led to on only */
#define  VENDOR_LED_RED_ON      (0x0200)  /* comand for set red led to on only */
#define  VENDOR_LED_ALL_ON      (0x0300)  /* comand for set all led to on */

/******************************************************************************/
/*  Static Variable Definition                                                */
/******************************************************************************/
/* buffer for vendor command transfer */
static uint8_t s_VendorInBuffer[VENDOR_BUFFER_SIZE];
static uint8_t s_VendorOutBuffer[VENDOR_BUFFER_SIZE];

/* current processing command */
static uint8_t s_CurrentCommand = NO_VENDOR_COMMADN;
/* object address */
static uint32_t s_ObjectAddress;
/* selected application after BGM adapter reset */
static uint8_t s_BgmResetSelectedApp;

/******************************************************************************/
/*  Local Function Prototypes                                                 */
/******************************************************************************/
/* vendor command process */
static uint8_t vendor_cmd_set_bgma_ptr(stc_usbn_t* pstcUsb, stc_usb_request_t* setup_info);
static void vendor_cmd_set_bgma_ptr_end(stc_usbn_t* pstcUsb, const uint8_t* buf, uint32_t len);
static uint8_t vendor_cmd_get_bgma_data(stc_usbn_t* pstcUsb, stc_usb_request_t* setup_info);
static uint8_t vendor_cmd_set_bgma_data(stc_usbn_t* pstcUsb, stc_usb_request_t* setup_info);
static void vendor_cmd_set_bgma_data_end(stc_usbn_t* pstcUsb, const uint8_t* buf, uint32_t len);
static uint8_t vendor_cmd_set_bgma_fer(stc_usbn_t* pstcUsb, stc_usb_request_t* setup_info);
static void vendor_cmd_set_bgma_fer_end(stc_usbn_t* pstcUsb, const uint8_t* buf, uint32_t len);
static uint8_t vendor_cmd_set_bgma_fwr(stc_usbn_t* pstcUsb, stc_usb_request_t* setup_info);
static void vendor_cmd_set_bgma_fwr_end(stc_usbn_t* pstcUsb, const uint8_t* buf, uint32_t len);
static uint8_t vendor_cmd_set_led(stc_usbn_t* pstcUsb, stc_usb_request_t* setup_info);
static uint8_t vendor_cmd_get_bgma_info(stc_usbn_t* pstcUsb, stc_usb_request_t* setup_info);
static uint8_t vendor_cmd_set_bgma_reset(stc_usbn_t* pstcUsb, stc_usb_request_t* setup_info);
static void vendor_cmd_set_bgma_reset_end(stc_usbn_t* pstcUsb, const uint8_t* buf, uint32_t len);
static uint8_t vendor_cmd_get_bgma_call(stc_usbn_t* pstcUsb, stc_usb_request_t* setup_info);
static uint8_t command_check(stc_usb_request_t* setup_info);

/******************************************************************************/
/*  Functions                                                                 */
/******************************************************************************/

/******************************************************************************/
/* Function Name  :  VENDOR_CommandProcess                                    */
/* Parameters     :  setup_info : setup packet information                    */
/* Return Value   :  none                                                     */
/* Description    :  vendor command process                                   */
/******************************************************************************/
void VENDOR_CommandProcess(stc_usbn_t* pstcUsb, stc_usb_request_t* setup_info)
{
    uint8_t result = TRUE;

    if((NULL == pstcUsb) || (NULL == setup_info)) {
        return;
    }
    if (command_check(setup_info) == TRUE)
    {
        switch(setup_info->bRequest) {
            /* set object address */
            case VSET_BMGA_PTR:
                /* set object address process */
                result = vendor_cmd_set_bgma_ptr(pstcUsb, setup_info);
                break;
            /* get data from object address */
            case VGET_BGMA_DATA:
                /* get data from object address process */
                result = vendor_cmd_get_bgma_data(pstcUsb, setup_info);
                break;
            /* set data to object address */
            case VSET_BGMA_DATA:
                /* set data to object address process */
                result = vendor_cmd_set_bgma_data(pstcUsb, setup_info);
                break;
            /* erase FlashROM */
            case VSET_BGMA_FER:
                /* erase FlashROM process */
                result = vendor_cmd_set_bgma_fer(pstcUsb, setup_info);
                break;
            /* write data into FlashROM */
            case VSET_BGMA_FWR:
                /* write data into FlashROM process */
                result = vendor_cmd_set_bgma_fwr(pstcUsb, setup_info);
                break;
            /* set LED */
            case VSET_LED:
                /* set LED */
                result = vendor_cmd_set_led(pstcUsb, setup_info);
                break;
            /* get BGM adapter's information */
            case VGET_BGMA_INFO:
                /* get BGM adapter's information process */
                result = vendor_cmd_get_bgma_info(pstcUsb, setup_info);
                break;
            /* reset BGM adapter */
            case VSET_BGMA_RESET:
                /* reset BGM adapter process */
                result = vendor_cmd_set_bgma_reset(pstcUsb, setup_info);
                break;
            /* call function in memory */
            case VGET_BGMA_CALL:
                /* call function in memory process */
                result = vendor_cmd_get_bgma_call(pstcUsb, setup_info);
                break;
            default:
                result = FALSE;
                break;
        }
        if (result == FALSE) {
            /* set EP0 to stall status */
            UsbDeviceVendor_StallControlEndpoint();
            USB_VENDOR_DBG_PRINTF("Ret FALSE, STALL EP0\r\n");
        }
    } else {
        /* set EP0 to stall status */
        UsbDeviceVendor_StallControlEndpoint();
        USB_VENDOR_DBG_PRINTF("Unknown vendor request, STALL EP0\r\n");
    }

    return;
}

/******************************************************************************/
/* Function Name  :  vendor_cmd_set_bgma_ptr                                  */
/* Parameters     :  setup_info : setup packet information                    */
/* Return Value   :  none                                                     */
/* Description    :  set object address process                               */
/******************************************************************************/
static uint8_t vendor_cmd_set_bgma_ptr(stc_usbn_t* pstcUsb, stc_usb_request_t* setup_info)
{
    USB_VENDOR_DBG_PRINTF("R PTR cmd\r\n");
    /* request to receive data */
    UsbDeviceVendor_ReceiveDataControl(pstcUsb, s_VendorOutBuffer, setup_info->wLength, vendor_cmd_set_bgma_ptr_end);
    return TRUE;
}

/******************************************************************************/
/* Function Name  :  vendor_cmd_set_bgma_ptr_end                              */
/* Parameters     :  setup_info : setup packet information                    */
/* Return Value   :  none                                                     */
/* Description    :  end of set object address process                        */
/******************************************************************************/
static void vendor_cmd_set_bgma_ptr_end(stc_usbn_t* pstcUsb, const uint8_t* buf, uint32_t len)
{
    (void)pstcUsb;
    /* received data size is not correct */
    if (len != 0x04) {
        /* set EP0 to stall status */
        UsbDeviceVendor_StallControlEndpoint();
    } else {
        /* set object address */
        s_ObjectAddress = LE_BUFFER_TO_WORD(buf);
        USB_VENDOR_DBG_PRINTF("s_ObjectAddress: 0x%x\r\n", (int)s_ObjectAddress);
        UsbDevice_SendDataControl(pstcUsb, (uint8_t *)NULL, 0);
    }
    /* set current command to no command */
    s_CurrentCommand = NO_VENDOR_COMMADN;
}

/******************************************************************************/
/* Function Name  :  vendor_cmd_get_bgma_data                                 */
/* Parameters     :  setup_info : setup packet information                    */
/* Return Value   :  none                                                     */
/* Description    :  get data from object address process                     */
/******************************************************************************/
static uint8_t vendor_cmd_get_bgma_data(stc_usbn_t* pstcUsb, stc_usb_request_t* setup_info)
{
    /* copy data from object address */
    if((EPCS_DEFAULT_HEADER_START_ADDR > s_ObjectAddress) || (EPCS_DEFAULT_HEADER_END_ADDR < s_ObjectAddress)) {
        /* set current command to no command */
        s_CurrentCommand = NO_VENDOR_COMMADN;
        return FALSE;
    }
    int index = (s_ObjectAddress - EPCS_DEFAULT_HEADER_START_ADDR) / 4;
    EPCS_MEMCPY(s_VendorInBuffer, (uint8_t*)(&(g_EpcsDefaultHeader[index])), setup_info->wLength);
    /* request to send data */
    UsbDevice_SendDataControl(pstcUsb, s_VendorInBuffer, setup_info->wLength);
    /* updata object address */
    s_ObjectAddress += setup_info->wLength;
    /* set current command to no command */
    s_CurrentCommand = NO_VENDOR_COMMADN;
    return TRUE;
}

/******************************************************************************/
/* Function Name  :  vendor_cmd_set_bgma_data                                 */
/* Parameters     :  setup_info : setup packet information                    */
/* Return Value   :  none                                                     */
/* Description    :  set data to object address process                       */
/******************************************************************************/
static uint8_t vendor_cmd_set_bgma_data(stc_usbn_t* pstcUsb, stc_usb_request_t* setup_info)
{
    /* request to receive data */
    UsbDeviceVendor_ReceiveDataControl(pstcUsb, s_VendorOutBuffer, setup_info->wLength, vendor_cmd_set_bgma_data_end);
    return TRUE;
}

/******************************************************************************/
/* Function Name  :  vendor_cmd_set_bgma_data_end                             */
/* Parameters     :  setup_info : setup packet information                    */
/* Return Value   :  none                                                     */
/* Description    :  end of set data to object address process                */
/******************************************************************************/
static void vendor_cmd_set_bgma_data_end(stc_usbn_t* pstcUsb, const uint8_t* buf, uint32_t len)
{
    (void)pstcUsb;
    /* copy data from object address */
    if((EPCS_DEFAULT_HEADER_START_ADDR <= s_ObjectAddress) && (EPCS_DEFAULT_HEADER_END_ADDR >= s_ObjectAddress)) {
        /* set EP0 to stall status */
        USB_VENDOR_DBG_PRINTF("VSET_BGMA_DATA command is not supported, STALL EP0. s_ObjectAddress:0x%x\r\n", (int)s_ObjectAddress);
        UsbDeviceVendor_StallControlEndpoint();
    } else {
        (void)buf;
        /* copy data to object address */
        //EPCS_MEMCPY((uint8_t*)s_ObjectAddress, (void *)buf, len);
        /* set EP0 to stall status */
        USB_VENDOR_DBG_PRINTF("VSET_BGMA_DATA command is not supported1, STALL EP0. s_ObjectAddress:0x%x\r\n", (int)s_ObjectAddress);
        UsbDeviceVendor_StallControlEndpoint();
    }
    /* updata object address */
    s_ObjectAddress += len;
    /* set current command to no command */
    s_CurrentCommand = NO_VENDOR_COMMADN;
    return;
}

/******************************************************************************/
/* Function Name  :  vendor_cmd_set_bgma_fer                                  */
/* Parameters     :  setup_info : setup packet information                    */
/* Return Value   :  none                                                     */
/* Description    :  erase FlashROM process                                   */
/******************************************************************************/
static uint8_t vendor_cmd_set_bgma_fer(stc_usbn_t* pstcUsb, stc_usb_request_t* setup_info)
{
    /* request to receive data */
    UsbDeviceVendor_ReceiveDataControl(pstcUsb, s_VendorOutBuffer, setup_info->wLength, vendor_cmd_set_bgma_fer_end);
    return TRUE;
}

/******************************************************************************/
/* Function Name  :  vendor_cmd_set_bgma_fer_end                              */
/* Parameters     :  setup_info : setup packet information                    */
/* Return Value   :  none                                                     */
/* Description    :  end of erase FlashROM process                            */
/******************************************************************************/
static void vendor_cmd_set_bgma_fer_end(stc_usbn_t* pstcUsb, const uint8_t* buf, uint32_t len)
{
    uint32_t erase_addr = 0;  /* sector address to erase */

    (void)pstcUsb;
    (void)erase_addr;
    /* received data size is not correct */
    if (len != 0x04) {
        /* set EP0 to stall status */
        UsbDeviceVendor_StallControlEndpoint();
    } else {
        /* set sector address to erase */
        erase_addr = LE_BUFFER_TO_WORD(buf);
        USB_VENDOR_DBG_PRINTF("erase_addr: 0x%x\r\n", (int)erase_addr);
        /* set EP0 to stall status */
        USB_VENDOR_DBG_PRINTF("VSET_BGMA_FER command is not supported, STALL EP0\r\n");
        UsbDeviceVendor_StallControlEndpoint();
    }
    /* set current command to no command */
    s_CurrentCommand = NO_VENDOR_COMMADN;
    return;
}

/******************************************************************************/
/* Function Name  :  vendor_cmd_set_bgma_fwr                                  */
/* Parameters     :  setup_info : setup packet information                    */
/* Return Value   :  none                                                     */
/* Description    :  write data into FlashROM process                         */
/******************************************************************************/
static uint8_t vendor_cmd_set_bgma_fwr(stc_usbn_t* pstcUsb, stc_usb_request_t* setup_info)
{
    /* request to receive data */
    UsbDeviceVendor_ReceiveDataControl(pstcUsb, s_VendorOutBuffer, setup_info->wLength, vendor_cmd_set_bgma_fwr_end);
    return TRUE;
}

/******************************************************************************/
/* Function Name  :  vendor_cmd_set_bgma_fwr_end                              */
/* Parameters     :  setup_info : setup packet information                    */
/* Return Value   :  none                                                     */
/* Description    :  end of write data into FlashROM process                  */
/******************************************************************************/
static void vendor_cmd_set_bgma_fwr_end(stc_usbn_t* pstcUsb, const uint8_t* buf, uint32_t len)
{
    uint32_t source_addr = 0;
    uint32_t destination_addr = 0;
    uint32_t write_size = 0;

    (void)pstcUsb;
    (void)source_addr;
    (void)destination_addr;
    (void)write_size;
    /* received data size is not correct */
    if (len != 0x0C) {
        /* set EP0 to stall status */
        UsbDeviceVendor_StallControlEndpoint();
    } else {
        /* set source address */
        source_addr = LE_BUFFER_TO_WORD(buf);
        /* set destination address */
        destination_addr = LE_BUFFER_TO_WORD(&buf[4]);
        /* set data size to write */
        write_size = LE_BUFFER_TO_WORD(&buf[8]);
        USB_VENDOR_DBG_PRINTF("source_addr:0x%x, destination_addr=0x%x, write_size:0x%x\r\n", (int)source_addr, (int)destination_addr, (int)write_size);
        /* set EP0 to stall status */
        USB_VENDOR_DBG_PRINTF("VSET_BGMA_FWR command is not supported, STALL EP0\r\n");
        UsbDeviceVendor_StallControlEndpoint();
        /* clear address of failed operation */
        g_EpcsFROMFailedAddr = 0;
    }
    /* set current command to no command */
    s_CurrentCommand = NO_VENDOR_COMMADN;
    return;
}

/******************************************************************************/
/* Function Name  :  vendor_cmd_set_led                                       */
/* Parameters     :  setup_info : setup packet information                    */
/* Return Value   :  none                                                     */
/* Description    :  set LED process                                          */
/******************************************************************************/
static uint8_t vendor_cmd_set_led(stc_usbn_t* pstcUsb, stc_usb_request_t* setup_info)
{
    (void)pstcUsb;
    switch(setup_info->wValue) {
        /* set all led to off */
        case VENDOR_LED_ALL_OFF:
            VENDOR_GREEN_LED_OFF();
            VENDOR_RED_LED_OFF();
            break;
        /* set green led to on only */
        case VENDOR_LED_GREEN_ON:
            VENDOR_GREEN_LED_ON();
            break;
        /* set red led to on only */
        case VENDOR_LED_RED_ON:
            VENDOR_RED_LED_ON();
            break;
        /* set all led to on */
        case VENDOR_LED_ALL_ON:
            VENDOR_GREEN_LED_ON();
            VENDOR_RED_LED_ON();
        break;
    }
    UsbDevice_SendDataControl(pstcUsb, (uint8_t *)NULL, 0);
    /* set current command to no command */
    s_CurrentCommand = NO_VENDOR_COMMADN;
    return TRUE;
}

/******************************************************************************/
/* Function Name  :  vendor_cmd_get_bgma_info                                 */
/* Parameters     :  setup_info : setup packet information                    */
/* Return Value   :  none                                                     */
/* Description    :  get BGM adapter's information process                    */
/******************************************************************************/
static uint8_t vendor_cmd_get_bgma_info(stc_usbn_t* pstcUsb, stc_usb_request_t* setup_info)
{
    uint8_t info_size = 0;  /* information size */

    /* get BGM adapter's information */
    EPCS_APP_GetBgmaInfo(s_VendorInBuffer, &info_size);
    info_size = (setup_info->wLength < info_size) ? setup_info->wLength : info_size;
    /* request to send data */
    UsbDevice_SendDataControl(pstcUsb, s_VendorInBuffer, info_size);
    /* set current command to no command */
    s_CurrentCommand = NO_VENDOR_COMMADN;
    return TRUE;
}

/******************************************************************************/
/* Function Name  :  vendor_cmd_set_bgma_reset                                */
/* Parameters     :  setup_info : setup packet information                    */
/* Return Value   :  none                                                     */
/* Description    :  reset BGM adapter process                                */
/******************************************************************************/
static uint8_t vendor_cmd_set_bgma_reset(stc_usbn_t* pstcUsb, stc_usb_request_t* setup_info)
{
    uint8_t ret = TRUE;

    if (setup_info->wValue == 0x0000) {
        /* select appoint application */
        s_BgmResetSelectedApp = EPCS_SELECT_APPOINTED_APP;
    } else if (setup_info->wValue == 0x0001) {
        /* select appoint application */
        s_BgmResetSelectedApp = EPCS_SELECT_DUMMY_APP;
    } else if (setup_info->wValue == 0xFFFF) {
        /* select appoint application */
        s_BgmResetSelectedApp = EPCS_SELECT_DEFAULT_APP;
    } else {
        ret = FALSE;
    }
    if (ret == TRUE) {
        if(0 < setup_info->wLength) {
            /* request to receive data */
            UsbDeviceVendor_ReceiveDataControl(pstcUsb, s_VendorOutBuffer, setup_info->wLength, vendor_cmd_set_bgma_reset_end);
            return (ret);
        } else {
            UsbDevice_SendDataControl(pstcUsb, (uint8_t *)NULL, 0);
        }
    }
    /* set current command to no command */
    s_CurrentCommand = NO_VENDOR_COMMADN;
    return (ret);
}

/******************************************************************************/
/* Function Name  :  vendor_cmd_set_bgma_reset_end                            */
/* Parameters     :  setup_info : setup packet information                    */
/* Return Value   :  none                                                     */
/* Description    :  end of reset BGM adapter process                         */
/******************************************************************************/
static void vendor_cmd_set_bgma_reset_end(stc_usbn_t* pstcUsb, const uint8_t* buf, uint32_t len)
{
    uint32_t reset_addr = 0;

    (void)pstcUsb;
    (void)reset_addr;
    /* set current command to no command */
    s_CurrentCommand = NO_VENDOR_COMMADN;
    /* received data size is not correct */
    if (len != 0x04) {
        /* set EP0 to stall status */
        UsbDeviceVendor_StallControlEndpoint();
    } else {
        /* set reset address */
        reset_addr = LE_BUFFER_TO_WORD(buf);
        USB_VENDOR_DBG_PRINTF("reset_addr： 0x%x\r\n", (int)reset_addr);
        /* set EP0 to stall status */
        //USB_VENDOR_DBG_PRINTF("VSET_BGMA_RESET command is not supported, STALL EP0\r\n");
        //UsbDeviceVendor_StallControlEndpoint();
        /* software reset */
        (void)s_BgmResetSelectedApp;
        NVIC_SystemReset();
    }
}

/******************************************************************************/
/* Function Name  :  vendor_cmd_get_bgma_call                                 */
/* Parameters     :  setup_info : setup packet information                    */
/* Return Value   :  none                                                     */
/* Description    :  call function in memory process                          */
/******************************************************************************/
static uint8_t vendor_cmd_get_bgma_call(stc_usbn_t* pstcUsb, stc_usb_request_t* setup_info)
{
    uint8_t ret = TRUE;
    uint32_t run_addr = 0;     /* function's address to call */
    uint32_t return_value = 0; /* return value of called function */

    (void)run_addr;
    /* set function's address to call */
    run_addr = LE_BUFFER_TO_WORD(&((uint8_t*)setup_info)[2]) & 0x00FFFFFF;
    USB_VENDOR_DBG_PRINTF("VGET_BGMA_CALL command is not supported, run_addr=0x%x\r\n", (int)run_addr);
    /* call appointed function */
    //return_value = VENDOR_CALL(run_addr);
    /* set return value */
    WORD_TO_LE_BUFFER(s_VendorInBuffer, return_value);
    /* request to send data */
    UsbDevice_SendDataControl(pstcUsb, s_VendorInBuffer, 0x04);
    /* set current command to no command */
    s_CurrentCommand = NO_VENDOR_COMMADN;

    return (ret);
}

/******************************************************************************/
/* Function Name  :  command_check                                            */
/* Parameters     :  setup_info : setup packet information                    */
/* Return Value   :  TRUE: check OK                                           */
/*                   FALSE: check NG                                          */
/* Description    :  check vendor command                                     */
/******************************************************************************/
static uint8_t command_check(stc_usb_request_t* setup_info)
{
    uint8_t ret = TRUE;

    /* another command is processing */
    if (s_CurrentCommand != NO_VENDOR_COMMADN) {
        ret = FALSE;
    } else {
        switch(setup_info->bRequest) {
            /* set object address */
            case VSET_BMGA_PTR:
                if ((setup_info->bmRequestType != 0x40) ||
                    (setup_info->wValue != 0x0000) ||
                    (setup_info->wIndex != 0x0000) ||
                    (setup_info->wLength != 0x0004)) {
                    ret = FALSE;
                }
                break;
            /* get data from object address */
            case VGET_BGMA_DATA:
                if ((setup_info->bmRequestType != 0xC0) ||
                    (setup_info->wValue != 0x0000) ||
                    (setup_info->wIndex != 0x0000) ||
                    (setup_info->wLength > 0x0040)) {
                    ret = FALSE;
                }
                break;
            /* set data to object address */
            case VSET_BGMA_DATA:
                if ((setup_info->bmRequestType != 0x40) ||
                    (setup_info->wValue != 0x0000) ||
                    (setup_info->wIndex != 0x0000) ||
                    (setup_info->wLength > 0x0040)) {
                    ret = FALSE;
                }
                break;
            /* erase FlashROM */
            case VSET_BGMA_FER:
                if ((setup_info->bmRequestType != 0x40) ||
                    (setup_info->wValue != 0x0000) ||
                    (setup_info->wIndex != 0x0000) ||
                    (setup_info->wLength != 0x0004)) {
                    ret = FALSE;
                }
                break;
            /* write data into FlashROM */
            case VSET_BGMA_FWR:
                if ((setup_info->bmRequestType != 0x40) ||
                    (setup_info->wValue != 0x0000) ||
                    (setup_info->wIndex != 0x0000) ||
                    (setup_info->wLength != 0x000C)) {
                    ret = FALSE;
                }
                break;
            /* set LED */
            case VSET_LED:
                if ((setup_info->bmRequestType != 0x40) ||
                    ((setup_info->wValue & 0x00FF) != 0x0000) ||
                    ((setup_info->wValue & 0xFF00) > 0x0300) ||
                    (setup_info->wIndex != 0x0000) ||
                    (setup_info->wLength != 0x0000)) {
                    ret = FALSE;
                }
                break;
            /* get BGM adapter's information */
            case VGET_BGMA_INFO:
                if ((setup_info->bmRequestType != 0xC0) ||
                    (setup_info->wValue != 0x0000) ||
                    (setup_info->wIndex != 0x0000) ||
                    (setup_info->wLength > 0x0040) ||
                    (setup_info->wLength < 0x000C)) {
                    ret = FALSE;
                }
                break;
            /* reset BGM adapter */
            case VSET_BGMA_RESET:
                if ((setup_info->bmRequestType != 0x40) ||
                    (setup_info->wIndex != 0x0000) ||
                    ((setup_info->wLength != 0x0004) &&
                    (setup_info->wLength != 0x0000))) {
                    ret = FALSE;
                }
                break;
            /* call function in memory */
            case VGET_BGMA_CALL:
                if ((setup_info->bmRequestType != 0xC0) ||
                    (setup_info->wLength != 0x0004)) {
                    ret = FALSE;
                }
                break;
            default: 
                ret = FALSE;
                break;
        }

        if (ret == TRUE){
            /* set command to current command */
            s_CurrentCommand = setup_info->bRequest;
        }
    }

    return (ret);
}
