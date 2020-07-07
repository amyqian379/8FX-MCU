/******************************************************************************/
/* File Name      : test_app.c                                                */
/* Project        : BGM Adapter                                               */
/* Module Function: application for connect test                              */
/* Author         : lijiale                                                   */
/* Version        : 1.0                                                       */
/* Date           : 2010/03/15                                                */
/* History        : 2010/03/15  create                                        */
/*                  Copyright 2010 FUJITSU ELECTRONICS INC.  LIMITED          */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/*  Headers                                                                   */
/*----------------------------------------------------------------------------*/
#include <string.h>
#include "epcs_usbio.h"
#include "dbg_print.h"
#include "LPCdef.h"
#include "bgma_misc.h"
#include "systick.h"

/*----------------------------------------------------------------------------*/
/*  Global Variable Definition                                                */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/*  Constant Definition                                                       */
/*----------------------------------------------------------------------------*/                             
#define APP_TRANSFER_BUFFER_SIZE     (1024)
#define APP_HOSTIF_BUFFER_SIZE       (512)
#define APP_RECEIVE_BUFFER_SIZE      (1024)

#define APP_TRANSFER_STATE_IDLE      (0)
#define APP_TRANSFER_STATE_BUSY      (1)
#define APP_TRANSFER_STATE_COMPLETE  (2)
#define APP_TRANSFER_STATE_ERROR     (3)

#define APP_FORMAT_OFFSET_HEADER     (0)
#define APP_FORMAT_OFFSET_ID         (1)
#define APP_FORMAT_OFFSET_LEN_L      (2)
#define APP_FORMAT_OFFSET_LEN_H      (3)
#define APP_FORMAT_OFFSET_DATA       (4)

#define APP_FORMAT_HEADER            (0xBA)
#define APP_FORMAT_ID_HOSTIF         (0x00)
#define APP_FORMAT_ID_UARTCTRL       (0x01)

/*----------------------------------------------------------------------------*/
/*  Static Variable Definition                                                */
/*----------------------------------------------------------------------------*/
/* send/receive information */
static struct {
    uint8_t  State;
    uint16_t Size;
    uint8_t  Buffer[APP_TRANSFER_BUFFER_SIZE];
}s_AppSend, s_AppReceive;

static uint8_t s_HostIfBuffer[APP_HOSTIF_BUFFER_SIZE];
static uint8_t s_ReceiveBuffer[APP_RECEIVE_BUFFER_SIZE];
static uint16_t s_ReceivedSize = 0;

uint8_t  UsbCommFlag = 0;  // USB communication in progress
uint32_t UsbCommTimer =0;  // USB communication timer

/*----------------------------------------------------------------------------*/
/*  Local Function Prototypes                                                 */
/*----------------------------------------------------------------------------*/
static void usb_transfer_task(void);
static void receive_data_process(void);
static void hostif_command_process(uint8_t* data, uint16_t length, uint8_t fn);
static void get_hostif_packet_process(uint8_t* data, uint16_t size);
static void set_hostif_packet_process(uint8_t* data, uint16_t size, uint8_t fn);
static void bgma_idle_process(void);


/*----------------------------------------------------------------------------*/
/*  Functions                                                                 */
/*----------------------------------------------------------------------------*/
/******************************************************************************/
/* Function Name  :  bgma_app_main                                            */
/* Parameters     :  none                                                     */
/* Return Value   :  none                                                     */
/* Description    :  test application's main process                          */
/******************************************************************************/
void bgma_app_main(void)
{
    s_ReceivedSize = 0;
       
    /* initialize USB function */
    epcs_initialize();

    InitSystick();
    bgma_io_initial();
    uart_init(UART_BAUD_RATE_62500);
    enable_uvccm_int();
    enable_rstmx_int();
    enable_poutflx_int();
    
    while(epcs_clear_read() < 0);

    Gpio1pin_Put( GPIO1PIN_P3B, 1);  // USB connection successful

    /* infinite loop */
    while(1) {
        usb_transfer_task();
    }
}

