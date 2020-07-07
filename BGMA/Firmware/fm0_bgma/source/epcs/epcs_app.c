/******************************************************************************/
/* File Name      : epcs_app.c                                                */
/* Project        : BGM Adapter                                               */
/* Module Function: application of epcs module                                */
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
#include "epcs_config.h"
#include "epcs_app.h"
#include "epcs_vendor.h"

/******************************************************************************/
/*  Global Variable Definition                                                */
/******************************************************************************/
uint32_t g_EpcsFROMFailedAddr;      /* address of failed operation at FlashROM */

/******************************************************************************/
/*  Constant Definition                                                       */
/******************************************************************************/
#define EPCS_CHECK_SIGNATURE       (0x42474D41) /* signature for application check */
#define EPCS_DEFAULT_APP_TOP_ADDR  (0x0F0000)   /* top address of default application (2010/7/6) 0x0E 0000 -> 0x0F 0000*/
#define EPCS_TOP_ADDR              (0x0FC000)   /* top address of EPCS */
#define EPCS_DUMMY_APP_TOP_ADDR    (0x0FFB00)   /* top address of dummy application */
#define EPCS_VECTOR_ADDR           (0x0FFC00)   /* vector address of EPCS */

/******************************************************************************/
/*  Header Definition                                                         */
/******************************************************************************/
// 0x0F0000
const uint32_t g_EpcsDefaultHeader[4] = {
    /* CheckSum */
    0xffffffff, 
    /* Version Level Release Option */
    0x01020800,
    /* Signature */
    EPCS_CHECK_SIGNATURE,
    /* VectorAddress */
    0x0F9C00
};
// 0x0FC000
const uint32_t g_EpcsHeader[4] = {
    /* CheckSum */
    0xffffffff, 
    /* Version Level Release Option */
    (BGMA_INFO_VERSION_NUMBER<<24) | (BGMA_INFO_LEVEL_NUMBER<<16) | (BGMA_INFO_RELEASE_NUMBER<<8) | (BGMA_INFO_OPTION_NUMBER),
    /* Signature */
    EPCS_CHECK_SIGNATURE, 
    /* VectorAddress */
    EPCS_VECTOR_ADDR 
};

/******************************************************************************/
/*  Static Variable Definition                                                */
/******************************************************************************/
static uint32_t s_EpcsRunningAppAddr;  /* address of running application */

/******************************************************************************/
/*  Local Function Prototypes                                                 */
/******************************************************************************/

/******************************************************************************/
/*  Functions                                                                 */
/******************************************************************************/

/******************************************************************************/
/* Function Name  :  EPCS_APP_Main                                            */
/* Parameters     :  none:                                                    */
/* Return Value   :  none                                                     */
/* Description    :  main process                                             */
/******************************************************************************/
void EPCS_APP_Main(void)
{
    /* clear address of failed operation at FlashROM */
    g_EpcsFROMFailedAddr = 0;
    /* set running application address */
    s_EpcsRunningAppAddr = EPCS_DEFAULT_APP_TOP_ADDR;
}

