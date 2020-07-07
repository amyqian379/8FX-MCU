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
/** \file gpio.h
 **
 ** Headerfile for GPIO functions
 **
 ** History:
 **   - 2014-11-10  1.0  EZh    First version.
 **   - 2015-02-05  1.1  MSc    Moved from PDL to MCU template
 **   - 2016-05-10  1.2  ACEH   Added brackets in PINRELOC_SET_EPFR
 **
 ******************************************************************************/

#ifndef __GPIO_H__
#define __GPIO_H__

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "base_types.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 ******************************************************************************
 ** \defgroup GpioGroup GPIO Defintions (GPIO)
 **
 ** Definitions of GPIO and resource pin relocation
 **
 ** \attention
 **            - Carefully check in device documentation, whether SOUBOUT pin
 **              at SOUBOUT[_n] or TIOB0 pin should be output. TIOB0-SUBOUT
 **              is <b>not</b> provided by this driver!
 **            - Internal LSYN connection is not provided by this driver!
 ******************************************************************************/
//@{

/******************************************************************************/
/* Defines                                                                    */
/******************************************************************************/

#define Gpio1pin_InitIn(p,settings)    do{ stc_gpio1pin_init_t __v__;\
                                         __v__.bPullup=0u;__v__.bInitVal=0u;\
                                         (settings);\
                                         p##_INITIN(__v__); }while(0)

#define Gpio1pin_InitOut(p,settings)   do{ stc_gpio1pin_init_t __v__;\
                                         __v__.bPullup=0u;__v__.bInitVal=0u;\
                                         (settings);\
                                         p##_INITOUT(__v__); }while(0)

#define Gpio1pin_Init(p,settings)      do{ stc_gpio1pin_init_t __v__;__v__.bOutput=0u;\
                                         __v__.bPullup=0u;__v__.bInitVal=0u;\
                                         (settings);\
                                         p##_INIT( __v__ ); }while(0)

#define Gpio1pin_InitDirectionInput    (__v__.bOutput=0u)
#define Gpio1pin_InitDirectionOutput   (__v__.bOutput=1u)
#define Gpio1pin_InitPullup(v)         (__v__.bPullup=(v))
#define Gpio1pin_InitVal(v)            (__v__.bInitVal=(v))



#define Gpio1pin_Get(p)	         p##_GET
#define Gpio1pin_Put(p,v)        p##_PUT(v)

#define PINRELOC_SET_EPFR(epfr,pos,width,value)    \
          ((epfr) = (((epfr) & ~(((1u<<(width))-1u)<<(pos))) | \
          ((value) << (pos))))

/******************************************************************************/
/* Types                                                                      */
/******************************************************************************/

typedef struct stc_gpio1pin_init
{
    boolean_t bOutput;
    boolean_t bInitVal;
    boolean_t bPullup;
} stc_gpio1pin_init_t;


//@} // GpioGroup

#ifdef __cplusplus
}
#endif

#endif /* __GPIO_H__ */

/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/
