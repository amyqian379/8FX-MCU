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
/** \file uartcomm.h
 **
 ** Headerfile for uart communication functions
 **
 ** History:
 **   - 2020-04-18  2.0  haxi  First version (starting at version 1.0)
 **
 ******************************************************************************/

#ifndef __UARTCOMM_H__
#define __UARTCOMM_H__

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "mcu.h"
#include "UARTio.h"

/* UART Timer setting */
#define UART_SEND_TIMEOUT_TIMER     2700
#define UART_REV_TIMEOUT_TIMER      50000
#define UART_CR_TIMEOUT_TIMER       250
#define UART_BREAK_TIMER            700
#define UART_ERASE_TIMER            10000




/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

uint8_t uart_put(uint8_t *cmd, uint32_t timer, uint8_t put_cnt);
uint8_t uart_get(uint8_t *cmd, uint32_t timer, uint8_t get_cnt);
void cr_put(UART_COMMAND* cmd, uint32_t timer);


uint8_t cr_get(void* DataPtr);
uint8_t erase_get(void* DataPtr);
void send_break();
uint8_t uart_communication(UART_COMMAND *cmd);
uint8_t uart_communication_16(UART_COMMAND_16 *cmd16);
uint8_t uart_communication_8(UART_COMMAND_8 *cmd8);

#ifdef __cplusplus
}
#endif

//@} // UsbGroup
#endif /* __UARTCOMM_H__ */
/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/