/******************************************************************************/
/* Func Name      :   usb_transfer_task                                       */
/* Parameters     :   none                                                    */
/* Return Value   :   none                                                    */
/* Description    :   usb transfer task                                       */
/******************************************************************************/
static void usb_transfer_task(void)
{
    int32_t epcs_ret;
    uint16_t size;
    static bool GreenLed = 0;
    
    while(1) {
        bgma_idle_process();
        epcs_ret = epcs_check_read();
        if(epcs_ret > 0){
            break;
        } else if(epcs_ret < 0) {
            /* Source MCLK 1/2 */
            //CPU_MAP_IO_CSELR_CKS = 0;
            //while((CPU_MAP_IO_CMONR_CKM != 0) ||(IO_CLKG.IO_CMONR.bit.MCRDY != 1)){};
            /* Reset */
            NVIC_SystemReset();
            /* wait */
            while(1){};
        } else {
            ;
        }
    }
    
    size = (epcs_ret < APP_TRANSFER_BUFFER_SIZE) ? epcs_ret : APP_TRANSFER_BUFFER_SIZE;
    epcs_ret = epcs_read_data(s_AppReceive.Buffer, 0, size);
    if (epcs_ret > 0) {
        s_AppReceive.Size = epcs_ret;
        receive_data_process();
        s_AppReceive.Size = 0;
        /* CHMA added */
        UsbCommFlag = 1;  // Indication USB is receiving/sending data
        ClrTimeOut(&UsbCommTimer);
        Gpio1pin_Put( GPIO1PIN_P3B, GreenLed);  // Blink the green led
        GreenLed = !GreenLed;
    }

    epcs_clear_read();

    if (s_AppSend.Size > 0) {
        // epcs_ret = epcs_check_write();
        epcs_ret = epcs_clear_write();
        if (epcs_ret == 0) {
            epcs_ret = epcs_write_data(s_AppSend.Buffer, s_AppSend.Size);
            if (epcs_ret == s_AppSend.Size) {
                epcs_write_data(s_AppSend.Buffer, 0);
                s_AppSend.Size = 0;
            }
        }
    }
    return;
}

/******************************************************************************/
/* Func Name      :   receive_data_process                                    */
/* Parameters     :   none                                                    */
/* Return Value   :   none                                                    */
/* Description    :   receive data process                                    */
/******************************************************************************/
static void receive_data_process(void)
{
    uint16_t length;

    if (s_AppReceive.Buffer[APP_FORMAT_OFFSET_HEADER] == APP_FORMAT_HEADER) {
        if (s_AppReceive.Buffer[APP_FORMAT_OFFSET_ID] == APP_FORMAT_ID_HOSTIF) {
            length = (((uint16_t)s_AppReceive.Buffer[APP_FORMAT_OFFSET_LEN_L]) | (((uint16_t)s_AppReceive.Buffer[APP_FORMAT_OFFSET_LEN_H]) << 8));
            memcpy(&s_ReceiveBuffer[s_ReceivedSize], &s_AppReceive.Buffer[APP_FORMAT_OFFSET_DATA], length);
            s_ReceivedSize += length;

            if ((s_AppReceive.Buffer[s_AppReceive.Size - 2] == 0x03) && (s_AppReceive.Buffer[s_AppReceive.Size - 3] == 0x10)) {
                get_hostif_packet_process(s_ReceiveBuffer, s_ReceivedSize);
                memset(s_ReceiveBuffer, 0, s_ReceivedSize);
                s_ReceivedSize = 0;
            }
        }
    }

    return;
}

/******************************************************************************/
/* Func Name      :   get_hostif_packet_process                               */
/* Parameters     :   none                                                    */
/* Return Value   :   none                                                    */
/* Description    :   get host IF command from received data                  */
/******************************************************************************/
static void get_hostif_packet_process(uint8_t* data, uint16_t size)
{
    uint8_t sum = 0;
    uint8_t* hostif;
    uint16_t i;
    uint16_t j;
    uint16_t data_size;

    if ((data[0] == 0x10) && (data[1] == 0x02) && (data[2] == 0x00) && (data[size - 3] == 0x10) && (data[size - 2] == 0x03)) {
        sum += data[3];
        if (data[3] != 0x10) {
            hostif = &data[4];
            data_size = size - 7;
        } else {
            hostif = &data[5];
            data_size = size - 8;
        }

        for (i = 0, j = 0; i < data_size; i++, j++) {
            s_HostIfBuffer[j] = hostif[i];
            sum += hostif[i];
            if (hostif[i] == 0x10) {
                if (hostif[i+1] == 0x10) {
                    i++;
                } else {
                    return;
                }
            }
        }

        if (sum == (uint8_t)~data[size - 1]) {
            hostif_command_process(s_HostIfBuffer, j, data[3]);
        }
    }

    return;
}