/******************************************************************************/
/* Function Name  :  EPCS_APP_GetBgmaInfo                                     */
/* Parameters     :  info: pointer to BGM Adapter's information               */
/*                   size: size of BGM Adapter's information                  */
/* Return Value   :  none                                                     */
/* Description    :  get BGM Adapter's information                            */
/******************************************************************************/
void EPCS_APP_GetBgmaInfo(uint8_t* info, uint8_t* size)
{
    uint8_t index = 0;

    /* set running application's address */
    info[index] = BGMA_INFO_ID_RUNNING_APP_ADDR;
    index ++;
    info[index] = (uint8_t)s_EpcsRunningAppAddr;
    index ++;
    info[index] = (uint8_t)(s_EpcsRunningAppAddr >> 8);
    index ++;
    info[index] = (uint8_t)(s_EpcsRunningAppAddr >> 16);
    index ++;

    /* set running application's version */
    info[index] = BGMA_INFO_ID_RUNNING_VERSION;
    index ++;
    info[index] = *((uint8_t*)(&g_EpcsDefaultHeader) + 7);
    index ++;
    info[index] = *((uint8_t*)(&g_EpcsDefaultHeader) + 6);
    index ++;
    info[index] = *((uint8_t*)(&g_EpcsDefaultHeader) + 5);
    index ++;

    /* set dummy(=EPCS) application's address */
    info[index] = BGMA_INFO_ID_DUMMY_APP_ADDR;
    index ++;
    info[index] = (uint8_t)EPCS_TOP_ADDR;
    index ++;
    info[index] = (uint8_t)(EPCS_TOP_ADDR >> 8);
    index ++;
    info[index] = (uint8_t)(EPCS_TOP_ADDR >> 16);
    index ++;

    /* set EPCS's version */
    info[index] = BGMA_INFO_ID_EPCS_VERSION;
    index ++;
    info[index] = *((uint8_t*)(&g_EpcsHeader) + 7);
    index ++;
    info[index] = *((uint8_t*)(&g_EpcsHeader) + 6);
    index ++;
    info[index] = *((uint8_t*)(&g_EpcsHeader) + 5);
    index ++;

    /* set status of FlashROM operation. */
    info[index] = BGMA_INFO_ID_FLASHROM_ADDR;
    index ++;
    info[index] = (uint8_t)g_EpcsFROMFailedAddr;
    index ++;
    info[index] = (uint8_t)(g_EpcsFROMFailedAddr >> 8);
    index ++;
    info[index] = (uint8_t)(g_EpcsFROMFailedAddr >> 16);
    index ++;

#if (BGMA_INFO_OPTIONAL_ADDITIONAL_3 == OPTIONAL_TRUE)
    /* set additional infomation */
    WORD_TO_LE_BUFFER(&info[index], BGMA_INFO_ADDITIONAL_3);
    index += 4;
#endif

#if (BGMA_INFO_OPTIONAL_ADDITIONAL_4 == OPTIONAL_TRUE)
    /* set additional infomation */
    WORD_TO_LE_BUFFER(&info[index], BGMA_INFO_ADDITIONAL_4);
    index += 4;
#endif

#if (BGMA_INFO_OPTIONAL_ADDITIONAL_5 == OPTIONAL_TRUE)
    /* set additional infomation */
    WORD_TO_LE_BUFFER(&info[index], BGMA_INFO_ADDITIONAL_5);
    index += 4;
#endif

#if (BGMA_INFO_OPTIONAL_ADDITIONAL_6 == OPTIONAL_TRUE)
    /* set additional infomation */
    WORD_TO_LE_BUFFER(&info[index], BGMA_INFO_ADDITIONAL_6);
    index += 4;
#endif

#if (BGMA_INFO_OPTIONAL_ADDITIONAL_7 == OPTIONAL_TRUE)
    /* set additional infomation */
    WORD_TO_LE_BUFFER(&info[index], BGMA_INFO_ADDITIONAL_7);
    index += 4;
#endif

#if (BGMA_INFO_OPTIONAL_ADDITIONAL_8 == OPTIONAL_TRUE)
    /* set additional infomation */
    WORD_TO_LE_BUFFER(&info[index], BGMA_INFO_ADDITIONAL_8);
    index += 4;
#endif

#if (BGMA_INFO_OPTIONAL_ADDITIONAL_9 == OPTIONAL_TRUE)
    /* set additional infomation */
    WORD_TO_LE_BUFFER(&info[index], BGMA_INFO_ADDITIONAL_9);
    index += 4;
#endif

#if (BGMA_INFO_OPTIONAL_ADDITIONAL_10 == OPTIONAL_TRUE)
    /* set additional infomation */
    WORD_TO_LE_BUFFER(&info[index], BGMA_INFO_ADDITIONAL_10);
    index += 4;
#endif

#if (BGMA_INFO_OPTIONAL_ADDITIONAL_11 == OPTIONAL_TRUE)
    /* set additional infomation */
    WORD_TO_LE_BUFFER(&info[index], BGMA_INFO_ADDITIONAL_11);
    index += 4;
#endif

#if (BGMA_INFO_OPTIONAL_ADDITIONAL_12 == OPTIONAL_TRUE)
    /* set additional infomation */
    WORD_TO_LE_BUFFER(&info[index], BGMA_INFO_ADDITIONAL_12);
    index += 4;
#endif

#if (BGMA_INFO_OPTIONAL_ADDITIONAL_13 == OPTIONAL_TRUE)
    /* set additional infomation */
    WORD_TO_LE_BUFFER(&info[index], BGMA_INFO_ADDITIONAL_13);
    index += 4;
#endif

    *size = index;

    return;
}

