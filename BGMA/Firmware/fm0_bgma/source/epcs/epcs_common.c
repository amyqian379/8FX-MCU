/******************************************************************************/
/* File Name      : epcs_common.c                                             */
/* Project        : BGM Adapter                                               */
/* Module Function: common function                                           */
/* Author         : lijiale                                                   */
/* Version        : 1.0                                                       */
/* Date           : 2010/03/15                                                */
/* History        : 2010/03/15  create                                        */
/*                  Copyright 2010 FUJITSU ELECTRONICS INC.  LIMITED          */
/******************************************************************************/

/******************************************************************************/
/* Headers                                                                    */
/******************************************************************************/
#include "epcs_common.h"

/******************************************************************************/
/* Functions                                                                  */
/******************************************************************************/

/******************************************************************************/
/* Function Name  :  EPCS_MEMCPY                                              */
/* Parameters     :  pDest: pointer to destination                            */
/*                   pSrc: pointer to source                                  */
/*                   Count: data size                                         */
/* Return Value   :  none                                                     */
/* Description    :  copy data                                                */
/******************************************************************************/
void EPCS_MEMCPY(void* pDest, void* pSrc, uint32_t Count)
{
    uint32_t i;
    uint8_t* dest = (uint8_t*)pDest;
    uint8_t* src;
    uint8_t cnt = (0 == (Count%4)) ? (Count/4) : ((Count/4)+1);

    src = (uint8_t*)pSrc + cnt * 4 - 1;
    for(i=0; i<Count; ++i) {
        dest[i] = *(src-i);
    }
    return;
}

/******************************************************************************/
/* Function Name  :  EPCS_MEMSET                                              */
/* Parameters     :  pBuffer: pointer to data buffer                          */
/*                   Data: data to set                                        */
/*                   Count: data size                                         */
/* Return Value   :  none                                                     */
/* Description    :  set data                                                 */
/******************************************************************************/
void EPCS_MEMSET(void* pBuffer, uint8_t Data, uint32_t Count)
{
    uint8_t* buf=(uint8_t*)pBuffer;

	while(Count-- > 0)
	{
		*buf++ = Data;
	}

	return;
}

