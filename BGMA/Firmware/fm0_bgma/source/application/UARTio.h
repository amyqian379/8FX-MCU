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
/** \file UARTio.h
 **
 ** Headerfile for UART io functions
 **
 ******************************************************************************/

#ifndef __UARTIO_H__
#define __UARTIO_H__

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "mcu.h"
#include "systick.h"

#define UART_DBG_CH    FM0P_MFS1
#define UART_PORT      0x01

#define UART_BAUDRATE(x)  (uint16_t)((__HCLK / ((APBC1_PSR_Val & 0x03) + 1))/((uint32_t)x )- 1)
#define PINRELOC_UnSet_EPFR(epfr,pos,width,value)    \
          ((epfr) = (((epfr) & ~(((1u<<(width))-1u)<<(pos))) & \
          ~((value) << (pos))))

/* UART receive max buffer size */
#define UART_REV_MAX_SIZE  0x0A
            
/*############ BGMA IF COMMAND LIST ##########*/
#define BGMA_PST        0x00U         /* Parameter Set */
#define BGMA_RD         0x81U         /* Read memory */
#define BGMA_DRD        0x82U         /* Dsu Read */
#define BGMA_WR         0x03U         /* Write memory */
#define BGMA_DWR        0x05U         /* Dsu Write */
#define BGMA_FER        0x06U         /* Flash Erase */
#define BGMA_FWR        0x07U         /* Flash Write */
#define BGMA_RST        0x08U         /* user Reset */
#define BGMA_GO         0x09U         /* user execute */
#define BGMA_CMD_A      0x0AU         /* Ram Code execute type A */
#define BGMA_CMD_B      0x8AU         /* Ram Code execute type B */
#define BGMA_RD_2       0x91U         /* clock operation */
#define BGMA_FWR_2      0x17U         /* clock operation */
#define BGMA_FWR8       0x27U         /* write 8 */
#define BGMA_RD16       0xA1U         /* read 16 */

/*############ HOST IF RETURN LIST ############*/
#define NORCOD  0x00U     /* normal end */
#define BUFFIL  0x01U     /* reserved */
#define MCUBUSY 0x02U     /* MCU busy */
#define NONEXE  0x03U     /* reserved */
#define LOWFRQ  0x04U     /* reserved */
#define NOWTRIM 0x20U     /* trim busy */

#define VCCERR  0x40U     /* power error */
#define URIERR  0x41U     /* user reset error */
#define VFYERR  0x42U     /* reserved */
#define RSTRER  0x43U     /* reserved */
#define RSTERR  0x44U     /* reserved */

#define COMERR  0x80U     /* invalid command */
#define PARAER  0x81U     /* parameter error */
#define OVRFLW  0x82U     /* over flow */
#define DDEFER  0x83U     /* reserved */
#define ALGNER  0x84U     /* reserved */
#define ERSERR  0x85U     /* erase error */
#define WRTERR  0x86U     /* write error */

#define TARERR  0xC0U     /* communication with target error */
#define FLEXER  0xF0U     /* reserved */
#define FLSHER  0xF1U     /* reserved */
#define SECERR  0xFDU     /* security error */
#define INTERR  0xFEU     /* inernal error */
#define FATAL   0xFFU     /* fatal error */
            
/* Baud rate setting */
#define UART_BAUD_RATE_62500   0
#define UART_BAUD_RATE_500k    1
#define UART_BAUD_RATE_125000  2            
            
/* structure of the UART command */
typedef struct __uart_command__ {   /* UART communication data structure */
    uint8_t FC;               /* command type */
    uint8_t AddrH;            /* higher 8bits address */
    uint8_t AddrL;            /* lower 8bits address */
    uint8_t RC;               /* response command from target */
} UART_COMMAND;

typedef struct __uart_command_16__ {   /* UART communication data structure */
    uint8_t FC;               /* command type */
    uint8_t Data0;           
    uint8_t Data1;           
    uint8_t Data2; 
    uint8_t Data3; 
    uint8_t Data4; 
    uint8_t Data5; 
    uint8_t Data6; 
    uint8_t Data7; 
    uint8_t Data8; 
    uint8_t Data9; 
    uint8_t Data10; 
    uint8_t Data11; 
    uint8_t Data12; 
    uint8_t Data13; 
    uint8_t Data14;            
    uint8_t Data15;
    uint8_t RC;               /* response command from target */
} UART_COMMAND_16;
typedef struct __uart_command_8__ {   /* UART communication data structure */
    uint8_t FC;               /* command type */
    uint8_t Data0;           
    uint8_t Data1;           
    uint8_t Data2; 
    uint8_t Data3; 
    uint8_t Data4; 
    uint8_t Data5; 
    uint8_t Data6; 
    uint8_t Data7; 
    uint8_t RC;               /* response command from target */
} UART_COMMAND_8;

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif
/* UART receive max size */
extern uint8_t rev_buf[UART_REV_MAX_SIZE];  
/* read pointer for rev_buf */
extern uint8_t *p_wr_buf;
/* write pointer for rev_buf */
extern uint8_t *p_rd_buf; 
/* uart error flag */
extern uint8_t uart_error;
/*record uart received data number*/
extern uint8_t Secu16BytesRec;
  
void waitus(uint32_t timer);
void wait60us(uint32_t timer);
void MFS_ChangeUARTPinToGPIO(void);
void uart_init(uint8_t Baudrate);
uint8_t uart_send(uint8_t *DataPtr, uint32_t time_out);
uint8_t uart_receive(uint8_t *DataPtr, uint32_t time_out, uint8_t cnt);
void sendbrk(uint32_t time_out);
uint8_t erase_receive(uint8_t *DataPtr, uint32_t time_out, uint8_t cnt);
uint8_t cr_receive(uint8_t *DataPtr);


void bt0_enable(uint8_t one_shot, uint32_t timer);
void clear_bt0_flag(void);
void bt0_disable(void);
uint8_t check_bt0_overflow(void);
#ifdef __cplusplus
}
#endif

//@} 
#endif 
/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/
