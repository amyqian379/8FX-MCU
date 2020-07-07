/******************************************************************************/
/* File Name      : dbg_print.c                                               */
/* Project        : USB Demo Soft                                             */
/* Module Function: implementation of the debug print support function        */
/* Author         : jialili                                                   */
/* Version        : 1.00                                                      */
/* Date           : 2010/02/01                                                */
/* History        : 2010/02/01  create                                        */
/*                  Copyright 2010 FUJITSU ELECTRONICS INC.  LIMITED          */
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/* Headers                                                                    */
/*----------------------------------------------------------------------------*/
#include "dbg_print.h"
#include <string.h>

#if (UART_PRINTF_ENABLED == ENABLED)

/*----------------------------------------------------------------------------*/
/* Constant Definition                                                        */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Type     Definition                                                        */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Static Variable Definition                                                 */
/*----------------------------------------------------------------------------*/
/* buffer for send message */
uint8_t  g_DbgBuffer[256];

/*----------------------------------------------------------------------------*/
/* Local Function Prototypes                                                  */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Functions                                                                  */
/*----------------------------------------------------------------------------*/
/*******************************************************************************
* Function Name: printf_dump_hex
********************************************************************************
*
* This function use to display a string message followed by up to 16 hex bytes
* of an array from application code.
*
* \param p   - Pointer to the data buffer.
*
* \param len - The size of print data buffer.
*
* \return None
*
*******************************************************************************/
void printf_dump_hex(const uint8_t *p, uint32_t len)
{
    uint32_t i;
    char buff1[100];

    if(0 == len)
    {
        printf("None\r\n");
        return;
    }
    while (len != 0)
    {
        memset(buff1, 0, sizeof(buff1));
        for (i = 0; i < len && i < 32; i++)
        {
            int s1 = (*p & 0xf0) >> 4;
            int s2 = *p & 0x0f;
            buff1[i * 3]     = (s1 >= 0 && s1 <= 9) ? s1 + '0' : s1 - 10 + 'A';
            buff1[i * 3 + 1] = (s2 >= 0 && s2 <= 9) ? s2 + '0' : s2 - 10 + 'A';
            buff1[i * 3 + 2] = ' ';
            p++;
        }
        len -= i;
        if (len != 0)
            printf("%s\r\n", buff1);
    }
    printf("%s\r\n", buff1);
}

#endif  //(UART_PRINTF_ENABLED == ENABLED)