/******************************************************************************/
/* Func Name      :   set_hostif_packet_process                               */
/* Parameters     :   none                                                    */
/* Return Value   :   none                                                    */
/* Description    :   setup host IF command for send                          */
/******************************************************************************/
static void set_hostif_packet_process(uint8_t* data, uint16_t size, uint8_t fn)
{
    uint8_t sum = 0;
    uint16_t i;
    uint16_t j;

    s_AppSend.Buffer[APP_FORMAT_OFFSET_HEADER] = APP_FORMAT_HEADER;
    s_AppSend.Buffer[APP_FORMAT_OFFSET_ID] = APP_FORMAT_ID_HOSTIF;

    s_AppSend.Buffer[APP_FORMAT_OFFSET_DATA+0] = 0x10;
    s_AppSend.Buffer[APP_FORMAT_OFFSET_DATA+1] = 0x02;
    s_AppSend.Buffer[APP_FORMAT_OFFSET_DATA+2] = 0x00;
    s_AppSend.Buffer[APP_FORMAT_OFFSET_DATA+3] = fn;
    if (fn == 0x10) {
        s_AppSend.Buffer[APP_FORMAT_OFFSET_DATA+4] = fn;
        j = APP_FORMAT_OFFSET_DATA+5;
    } else {
        j = APP_FORMAT_OFFSET_DATA+4;
    }
    sum += fn;

    for (i = 0 ; i < size; i++, j++) {
        s_AppSend.Buffer[j] = data[i];
        sum += data[i];

        if (data[i] == 0x10) {
            s_AppSend.Buffer[++j] = data[i];
        }
    }

    s_AppSend.Buffer[j++] = 0x10;
    s_AppSend.Buffer[j++] = 0x03;
    s_AppSend.Buffer[j++] = (uint8_t)~sum;

  //  send_data_process(s_HostIfBuffer, j);

  //  s_AppSend.Buffer[APP_FORMAT_OFFSET_HEADER] = APP_FORMAT_HEADER;
  //  s_AppSend.Buffer[APP_FORMAT_OFFSET_ID] = APP_FORMAT_ID_HOSTIF;
    s_AppSend.Buffer[APP_FORMAT_OFFSET_LEN_L] = (uint8_t)j;
    s_AppSend.Buffer[APP_FORMAT_OFFSET_LEN_H] = (uint8_t)(j >> 8);
//    memcpy(&s_AppSend.Buffer[APP_FORMAT_OFFSET_DATA], data, size);

    //s_AppSend.Size = j + 4;  // delete by Levi, 2015-03-20, why add 4 more bytes for the sending package??
    s_AppSend.Size = j;        // 2015-03-20, Levi
    
    return;
}

/******************************************************************************/
/* Func Name      :   hostif_command_process                                  */
/* Parameters     :   none                                                    */
/* Return Value   :   none                                                    */
/* Description    :   host IF command process                                 */
/******************************************************************************/
static void hostif_command_process(uint8_t* data, uint16_t length, uint8_t fn)
{
    uint16_t response_size = 0;
    uint8_t* response_data = NULL;
    const CMDTBL *tbl;
    uint16_t command = (((uint16_t)data[1]) | (((uint16_t)data[0]) << 8));
    
    (void)length;
    set_usbbuf_pointer(data);
    tbl= commandtable;
    while (tbl->fc != 0xFFFFU) {                 /* parsing FC */
        if (command == tbl->fc) break;
        tbl++;
    }
    if (command == EXIT_MON) monitor_state &= ~MON_START;
    
    /* send VCCERR if LOWPOWERIDT is true; send NOWTRIM if BGMA still in trim process */
    if (((monitor_state & TRIMMING) == TRIMMING) || ((power_state & LOWPOWERIDT) == LOWPOWERIDT)){
        if ((command == LOAD_ADPT_ENV)||(command == CNG_ADPT_MODE)){
            (tbl->func)();
        }else{
            if ((power_state & LOWPOWERIDT) == LOWPOWERIDT){
                set_errcode(VCCERR);
                power_state &= ~LOWPOWERIDT;
            }else set_errcode(NOWTRIM);
        }
    }else if ((power_state & LOW_POWER) == LOW_POWER || (power_state & OVER_CURRENT) == OVER_CURRENT){
        if ((command == LOAD_ADPT_ENV)||(command == CNG_ADPT_MODE)){
            (tbl->func)();
        } else if(command == BGMA_POW){
            if((power_state & LOW_POWER) == LOW_POWER){
                (tbl->func)();
            }
        }
        else set_errcode(VCCERR);
    } else {
        if ((monitor_state & MCU_RUN) == MCU_RUN){
            switch (command){ /* some command is different in MCU_RUN mode */
                case READ_BRK_STAT:
                    (tbl->func)();
                    break;   /* break status: 00 00 ff ff ff ff 00 00 00 00 */
                
                case ABORT_MCU:
                    (tbl->func)();
                    /* mcu_state = MCU_BREAK; */
                    break;   /* force to stop the free run mode */
                
                case LOAD_ADPT_ENV:
                    (tbl->func)();
                    break; 
                
                case CNG_ADPT_MODE:
                    (tbl->func)();
                    break; 
                case READ_RCK_SMDAT:
                    ram_mon_flag = 1;
                    (tbl->func)();
                    ram_mon_flag = 0;
                    break;
                case BGMA_POW:
                    (tbl->func)();
                    break;
                default:
                    set_errcode(MCUBUSY);  /* return MCU busy frame to host */
            }
        }
        else {       /* MCU_BREAK */
            (tbl->func)(); /* process command */
        }
    }
    
    response_data = get_usbbuf_pointer();
    response_size = get_usbbuf_size();
    if (response_size != 0) {
        set_hostif_packet_process(response_data, response_size, fn);
    }

    return;
}

