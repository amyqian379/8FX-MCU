/******************************************************************************/
/* File Name      : dbg_print.h                                               */
/* Project        : USB Demo Soft                                             */
/* Module Function: implementation of the debug print support function        */
/* Author         : jialili                                                   */
/* Version        : 1.00                                                      */
/* Date           : 2010/02/01                                                */
/* History        : 2010/02/01  create                                        */
/*                  Copyright 2010 FUJITSU ELECTRONICS INC.  LIMITED          */
/******************************************************************************/
#ifndef __DBG_PRINT_INC__
#define __DBG_PRINT_INC__

/*----------------------------------------------------------------------------*/
/* Headers                                                                    */
/*----------------------------------------------------------------------------*/
#include "config.h"
#include <stdio.h>

/*----------------------------------------------------------------------------*/
/* Constant Definition                                                        */
/*----------------------------------------------------------------------------*/

#if (UART_PRINTF_ENABLED == ENABLED)

/*----------------------------------------------------------------------------*/
/* Global Variable Declaration                                                */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Global Function Prototypes                                                 */
/*----------------------------------------------------------------------------*/
void printf_dump_hex(const uint8_t *p, uint32_t len);

/* macro for only print message */
#define DbgPrintMsg(...)                (printf(__VA_ARGS__))
/* macro for print message and data */
#define DbgPrintArray(a, b)             printf_dump_hex(a, b)

#else

/* dummy */
#define DbgPrintMsg(...);               {;}
#define DbgPrintArray(a,b)              {;}
    
#endif  /* UART_PRINTF_ENABLED */

#endif /* __DBG_PRINT_INC__ */

