/******************************************************************************/
/* File Name      : epcs_config.h                                             */
/* Project        : BGM Adapter                                               */
/* Module Function: configuration for epcs module                             */
/* Author         : lijiale                                                   */
/* Version        : 1.0                                                       */
/* Date           : 2010/03/15                                                */
/* History        : 2010/03/15  create                                        */
/*                  Copyright 2010 FUJITSU ELECTRONICS INC.  LIMITED          */
/******************************************************************************/
#ifndef __EPCS_CONFIG_INC__
#define __EPCS_CONFIG_INC__

/******************************************************************************/
/*  Headers                                                                   */
/******************************************************************************/

/******************************************************************************/
/*  Constant Definition                                                       */
/******************************************************************************/
/* definition to BGM Adapter information */
#define BGMA_INFO_ID_RUNNING_APP_ADDR  (0x00)  /* fixed ID for running application's address */
#define BGMA_INFO_ID_RUNNING_VERSION   (0x01)  /* fixed ID for running application's version */
#define BGMA_INFO_ID_DUMMY_APP_ADDR    (0x02)  /* fixed ID for dummy(EPCS) application's address */
#define BGMA_INFO_ID_EPCS_VERSION      (0x03)  /* fixed ID for EPCS's version */
#define BGMA_INFO_ID_FLASHROM_ADDR     (0xFF)  /* fixed ID for FlashROM operation fail address */

#define BGMA_INFO_VERSION_NUMBER       (0xF1)  /* version number */
#define BGMA_INFO_LEVEL_NUMBER         (0x00)  /* level number */
#define BGMA_INFO_RELEASE_NUMBER       (0x03)  /* release number */
#define BGMA_INFO_OPTION_NUMBER        (0x00)  /* option number */

/* configuration for additional information */
#define OPTIONAL_TRUE                  (0x01)
#define OPTIONAL_FALSE                 (0x00)

#define BGMA_INFO_OPTIONAL_ADDITIONAL_1   (OPTIONAL_TRUE)
#define BGMA_INFO_OPTIONAL_ADDITIONAL_2   (OPTIONAL_TRUE)
#define BGMA_INFO_OPTIONAL_ADDITIONAL_3   (OPTIONAL_TRUE)
#define BGMA_INFO_OPTIONAL_ADDITIONAL_4   (OPTIONAL_TRUE)
#define BGMA_INFO_OPTIONAL_ADDITIONAL_5   (OPTIONAL_TRUE)
#define BGMA_INFO_OPTIONAL_ADDITIONAL_6   (OPTIONAL_TRUE)
#define BGMA_INFO_OPTIONAL_ADDITIONAL_7   (OPTIONAL_TRUE)
#define BGMA_INFO_OPTIONAL_ADDITIONAL_8   (OPTIONAL_TRUE)
#define BGMA_INFO_OPTIONAL_ADDITIONAL_9   (OPTIONAL_TRUE)
#define BGMA_INFO_OPTIONAL_ADDITIONAL_10  (OPTIONAL_TRUE)
#define BGMA_INFO_OPTIONAL_ADDITIONAL_11  (OPTIONAL_TRUE)
#define BGMA_INFO_OPTIONAL_ADDITIONAL_12  (OPTIONAL_TRUE)
#define BGMA_INFO_OPTIONAL_ADDITIONAL_13  (OPTIONAL_TRUE)

/* additional infomation */
#define BGMA_INFO_ADDITIONAL_1         (0x00000003)  /* additional infomation -1 */
#define BGMA_INFO_ADDITIONAL_2         (0x00000004)  /* additional infomation -2 */
#define BGMA_INFO_ADDITIONAL_3         (0x00000005)  /* additional infomation -3 */
#define BGMA_INFO_ADDITIONAL_4         (0x00000006)  /* additional infomation -4 */
#define BGMA_INFO_ADDITIONAL_5         (0x00000007)  /* additional infomation -5 */
#define BGMA_INFO_ADDITIONAL_6         (0x00000008)  /* additional infomation -6 */
#define BGMA_INFO_ADDITIONAL_7         (0x00000009)  /* additional infomation -7 */
#define BGMA_INFO_ADDITIONAL_8         (0x0000000A)  /* additional infomation -8 */
#define BGMA_INFO_ADDITIONAL_9         (0x0000000B)  /* additional infomation -9 */
#define BGMA_INFO_ADDITIONAL_10        (0x0000000C)  /* additional infomation -10 */
#define BGMA_INFO_ADDITIONAL_11        (0x0000000D)  /* additional infomation -11 */
#define BGMA_INFO_ADDITIONAL_12        (0x0000000E)  /* additional infomation -12 */
#define BGMA_INFO_ADDITIONAL_13        (0x0000000F)  /* additional infomation -13 */

#endif
