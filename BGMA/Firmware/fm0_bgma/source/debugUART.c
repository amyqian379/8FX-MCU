/**
 * @file debugUART.c
 *
 * @brief @{Debug UART interface source file@}
 */

/*
 * Copyright (2014-2017), Cypress Semiconductor Corporation or a subsidiary of
 * Cypress Semiconductor Corporation. All rights reserved.
 *
 * This software, including source code, documentation and related materials
 * (“Software”), is owned by Cypress Semiconductor Corporation or one of its
 * subsidiaries (“Cypress”) and is protected by and subject to worldwide patent
 * protection (United States and foreign), United States copyright laws and
 * international treaty provisions. Therefore, you may use this Software only
 * as provided in the license agreement accompanying the software package from
 * which you obtained this Software (“EULA”).
 *
 * If no EULA applies, Cypress hereby grants you a personal, nonexclusive,
 * non-transferable license to copy, modify, and compile the Software source
 * code solely for use in connection with Cypress’s integrated circuit
 * products. Any reproduction, modification, translation, compilation, or
 * representation of this Software except as specified above is prohibited
 * without the express written permission of Cypress. Disclaimer: THIS SOFTWARE
 * IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress reserves the
 * right to make changes to the Software without notice. Cypress does not
 * assume any liability arising out of the application or use of the Software
 * or any product or circuit described in the Software. Cypress does not
 * authorize its products for use in any products where a malfunction or
 * failure of the Cypress product may reasonably be expected to result in
 * significant property damage, injury or death (“High Risk Product”). By
 * including Cypress’s product in a High Risk Product, the manufacturer of such
 * system or application assumes all risk of such use and in doing so agrees to
 * indemnify Cypress against all liability.
 */
#include "string.h"
#include <mcu.h>
#include "debugUART.h"

#if (DEBUG_UART == ENABLED)

#define stc_mfsn_uart_t FM_MFS_UART_TypeDef 
#define DEBUG_UART_HW   (*((volatile stc_mfsn_uart_t *) FM_MFS7_UART_BASE))


/**
 * @brief: Initialize debug UART.
 */
void debugUARTInit(void)
{
    /* Preset local register variables to zero */
    stc_mfs_uart_smr_field_t  stcSMR;
    stc_mfs_uart_scr_field_t  stcSCR;
    stc_mfs_uart_escr_field_t stcESCR;
    memset((uint8_t*)&(stcSMR), 0, (uint32_t)(sizeof(stcSMR)));
    memset((uint8_t*)&(stcSCR), 0, (uint32_t)(sizeof(stcSCR)));
    memset((uint8_t*)&(stcESCR), 0, (uint32_t)(sizeof(stcESCR)));
    
    /* Set UART mode */
    stcSMR.MD = 0u;   /* Normal mode */
    /* Enable SOE */
    stcSMR.SOE = TRUE;
    /* Set Parity */
    stcESCR.P   = FALSE; /* Parity type selection (0-even/1-odd) */
    stcESCR.PEN = FALSE; /* Parity disable */
    /* Set Stop bit length */
    stcSMR.SBL   = FALSE;
    stcESCR.ESBL = FALSE;   
    /* Set Data bit length (5 - 9bits) */  
    stcESCR.L = 0;
    /* Set Bit direction (LSB/MSB) */    
    stcSMR.BDS = 0;
    /* HW Flow */
    stcESCR.FLWEN = FALSE;
    /* Set Signal system (NRZ/Int-NRZ) */
    stcESCR.INV = FALSE;
    /* Clear MFS by setting the Software Reset bit */
    DEBUG_UART_HW.SCR_f.UPCL = TRUE;

    /* Set Baudrate */
    uint32_t u32Pclk1;
    SystemCoreClockUpdate();  
    u32Pclk1 = SystemCoreClock / (1ul << (FM_CRG->APBC1_PSR & 0x03u)); /* MFS is attached on APB1 bus in FM0+ device */    
    DEBUG_UART_HW.BGR_f.BGR = (u32Pclk1/115200) - 1;

    /* Set registers value */
    DEBUG_UART_HW.SMR_f  = stcSMR;
    DEBUG_UART_HW.SCR_f  = stcSCR;
    DEBUG_UART_HW.ESCR_f = stcESCR;
    /* Set external clock */
    DEBUG_UART_HW.BGR_f.EXT = 0u;
    
    /* Configue FIFO */
    /* Reset FIFO */
    DEBUG_UART_HW.FCR_f.FCL1 = 1;
    DEBUG_UART_HW.FCR_f.FCL2 = 1;
    /* Enable FIFO receive Idle detection */
    DEBUG_UART_HW.FCR_f.FRIIE = 1u;
    /* Selection TX and RX FIFO  */
    DEBUG_UART_HW.FCR_f.FSEL = 0u;
    /* Set FIFO count */
    DEBUG_UART_HW.FBYTE1 = 0u;
    DEBUG_UART_HW.FBYTE2 = 0u;
    /* Enable FIFO  */
    DEBUG_UART_HW.FCR_f.FE1 = 1u;
    DEBUG_UART_HW.FCR_f.FE2 = 1u;

    /* Enable Tx and disable Rx operation in the MFS block */
    DEBUG_UART_HW.SCR_f.TXE = 1u;
    DEBUG_UART_HW.SCR_f.RXE = 0u;
    
    /* Set SIN and SOT pins based on CYDWR selections or control file */
    //SetPinFunc_SIN7_1();
    SetPinFunc_SOT7_1(); 
}

/**
 * @brief: Check UART tranfer buffer empty status.
 */
boolean_t debugUARTTxIsEmpty(void)
{
    return (DEBUG_UART_HW.SSR_f.TDRE == 1u) ? TRUE : FALSE;
}

/**
 * @brief: Write UART data buffer.
 */
void debugUARTSendData(uint16_t u16Data)
{
    DEBUG_UART_HW.TDR = u16Data;
}

/**
 * @brief: Send one byte by UART
 */
void debugUARTTransmitUartByte(uint8_t data)
{
    while((FALSE == debugUARTTxIsEmpty()));
    debugUARTSendData(data);
}

#endif

/* [] END OF FILE */