/******************************************************************************/
/* Func Name      :   bgma_idle_process                                       */
/* Description    :   implement BGMA idle process                             */
/* Parameters     :   none                                                    */
/* Return Value   :   none                                                    */
/******************************************************************************/
static void bgma_idle_process(void)
{
    UART_COMMAND cmd;
    static bool RedLed=0;
    
    if ((power_state & LOW_POWER) == LOW_POWER) /* low power happened */
    {
        if (IO_UVCCM)  /* UVCC recover? */
        {               
            power_on_init();
            bFM0P_GPIO_ADE_AN01 = 0;  // Disable pin ADC function
            Gpio1pin_InitIn ( GPIO1PIN_P11, Gpio1pin_InitPullup( 0u ) );  // SI pin
            Gpio1pin_InitIn ( GPIO1PIN_P50, Gpio1pin_InitPullup( 0u ) );  // RSTMX pin
            //IO_RSTX = 1;
        }
    }
    if ((monitor_state & MCU_RUN) == MCU_RUN)  /* EXE_MCU is active */
    {
        check_break_stat(&cmd);
    }
    if ((power_state & USER_RST) == USER_RST) 
    {
        if (IO_RSTMX)
        {              /* reset complete */
            power_state &= ~USER_RST;      /* clear user reset flag */
            delay_time = 0x0000U;          /* recover delay time */
            enable_rstmx_int();
            if (((monitor_state & MON_START) == MON_START) &&
                ((monitor_state & MCU_RUN) == MCU_BREAK)) 
            {
                power_state |= RST_ERROR;   /* set RST_ERROR flag if MON start */
            }
        }
    }
    if ((monitor_state & TRIMMING) == TRIMMING)  /* still in trim process */
    {  
        bFM0P_GPIO_ADE_AN01 = 0;  // Disable pin ADC function
        Gpio1pin_InitIn ( GPIO1PIN_P11, Gpio1pin_InitPullup( 0u ) );  // SI pin
        Gpio1pin_InitIn ( GPIO1PIN_P50, Gpio1pin_InitPullup( 0u ) );  // RSTMX pin
        if (retry_counter > CR_RETRY_TIME)
        {
            CR_state = TRIM_FAIL;
            monitor_state &= ~TRIMMING;
            retry_counter = 0;
            monitor_state |= CR_FINE;
        } else 
        {
            if (trim_cr(&cmd) == NORMAL)
            {
                monitor_state &= ~TRIMMING;
                retry_counter = 0;
                monitor_state |= CR_FINE;
          //      RegBuff_Init(&cmd);
            }
            else 
            {
                retry_counter++;
            }
        }
        /* CHMA added */
        RedLed = !RedLed;
        Gpio1pin_Put( GPIO1PIN_P3C, RedLed);  // Turn on red led
        return;
    }
    
    /* CHMA added */
    if ( (CR_state & TRIM_FAIL) == TRIM_FAIL )
    {
         Gpio1pin_Put( GPIO1PIN_P3C, 1);  // Turn on red led
    }
    else 
    {
         Gpio1pin_Put( GPIO1PIN_P3C, 0);  // Turn off red led
    }
    
    /* CHMA added */
    if ( UsbCommFlag )
    {
        if ( IsTimeOut(&UsbCommTimer, 400) )
        {
            UsbCommFlag = 0;
            Gpio1pin_Put( GPIO1PIN_P3B, 1);  // Turn on green led
        }
    }
    return;
}



