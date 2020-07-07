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
/** \file gpio_s6e1c3xc.h
 **
 ** Header file for S6E1C3XC GPIO functions, included in gpio.h
 **
 ** History:
 **   - 2015-12-04  2.0  NOSU	Clean ALL FM Series pin files
 **
 ** Timestamp:
 **   - 2015-12-16 18:30:19  Auto created by GpioHeaderGenerator Rev 1.0.0
 **
 ******************************************************************************/

#ifndef __GPIO_S6E1C3XC_H__
#define __GPIO_S6E1C3XC_H__

#include <stdint.h>

#define PINCONFIG_SET_REG(pinreg,pos,width,value)    \
          ((pinreg) = (((pinreg) & ~(((1u<<(width))-1u)<<(pos))) | \
          ((value) << (pos))))

/******************************************************************************
   GPIO
*******************************************************************************/

/*---- GPIO bit P01 ----*/
#define GPIO1PIN_P01_GET                ( bFM_GPIO_PDIR0_P1 )

#define GPIO1PIN_P01_PUT(v)             ( bFM_GPIO_PDOR0_P1=(v) )

#define GPIO1PIN_P01_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P01_INITIN(v) \
                                                           : GPIO1PIN_P01_INITOUT(v) )

#define GPIO1PIN_P01_INITIN(v)          do{ \
                                            bFM_GPIO_PCR0_P1=(v).bPullup; \
                                            bFM_GPIO_DDR0_P1=0u; \
                                            bFM_GPIO_PFR0_P1=0u; }while(0u)

#define GPIO1PIN_P01_INITOUT(v)         do{ \
                                            bFM_GPIO_PDOR0_P1=(v).bInitVal; \
                                            bFM_GPIO_DDR0_P1=1u; \
                                            bFM_GPIO_PFR0_P1=0u; }while(0u)

/*---- GPIO bit NP01 ----*/
#define GPIO1PIN_NP01_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR0_P1)) )

#define GPIO1PIN_NP01_PUT(v)            ( bFM_GPIO_PDOR0_P1=(uint32_t)(!(v)) )

#define GPIO1PIN_NP01_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP01_INITIN(v) \
                                                           : GPIO1PIN_NP01_INITOUT(v) )

#define GPIO1PIN_NP01_INITIN(v)         do{ \
                                            bFM_GPIO_PCR0_P1=(v).bPullup; \
                                            bFM_GPIO_DDR0_P1=0u; \
                                            bFM_GPIO_PFR0_P1=0u; }while(0u)

#define GPIO1PIN_NP01_INITOUT(v)        do{ \
                                            bFM_GPIO_PDOR0_P1=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR0_P1=1u; \
                                            bFM_GPIO_PFR0_P1=0u; }while(0u)

/*---- GPIO bit P03 ----*/
#define GPIO1PIN_P03_GET                ( bFM_GPIO_PDIR0_P3 )

#define GPIO1PIN_P03_PUT(v)             ( bFM_GPIO_PDOR0_P3=(v) )

#define GPIO1PIN_P03_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P03_INITIN(v) \
                                                           : GPIO1PIN_P03_INITOUT(v) )

#define GPIO1PIN_P03_INITIN(v)          do{ \
                                            bFM_GPIO_PCR0_P3=(v).bPullup; \
                                            bFM_GPIO_DDR0_P3=0u; \
                                            bFM_GPIO_PFR0_P3=0u; }while(0u)

#define GPIO1PIN_P03_INITOUT(v)         do{ \
                                            bFM_GPIO_PDOR0_P3=(v).bInitVal; \
                                            bFM_GPIO_DDR0_P3=1u; \
                                            bFM_GPIO_PFR0_P3=0u; }while(0u)

/*---- GPIO bit NP03 ----*/
#define GPIO1PIN_NP03_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR0_P3)) )

#define GPIO1PIN_NP03_PUT(v)            ( bFM_GPIO_PDOR0_P3=(uint32_t)(!(v)) )

#define GPIO1PIN_NP03_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP03_INITIN(v) \
                                                           : GPIO1PIN_NP03_INITOUT(v) )

#define GPIO1PIN_NP03_INITIN(v)         do{ \
                                            bFM_GPIO_PCR0_P3=(v).bPullup; \
                                            bFM_GPIO_DDR0_P3=0u; \
                                            bFM_GPIO_PFR0_P3=0u; }while(0u)

#define GPIO1PIN_NP03_INITOUT(v)        do{ \
                                            bFM_GPIO_PDOR0_P3=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR0_P3=1u; \
                                            bFM_GPIO_PFR0_P3=0u; }while(0u)

/*---- GPIO bit P05 ----*/
#define GPIO1PIN_P05_GET                ( bFM_GPIO_PDIR0_P5 )

#define GPIO1PIN_P05_PUT(v)             ( bFM_GPIO_PDOR0_P5=(v) )

#define GPIO1PIN_P05_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P05_INITIN(v) \
                                                           : GPIO1PIN_P05_INITOUT(v) )

#define GPIO1PIN_P05_INITIN(v)          do{ \
                                            bFM_GPIO_PCR0_P5=(v).bPullup; \
                                            bFM_GPIO_DDR0_P5=0u; \
                                            bFM_GPIO_PFR0_P5=0u; }while(0u)

#define GPIO1PIN_P05_INITOUT(v)         do{ \
                                            bFM_GPIO_PDOR0_P5=(v).bInitVal; \
                                            bFM_GPIO_DDR0_P5=1u; \
                                            bFM_GPIO_PFR0_P5=0u; }while(0u)

/*---- GPIO bit NP05 ----*/
#define GPIO1PIN_NP05_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR0_P5)) )

#define GPIO1PIN_NP05_PUT(v)            ( bFM_GPIO_PDOR0_P5=(uint32_t)(!(v)) )

#define GPIO1PIN_NP05_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP05_INITIN(v) \
                                                           : GPIO1PIN_NP05_INITOUT(v) )

#define GPIO1PIN_NP05_INITIN(v)         do{ \
                                            bFM_GPIO_PCR0_P5=(v).bPullup; \
                                            bFM_GPIO_DDR0_P5=0u; \
                                            bFM_GPIO_PFR0_P5=0u; }while(0u)

#define GPIO1PIN_NP05_INITOUT(v)        do{ \
                                            bFM_GPIO_PDOR0_P5=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR0_P5=1u; \
                                            bFM_GPIO_PFR0_P5=0u; }while(0u)

/*---- GPIO bit P0F ----*/
#define GPIO1PIN_P0F_GET                ( bFM_GPIO_PDIR0_PF )

#define GPIO1PIN_P0F_PUT(v)             ( bFM_GPIO_PDOR0_PF=(v) )

#define GPIO1PIN_P0F_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P0F_INITIN(v) \
                                                           : GPIO1PIN_P0F_INITOUT(v) )

#define GPIO1PIN_P0F_INITIN(v)          do{ \
                                            bFM_GPIO_PCR0_PF=(v).bPullup; \
                                            bFM_GPIO_DDR0_PF=0u; \
                                            bFM_GPIO_PFR0_PF=0u; }while(0u)

#define GPIO1PIN_P0F_INITOUT(v)         do{ \
                                            bFM_GPIO_PDOR0_PF=(v).bInitVal; \
                                            bFM_GPIO_DDR0_PF=1u; \
                                            bFM_GPIO_PFR0_PF=0u; }while(0u)

/*---- GPIO bit NP0F ----*/
#define GPIO1PIN_NP0F_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR0_PF)) )

#define GPIO1PIN_NP0F_PUT(v)            ( bFM_GPIO_PDOR0_PF=(uint32_t)(!(v)) )

#define GPIO1PIN_NP0F_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP0F_INITIN(v) \
                                                           : GPIO1PIN_NP0F_INITOUT(v) )

#define GPIO1PIN_NP0F_INITIN(v)         do{ \
                                            bFM_GPIO_PCR0_PF=(v).bPullup; \
                                            bFM_GPIO_DDR0_PF=0u; \
                                            bFM_GPIO_PFR0_PF=0u; }while(0u)

#define GPIO1PIN_NP0F_INITOUT(v)        do{ \
                                            bFM_GPIO_PDOR0_PF=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR0_PF=1u; \
                                            bFM_GPIO_PFR0_PF=0u; }while(0u)

/*---- GPIO bit P10 ----*/
#define GPIO1PIN_P10_GET                ( bFM_GPIO_PDIR1_P0 )

#define GPIO1PIN_P10_PUT(v)             ( bFM_GPIO_PDOR1_P0=(v) )

#define GPIO1PIN_P10_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P10_INITIN(v) \
                                                           : GPIO1PIN_P10_INITOUT(v) )

#define GPIO1PIN_P10_INITIN(v)          do{ \
                                            bFM_GPIO_ADE_AN00=0u; \
                                            bFM_GPIO_PCR1_P0=(v).bPullup; \
                                            bFM_GPIO_DDR1_P0=0u; \
                                            bFM_GPIO_PFR1_P0=0u; }while(0u)

#define GPIO1PIN_P10_INITOUT(v)         do{ \
                                            bFM_GPIO_ADE_AN00=0u; \
                                            bFM_GPIO_PDOR1_P0=(v).bInitVal; \
                                            bFM_GPIO_DDR1_P0=1u; \
                                            bFM_GPIO_PFR1_P0=0u; }while(0u)

/*---- GPIO bit NP10 ----*/
#define GPIO1PIN_NP10_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR1_P0)) )

#define GPIO1PIN_NP10_PUT(v)            ( bFM_GPIO_PDOR1_P0=(uint32_t)(!(v)) )

#define GPIO1PIN_NP10_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP10_INITIN(v) \
                                                           : GPIO1PIN_NP10_INITOUT(v) )

#define GPIO1PIN_NP10_INITIN(v)         do{ \
                                            bFM_GPIO_ADE_AN00=0u; \
                                            bFM_GPIO_PCR1_P0=(v).bPullup; \
                                            bFM_GPIO_DDR1_P0=0u; \
                                            bFM_GPIO_PFR1_P0=0u; }while(0u)

#define GPIO1PIN_NP10_INITOUT(v)        do{ \
                                            bFM_GPIO_ADE_AN00=0u; \
                                            bFM_GPIO_PDOR1_P0=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR1_P0=1u; \
                                            bFM_GPIO_PFR1_P0=0u; }while(0u)

/*---- GPIO bit P11 ----*/
#define GPIO1PIN_P11_GET                ( bFM_GPIO_PDIR1_P1 )

#define GPIO1PIN_P11_PUT(v)             ( bFM_GPIO_PDOR1_P1=(v) )

#define GPIO1PIN_P11_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P11_INITIN(v) \
                                                           : GPIO1PIN_P11_INITOUT(v) )

#define GPIO1PIN_P11_INITIN(v)          do{ \
                                            bFM_GPIO_ADE_AN01=0u; \
                                            bFM_GPIO_PCR1_P1=(v).bPullup; \
                                            bFM_GPIO_DDR1_P1=0u; \
                                            bFM_GPIO_PFR1_P1=0u; }while(0u)

#define GPIO1PIN_P11_INITOUT(v)         do{ \
                                            bFM_GPIO_ADE_AN01=0u; \
                                            bFM_GPIO_PDOR1_P1=(v).bInitVal; \
                                            bFM_GPIO_DDR1_P1=1u; \
                                            bFM_GPIO_PFR1_P1=0u; }while(0u)

/*---- GPIO bit NP11 ----*/
#define GPIO1PIN_NP11_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR1_P1)) )

#define GPIO1PIN_NP11_PUT(v)            ( bFM_GPIO_PDOR1_P1=(uint32_t)(!(v)) )

#define GPIO1PIN_NP11_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP11_INITIN(v) \
                                                           : GPIO1PIN_NP11_INITOUT(v) )

#define GPIO1PIN_NP11_INITIN(v)         do{ \
                                            bFM_GPIO_ADE_AN01=0u; \
                                            bFM_GPIO_PCR1_P1=(v).bPullup; \
                                            bFM_GPIO_DDR1_P1=0u; \
                                            bFM_GPIO_PFR1_P1=0u; }while(0u)

#define GPIO1PIN_NP11_INITOUT(v)        do{ \
                                            bFM_GPIO_ADE_AN01=0u; \
                                            bFM_GPIO_PDOR1_P1=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR1_P1=1u; \
                                            bFM_GPIO_PFR1_P1=0u; }while(0u)

/*---- GPIO bit P12 ----*/
#define GPIO1PIN_P12_GET                ( bFM_GPIO_PDIR1_P2 )

#define GPIO1PIN_P12_PUT(v)             ( bFM_GPIO_PDOR1_P2=(v) )

#define GPIO1PIN_P12_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P12_INITIN(v) \
                                                           : GPIO1PIN_P12_INITOUT(v) )

#define GPIO1PIN_P12_INITIN(v)          do{ \
                                            bFM_GPIO_ADE_AN02=0u; \
                                            bFM_GPIO_PCR1_P2=(v).bPullup; \
                                            bFM_GPIO_DDR1_P2=0u; \
                                            bFM_GPIO_PFR1_P2=0u; }while(0u)

#define GPIO1PIN_P12_INITOUT(v)         do{ \
                                            bFM_GPIO_ADE_AN02=0u; \
                                            bFM_GPIO_PDOR1_P2=(v).bInitVal; \
                                            bFM_GPIO_DDR1_P2=1u; \
                                            bFM_GPIO_PFR1_P2=0u; }while(0u)

/*---- GPIO bit NP12 ----*/
#define GPIO1PIN_NP12_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR1_P2)) )

#define GPIO1PIN_NP12_PUT(v)            ( bFM_GPIO_PDOR1_P2=(uint32_t)(!(v)) )

#define GPIO1PIN_NP12_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP12_INITIN(v) \
                                                           : GPIO1PIN_NP12_INITOUT(v) )

#define GPIO1PIN_NP12_INITIN(v)         do{ \
                                            bFM_GPIO_ADE_AN02=0u; \
                                            bFM_GPIO_PCR1_P2=(v).bPullup; \
                                            bFM_GPIO_DDR1_P2=0u; \
                                            bFM_GPIO_PFR1_P2=0u; }while(0u)

#define GPIO1PIN_NP12_INITOUT(v)        do{ \
                                            bFM_GPIO_ADE_AN02=0u; \
                                            bFM_GPIO_PDOR1_P2=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR1_P2=1u; \
                                            bFM_GPIO_PFR1_P2=0u; }while(0u)

/*---- GPIO bit P13 ----*/
#define GPIO1PIN_P13_GET                ( bFM_GPIO_PDIR1_P3 )

#define GPIO1PIN_P13_PUT(v)             ( bFM_GPIO_PDOR1_P3=(v) )

#define GPIO1PIN_P13_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P13_INITIN(v) \
                                                           : GPIO1PIN_P13_INITOUT(v) )

#define GPIO1PIN_P13_INITIN(v)          do{ \
                                            bFM_GPIO_ADE_AN03=0u; \
                                            bFM_GPIO_PCR1_P3=(v).bPullup; \
                                            bFM_GPIO_DDR1_P3=0u; \
                                            bFM_GPIO_PFR1_P3=0u; }while(0u)

#define GPIO1PIN_P13_INITOUT(v)         do{ \
                                            bFM_GPIO_ADE_AN03=0u; \
                                            bFM_GPIO_PDOR1_P3=(v).bInitVal; \
                                            bFM_GPIO_DDR1_P3=1u; \
                                            bFM_GPIO_PFR1_P3=0u; }while(0u)

/*---- GPIO bit NP13 ----*/
#define GPIO1PIN_NP13_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR1_P3)) )

#define GPIO1PIN_NP13_PUT(v)            ( bFM_GPIO_PDOR1_P3=(uint32_t)(!(v)) )

#define GPIO1PIN_NP13_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP13_INITIN(v) \
                                                           : GPIO1PIN_NP13_INITOUT(v) )

#define GPIO1PIN_NP13_INITIN(v)         do{ \
                                            bFM_GPIO_ADE_AN03=0u; \
                                            bFM_GPIO_PCR1_P3=(v).bPullup; \
                                            bFM_GPIO_DDR1_P3=0u; \
                                            bFM_GPIO_PFR1_P3=0u; }while(0u)

#define GPIO1PIN_NP13_INITOUT(v)        do{ \
                                            bFM_GPIO_ADE_AN03=0u; \
                                            bFM_GPIO_PDOR1_P3=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR1_P3=1u; \
                                            bFM_GPIO_PFR1_P3=0u; }while(0u)

/*---- GPIO bit P14 ----*/
#define GPIO1PIN_P14_GET                ( bFM_GPIO_PDIR1_P4 )

#define GPIO1PIN_P14_PUT(v)             ( bFM_GPIO_PDOR1_P4=(v) )

#define GPIO1PIN_P14_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P14_INITIN(v) \
                                                           : GPIO1PIN_P14_INITOUT(v) )

#define GPIO1PIN_P14_INITIN(v)          do{ \
                                            bFM_GPIO_ADE_AN04=0u; \
                                            bFM_GPIO_PCR1_P4=(v).bPullup; \
                                            bFM_GPIO_DDR1_P4=0u; \
                                            bFM_GPIO_PFR1_P4=0u; }while(0u)

#define GPIO1PIN_P14_INITOUT(v)         do{ \
                                            bFM_GPIO_ADE_AN04=0u; \
                                            bFM_GPIO_PDOR1_P4=(v).bInitVal; \
                                            bFM_GPIO_DDR1_P4=1u; \
                                            bFM_GPIO_PFR1_P4=0u; }while(0u)

/*---- GPIO bit NP14 ----*/
#define GPIO1PIN_NP14_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR1_P4)) )

#define GPIO1PIN_NP14_PUT(v)            ( bFM_GPIO_PDOR1_P4=(uint32_t)(!(v)) )

#define GPIO1PIN_NP14_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP14_INITIN(v) \
                                                           : GPIO1PIN_NP14_INITOUT(v) )

#define GPIO1PIN_NP14_INITIN(v)         do{ \
                                            bFM_GPIO_ADE_AN04=0u; \
                                            bFM_GPIO_PCR1_P4=(v).bPullup; \
                                            bFM_GPIO_DDR1_P4=0u; \
                                            bFM_GPIO_PFR1_P4=0u; }while(0u)

#define GPIO1PIN_NP14_INITOUT(v)        do{ \
                                            bFM_GPIO_ADE_AN04=0u; \
                                            bFM_GPIO_PDOR1_P4=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR1_P4=1u; \
                                            bFM_GPIO_PFR1_P4=0u; }while(0u)

/*---- GPIO bit P15 ----*/
#define GPIO1PIN_P15_GET                ( bFM_GPIO_PDIR1_P5 )

#define GPIO1PIN_P15_PUT(v)             ( bFM_GPIO_PDOR1_P5=(v) )

#define GPIO1PIN_P15_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P15_INITIN(v) \
                                                           : GPIO1PIN_P15_INITOUT(v) )

#define GPIO1PIN_P15_INITIN(v)          do{ \
                                            bFM_GPIO_ADE_AN05=0u; \
                                            bFM_GPIO_PCR1_P5=(v).bPullup; \
                                            bFM_GPIO_DDR1_P5=0u; \
                                            bFM_GPIO_PFR1_P5=0u; }while(0u)

#define GPIO1PIN_P15_INITOUT(v)         do{ \
                                            bFM_GPIO_ADE_AN05=0u; \
                                            bFM_GPIO_PDOR1_P5=(v).bInitVal; \
                                            bFM_GPIO_DDR1_P5=1u; \
                                            bFM_GPIO_PFR1_P5=0u; }while(0u)

/*---- GPIO bit NP15 ----*/
#define GPIO1PIN_NP15_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR1_P5)) )

#define GPIO1PIN_NP15_PUT(v)            ( bFM_GPIO_PDOR1_P5=(uint32_t)(!(v)) )

#define GPIO1PIN_NP15_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP15_INITIN(v) \
                                                           : GPIO1PIN_NP15_INITOUT(v) )

#define GPIO1PIN_NP15_INITIN(v)         do{ \
                                            bFM_GPIO_ADE_AN05=0u; \
                                            bFM_GPIO_PCR1_P5=(v).bPullup; \
                                            bFM_GPIO_DDR1_P5=0u; \
                                            bFM_GPIO_PFR1_P5=0u; }while(0u)

#define GPIO1PIN_NP15_INITOUT(v)        do{ \
                                            bFM_GPIO_ADE_AN05=0u; \
                                            bFM_GPIO_PDOR1_P5=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR1_P5=1u; \
                                            bFM_GPIO_PFR1_P5=0u; }while(0u)

/*---- GPIO bit P1A ----*/
#define GPIO1PIN_P1A_GET                ( bFM_GPIO_PDIR1_PA )

#define GPIO1PIN_P1A_PUT(v)             ( bFM_GPIO_PDOR1_PA=(v) )

#define GPIO1PIN_P1A_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P1A_INITIN(v) \
                                                           : GPIO1PIN_P1A_INITOUT(v) )

#define GPIO1PIN_P1A_INITIN(v)          do{ \
                                            PINCONFIG_SET_REG(FM_DS->CEC_CTL, 0u, 2u, 0u); \
                                            bFM_GPIO_PCR1_PA=(v).bPullup; \
                                            bFM_GPIO_DDR1_PA=0u; \
                                            bFM_GPIO_PFR1_PA=0u; }while(0u)

#define GPIO1PIN_P1A_INITOUT(v)         do{ \
                                            PINCONFIG_SET_REG(FM_DS->CEC_CTL, 0u, 2u, 0u); \
                                            bFM_GPIO_PDOR1_PA=(v).bInitVal; \
                                            bFM_GPIO_DDR1_PA=1u; \
                                            bFM_GPIO_PFR1_PA=0u; }while(0u)

/*---- GPIO bit NP1A ----*/
#define GPIO1PIN_NP1A_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR1_PA)) )

#define GPIO1PIN_NP1A_PUT(v)            ( bFM_GPIO_PDOR1_PA=(uint32_t)(!(v)) )

#define GPIO1PIN_NP1A_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP1A_INITIN(v) \
                                                           : GPIO1PIN_NP1A_INITOUT(v) )

#define GPIO1PIN_NP1A_INITIN(v)         do{ \
                                            PINCONFIG_SET_REG(FM_DS->CEC_CTL, 0u, 2u, 0u); \
                                            bFM_GPIO_PCR1_PA=(v).bPullup; \
                                            bFM_GPIO_DDR1_PA=0u; \
                                            bFM_GPIO_PFR1_PA=0u; }while(0u)

#define GPIO1PIN_NP1A_INITOUT(v)        do{ \
                                            PINCONFIG_SET_REG(FM_DS->CEC_CTL, 0u, 2u, 0u); \
                                            bFM_GPIO_PDOR1_PA=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR1_PA=1u; \
                                            bFM_GPIO_PFR1_PA=0u; }while(0u)

/*---- GPIO bit P1B ----*/
#define GPIO1PIN_P1B_GET                ( bFM_GPIO_PDIR1_PB )

#define GPIO1PIN_P1B_PUT(v)             ( bFM_GPIO_PDOR1_PB=(v) )

#define GPIO1PIN_P1B_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P1B_INITIN(v) \
                                                           : GPIO1PIN_P1B_INITOUT(v) )

#define GPIO1PIN_P1B_INITIN(v)          do{ \
                                            bFM_GPIO_PCR1_PB=(v).bPullup; \
                                            bFM_GPIO_DDR1_PB=0u; \
                                            bFM_GPIO_PFR1_PB=0u; }while(0u)

#define GPIO1PIN_P1B_INITOUT(v)         do{ \
                                            bFM_GPIO_PDOR1_PB=(v).bInitVal; \
                                            bFM_GPIO_DDR1_PB=1u; \
                                            bFM_GPIO_PFR1_PB=0u; }while(0u)

/*---- GPIO bit NP1B ----*/
#define GPIO1PIN_NP1B_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR1_PB)) )

#define GPIO1PIN_NP1B_PUT(v)            ( bFM_GPIO_PDOR1_PB=(uint32_t)(!(v)) )

#define GPIO1PIN_NP1B_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP1B_INITIN(v) \
                                                           : GPIO1PIN_NP1B_INITOUT(v) )

#define GPIO1PIN_NP1B_INITIN(v)         do{ \
                                            bFM_GPIO_PCR1_PB=(v).bPullup; \
                                            bFM_GPIO_DDR1_PB=0u; \
                                            bFM_GPIO_PFR1_PB=0u; }while(0u)

#define GPIO1PIN_NP1B_INITOUT(v)        do{ \
                                            bFM_GPIO_PDOR1_PB=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR1_PB=1u; \
                                            bFM_GPIO_PFR1_PB=0u; }while(0u)

/*---- GPIO bit P21 ----*/
#define GPIO1PIN_P21_GET                ( bFM_GPIO_PDIR2_P1 )

#define GPIO1PIN_P21_PUT(v)             ( bFM_GPIO_PDOR2_P1=(v) )

#define GPIO1PIN_P21_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P21_INITIN(v) \
                                                           : GPIO1PIN_P21_INITOUT(v) )

#define GPIO1PIN_P21_INITIN(v)          do{ \
                                            bFM_GPIO_PCR2_P1=(v).bPullup; \
                                            bFM_GPIO_DDR2_P1=0u; \
                                            bFM_GPIO_PFR2_P1=0u; }while(0u)

#define GPIO1PIN_P21_INITOUT(v)         do{ \
                                            bFM_GPIO_PDOR2_P1=(v).bInitVal; \
                                            bFM_GPIO_DDR2_P1=1u; \
                                            bFM_GPIO_PFR2_P1=0u; }while(0u)

/*---- GPIO bit NP21 ----*/
#define GPIO1PIN_NP21_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR2_P1)) )

#define GPIO1PIN_NP21_PUT(v)            ( bFM_GPIO_PDOR2_P1=(uint32_t)(!(v)) )

#define GPIO1PIN_NP21_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP21_INITIN(v) \
                                                           : GPIO1PIN_NP21_INITOUT(v) )

#define GPIO1PIN_NP21_INITIN(v)         do{ \
                                            bFM_GPIO_PCR2_P1=(v).bPullup; \
                                            bFM_GPIO_DDR2_P1=0u; \
                                            bFM_GPIO_PFR2_P1=0u; }while(0u)

#define GPIO1PIN_NP21_INITOUT(v)        do{ \
                                            bFM_GPIO_PDOR2_P1=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR2_P1=1u; \
                                            bFM_GPIO_PFR2_P1=0u; }while(0u)

/*---- GPIO bit P22 ----*/
#define GPIO1PIN_P22_GET                ( bFM_GPIO_PDIR2_P2 )

#define GPIO1PIN_P22_PUT(v)             ( bFM_GPIO_PDOR2_P2=(v) )

#define GPIO1PIN_P22_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P22_INITIN(v) \
                                                           : GPIO1PIN_P22_INITOUT(v) )

#define GPIO1PIN_P22_INITIN(v)          do{ \
                                            bFM_GPIO_ADE_AN07=0u; \
                                            bFM_GPIO_PCR2_P2=(v).bPullup; \
                                            bFM_GPIO_DDR2_P2=0u; \
                                            bFM_GPIO_PFR2_P2=0u; }while(0u)

#define GPIO1PIN_P22_INITOUT(v)         do{ \
                                            bFM_GPIO_ADE_AN07=0u; \
                                            bFM_GPIO_PDOR2_P2=(v).bInitVal; \
                                            bFM_GPIO_DDR2_P2=1u; \
                                            bFM_GPIO_PFR2_P2=0u; }while(0u)

/*---- GPIO bit NP22 ----*/
#define GPIO1PIN_NP22_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR2_P2)) )

#define GPIO1PIN_NP22_PUT(v)            ( bFM_GPIO_PDOR2_P2=(uint32_t)(!(v)) )

#define GPIO1PIN_NP22_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP22_INITIN(v) \
                                                           : GPIO1PIN_NP22_INITOUT(v) )

#define GPIO1PIN_NP22_INITIN(v)         do{ \
                                            bFM_GPIO_ADE_AN07=0u; \
                                            bFM_GPIO_PCR2_P2=(v).bPullup; \
                                            bFM_GPIO_DDR2_P2=0u; \
                                            bFM_GPIO_PFR2_P2=0u; }while(0u)

#define GPIO1PIN_NP22_INITOUT(v)        do{ \
                                            bFM_GPIO_ADE_AN07=0u; \
                                            bFM_GPIO_PDOR2_P2=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR2_P2=1u; \
                                            bFM_GPIO_PFR2_P2=0u; }while(0u)

/*---- GPIO bit P23 ----*/
#define GPIO1PIN_P23_GET                ( bFM_GPIO_PDIR2_P3 )

#define GPIO1PIN_P23_PUT(v)             ( bFM_GPIO_PDOR2_P3=(v) )

#define GPIO1PIN_P23_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P23_INITIN(v) \
                                                           : GPIO1PIN_P23_INITOUT(v) )

#define GPIO1PIN_P23_INITIN(v)          do{ \
                                            bFM_GPIO_ADE_AN06=0u; \
                                            bFM_GPIO_PCR2_P3=(v).bPullup; \
                                            bFM_GPIO_DDR2_P3=0u; \
                                            bFM_GPIO_PFR2_P3=0u; }while(0u)

#define GPIO1PIN_P23_INITOUT(v)         do{ \
                                            bFM_GPIO_ADE_AN06=0u; \
                                            bFM_GPIO_PDOR2_P3=(v).bInitVal; \
                                            bFM_GPIO_DDR2_P3=1u; \
                                            bFM_GPIO_PFR2_P3=0u; }while(0u)

/*---- GPIO bit NP23 ----*/
#define GPIO1PIN_NP23_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR2_P3)) )

#define GPIO1PIN_NP23_PUT(v)            ( bFM_GPIO_PDOR2_P3=(uint32_t)(!(v)) )

#define GPIO1PIN_NP23_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP23_INITIN(v) \
                                                           : GPIO1PIN_NP23_INITOUT(v) )

#define GPIO1PIN_NP23_INITIN(v)         do{ \
                                            bFM_GPIO_ADE_AN06=0u; \
                                            bFM_GPIO_PCR2_P3=(v).bPullup; \
                                            bFM_GPIO_DDR2_P3=0u; \
                                            bFM_GPIO_PFR2_P3=0u; }while(0u)

#define GPIO1PIN_NP23_INITOUT(v)        do{ \
                                            bFM_GPIO_ADE_AN06=0u; \
                                            bFM_GPIO_PDOR2_P3=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR2_P3=1u; \
                                            bFM_GPIO_PFR2_P3=0u; }while(0u)

/*---- GPIO bit P30 ----*/
#define GPIO1PIN_P30_GET                ( bFM_GPIO_PDIR3_P0 )

#define GPIO1PIN_P30_PUT(v)             ( bFM_GPIO_PDOR3_P0=(v) )

#define GPIO1PIN_P30_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P30_INITIN(v) \
                                                           : GPIO1PIN_P30_INITOUT(v) )

#define GPIO1PIN_P30_INITIN(v)          do{ \
                                            bFM_GPIO_PCR3_P0=(v).bPullup; \
                                            bFM_GPIO_DDR3_P0=0u; \
                                            bFM_GPIO_PFR3_P0=0u; }while(0u)

#define GPIO1PIN_P30_INITOUT(v)         do{ \
                                            bFM_GPIO_PDOR3_P0=(v).bInitVal; \
                                            bFM_GPIO_DDR3_P0=1u; \
                                            bFM_GPIO_PFR3_P0=0u; }while(0u)

/*---- GPIO bit NP30 ----*/
#define GPIO1PIN_NP30_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR3_P0)) )

#define GPIO1PIN_NP30_PUT(v)            ( bFM_GPIO_PDOR3_P0=(uint32_t)(!(v)) )

#define GPIO1PIN_NP30_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP30_INITIN(v) \
                                                           : GPIO1PIN_NP30_INITOUT(v) )

#define GPIO1PIN_NP30_INITIN(v)         do{ \
                                            bFM_GPIO_PCR3_P0=(v).bPullup; \
                                            bFM_GPIO_DDR3_P0=0u; \
                                            bFM_GPIO_PFR3_P0=0u; }while(0u)

#define GPIO1PIN_NP30_INITOUT(v)        do{ \
                                            bFM_GPIO_PDOR3_P0=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR3_P0=1u; \
                                            bFM_GPIO_PFR3_P0=0u; }while(0u)

/*---- GPIO bit P31 ----*/
#define GPIO1PIN_P31_GET                ( bFM_GPIO_PDIR3_P1 )

#define GPIO1PIN_P31_PUT(v)             ( bFM_GPIO_PDOR3_P1=(v) )

#define GPIO1PIN_P31_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P31_INITIN(v) \
                                                           : GPIO1PIN_P31_INITOUT(v) )

#define GPIO1PIN_P31_INITIN(v)          do{ \
                                            bFM_GPIO_PCR3_P1=(v).bPullup; \
                                            bFM_GPIO_DDR3_P1=0u; \
                                            bFM_GPIO_PFR3_P1=0u; }while(0u)

#define GPIO1PIN_P31_INITOUT(v)         do{ \
                                            bFM_GPIO_PDOR3_P1=(v).bInitVal; \
                                            bFM_GPIO_DDR3_P1=1u; \
                                            bFM_GPIO_PFR3_P1=0u; }while(0u)

/*---- GPIO bit NP31 ----*/
#define GPIO1PIN_NP31_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR3_P1)) )

#define GPIO1PIN_NP31_PUT(v)            ( bFM_GPIO_PDOR3_P1=(uint32_t)(!(v)) )

#define GPIO1PIN_NP31_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP31_INITIN(v) \
                                                           : GPIO1PIN_NP31_INITOUT(v) )

#define GPIO1PIN_NP31_INITIN(v)         do{ \
                                            bFM_GPIO_PCR3_P1=(v).bPullup; \
                                            bFM_GPIO_DDR3_P1=0u; \
                                            bFM_GPIO_PFR3_P1=0u; }while(0u)

#define GPIO1PIN_NP31_INITOUT(v)        do{ \
                                            bFM_GPIO_PDOR3_P1=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR3_P1=1u; \
                                            bFM_GPIO_PFR3_P1=0u; }while(0u)

/*---- GPIO bit P32 ----*/
#define GPIO1PIN_P32_GET                ( bFM_GPIO_PDIR3_P2 )

#define GPIO1PIN_P32_PUT(v)             ( bFM_GPIO_PDOR3_P2=(v) )

#define GPIO1PIN_P32_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P32_INITIN(v) \
                                                           : GPIO1PIN_P32_INITOUT(v) )

#define GPIO1PIN_P32_INITIN(v)          do{ \
                                            bFM_GPIO_PCR3_P2=(v).bPullup; \
                                            bFM_GPIO_DDR3_P2=0u; \
                                            bFM_GPIO_PFR3_P2=0u; }while(0u)

#define GPIO1PIN_P32_INITOUT(v)         do{ \
                                            bFM_GPIO_PDOR3_P2=(v).bInitVal; \
                                            bFM_GPIO_DDR3_P2=1u; \
                                            bFM_GPIO_PFR3_P2=0u; }while(0u)

/*---- GPIO bit NP32 ----*/
#define GPIO1PIN_NP32_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR3_P2)) )

#define GPIO1PIN_NP32_PUT(v)            ( bFM_GPIO_PDOR3_P2=(uint32_t)(!(v)) )

#define GPIO1PIN_NP32_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP32_INITIN(v) \
                                                           : GPIO1PIN_NP32_INITOUT(v) )

#define GPIO1PIN_NP32_INITIN(v)         do{ \
                                            bFM_GPIO_PCR3_P2=(v).bPullup; \
                                            bFM_GPIO_DDR3_P2=0u; \
                                            bFM_GPIO_PFR3_P2=0u; }while(0u)

#define GPIO1PIN_NP32_INITOUT(v)        do{ \
                                            bFM_GPIO_PDOR3_P2=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR3_P2=1u; \
                                            bFM_GPIO_PFR3_P2=0u; }while(0u)

/*---- GPIO bit P33 ----*/
#define GPIO1PIN_P33_GET                ( bFM_GPIO_PDIR3_P3 )

#define GPIO1PIN_P33_PUT(v)             ( bFM_GPIO_PDOR3_P3=(v) )

#define GPIO1PIN_P33_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P33_INITIN(v) \
                                                           : GPIO1PIN_P33_INITOUT(v) )

#define GPIO1PIN_P33_INITIN(v)          do{ \
                                            bFM_GPIO_PCR3_P3=(v).bPullup; \
                                            bFM_GPIO_DDR3_P3=0u; \
                                            bFM_GPIO_PFR3_P3=0u; }while(0u)

#define GPIO1PIN_P33_INITOUT(v)         do{ \
                                            bFM_GPIO_PDOR3_P3=(v).bInitVal; \
                                            bFM_GPIO_DDR3_P3=1u; \
                                            bFM_GPIO_PFR3_P3=0u; }while(0u)

/*---- GPIO bit NP33 ----*/
#define GPIO1PIN_NP33_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR3_P3)) )

#define GPIO1PIN_NP33_PUT(v)            ( bFM_GPIO_PDOR3_P3=(uint32_t)(!(v)) )

#define GPIO1PIN_NP33_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP33_INITIN(v) \
                                                           : GPIO1PIN_NP33_INITOUT(v) )

#define GPIO1PIN_NP33_INITIN(v)         do{ \
                                            bFM_GPIO_PCR3_P3=(v).bPullup; \
                                            bFM_GPIO_DDR3_P3=0u; \
                                            bFM_GPIO_PFR3_P3=0u; }while(0u)

#define GPIO1PIN_NP33_INITOUT(v)        do{ \
                                            bFM_GPIO_PDOR3_P3=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR3_P3=1u; \
                                            bFM_GPIO_PFR3_P3=0u; }while(0u)

/*---- GPIO bit P34 ----*/
#define GPIO1PIN_P34_GET                ( bFM_GPIO_PDIR3_P4 )

#define GPIO1PIN_P34_PUT(v)             ( bFM_GPIO_PDOR3_P4=(v) )

#define GPIO1PIN_P34_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P34_INITIN(v) \
                                                           : GPIO1PIN_P34_INITOUT(v) )

#define GPIO1PIN_P34_INITIN(v)          do{ \
                                            bFM_GPIO_PCR3_P4=(v).bPullup; \
                                            bFM_GPIO_DDR3_P4=0u; \
                                            bFM_GPIO_PFR3_P4=0u; }while(0u)

#define GPIO1PIN_P34_INITOUT(v)         do{ \
                                            bFM_GPIO_PDOR3_P4=(v).bInitVal; \
                                            bFM_GPIO_DDR3_P4=1u; \
                                            bFM_GPIO_PFR3_P4=0u; }while(0u)

/*---- GPIO bit NP34 ----*/
#define GPIO1PIN_NP34_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR3_P4)) )

#define GPIO1PIN_NP34_PUT(v)            ( bFM_GPIO_PDOR3_P4=(uint32_t)(!(v)) )

#define GPIO1PIN_NP34_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP34_INITIN(v) \
                                                           : GPIO1PIN_NP34_INITOUT(v) )

#define GPIO1PIN_NP34_INITIN(v)         do{ \
                                            bFM_GPIO_PCR3_P4=(v).bPullup; \
                                            bFM_GPIO_DDR3_P4=0u; \
                                            bFM_GPIO_PFR3_P4=0u; }while(0u)

#define GPIO1PIN_NP34_INITOUT(v)        do{ \
                                            bFM_GPIO_PDOR3_P4=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR3_P4=1u; \
                                            bFM_GPIO_PFR3_P4=0u; }while(0u)

/*---- GPIO bit P3A ----*/
#define GPIO1PIN_P3A_GET                ( bFM_GPIO_PDIR3_PA )

#define GPIO1PIN_P3A_PUT(v)             ( bFM_GPIO_PDOR3_PA=(v) )

#define GPIO1PIN_P3A_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P3A_INITIN(v) \
                                                           : GPIO1PIN_P3A_INITOUT(v) )

#define GPIO1PIN_P3A_INITIN(v)          do{ \
                                            bFM_GPIO_PCR3_PA=(v).bPullup; \
                                            bFM_GPIO_DDR3_PA=0u; \
                                            bFM_GPIO_PFR3_PA=0u; }while(0u)

#define GPIO1PIN_P3A_INITOUT(v)         do{ \
                                            bFM_GPIO_PDOR3_PA=(v).bInitVal; \
                                            bFM_GPIO_DDR3_PA=1u; \
                                            bFM_GPIO_PFR3_PA=0u; }while(0u)

/*---- GPIO bit NP3A ----*/
#define GPIO1PIN_NP3A_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR3_PA)) )

#define GPIO1PIN_NP3A_PUT(v)            ( bFM_GPIO_PDOR3_PA=(uint32_t)(!(v)) )

#define GPIO1PIN_NP3A_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP3A_INITIN(v) \
                                                           : GPIO1PIN_NP3A_INITOUT(v) )

#define GPIO1PIN_NP3A_INITIN(v)         do{ \
                                            bFM_GPIO_PCR3_PA=(v).bPullup; \
                                            bFM_GPIO_DDR3_PA=0u; \
                                            bFM_GPIO_PFR3_PA=0u; }while(0u)

#define GPIO1PIN_NP3A_INITOUT(v)        do{ \
                                            bFM_GPIO_PDOR3_PA=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR3_PA=1u; \
                                            bFM_GPIO_PFR3_PA=0u; }while(0u)

/*---- GPIO bit P3B ----*/
#define GPIO1PIN_P3B_GET                ( bFM_GPIO_PDIR3_PB )

#define GPIO1PIN_P3B_PUT(v)             ( bFM_GPIO_PDOR3_PB=(v) )

#define GPIO1PIN_P3B_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P3B_INITIN(v) \
                                                           : GPIO1PIN_P3B_INITOUT(v) )

#define GPIO1PIN_P3B_INITIN(v)          do{ \
                                            bFM_GPIO_PCR3_PB=(v).bPullup; \
                                            bFM_GPIO_DDR3_PB=0u; \
                                            bFM_GPIO_PFR3_PB=0u; }while(0u)

#define GPIO1PIN_P3B_INITOUT(v)         do{ \
                                            bFM_GPIO_PDOR3_PB=(v).bInitVal; \
                                            bFM_GPIO_DDR3_PB=1u; \
                                            bFM_GPIO_PFR3_PB=0u; }while(0u)

/*---- GPIO bit NP3B ----*/
#define GPIO1PIN_NP3B_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR3_PB)) )

#define GPIO1PIN_NP3B_PUT(v)            ( bFM_GPIO_PDOR3_PB=(uint32_t)(!(v)) )

#define GPIO1PIN_NP3B_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP3B_INITIN(v) \
                                                           : GPIO1PIN_NP3B_INITOUT(v) )

#define GPIO1PIN_NP3B_INITIN(v)         do{ \
                                            bFM_GPIO_PCR3_PB=(v).bPullup; \
                                            bFM_GPIO_DDR3_PB=0u; \
                                            bFM_GPIO_PFR3_PB=0u; }while(0u)

#define GPIO1PIN_NP3B_INITOUT(v)        do{ \
                                            bFM_GPIO_PDOR3_PB=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR3_PB=1u; \
                                            bFM_GPIO_PFR3_PB=0u; }while(0u)

/*---- GPIO bit P3C ----*/
#define GPIO1PIN_P3C_GET                ( bFM_GPIO_PDIR3_PC )

#define GPIO1PIN_P3C_PUT(v)             ( bFM_GPIO_PDOR3_PC=(v) )

#define GPIO1PIN_P3C_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P3C_INITIN(v) \
                                                           : GPIO1PIN_P3C_INITOUT(v) )

#define GPIO1PIN_P3C_INITIN(v)          do{ \
                                            bFM_GPIO_PCR3_PC=(v).bPullup; \
                                            bFM_GPIO_DDR3_PC=0u; \
                                            bFM_GPIO_PFR3_PC=0u; }while(0u)

#define GPIO1PIN_P3C_INITOUT(v)         do{ \
                                            bFM_GPIO_PDOR3_PC=(v).bInitVal; \
                                            bFM_GPIO_DDR3_PC=1u; \
                                            bFM_GPIO_PFR3_PC=0u; }while(0u)

/*---- GPIO bit NP3C ----*/
#define GPIO1PIN_NP3C_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR3_PC)) )

#define GPIO1PIN_NP3C_PUT(v)            ( bFM_GPIO_PDOR3_PC=(uint32_t)(!(v)) )

#define GPIO1PIN_NP3C_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP3C_INITIN(v) \
                                                           : GPIO1PIN_NP3C_INITOUT(v) )

#define GPIO1PIN_NP3C_INITIN(v)         do{ \
                                            bFM_GPIO_PCR3_PC=(v).bPullup; \
                                            bFM_GPIO_DDR3_PC=0u; \
                                            bFM_GPIO_PFR3_PC=0u; }while(0u)

#define GPIO1PIN_NP3C_INITOUT(v)        do{ \
                                            bFM_GPIO_PDOR3_PC=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR3_PC=1u; \
                                            bFM_GPIO_PFR3_PC=0u; }while(0u)

/*---- GPIO bit P46 ----*/
#define GPIO1PIN_P46_GET                ( bFM_GPIO_PDIR4_P6 )

#define GPIO1PIN_P46_PUT(v)             ( bFM_GPIO_PDOR4_P6=(v) )

#define GPIO1PIN_P46_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P46_INITIN(v) \
                                                           : GPIO1PIN_P46_INITOUT(v) )

#define GPIO1PIN_P46_INITIN(v)          do{ \
                                            PINCONFIG_SET_REG(FM_DS->SUBOSC_CTL, 0u, 2u, 0u); \
                                            bFM_GPIO_PCR4_P6=(v).bPullup; \
                                            bFM_GPIO_DDR4_P6=0u; \
                                            bFM_GPIO_PFR4_P6=0u; }while(0u)

#define GPIO1PIN_P46_INITOUT(v)         do{ \
                                            PINCONFIG_SET_REG(FM_DS->SUBOSC_CTL, 0u, 2u, 0u); \
                                            bFM_GPIO_PDOR4_P6=(v).bInitVal; \
                                            bFM_GPIO_DDR4_P6=1u; \
                                            bFM_GPIO_PFR4_P6=0u; }while(0u)

/*---- GPIO bit NP46 ----*/
#define GPIO1PIN_NP46_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR4_P6)) )

#define GPIO1PIN_NP46_PUT(v)            ( bFM_GPIO_PDOR4_P6=(uint32_t)(!(v)) )

#define GPIO1PIN_NP46_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP46_INITIN(v) \
                                                           : GPIO1PIN_NP46_INITOUT(v) )

#define GPIO1PIN_NP46_INITIN(v)         do{ \
                                            PINCONFIG_SET_REG(FM_DS->SUBOSC_CTL, 0u, 2u, 0u); \
                                            bFM_GPIO_PCR4_P6=(v).bPullup; \
                                            bFM_GPIO_DDR4_P6=0u; \
                                            bFM_GPIO_PFR4_P6=0u; }while(0u)

#define GPIO1PIN_NP46_INITOUT(v)        do{ \
                                            PINCONFIG_SET_REG(FM_DS->SUBOSC_CTL, 0u, 2u, 0u); \
                                            bFM_GPIO_PDOR4_P6=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR4_P6=1u; \
                                            bFM_GPIO_PFR4_P6=0u; }while(0u)

/*---- GPIO bit P47 ----*/
#define GPIO1PIN_P47_GET                ( bFM_GPIO_PDIR4_P7 )

#define GPIO1PIN_P47_PUT(v)             ( bFM_GPIO_PDOR4_P7=(v) )

#define GPIO1PIN_P47_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P47_INITIN(v) \
                                                           : GPIO1PIN_P47_INITOUT(v) )

#define GPIO1PIN_P47_INITIN(v)          do{ \
                                            PINCONFIG_SET_REG(FM_DS->SUBOSC_CTL, 0u, 2u, 0u); \
                                            bFM_GPIO_PCR4_P7=(v).bPullup; \
                                            bFM_GPIO_DDR4_P7=0u; \
                                            bFM_GPIO_PFR4_P7=0u; }while(0u)

#define GPIO1PIN_P47_INITOUT(v)         do{ \
                                            PINCONFIG_SET_REG(FM_DS->SUBOSC_CTL, 0u, 2u, 0u); \
                                            bFM_GPIO_PDOR4_P7=(v).bInitVal; \
                                            bFM_GPIO_DDR4_P7=1u; \
                                            bFM_GPIO_PFR4_P7=0u; }while(0u)

/*---- GPIO bit NP47 ----*/
#define GPIO1PIN_NP47_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR4_P7)) )

#define GPIO1PIN_NP47_PUT(v)            ( bFM_GPIO_PDOR4_P7=(uint32_t)(!(v)) )

#define GPIO1PIN_NP47_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP47_INITIN(v) \
                                                           : GPIO1PIN_NP47_INITOUT(v) )

#define GPIO1PIN_NP47_INITIN(v)         do{ \
                                            PINCONFIG_SET_REG(FM_DS->SUBOSC_CTL, 0u, 2u, 0u); \
                                            bFM_GPIO_PCR4_P7=(v).bPullup; \
                                            bFM_GPIO_DDR4_P7=0u; \
                                            bFM_GPIO_PFR4_P7=0u; }while(0u)

#define GPIO1PIN_NP47_INITOUT(v)        do{ \
                                            PINCONFIG_SET_REG(FM_DS->SUBOSC_CTL, 0u, 2u, 0u); \
                                            bFM_GPIO_PDOR4_P7=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR4_P7=1u; \
                                            bFM_GPIO_PFR4_P7=0u; }while(0u)

/*---- GPIO bit P4C ----*/
#define GPIO1PIN_P4C_GET                ( bFM_GPIO_PDIR4_PC )

#define GPIO1PIN_P4C_PUT(v)             ( bFM_GPIO_PDOR4_PC=(v) )

#define GPIO1PIN_P4C_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P4C_INITIN(v) \
                                                           : GPIO1PIN_P4C_INITOUT(v) )

#define GPIO1PIN_P4C_INITIN(v)          do{ \
                                            bFM_GPIO_PCR4_PC=(v).bPullup; \
                                            bFM_GPIO_DDR4_PC=0u; \
                                            bFM_GPIO_PFR4_PC=0u; }while(0u)

#define GPIO1PIN_P4C_INITOUT(v)         do{ \
                                            bFM_GPIO_PDOR4_PC=(v).bInitVal; \
                                            bFM_GPIO_DDR4_PC=1u; \
                                            bFM_GPIO_PFR4_PC=0u; }while(0u)

/*---- GPIO bit NP4C ----*/
#define GPIO1PIN_NP4C_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR4_PC)) )

#define GPIO1PIN_NP4C_PUT(v)            ( bFM_GPIO_PDOR4_PC=(uint32_t)(!(v)) )

#define GPIO1PIN_NP4C_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP4C_INITIN(v) \
                                                           : GPIO1PIN_NP4C_INITOUT(v) )

#define GPIO1PIN_NP4C_INITIN(v)         do{ \
                                            bFM_GPIO_PCR4_PC=(v).bPullup; \
                                            bFM_GPIO_DDR4_PC=0u; \
                                            bFM_GPIO_PFR4_PC=0u; }while(0u)

#define GPIO1PIN_NP4C_INITOUT(v)        do{ \
                                            bFM_GPIO_PDOR4_PC=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR4_PC=1u; \
                                            bFM_GPIO_PFR4_PC=0u; }while(0u)

/*---- GPIO bit P4D ----*/
#define GPIO1PIN_P4D_GET                ( bFM_GPIO_PDIR4_PD )

#define GPIO1PIN_P4D_PUT(v)             ( bFM_GPIO_PDOR4_PD=(v) )

#define GPIO1PIN_P4D_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P4D_INITIN(v) \
                                                           : GPIO1PIN_P4D_INITOUT(v) )

#define GPIO1PIN_P4D_INITIN(v)          do{ \
                                            bFM_GPIO_PCR4_PD=(v).bPullup; \
                                            bFM_GPIO_DDR4_PD=0u; \
                                            bFM_GPIO_PFR4_PD=0u; }while(0u)

#define GPIO1PIN_P4D_INITOUT(v)         do{ \
                                            bFM_GPIO_PDOR4_PD=(v).bInitVal; \
                                            bFM_GPIO_DDR4_PD=1u; \
                                            bFM_GPIO_PFR4_PD=0u; }while(0u)

/*---- GPIO bit NP4D ----*/
#define GPIO1PIN_NP4D_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR4_PD)) )

#define GPIO1PIN_NP4D_PUT(v)            ( bFM_GPIO_PDOR4_PD=(uint32_t)(!(v)) )

#define GPIO1PIN_NP4D_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP4D_INITIN(v) \
                                                           : GPIO1PIN_NP4D_INITOUT(v) )

#define GPIO1PIN_NP4D_INITIN(v)         do{ \
                                            bFM_GPIO_PCR4_PD=(v).bPullup; \
                                            bFM_GPIO_DDR4_PD=0u; \
                                            bFM_GPIO_PFR4_PD=0u; }while(0u)

#define GPIO1PIN_NP4D_INITOUT(v)        do{ \
                                            bFM_GPIO_PDOR4_PD=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR4_PD=1u; \
                                            bFM_GPIO_PFR4_PD=0u; }while(0u)

/*---- GPIO bit P4E ----*/
#define GPIO1PIN_P4E_GET                ( bFM_GPIO_PDIR4_PE )

#define GPIO1PIN_P4E_PUT(v)             ( bFM_GPIO_PDOR4_PE=(v) )

#define GPIO1PIN_P4E_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P4E_INITIN(v) \
                                                           : GPIO1PIN_P4E_INITOUT(v) )

#define GPIO1PIN_P4E_INITIN(v)          do{ \
                                            bFM_GPIO_PCR4_PE=(v).bPullup; \
                                            bFM_GPIO_DDR4_PE=0u; \
                                            bFM_GPIO_PFR4_PE=0u; }while(0u)

#define GPIO1PIN_P4E_INITOUT(v)         do{ \
                                            bFM_GPIO_PDOR4_PE=(v).bInitVal; \
                                            bFM_GPIO_DDR4_PE=1u; \
                                            bFM_GPIO_PFR4_PE=0u; }while(0u)

/*---- GPIO bit NP4E ----*/
#define GPIO1PIN_NP4E_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR4_PE)) )

#define GPIO1PIN_NP4E_PUT(v)            ( bFM_GPIO_PDOR4_PE=(uint32_t)(!(v)) )

#define GPIO1PIN_NP4E_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP4E_INITIN(v) \
                                                           : GPIO1PIN_NP4E_INITOUT(v) )

#define GPIO1PIN_NP4E_INITIN(v)         do{ \
                                            bFM_GPIO_PCR4_PE=(v).bPullup; \
                                            bFM_GPIO_DDR4_PE=0u; \
                                            bFM_GPIO_PFR4_PE=0u; }while(0u)

#define GPIO1PIN_NP4E_INITOUT(v)        do{ \
                                            bFM_GPIO_PDOR4_PE=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR4_PE=1u; \
                                            bFM_GPIO_PFR4_PE=0u; }while(0u)

/*---- GPIO bit P50 ----*/
#define GPIO1PIN_P50_GET                ( bFM_GPIO_PDIR5_P0 )

#define GPIO1PIN_P50_PUT(v)             ( bFM_GPIO_PDOR5_P0=(v) )

#define GPIO1PIN_P50_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P50_INITIN(v) \
                                                           : GPIO1PIN_P50_INITOUT(v) )

#define GPIO1PIN_P50_INITIN(v)          do{ \
                                            bFM_GPIO_PCR5_P0=(v).bPullup; \
                                            bFM_GPIO_DDR5_P0=0u; \
                                            bFM_GPIO_PFR5_P0=0u; }while(0u)

#define GPIO1PIN_P50_INITOUT(v)         do{ \
                                            bFM_GPIO_PDOR5_P0=(v).bInitVal; \
                                            bFM_GPIO_DDR5_P0=1u; \
                                            bFM_GPIO_PFR5_P0=0u; }while(0u)

/*---- GPIO bit NP50 ----*/
#define GPIO1PIN_NP50_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR5_P0)) )

#define GPIO1PIN_NP50_PUT(v)            ( bFM_GPIO_PDOR5_P0=(uint32_t)(!(v)) )

#define GPIO1PIN_NP50_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP50_INITIN(v) \
                                                           : GPIO1PIN_NP50_INITOUT(v) )

#define GPIO1PIN_NP50_INITIN(v)         do{ \
                                            bFM_GPIO_PCR5_P0=(v).bPullup; \
                                            bFM_GPIO_DDR5_P0=0u; \
                                            bFM_GPIO_PFR5_P0=0u; }while(0u)

#define GPIO1PIN_NP50_INITOUT(v)        do{ \
                                            bFM_GPIO_PDOR5_P0=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR5_P0=1u; \
                                            bFM_GPIO_PFR5_P0=0u; }while(0u)

/*---- GPIO bit P51 ----*/
#define GPIO1PIN_P51_GET                ( bFM_GPIO_PDIR5_P1 )

#define GPIO1PIN_P51_PUT(v)             ( bFM_GPIO_PDOR5_P1=(v) )

#define GPIO1PIN_P51_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P51_INITIN(v) \
                                                           : GPIO1PIN_P51_INITOUT(v) )

#define GPIO1PIN_P51_INITIN(v)          do{ \
                                            bFM_GPIO_PCR5_P1=(v).bPullup; \
                                            bFM_GPIO_DDR5_P1=0u; \
                                            bFM_GPIO_PFR5_P1=0u; }while(0u)

#define GPIO1PIN_P51_INITOUT(v)         do{ \
                                            bFM_GPIO_PDOR5_P1=(v).bInitVal; \
                                            bFM_GPIO_DDR5_P1=1u; \
                                            bFM_GPIO_PFR5_P1=0u; }while(0u)

/*---- GPIO bit NP51 ----*/
#define GPIO1PIN_NP51_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR5_P1)) )

#define GPIO1PIN_NP51_PUT(v)            ( bFM_GPIO_PDOR5_P1=(uint32_t)(!(v)) )

#define GPIO1PIN_NP51_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP51_INITIN(v) \
                                                           : GPIO1PIN_NP51_INITOUT(v) )

#define GPIO1PIN_NP51_INITIN(v)         do{ \
                                            bFM_GPIO_PCR5_P1=(v).bPullup; \
                                            bFM_GPIO_DDR5_P1=0u; \
                                            bFM_GPIO_PFR5_P1=0u; }while(0u)

#define GPIO1PIN_NP51_INITOUT(v)        do{ \
                                            bFM_GPIO_PDOR5_P1=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR5_P1=1u; \
                                            bFM_GPIO_PFR5_P1=0u; }while(0u)

/*---- GPIO bit P52 ----*/
#define GPIO1PIN_P52_GET                ( bFM_GPIO_PDIR5_P2 )

#define GPIO1PIN_P52_PUT(v)             ( bFM_GPIO_PDOR5_P2=(v) )

#define GPIO1PIN_P52_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P52_INITIN(v) \
                                                           : GPIO1PIN_P52_INITOUT(v) )

#define GPIO1PIN_P52_INITIN(v)          do{ \
                                            bFM_GPIO_PCR5_P2=(v).bPullup; \
                                            bFM_GPIO_DDR5_P2=0u; \
                                            bFM_GPIO_PFR5_P2=0u; }while(0u)

#define GPIO1PIN_P52_INITOUT(v)         do{ \
                                            bFM_GPIO_PDOR5_P2=(v).bInitVal; \
                                            bFM_GPIO_DDR5_P2=1u; \
                                            bFM_GPIO_PFR5_P2=0u; }while(0u)

/*---- GPIO bit NP52 ----*/
#define GPIO1PIN_NP52_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR5_P2)) )

#define GPIO1PIN_NP52_PUT(v)            ( bFM_GPIO_PDOR5_P2=(uint32_t)(!(v)) )

#define GPIO1PIN_NP52_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP52_INITIN(v) \
                                                           : GPIO1PIN_NP52_INITOUT(v) )

#define GPIO1PIN_NP52_INITIN(v)         do{ \
                                            bFM_GPIO_PCR5_P2=(v).bPullup; \
                                            bFM_GPIO_DDR5_P2=0u; \
                                            bFM_GPIO_PFR5_P2=0u; }while(0u)

#define GPIO1PIN_NP52_INITOUT(v)        do{ \
                                            bFM_GPIO_PDOR5_P2=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR5_P2=1u; \
                                            bFM_GPIO_PFR5_P2=0u; }while(0u)

/*---- GPIO bit P53 ----*/
#define GPIO1PIN_P53_GET                ( bFM_GPIO_PDIR5_P3 )

#define GPIO1PIN_P53_PUT(v)             ( bFM_GPIO_PDOR5_P3=(v) )

#define GPIO1PIN_P53_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P53_INITIN(v) \
                                                           : GPIO1PIN_P53_INITOUT(v) )

#define GPIO1PIN_P53_INITIN(v)          do{ \
                                            bFM_GPIO_PCR5_P3=(v).bPullup; \
                                            bFM_GPIO_DDR5_P3=0u; \
                                            bFM_GPIO_PFR5_P3=0u; }while(0u)

#define GPIO1PIN_P53_INITOUT(v)         do{ \
                                            bFM_GPIO_PDOR5_P3=(v).bInitVal; \
                                            bFM_GPIO_DDR5_P3=1u; \
                                            bFM_GPIO_PFR5_P3=0u; }while(0u)

/*---- GPIO bit NP53 ----*/
#define GPIO1PIN_NP53_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR5_P3)) )

#define GPIO1PIN_NP53_PUT(v)            ( bFM_GPIO_PDOR5_P3=(uint32_t)(!(v)) )

#define GPIO1PIN_NP53_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP53_INITIN(v) \
                                                           : GPIO1PIN_NP53_INITOUT(v) )

#define GPIO1PIN_NP53_INITIN(v)         do{ \
                                            bFM_GPIO_PCR5_P3=(v).bPullup; \
                                            bFM_GPIO_DDR5_P3=0u; \
                                            bFM_GPIO_PFR5_P3=0u; }while(0u)

#define GPIO1PIN_NP53_INITOUT(v)        do{ \
                                            bFM_GPIO_PDOR5_P3=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR5_P3=1u; \
                                            bFM_GPIO_PFR5_P3=0u; }while(0u)

/*---- GPIO bit P60 ----*/
#define GPIO1PIN_P60_GET                ( bFM_GPIO_PDIR6_P0 )

#define GPIO1PIN_P60_PUT(v)             ( bFM_GPIO_PDOR6_P0=(v) )

#define GPIO1PIN_P60_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P60_INITIN(v) \
                                                           : GPIO1PIN_P60_INITOUT(v) )

#define GPIO1PIN_P60_INITIN(v)          do{ \
                                            PINCONFIG_SET_REG(FM_DS->CEC_CTL, 2u, 2u, 0u); \
                                            bFM_GPIO_PCR6_P0=(v).bPullup; \
                                            bFM_GPIO_DDR6_P0=0u; \
                                            bFM_GPIO_PFR6_P0=0u; }while(0u)

#define GPIO1PIN_P60_INITOUT(v)         do{ \
                                            PINCONFIG_SET_REG(FM_DS->CEC_CTL, 2u, 2u, 0u); \
                                            bFM_GPIO_PDOR6_P0=(v).bInitVal; \
                                            bFM_GPIO_DDR6_P0=1u; \
                                            bFM_GPIO_PFR6_P0=0u; }while(0u)

/*---- GPIO bit NP60 ----*/
#define GPIO1PIN_NP60_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR6_P0)) )

#define GPIO1PIN_NP60_PUT(v)            ( bFM_GPIO_PDOR6_P0=(uint32_t)(!(v)) )

#define GPIO1PIN_NP60_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP60_INITIN(v) \
                                                           : GPIO1PIN_NP60_INITOUT(v) )

#define GPIO1PIN_NP60_INITIN(v)         do{ \
                                            PINCONFIG_SET_REG(FM_DS->CEC_CTL, 2u, 2u, 0u); \
                                            bFM_GPIO_PCR6_P0=(v).bPullup; \
                                            bFM_GPIO_DDR6_P0=0u; \
                                            bFM_GPIO_PFR6_P0=0u; }while(0u)

#define GPIO1PIN_NP60_INITOUT(v)        do{ \
                                            PINCONFIG_SET_REG(FM_DS->CEC_CTL, 2u, 2u, 0u); \
                                            bFM_GPIO_PDOR6_P0=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR6_P0=1u; \
                                            bFM_GPIO_PFR6_P0=0u; }while(0u)

/*---- GPIO bit P61 ----*/
#define GPIO1PIN_P61_GET                ( bFM_GPIO_PDIR6_P1 )

#define GPIO1PIN_P61_PUT(v)             ( bFM_GPIO_PDOR6_P1=(v) )

#define GPIO1PIN_P61_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P61_INITIN(v) \
                                                           : GPIO1PIN_P61_INITOUT(v) )

#define GPIO1PIN_P61_INITIN(v)          do{ \
                                            bFM_GPIO_PCR6_P1=(v).bPullup; \
                                            bFM_GPIO_DDR6_P1=0u; \
                                            bFM_GPIO_PFR6_P1=0u; }while(0u)

#define GPIO1PIN_P61_INITOUT(v)         do{ \
                                            bFM_GPIO_PDOR6_P1=(v).bInitVal; \
                                            bFM_GPIO_DDR6_P1=1u; \
                                            bFM_GPIO_PFR6_P1=0u; }while(0u)

/*---- GPIO bit NP61 ----*/
#define GPIO1PIN_NP61_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR6_P1)) )

#define GPIO1PIN_NP61_PUT(v)            ( bFM_GPIO_PDOR6_P1=(uint32_t)(!(v)) )

#define GPIO1PIN_NP61_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP61_INITIN(v) \
                                                           : GPIO1PIN_NP61_INITOUT(v) )

#define GPIO1PIN_NP61_INITIN(v)         do{ \
                                            bFM_GPIO_PCR6_P1=(v).bPullup; \
                                            bFM_GPIO_DDR6_P1=0u; \
                                            bFM_GPIO_PFR6_P1=0u; }while(0u)

#define GPIO1PIN_NP61_INITOUT(v)        do{ \
                                            bFM_GPIO_PDOR6_P1=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR6_P1=1u; \
                                            bFM_GPIO_PFR6_P1=0u; }while(0u)

/*---- GPIO bit P80 ----*/
#define GPIO1PIN_P80_GET                ( bFM_GPIO_PDIR8_P0 )

#define GPIO1PIN_P80_PUT(v)             ( bFM_GPIO_PDOR8_P0=(v) )

#define GPIO1PIN_P80_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P80_INITIN(v) \
                                                           : GPIO1PIN_P80_INITOUT(v) )

#define GPIO1PIN_P80_INITIN(v)          do{ \
                                            bFM_GPIO_SPSR_USB0C=0u; \
                                            bFM_GPIO_DDR8_P0=0u; \
                                            bFM_GPIO_PFR8_P0=0u; }while(0u)

#define GPIO1PIN_P80_INITOUT(v)         do{ \
                                            bFM_GPIO_SPSR_USB0C=0u; \
                                            bFM_GPIO_PDOR8_P0=(v).bInitVal; \
                                            bFM_GPIO_DDR8_P0=1u; \
                                            bFM_GPIO_PFR8_P0=0u; }while(0u)

/*---- GPIO bit NP80 ----*/
#define GPIO1PIN_NP80_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR8_P0)) )

#define GPIO1PIN_NP80_PUT(v)            ( bFM_GPIO_PDOR8_P0=(uint32_t)(!(v)) )

#define GPIO1PIN_NP80_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP80_INITIN(v) \
                                                           : GPIO1PIN_NP80_INITOUT(v) )

#define GPIO1PIN_NP80_INITIN(v)         do{ \
                                            bFM_GPIO_SPSR_USB0C=0u; \
                                            bFM_GPIO_DDR8_P0=0u; \
                                            bFM_GPIO_PFR8_P0=0u; }while(0u)

#define GPIO1PIN_NP80_INITOUT(v)        do{ \
                                            bFM_GPIO_SPSR_USB0C=0u; \
                                            bFM_GPIO_PDOR8_P0=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR8_P0=1u; \
                                            bFM_GPIO_PFR8_P0=0u; }while(0u)

/*---- GPIO bit P81 ----*/
#define GPIO1PIN_P81_GET                ( bFM_GPIO_PDIR8_P1 )

#define GPIO1PIN_P81_PUT(v)             ( bFM_GPIO_PDOR8_P1=(v) )

#define GPIO1PIN_P81_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_P81_INITIN(v) \
                                                           : GPIO1PIN_P81_INITOUT(v) )

#define GPIO1PIN_P81_INITIN(v)          do{ \
                                            bFM_GPIO_SPSR_USB0C=0u; \
                                            bFM_GPIO_DDR8_P1=0u; \
                                            bFM_GPIO_PFR8_P1=0u; }while(0u)

#define GPIO1PIN_P81_INITOUT(v)         do{ \
                                            bFM_GPIO_SPSR_USB0C=0u; \
                                            bFM_GPIO_PDOR8_P1=(v).bInitVal; \
                                            bFM_GPIO_DDR8_P1=1u; \
                                            bFM_GPIO_PFR8_P1=0u; }while(0u)

/*---- GPIO bit NP81 ----*/
#define GPIO1PIN_NP81_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIR8_P1)) )

#define GPIO1PIN_NP81_PUT(v)            ( bFM_GPIO_PDOR8_P1=(uint32_t)(!(v)) )

#define GPIO1PIN_NP81_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NP81_INITIN(v) \
                                                           : GPIO1PIN_NP81_INITOUT(v) )

#define GPIO1PIN_NP81_INITIN(v)         do{ \
                                            bFM_GPIO_SPSR_USB0C=0u; \
                                            bFM_GPIO_DDR8_P1=0u; \
                                            bFM_GPIO_PFR8_P1=0u; }while(0u)

#define GPIO1PIN_NP81_INITOUT(v)        do{ \
                                            bFM_GPIO_SPSR_USB0C=0u; \
                                            bFM_GPIO_PDOR8_P1=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDR8_P1=1u; \
                                            bFM_GPIO_PFR8_P1=0u; }while(0u)

/*---- GPIO bit PE2 ----*/
#define GPIO1PIN_PE2_GET                ( bFM_GPIO_PDIRE_P2 )

#define GPIO1PIN_PE2_PUT(v)             ( bFM_GPIO_PDORE_P2=(v) )

#define GPIO1PIN_PE2_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_PE2_INITIN(v) \
                                                           : GPIO1PIN_PE2_INITOUT(v) )

#define GPIO1PIN_PE2_INITIN(v)          do{ \
                                            PINCONFIG_SET_REG(FM_GPIO->SPSR, 2u, 2u, 0u); \
                                            bFM_GPIO_PCRE_P2=(v).bPullup; \
                                            bFM_GPIO_DDRE_P2=0u; \
                                            bFM_GPIO_PFRE_P2=0u; }while(0u)

#define GPIO1PIN_PE2_INITOUT(v)         do{ \
                                            PINCONFIG_SET_REG(FM_GPIO->SPSR, 2u, 2u, 0u); \
                                            bFM_GPIO_PDORE_P2=(v).bInitVal; \
                                            bFM_GPIO_DDRE_P2=1u; \
                                            bFM_GPIO_PFRE_P2=0u; }while(0u)

/*---- GPIO bit NPE2 ----*/
#define GPIO1PIN_NPE2_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIRE_P2)) )

#define GPIO1PIN_NPE2_PUT(v)            ( bFM_GPIO_PDORE_P2=(uint32_t)(!(v)) )

#define GPIO1PIN_NPE2_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NPE2_INITIN(v) \
                                                           : GPIO1PIN_NPE2_INITOUT(v) )

#define GPIO1PIN_NPE2_INITIN(v)         do{ \
                                            PINCONFIG_SET_REG(FM_GPIO->SPSR, 2u, 2u, 0u); \
                                            bFM_GPIO_PCRE_P2=(v).bPullup; \
                                            bFM_GPIO_DDRE_P2=0u; \
                                            bFM_GPIO_PFRE_P2=0u; }while(0u)

#define GPIO1PIN_NPE2_INITOUT(v)        do{ \
                                            PINCONFIG_SET_REG(FM_GPIO->SPSR, 2u, 2u, 0u); \
                                            bFM_GPIO_PDORE_P2=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDRE_P2=1u; \
                                            bFM_GPIO_PFRE_P2=0u; }while(0u)

/*---- GPIO bit PE3 ----*/
#define GPIO1PIN_PE3_GET                ( bFM_GPIO_PDIRE_P3 )

#define GPIO1PIN_PE3_PUT(v)             ( bFM_GPIO_PDORE_P3=(v) )

#define GPIO1PIN_PE3_INIT(v)            ( (0==(v).bOutput) ? GPIO1PIN_PE3_INITIN(v) \
                                                           : GPIO1PIN_PE3_INITOUT(v) )

#define GPIO1PIN_PE3_INITIN(v)          do{ \
                                            PINCONFIG_SET_REG(FM_GPIO->SPSR, 2u, 2u, 0u); \
                                            bFM_GPIO_PCRE_P3=(v).bPullup; \
                                            bFM_GPIO_DDRE_P3=0u; \
                                            bFM_GPIO_PFRE_P3=0u; }while(0u)

#define GPIO1PIN_PE3_INITOUT(v)         do{ \
                                            PINCONFIG_SET_REG(FM_GPIO->SPSR, 2u, 2u, 0u); \
                                            bFM_GPIO_PDORE_P3=(v).bInitVal; \
                                            bFM_GPIO_DDRE_P3=1u; \
                                            bFM_GPIO_PFRE_P3=0u; }while(0u)

/*---- GPIO bit NPE3 ----*/
#define GPIO1PIN_NPE3_GET               ( (uint32_t)(!(uint32_t)(bFM_GPIO_PDIRE_P3)) )

#define GPIO1PIN_NPE3_PUT(v)            ( bFM_GPIO_PDORE_P3=(uint32_t)(!(v)) )

#define GPIO1PIN_NPE3_INIT(v)           ( (0==(v).bOutput) ? GPIO1PIN_NPE3_INITIN(v) \
                                                           : GPIO1PIN_NPE3_INITOUT(v) )

#define GPIO1PIN_NPE3_INITIN(v)         do{ \
                                            PINCONFIG_SET_REG(FM_GPIO->SPSR, 2u, 2u, 0u); \
                                            bFM_GPIO_PCRE_P3=(v).bPullup; \
                                            bFM_GPIO_DDRE_P3=0u; \
                                            bFM_GPIO_PFRE_P3=0u; }while(0u)

#define GPIO1PIN_NPE3_INITOUT(v)        do{ \
                                            PINCONFIG_SET_REG(FM_GPIO->SPSR, 2u, 2u, 0u); \
                                            bFM_GPIO_PDORE_P3=(uint32_t)(!((uint32_t)(v).bInitVal)); \
                                            bFM_GPIO_DDRE_P3=1u; \
                                            bFM_GPIO_PFRE_P3=0u; }while(0u)

/******************************************************************************
   Fast GPIO
*******************************************************************************/

/*---- Fast GPIO bit P01 ----*/
#define FGPIO1PIN_P01_GET               ( FM_FASTIO->FPDIR0_f.P1 )

#define FGPIO1PIN_P01_PUT(v)            ( FM_FASTIO->FPDOR0_f.P1=(v) )

#define FGPIO1PIN_P01_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P01_INITIN(v) \
                                                           : FGPIO1PIN_P01_INITOUT(v) )

#define FGPIO1PIN_P01_INITIN(v)         do{ \
                                            bFM_GPIO_PCR0_P1=(v).bPullup; \
                                            bFM_GPIO_DDR0_P1=0u; \
                                            bFM_GPIO_PFR0_P1=0u; }while(0u)

#define FGPIO1PIN_P01_INITOUT(v)        do{ \
                                            FM_FASTIO->FPDOR0_f.P1=(v).bInitVal; \
                                            FM_GPIO->FPOER0_f.P1=1u; \
                                            bFM_GPIO_DDR0_P1=1u; \
                                            bFM_GPIO_PFR0_P1=0u; }while(0u)

/*---- Fast GPIO bit NP01 ----*/
#define FGPIO1PIN_NP01_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR0_f.P1)) )

#define FGPIO1PIN_NP01_PUT(v)           ( FM_FASTIO->FPDOR0_f.P1=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP01_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP01_INITIN(v) \
                                                           : FGPIO1PIN_NP01_INITOUT(v) )

#define FGPIO1PIN_NP01_INITIN(v)        do{ \
                                            bFM_GPIO_PCR0_P1=(v).bPullup; \
                                            bFM_GPIO_DDR0_P1=0u; \
                                            bFM_GPIO_PFR0_P1=0u; }while(0u)

#define FGPIO1PIN_NP01_INITOUT(v)       do{ \
                                            FM_FASTIO->FPDOR0_f.P1=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER0_f.P1=1u; \
                                            bFM_GPIO_DDR0_P1=1u; \
                                            bFM_GPIO_PFR0_P1=0u; }while(0u)

/*---- Fast GPIO bit P03 ----*/
#define FGPIO1PIN_P03_GET               ( FM_FASTIO->FPDIR0_f.P3 )

#define FGPIO1PIN_P03_PUT(v)            ( FM_FASTIO->FPDOR0_f.P3=(v) )

#define FGPIO1PIN_P03_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P03_INITIN(v) \
                                                           : FGPIO1PIN_P03_INITOUT(v) )

#define FGPIO1PIN_P03_INITIN(v)         do{ \
                                            bFM_GPIO_PCR0_P3=(v).bPullup; \
                                            bFM_GPIO_DDR0_P3=0u; \
                                            bFM_GPIO_PFR0_P3=0u; }while(0u)

#define FGPIO1PIN_P03_INITOUT(v)        do{ \
                                            FM_FASTIO->FPDOR0_f.P3=(v).bInitVal; \
                                            FM_GPIO->FPOER0_f.P3=1u; \
                                            bFM_GPIO_DDR0_P3=1u; \
                                            bFM_GPIO_PFR0_P3=0u; }while(0u)

/*---- Fast GPIO bit NP03 ----*/
#define FGPIO1PIN_NP03_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR0_f.P3)) )

#define FGPIO1PIN_NP03_PUT(v)           ( FM_FASTIO->FPDOR0_f.P3=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP03_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP03_INITIN(v) \
                                                           : FGPIO1PIN_NP03_INITOUT(v) )

#define FGPIO1PIN_NP03_INITIN(v)        do{ \
                                            bFM_GPIO_PCR0_P3=(v).bPullup; \
                                            bFM_GPIO_DDR0_P3=0u; \
                                            bFM_GPIO_PFR0_P3=0u; }while(0u)

#define FGPIO1PIN_NP03_INITOUT(v)       do{ \
                                            FM_FASTIO->FPDOR0_f.P3=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER0_f.P3=1u; \
                                            bFM_GPIO_DDR0_P3=1u; \
                                            bFM_GPIO_PFR0_P3=0u; }while(0u)

/*---- Fast GPIO bit P05 ----*/
#define FGPIO1PIN_P05_GET               ( FM_FASTIO->FPDIR0_f.P5 )

#define FGPIO1PIN_P05_PUT(v)            ( FM_FASTIO->FPDOR0_f.P5=(v) )

#define FGPIO1PIN_P05_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P05_INITIN(v) \
                                                           : FGPIO1PIN_P05_INITOUT(v) )

#define FGPIO1PIN_P05_INITIN(v)         do{ \
                                            bFM_GPIO_PCR0_P5=(v).bPullup; \
                                            bFM_GPIO_DDR0_P5=0u; \
                                            bFM_GPIO_PFR0_P5=0u; }while(0u)

#define FGPIO1PIN_P05_INITOUT(v)        do{ \
                                            FM_FASTIO->FPDOR0_f.P5=(v).bInitVal; \
                                            FM_GPIO->FPOER0_f.P5=1u; \
                                            bFM_GPIO_DDR0_P5=1u; \
                                            bFM_GPIO_PFR0_P5=0u; }while(0u)

/*---- Fast GPIO bit NP05 ----*/
#define FGPIO1PIN_NP05_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR0_f.P5)) )

#define FGPIO1PIN_NP05_PUT(v)           ( FM_FASTIO->FPDOR0_f.P5=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP05_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP05_INITIN(v) \
                                                           : FGPIO1PIN_NP05_INITOUT(v) )

#define FGPIO1PIN_NP05_INITIN(v)        do{ \
                                            bFM_GPIO_PCR0_P5=(v).bPullup; \
                                            bFM_GPIO_DDR0_P5=0u; \
                                            bFM_GPIO_PFR0_P5=0u; }while(0u)

#define FGPIO1PIN_NP05_INITOUT(v)       do{ \
                                            FM_FASTIO->FPDOR0_f.P5=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER0_f.P5=1u; \
                                            bFM_GPIO_DDR0_P5=1u; \
                                            bFM_GPIO_PFR0_P5=0u; }while(0u)

/*---- Fast GPIO bit P0F ----*/
#define FGPIO1PIN_P0F_GET               ( FM_FASTIO->FPDIR0_f.PF )

#define FGPIO1PIN_P0F_PUT(v)            ( FM_FASTIO->FPDOR0_f.PF=(v) )

#define FGPIO1PIN_P0F_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P0F_INITIN(v) \
                                                           : FGPIO1PIN_P0F_INITOUT(v) )

#define FGPIO1PIN_P0F_INITIN(v)         do{ \
                                            bFM_GPIO_PCR0_PF=(v).bPullup; \
                                            bFM_GPIO_DDR0_PF=0u; \
                                            bFM_GPIO_PFR0_PF=0u; }while(0u)

#define FGPIO1PIN_P0F_INITOUT(v)        do{ \
                                            FM_FASTIO->FPDOR0_f.PF=(v).bInitVal; \
                                            FM_GPIO->FPOER0_f.PF=1u; \
                                            bFM_GPIO_DDR0_PF=1u; \
                                            bFM_GPIO_PFR0_PF=0u; }while(0u)

/*---- Fast GPIO bit NP0F ----*/
#define FGPIO1PIN_NP0F_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR0_f.PF)) )

#define FGPIO1PIN_NP0F_PUT(v)           ( FM_FASTIO->FPDOR0_f.PF=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP0F_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP0F_INITIN(v) \
                                                           : FGPIO1PIN_NP0F_INITOUT(v) )

#define FGPIO1PIN_NP0F_INITIN(v)        do{ \
                                            bFM_GPIO_PCR0_PF=(v).bPullup; \
                                            bFM_GPIO_DDR0_PF=0u; \
                                            bFM_GPIO_PFR0_PF=0u; }while(0u)

#define FGPIO1PIN_NP0F_INITOUT(v)       do{ \
                                            FM_FASTIO->FPDOR0_f.PF=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER0_f.PF=1u; \
                                            bFM_GPIO_DDR0_PF=1u; \
                                            bFM_GPIO_PFR0_PF=0u; }while(0u)

/*---- Fast GPIO bit P10 ----*/
#define FGPIO1PIN_P10_GET               ( FM_FASTIO->FPDIR1_f.P0 )

#define FGPIO1PIN_P10_PUT(v)            ( FM_FASTIO->FPDOR1_f.P0=(v) )

#define FGPIO1PIN_P10_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P10_INITIN(v) \
                                                           : FGPIO1PIN_P10_INITOUT(v) )

#define FGPIO1PIN_P10_INITIN(v)         do{ \
                                            bFM_GPIO_ADE_AN00=0u; \
                                            bFM_GPIO_PCR1_P0=(v).bPullup; \
                                            bFM_GPIO_DDR1_P0=0u; \
                                            bFM_GPIO_PFR1_P0=0u; }while(0u)

#define FGPIO1PIN_P10_INITOUT(v)        do{ \
                                            bFM_GPIO_ADE_AN00=0u; \
                                            FM_FASTIO->FPDOR1_f.P0=(v).bInitVal; \
                                            FM_GPIO->FPOER1_f.P0=1u; \
                                            bFM_GPIO_DDR1_P0=1u; \
                                            bFM_GPIO_PFR1_P0=0u; }while(0u)

/*---- Fast GPIO bit NP10 ----*/
#define FGPIO1PIN_NP10_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR1_f.P0)) )

#define FGPIO1PIN_NP10_PUT(v)           ( FM_FASTIO->FPDOR1_f.P0=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP10_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP10_INITIN(v) \
                                                           : FGPIO1PIN_NP10_INITOUT(v) )

#define FGPIO1PIN_NP10_INITIN(v)        do{ \
                                            bFM_GPIO_ADE_AN00=0u; \
                                            bFM_GPIO_PCR1_P0=(v).bPullup; \
                                            bFM_GPIO_DDR1_P0=0u; \
                                            bFM_GPIO_PFR1_P0=0u; }while(0u)

#define FGPIO1PIN_NP10_INITOUT(v)       do{ \
                                            bFM_GPIO_ADE_AN00=0u; \
                                            FM_FASTIO->FPDOR1_f.P0=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER1_f.P0=1u; \
                                            bFM_GPIO_DDR1_P0=1u; \
                                            bFM_GPIO_PFR1_P0=0u; }while(0u)

/*---- Fast GPIO bit P11 ----*/
#define FGPIO1PIN_P11_GET               ( FM_FASTIO->FPDIR1_f.P1 )

#define FGPIO1PIN_P11_PUT(v)            ( FM_FASTIO->FPDOR1_f.P1=(v) )

#define FGPIO1PIN_P11_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P11_INITIN(v) \
                                                           : FGPIO1PIN_P11_INITOUT(v) )

#define FGPIO1PIN_P11_INITIN(v)         do{ \
                                            bFM_GPIO_ADE_AN01=0u; \
                                            bFM_GPIO_PCR1_P1=(v).bPullup; \
                                            bFM_GPIO_DDR1_P1=0u; \
                                            bFM_GPIO_PFR1_P1=0u; }while(0u)

#define FGPIO1PIN_P11_INITOUT(v)        do{ \
                                            bFM_GPIO_ADE_AN01=0u; \
                                            FM_FASTIO->FPDOR1_f.P1=(v).bInitVal; \
                                            FM_GPIO->FPOER1_f.P1=1u; \
                                            bFM_GPIO_DDR1_P1=1u; \
                                            bFM_GPIO_PFR1_P1=0u; }while(0u)

/*---- Fast GPIO bit NP11 ----*/
#define FGPIO1PIN_NP11_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR1_f.P1)) )

#define FGPIO1PIN_NP11_PUT(v)           ( FM_FASTIO->FPDOR1_f.P1=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP11_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP11_INITIN(v) \
                                                           : FGPIO1PIN_NP11_INITOUT(v) )

#define FGPIO1PIN_NP11_INITIN(v)        do{ \
                                            bFM_GPIO_ADE_AN01=0u; \
                                            bFM_GPIO_PCR1_P1=(v).bPullup; \
                                            bFM_GPIO_DDR1_P1=0u; \
                                            bFM_GPIO_PFR1_P1=0u; }while(0u)

#define FGPIO1PIN_NP11_INITOUT(v)       do{ \
                                            bFM_GPIO_ADE_AN01=0u; \
                                            FM_FASTIO->FPDOR1_f.P1=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER1_f.P1=1u; \
                                            bFM_GPIO_DDR1_P1=1u; \
                                            bFM_GPIO_PFR1_P1=0u; }while(0u)

/*---- Fast GPIO bit P12 ----*/
#define FGPIO1PIN_P12_GET               ( FM_FASTIO->FPDIR1_f.P2 )

#define FGPIO1PIN_P12_PUT(v)            ( FM_FASTIO->FPDOR1_f.P2=(v) )

#define FGPIO1PIN_P12_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P12_INITIN(v) \
                                                           : FGPIO1PIN_P12_INITOUT(v) )

#define FGPIO1PIN_P12_INITIN(v)         do{ \
                                            bFM_GPIO_ADE_AN02=0u; \
                                            bFM_GPIO_PCR1_P2=(v).bPullup; \
                                            bFM_GPIO_DDR1_P2=0u; \
                                            bFM_GPIO_PFR1_P2=0u; }while(0u)

#define FGPIO1PIN_P12_INITOUT(v)        do{ \
                                            bFM_GPIO_ADE_AN02=0u; \
                                            FM_FASTIO->FPDOR1_f.P2=(v).bInitVal; \
                                            FM_GPIO->FPOER1_f.P2=1u; \
                                            bFM_GPIO_DDR1_P2=1u; \
                                            bFM_GPIO_PFR1_P2=0u; }while(0u)

/*---- Fast GPIO bit NP12 ----*/
#define FGPIO1PIN_NP12_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR1_f.P2)) )

#define FGPIO1PIN_NP12_PUT(v)           ( FM_FASTIO->FPDOR1_f.P2=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP12_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP12_INITIN(v) \
                                                           : FGPIO1PIN_NP12_INITOUT(v) )

#define FGPIO1PIN_NP12_INITIN(v)        do{ \
                                            bFM_GPIO_ADE_AN02=0u; \
                                            bFM_GPIO_PCR1_P2=(v).bPullup; \
                                            bFM_GPIO_DDR1_P2=0u; \
                                            bFM_GPIO_PFR1_P2=0u; }while(0u)

#define FGPIO1PIN_NP12_INITOUT(v)       do{ \
                                            bFM_GPIO_ADE_AN02=0u; \
                                            FM_FASTIO->FPDOR1_f.P2=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER1_f.P2=1u; \
                                            bFM_GPIO_DDR1_P2=1u; \
                                            bFM_GPIO_PFR1_P2=0u; }while(0u)

/*---- Fast GPIO bit P13 ----*/
#define FGPIO1PIN_P13_GET               ( FM_FASTIO->FPDIR1_f.P3 )

#define FGPIO1PIN_P13_PUT(v)            ( FM_FASTIO->FPDOR1_f.P3=(v) )

#define FGPIO1PIN_P13_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P13_INITIN(v) \
                                                           : FGPIO1PIN_P13_INITOUT(v) )

#define FGPIO1PIN_P13_INITIN(v)         do{ \
                                            bFM_GPIO_ADE_AN03=0u; \
                                            bFM_GPIO_PCR1_P3=(v).bPullup; \
                                            bFM_GPIO_DDR1_P3=0u; \
                                            bFM_GPIO_PFR1_P3=0u; }while(0u)

#define FGPIO1PIN_P13_INITOUT(v)        do{ \
                                            bFM_GPIO_ADE_AN03=0u; \
                                            FM_FASTIO->FPDOR1_f.P3=(v).bInitVal; \
                                            FM_GPIO->FPOER1_f.P3=1u; \
                                            bFM_GPIO_DDR1_P3=1u; \
                                            bFM_GPIO_PFR1_P3=0u; }while(0u)

/*---- Fast GPIO bit NP13 ----*/
#define FGPIO1PIN_NP13_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR1_f.P3)) )

#define FGPIO1PIN_NP13_PUT(v)           ( FM_FASTIO->FPDOR1_f.P3=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP13_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP13_INITIN(v) \
                                                           : FGPIO1PIN_NP13_INITOUT(v) )

#define FGPIO1PIN_NP13_INITIN(v)        do{ \
                                            bFM_GPIO_ADE_AN03=0u; \
                                            bFM_GPIO_PCR1_P3=(v).bPullup; \
                                            bFM_GPIO_DDR1_P3=0u; \
                                            bFM_GPIO_PFR1_P3=0u; }while(0u)

#define FGPIO1PIN_NP13_INITOUT(v)       do{ \
                                            bFM_GPIO_ADE_AN03=0u; \
                                            FM_FASTIO->FPDOR1_f.P3=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER1_f.P3=1u; \
                                            bFM_GPIO_DDR1_P3=1u; \
                                            bFM_GPIO_PFR1_P3=0u; }while(0u)

/*---- Fast GPIO bit P14 ----*/
#define FGPIO1PIN_P14_GET               ( FM_FASTIO->FPDIR1_f.P4 )

#define FGPIO1PIN_P14_PUT(v)            ( FM_FASTIO->FPDOR1_f.P4=(v) )

#define FGPIO1PIN_P14_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P14_INITIN(v) \
                                                           : FGPIO1PIN_P14_INITOUT(v) )

#define FGPIO1PIN_P14_INITIN(v)         do{ \
                                            bFM_GPIO_ADE_AN04=0u; \
                                            bFM_GPIO_PCR1_P4=(v).bPullup; \
                                            bFM_GPIO_DDR1_P4=0u; \
                                            bFM_GPIO_PFR1_P4=0u; }while(0u)

#define FGPIO1PIN_P14_INITOUT(v)        do{ \
                                            bFM_GPIO_ADE_AN04=0u; \
                                            FM_FASTIO->FPDOR1_f.P4=(v).bInitVal; \
                                            FM_GPIO->FPOER1_f.P4=1u; \
                                            bFM_GPIO_DDR1_P4=1u; \
                                            bFM_GPIO_PFR1_P4=0u; }while(0u)

/*---- Fast GPIO bit NP14 ----*/
#define FGPIO1PIN_NP14_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR1_f.P4)) )

#define FGPIO1PIN_NP14_PUT(v)           ( FM_FASTIO->FPDOR1_f.P4=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP14_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP14_INITIN(v) \
                                                           : FGPIO1PIN_NP14_INITOUT(v) )

#define FGPIO1PIN_NP14_INITIN(v)        do{ \
                                            bFM_GPIO_ADE_AN04=0u; \
                                            bFM_GPIO_PCR1_P4=(v).bPullup; \
                                            bFM_GPIO_DDR1_P4=0u; \
                                            bFM_GPIO_PFR1_P4=0u; }while(0u)

#define FGPIO1PIN_NP14_INITOUT(v)       do{ \
                                            bFM_GPIO_ADE_AN04=0u; \
                                            FM_FASTIO->FPDOR1_f.P4=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER1_f.P4=1u; \
                                            bFM_GPIO_DDR1_P4=1u; \
                                            bFM_GPIO_PFR1_P4=0u; }while(0u)

/*---- Fast GPIO bit P15 ----*/
#define FGPIO1PIN_P15_GET               ( FM_FASTIO->FPDIR1_f.P5 )

#define FGPIO1PIN_P15_PUT(v)            ( FM_FASTIO->FPDOR1_f.P5=(v) )

#define FGPIO1PIN_P15_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P15_INITIN(v) \
                                                           : FGPIO1PIN_P15_INITOUT(v) )

#define FGPIO1PIN_P15_INITIN(v)         do{ \
                                            bFM_GPIO_ADE_AN05=0u; \
                                            bFM_GPIO_PCR1_P5=(v).bPullup; \
                                            bFM_GPIO_DDR1_P5=0u; \
                                            bFM_GPIO_PFR1_P5=0u; }while(0u)

#define FGPIO1PIN_P15_INITOUT(v)        do{ \
                                            bFM_GPIO_ADE_AN05=0u; \
                                            FM_FASTIO->FPDOR1_f.P5=(v).bInitVal; \
                                            FM_GPIO->FPOER1_f.P5=1u; \
                                            bFM_GPIO_DDR1_P5=1u; \
                                            bFM_GPIO_PFR1_P5=0u; }while(0u)

/*---- Fast GPIO bit NP15 ----*/
#define FGPIO1PIN_NP15_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR1_f.P5)) )

#define FGPIO1PIN_NP15_PUT(v)           ( FM_FASTIO->FPDOR1_f.P5=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP15_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP15_INITIN(v) \
                                                           : FGPIO1PIN_NP15_INITOUT(v) )

#define FGPIO1PIN_NP15_INITIN(v)        do{ \
                                            bFM_GPIO_ADE_AN05=0u; \
                                            bFM_GPIO_PCR1_P5=(v).bPullup; \
                                            bFM_GPIO_DDR1_P5=0u; \
                                            bFM_GPIO_PFR1_P5=0u; }while(0u)

#define FGPIO1PIN_NP15_INITOUT(v)       do{ \
                                            bFM_GPIO_ADE_AN05=0u; \
                                            FM_FASTIO->FPDOR1_f.P5=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER1_f.P5=1u; \
                                            bFM_GPIO_DDR1_P5=1u; \
                                            bFM_GPIO_PFR1_P5=0u; }while(0u)

/*---- Fast GPIO bit P1A ----*/
#define FGPIO1PIN_P1A_GET               ( FM_FASTIO->FPDIR1_f.PA )

#define FGPIO1PIN_P1A_PUT(v)            ( FM_FASTIO->FPDOR1_f.PA=(v) )

#define FGPIO1PIN_P1A_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P1A_INITIN(v) \
                                                           : FGPIO1PIN_P1A_INITOUT(v) )

#define FGPIO1PIN_P1A_INITIN(v)         do{ \
                                            PINCONFIG_SET_REG(FM_DS->CEC_CTL, 0u, 2u, 0u); \
                                            bFM_GPIO_PCR1_PA=(v).bPullup; \
                                            bFM_GPIO_DDR1_PA=0u; \
                                            bFM_GPIO_PFR1_PA=0u; }while(0u)

#define FGPIO1PIN_P1A_INITOUT(v)        do{ \
                                            PINCONFIG_SET_REG(FM_DS->CEC_CTL, 0u, 2u, 0u); \
                                            FM_FASTIO->FPDOR1_f.PA=(v).bInitVal; \
                                            FM_GPIO->FPOER1_f.PA=1u; \
                                            bFM_GPIO_DDR1_PA=1u; \
                                            bFM_GPIO_PFR1_PA=0u; }while(0u)

/*---- Fast GPIO bit NP1A ----*/
#define FGPIO1PIN_NP1A_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR1_f.PA)) )

#define FGPIO1PIN_NP1A_PUT(v)           ( FM_FASTIO->FPDOR1_f.PA=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP1A_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP1A_INITIN(v) \
                                                           : FGPIO1PIN_NP1A_INITOUT(v) )

#define FGPIO1PIN_NP1A_INITIN(v)        do{ \
                                            PINCONFIG_SET_REG(FM_DS->CEC_CTL, 0u, 2u, 0u); \
                                            bFM_GPIO_PCR1_PA=(v).bPullup; \
                                            bFM_GPIO_DDR1_PA=0u; \
                                            bFM_GPIO_PFR1_PA=0u; }while(0u)

#define FGPIO1PIN_NP1A_INITOUT(v)       do{ \
                                            PINCONFIG_SET_REG(FM_DS->CEC_CTL, 0u, 2u, 0u); \
                                            FM_FASTIO->FPDOR1_f.PA=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER1_f.PA=1u; \
                                            bFM_GPIO_DDR1_PA=1u; \
                                            bFM_GPIO_PFR1_PA=0u; }while(0u)

/*---- Fast GPIO bit P1B ----*/
#define FGPIO1PIN_P1B_GET               ( FM_FASTIO->FPDIR1_f.PB )

#define FGPIO1PIN_P1B_PUT(v)            ( FM_FASTIO->FPDOR1_f.PB=(v) )

#define FGPIO1PIN_P1B_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P1B_INITIN(v) \
                                                           : FGPIO1PIN_P1B_INITOUT(v) )

#define FGPIO1PIN_P1B_INITIN(v)         do{ \
                                            bFM_GPIO_PCR1_PB=(v).bPullup; \
                                            bFM_GPIO_DDR1_PB=0u; \
                                            bFM_GPIO_PFR1_PB=0u; }while(0u)

#define FGPIO1PIN_P1B_INITOUT(v)        do{ \
                                            FM_FASTIO->FPDOR1_f.PB=(v).bInitVal; \
                                            FM_GPIO->FPOER1_f.PB=1u; \
                                            bFM_GPIO_DDR1_PB=1u; \
                                            bFM_GPIO_PFR1_PB=0u; }while(0u)

/*---- Fast GPIO bit NP1B ----*/
#define FGPIO1PIN_NP1B_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR1_f.PB)) )

#define FGPIO1PIN_NP1B_PUT(v)           ( FM_FASTIO->FPDOR1_f.PB=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP1B_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP1B_INITIN(v) \
                                                           : FGPIO1PIN_NP1B_INITOUT(v) )

#define FGPIO1PIN_NP1B_INITIN(v)        do{ \
                                            bFM_GPIO_PCR1_PB=(v).bPullup; \
                                            bFM_GPIO_DDR1_PB=0u; \
                                            bFM_GPIO_PFR1_PB=0u; }while(0u)

#define FGPIO1PIN_NP1B_INITOUT(v)       do{ \
                                            FM_FASTIO->FPDOR1_f.PB=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER1_f.PB=1u; \
                                            bFM_GPIO_DDR1_PB=1u; \
                                            bFM_GPIO_PFR1_PB=0u; }while(0u)

/*---- Fast GPIO bit P21 ----*/
#define FGPIO1PIN_P21_GET               ( FM_FASTIO->FPDIR2_f.P1 )

#define FGPIO1PIN_P21_PUT(v)            ( FM_FASTIO->FPDOR2_f.P1=(v) )

#define FGPIO1PIN_P21_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P21_INITIN(v) \
                                                           : FGPIO1PIN_P21_INITOUT(v) )

#define FGPIO1PIN_P21_INITIN(v)         do{ \
                                            bFM_GPIO_PCR2_P1=(v).bPullup; \
                                            bFM_GPIO_DDR2_P1=0u; \
                                            bFM_GPIO_PFR2_P1=0u; }while(0u)

#define FGPIO1PIN_P21_INITOUT(v)        do{ \
                                            FM_FASTIO->FPDOR2_f.P1=(v).bInitVal; \
                                            FM_GPIO->FPOER2_f.P1=1u; \
                                            bFM_GPIO_DDR2_P1=1u; \
                                            bFM_GPIO_PFR2_P1=0u; }while(0u)

/*---- Fast GPIO bit NP21 ----*/
#define FGPIO1PIN_NP21_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR2_f.P1)) )

#define FGPIO1PIN_NP21_PUT(v)           ( FM_FASTIO->FPDOR2_f.P1=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP21_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP21_INITIN(v) \
                                                           : FGPIO1PIN_NP21_INITOUT(v) )

#define FGPIO1PIN_NP21_INITIN(v)        do{ \
                                            bFM_GPIO_PCR2_P1=(v).bPullup; \
                                            bFM_GPIO_DDR2_P1=0u; \
                                            bFM_GPIO_PFR2_P1=0u; }while(0u)

#define FGPIO1PIN_NP21_INITOUT(v)       do{ \
                                            FM_FASTIO->FPDOR2_f.P1=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER2_f.P1=1u; \
                                            bFM_GPIO_DDR2_P1=1u; \
                                            bFM_GPIO_PFR2_P1=0u; }while(0u)

/*---- Fast GPIO bit P22 ----*/
#define FGPIO1PIN_P22_GET               ( FM_FASTIO->FPDIR2_f.P2 )

#define FGPIO1PIN_P22_PUT(v)            ( FM_FASTIO->FPDOR2_f.P2=(v) )

#define FGPIO1PIN_P22_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P22_INITIN(v) \
                                                           : FGPIO1PIN_P22_INITOUT(v) )

#define FGPIO1PIN_P22_INITIN(v)         do{ \
                                            bFM_GPIO_ADE_AN07=0u; \
                                            bFM_GPIO_PCR2_P2=(v).bPullup; \
                                            bFM_GPIO_DDR2_P2=0u; \
                                            bFM_GPIO_PFR2_P2=0u; }while(0u)

#define FGPIO1PIN_P22_INITOUT(v)        do{ \
                                            bFM_GPIO_ADE_AN07=0u; \
                                            FM_FASTIO->FPDOR2_f.P2=(v).bInitVal; \
                                            FM_GPIO->FPOER2_f.P2=1u; \
                                            bFM_GPIO_DDR2_P2=1u; \
                                            bFM_GPIO_PFR2_P2=0u; }while(0u)

/*---- Fast GPIO bit NP22 ----*/
#define FGPIO1PIN_NP22_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR2_f.P2)) )

#define FGPIO1PIN_NP22_PUT(v)           ( FM_FASTIO->FPDOR2_f.P2=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP22_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP22_INITIN(v) \
                                                           : FGPIO1PIN_NP22_INITOUT(v) )

#define FGPIO1PIN_NP22_INITIN(v)        do{ \
                                            bFM_GPIO_ADE_AN07=0u; \
                                            bFM_GPIO_PCR2_P2=(v).bPullup; \
                                            bFM_GPIO_DDR2_P2=0u; \
                                            bFM_GPIO_PFR2_P2=0u; }while(0u)

#define FGPIO1PIN_NP22_INITOUT(v)       do{ \
                                            bFM_GPIO_ADE_AN07=0u; \
                                            FM_FASTIO->FPDOR2_f.P2=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER2_f.P2=1u; \
                                            bFM_GPIO_DDR2_P2=1u; \
                                            bFM_GPIO_PFR2_P2=0u; }while(0u)

/*---- Fast GPIO bit P23 ----*/
#define FGPIO1PIN_P23_GET               ( FM_FASTIO->FPDIR2_f.P3 )

#define FGPIO1PIN_P23_PUT(v)            ( FM_FASTIO->FPDOR2_f.P3=(v) )

#define FGPIO1PIN_P23_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P23_INITIN(v) \
                                                           : FGPIO1PIN_P23_INITOUT(v) )

#define FGPIO1PIN_P23_INITIN(v)         do{ \
                                            bFM_GPIO_ADE_AN06=0u; \
                                            bFM_GPIO_PCR2_P3=(v).bPullup; \
                                            bFM_GPIO_DDR2_P3=0u; \
                                            bFM_GPIO_PFR2_P3=0u; }while(0u)

#define FGPIO1PIN_P23_INITOUT(v)        do{ \
                                            bFM_GPIO_ADE_AN06=0u; \
                                            FM_FASTIO->FPDOR2_f.P3=(v).bInitVal; \
                                            FM_GPIO->FPOER2_f.P3=1u; \
                                            bFM_GPIO_DDR2_P3=1u; \
                                            bFM_GPIO_PFR2_P3=0u; }while(0u)

/*---- Fast GPIO bit NP23 ----*/
#define FGPIO1PIN_NP23_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR2_f.P3)) )

#define FGPIO1PIN_NP23_PUT(v)           ( FM_FASTIO->FPDOR2_f.P3=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP23_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP23_INITIN(v) \
                                                           : FGPIO1PIN_NP23_INITOUT(v) )

#define FGPIO1PIN_NP23_INITIN(v)        do{ \
                                            bFM_GPIO_ADE_AN06=0u; \
                                            bFM_GPIO_PCR2_P3=(v).bPullup; \
                                            bFM_GPIO_DDR2_P3=0u; \
                                            bFM_GPIO_PFR2_P3=0u; }while(0u)

#define FGPIO1PIN_NP23_INITOUT(v)       do{ \
                                            bFM_GPIO_ADE_AN06=0u; \
                                            FM_FASTIO->FPDOR2_f.P3=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER2_f.P3=1u; \
                                            bFM_GPIO_DDR2_P3=1u; \
                                            bFM_GPIO_PFR2_P3=0u; }while(0u)

/*---- Fast GPIO bit P30 ----*/
#define FGPIO1PIN_P30_GET               ( FM_FASTIO->FPDIR3_f.P0 )

#define FGPIO1PIN_P30_PUT(v)            ( FM_FASTIO->FPDOR3_f.P0=(v) )

#define FGPIO1PIN_P30_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P30_INITIN(v) \
                                                           : FGPIO1PIN_P30_INITOUT(v) )

#define FGPIO1PIN_P30_INITIN(v)         do{ \
                                            bFM_GPIO_PCR3_P0=(v).bPullup; \
                                            bFM_GPIO_DDR3_P0=0u; \
                                            bFM_GPIO_PFR3_P0=0u; }while(0u)

#define FGPIO1PIN_P30_INITOUT(v)        do{ \
                                            FM_FASTIO->FPDOR3_f.P0=(v).bInitVal; \
                                            FM_GPIO->FPOER3_f.P0=1u; \
                                            bFM_GPIO_DDR3_P0=1u; \
                                            bFM_GPIO_PFR3_P0=0u; }while(0u)

/*---- Fast GPIO bit NP30 ----*/
#define FGPIO1PIN_NP30_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR3_f.P0)) )

#define FGPIO1PIN_NP30_PUT(v)           ( FM_FASTIO->FPDOR3_f.P0=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP30_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP30_INITIN(v) \
                                                           : FGPIO1PIN_NP30_INITOUT(v) )

#define FGPIO1PIN_NP30_INITIN(v)        do{ \
                                            bFM_GPIO_PCR3_P0=(v).bPullup; \
                                            bFM_GPIO_DDR3_P0=0u; \
                                            bFM_GPIO_PFR3_P0=0u; }while(0u)

#define FGPIO1PIN_NP30_INITOUT(v)       do{ \
                                            FM_FASTIO->FPDOR3_f.P0=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER3_f.P0=1u; \
                                            bFM_GPIO_DDR3_P0=1u; \
                                            bFM_GPIO_PFR3_P0=0u; }while(0u)

/*---- Fast GPIO bit P31 ----*/
#define FGPIO1PIN_P31_GET               ( FM_FASTIO->FPDIR3_f.P1 )

#define FGPIO1PIN_P31_PUT(v)            ( FM_FASTIO->FPDOR3_f.P1=(v) )

#define FGPIO1PIN_P31_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P31_INITIN(v) \
                                                           : FGPIO1PIN_P31_INITOUT(v) )

#define FGPIO1PIN_P31_INITIN(v)         do{ \
                                            bFM_GPIO_PCR3_P1=(v).bPullup; \
                                            bFM_GPIO_DDR3_P1=0u; \
                                            bFM_GPIO_PFR3_P1=0u; }while(0u)

#define FGPIO1PIN_P31_INITOUT(v)        do{ \
                                            FM_FASTIO->FPDOR3_f.P1=(v).bInitVal; \
                                            FM_GPIO->FPOER3_f.P1=1u; \
                                            bFM_GPIO_DDR3_P1=1u; \
                                            bFM_GPIO_PFR3_P1=0u; }while(0u)

/*---- Fast GPIO bit NP31 ----*/
#define FGPIO1PIN_NP31_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR3_f.P1)) )

#define FGPIO1PIN_NP31_PUT(v)           ( FM_FASTIO->FPDOR3_f.P1=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP31_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP31_INITIN(v) \
                                                           : FGPIO1PIN_NP31_INITOUT(v) )

#define FGPIO1PIN_NP31_INITIN(v)        do{ \
                                            bFM_GPIO_PCR3_P1=(v).bPullup; \
                                            bFM_GPIO_DDR3_P1=0u; \
                                            bFM_GPIO_PFR3_P1=0u; }while(0u)

#define FGPIO1PIN_NP31_INITOUT(v)       do{ \
                                            FM_FASTIO->FPDOR3_f.P1=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER3_f.P1=1u; \
                                            bFM_GPIO_DDR3_P1=1u; \
                                            bFM_GPIO_PFR3_P1=0u; }while(0u)

/*---- Fast GPIO bit P32 ----*/
#define FGPIO1PIN_P32_GET               ( FM_FASTIO->FPDIR3_f.P2 )

#define FGPIO1PIN_P32_PUT(v)            ( FM_FASTIO->FPDOR3_f.P2=(v) )

#define FGPIO1PIN_P32_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P32_INITIN(v) \
                                                           : FGPIO1PIN_P32_INITOUT(v) )

#define FGPIO1PIN_P32_INITIN(v)         do{ \
                                            bFM_GPIO_PCR3_P2=(v).bPullup; \
                                            bFM_GPIO_DDR3_P2=0u; \
                                            bFM_GPIO_PFR3_P2=0u; }while(0u)

#define FGPIO1PIN_P32_INITOUT(v)        do{ \
                                            FM_FASTIO->FPDOR3_f.P2=(v).bInitVal; \
                                            FM_GPIO->FPOER3_f.P2=1u; \
                                            bFM_GPIO_DDR3_P2=1u; \
                                            bFM_GPIO_PFR3_P2=0u; }while(0u)

/*---- Fast GPIO bit NP32 ----*/
#define FGPIO1PIN_NP32_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR3_f.P2)) )

#define FGPIO1PIN_NP32_PUT(v)           ( FM_FASTIO->FPDOR3_f.P2=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP32_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP32_INITIN(v) \
                                                           : FGPIO1PIN_NP32_INITOUT(v) )

#define FGPIO1PIN_NP32_INITIN(v)        do{ \
                                            bFM_GPIO_PCR3_P2=(v).bPullup; \
                                            bFM_GPIO_DDR3_P2=0u; \
                                            bFM_GPIO_PFR3_P2=0u; }while(0u)

#define FGPIO1PIN_NP32_INITOUT(v)       do{ \
                                            FM_FASTIO->FPDOR3_f.P2=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER3_f.P2=1u; \
                                            bFM_GPIO_DDR3_P2=1u; \
                                            bFM_GPIO_PFR3_P2=0u; }while(0u)

/*---- Fast GPIO bit P33 ----*/
#define FGPIO1PIN_P33_GET               ( FM_FASTIO->FPDIR3_f.P3 )

#define FGPIO1PIN_P33_PUT(v)            ( FM_FASTIO->FPDOR3_f.P3=(v) )

#define FGPIO1PIN_P33_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P33_INITIN(v) \
                                                           : FGPIO1PIN_P33_INITOUT(v) )

#define FGPIO1PIN_P33_INITIN(v)         do{ \
                                            bFM_GPIO_PCR3_P3=(v).bPullup; \
                                            bFM_GPIO_DDR3_P3=0u; \
                                            bFM_GPIO_PFR3_P3=0u; }while(0u)

#define FGPIO1PIN_P33_INITOUT(v)        do{ \
                                            FM_FASTIO->FPDOR3_f.P3=(v).bInitVal; \
                                            FM_GPIO->FPOER3_f.P3=1u; \
                                            bFM_GPIO_DDR3_P3=1u; \
                                            bFM_GPIO_PFR3_P3=0u; }while(0u)

/*---- Fast GPIO bit NP33 ----*/
#define FGPIO1PIN_NP33_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR3_f.P3)) )

#define FGPIO1PIN_NP33_PUT(v)           ( FM_FASTIO->FPDOR3_f.P3=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP33_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP33_INITIN(v) \
                                                           : FGPIO1PIN_NP33_INITOUT(v) )

#define FGPIO1PIN_NP33_INITIN(v)        do{ \
                                            bFM_GPIO_PCR3_P3=(v).bPullup; \
                                            bFM_GPIO_DDR3_P3=0u; \
                                            bFM_GPIO_PFR3_P3=0u; }while(0u)

#define FGPIO1PIN_NP33_INITOUT(v)       do{ \
                                            FM_FASTIO->FPDOR3_f.P3=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER3_f.P3=1u; \
                                            bFM_GPIO_DDR3_P3=1u; \
                                            bFM_GPIO_PFR3_P3=0u; }while(0u)

/*---- Fast GPIO bit P34 ----*/
#define FGPIO1PIN_P34_GET               ( FM_FASTIO->FPDIR3_f.P4 )

#define FGPIO1PIN_P34_PUT(v)            ( FM_FASTIO->FPDOR3_f.P4=(v) )

#define FGPIO1PIN_P34_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P34_INITIN(v) \
                                                           : FGPIO1PIN_P34_INITOUT(v) )

#define FGPIO1PIN_P34_INITIN(v)         do{ \
                                            bFM_GPIO_PCR3_P4=(v).bPullup; \
                                            bFM_GPIO_DDR3_P4=0u; \
                                            bFM_GPIO_PFR3_P4=0u; }while(0u)

#define FGPIO1PIN_P34_INITOUT(v)        do{ \
                                            FM_FASTIO->FPDOR3_f.P4=(v).bInitVal; \
                                            FM_GPIO->FPOER3_f.P4=1u; \
                                            bFM_GPIO_DDR3_P4=1u; \
                                            bFM_GPIO_PFR3_P4=0u; }while(0u)

/*---- Fast GPIO bit NP34 ----*/
#define FGPIO1PIN_NP34_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR3_f.P4)) )

#define FGPIO1PIN_NP34_PUT(v)           ( FM_FASTIO->FPDOR3_f.P4=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP34_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP34_INITIN(v) \
                                                           : FGPIO1PIN_NP34_INITOUT(v) )

#define FGPIO1PIN_NP34_INITIN(v)        do{ \
                                            bFM_GPIO_PCR3_P4=(v).bPullup; \
                                            bFM_GPIO_DDR3_P4=0u; \
                                            bFM_GPIO_PFR3_P4=0u; }while(0u)

#define FGPIO1PIN_NP34_INITOUT(v)       do{ \
                                            FM_FASTIO->FPDOR3_f.P4=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER3_f.P4=1u; \
                                            bFM_GPIO_DDR3_P4=1u; \
                                            bFM_GPIO_PFR3_P4=0u; }while(0u)

/*---- Fast GPIO bit P3A ----*/
#define FGPIO1PIN_P3A_GET               ( FM_FASTIO->FPDIR3_f.PA )

#define FGPIO1PIN_P3A_PUT(v)            ( FM_FASTIO->FPDOR3_f.PA=(v) )

#define FGPIO1PIN_P3A_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P3A_INITIN(v) \
                                                           : FGPIO1PIN_P3A_INITOUT(v) )

#define FGPIO1PIN_P3A_INITIN(v)         do{ \
                                            bFM_GPIO_PCR3_PA=(v).bPullup; \
                                            bFM_GPIO_DDR3_PA=0u; \
                                            bFM_GPIO_PFR3_PA=0u; }while(0u)

#define FGPIO1PIN_P3A_INITOUT(v)        do{ \
                                            FM_FASTIO->FPDOR3_f.PA=(v).bInitVal; \
                                            FM_GPIO->FPOER3_f.PA=1u; \
                                            bFM_GPIO_DDR3_PA=1u; \
                                            bFM_GPIO_PFR3_PA=0u; }while(0u)

/*---- Fast GPIO bit NP3A ----*/
#define FGPIO1PIN_NP3A_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR3_f.PA)) )

#define FGPIO1PIN_NP3A_PUT(v)           ( FM_FASTIO->FPDOR3_f.PA=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP3A_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP3A_INITIN(v) \
                                                           : FGPIO1PIN_NP3A_INITOUT(v) )

#define FGPIO1PIN_NP3A_INITIN(v)        do{ \
                                            bFM_GPIO_PCR3_PA=(v).bPullup; \
                                            bFM_GPIO_DDR3_PA=0u; \
                                            bFM_GPIO_PFR3_PA=0u; }while(0u)

#define FGPIO1PIN_NP3A_INITOUT(v)       do{ \
                                            FM_FASTIO->FPDOR3_f.PA=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER3_f.PA=1u; \
                                            bFM_GPIO_DDR3_PA=1u; \
                                            bFM_GPIO_PFR3_PA=0u; }while(0u)

/*---- Fast GPIO bit P3B ----*/
#define FGPIO1PIN_P3B_GET               ( FM_FASTIO->FPDIR3_f.PB )

#define FGPIO1PIN_P3B_PUT(v)            ( FM_FASTIO->FPDOR3_f.PB=(v) )

#define FGPIO1PIN_P3B_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P3B_INITIN(v) \
                                                           : FGPIO1PIN_P3B_INITOUT(v) )

#define FGPIO1PIN_P3B_INITIN(v)         do{ \
                                            bFM_GPIO_PCR3_PB=(v).bPullup; \
                                            bFM_GPIO_DDR3_PB=0u; \
                                            bFM_GPIO_PFR3_PB=0u; }while(0u)

#define FGPIO1PIN_P3B_INITOUT(v)        do{ \
                                            FM_FASTIO->FPDOR3_f.PB=(v).bInitVal; \
                                            FM_GPIO->FPOER3_f.PB=1u; \
                                            bFM_GPIO_DDR3_PB=1u; \
                                            bFM_GPIO_PFR3_PB=0u; }while(0u)

/*---- Fast GPIO bit NP3B ----*/
#define FGPIO1PIN_NP3B_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR3_f.PB)) )

#define FGPIO1PIN_NP3B_PUT(v)           ( FM_FASTIO->FPDOR3_f.PB=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP3B_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP3B_INITIN(v) \
                                                           : FGPIO1PIN_NP3B_INITOUT(v) )

#define FGPIO1PIN_NP3B_INITIN(v)        do{ \
                                            bFM_GPIO_PCR3_PB=(v).bPullup; \
                                            bFM_GPIO_DDR3_PB=0u; \
                                            bFM_GPIO_PFR3_PB=0u; }while(0u)

#define FGPIO1PIN_NP3B_INITOUT(v)       do{ \
                                            FM_FASTIO->FPDOR3_f.PB=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER3_f.PB=1u; \
                                            bFM_GPIO_DDR3_PB=1u; \
                                            bFM_GPIO_PFR3_PB=0u; }while(0u)

/*---- Fast GPIO bit P3C ----*/
#define FGPIO1PIN_P3C_GET               ( FM_FASTIO->FPDIR3_f.PC )

#define FGPIO1PIN_P3C_PUT(v)            ( FM_FASTIO->FPDOR3_f.PC=(v) )

#define FGPIO1PIN_P3C_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P3C_INITIN(v) \
                                                           : FGPIO1PIN_P3C_INITOUT(v) )

#define FGPIO1PIN_P3C_INITIN(v)         do{ \
                                            bFM_GPIO_PCR3_PC=(v).bPullup; \
                                            bFM_GPIO_DDR3_PC=0u; \
                                            bFM_GPIO_PFR3_PC=0u; }while(0u)

#define FGPIO1PIN_P3C_INITOUT(v)        do{ \
                                            FM_FASTIO->FPDOR3_f.PC=(v).bInitVal; \
                                            FM_GPIO->FPOER3_f.PC=1u; \
                                            bFM_GPIO_DDR3_PC=1u; \
                                            bFM_GPIO_PFR3_PC=0u; }while(0u)

/*---- Fast GPIO bit NP3C ----*/
#define FGPIO1PIN_NP3C_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR3_f.PC)) )

#define FGPIO1PIN_NP3C_PUT(v)           ( FM_FASTIO->FPDOR3_f.PC=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP3C_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP3C_INITIN(v) \
                                                           : FGPIO1PIN_NP3C_INITOUT(v) )

#define FGPIO1PIN_NP3C_INITIN(v)        do{ \
                                            bFM_GPIO_PCR3_PC=(v).bPullup; \
                                            bFM_GPIO_DDR3_PC=0u; \
                                            bFM_GPIO_PFR3_PC=0u; }while(0u)

#define FGPIO1PIN_NP3C_INITOUT(v)       do{ \
                                            FM_FASTIO->FPDOR3_f.PC=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER3_f.PC=1u; \
                                            bFM_GPIO_DDR3_PC=1u; \
                                            bFM_GPIO_PFR3_PC=0u; }while(0u)

/*---- Fast GPIO bit P46 ----*/
#define FGPIO1PIN_P46_GET               ( FM_FASTIO->FPDIR4_f.P6 )

#define FGPIO1PIN_P46_PUT(v)            ( FM_FASTIO->FPDOR4_f.P6=(v) )

#define FGPIO1PIN_P46_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P46_INITIN(v) \
                                                           : FGPIO1PIN_P46_INITOUT(v) )

#define FGPIO1PIN_P46_INITIN(v)         do{ \
                                            PINCONFIG_SET_REG(FM_DS->SUBOSC_CTL, 0u, 2u, 0u); \
                                            bFM_GPIO_PCR4_P6=(v).bPullup; \
                                            bFM_GPIO_DDR4_P6=0u; \
                                            bFM_GPIO_PFR4_P6=0u; }while(0u)

#define FGPIO1PIN_P46_INITOUT(v)        do{ \
                                            PINCONFIG_SET_REG(FM_DS->SUBOSC_CTL, 0u, 2u, 0u); \
                                            FM_FASTIO->FPDOR4_f.P6=(v).bInitVal; \
                                            FM_GPIO->FPOER4_f.P6=1u; \
                                            bFM_GPIO_DDR4_P6=1u; \
                                            bFM_GPIO_PFR4_P6=0u; }while(0u)

/*---- Fast GPIO bit NP46 ----*/
#define FGPIO1PIN_NP46_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR4_f.P6)) )

#define FGPIO1PIN_NP46_PUT(v)           ( FM_FASTIO->FPDOR4_f.P6=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP46_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP46_INITIN(v) \
                                                           : FGPIO1PIN_NP46_INITOUT(v) )

#define FGPIO1PIN_NP46_INITIN(v)        do{ \
                                            PINCONFIG_SET_REG(FM_DS->SUBOSC_CTL, 0u, 2u, 0u); \
                                            bFM_GPIO_PCR4_P6=(v).bPullup; \
                                            bFM_GPIO_DDR4_P6=0u; \
                                            bFM_GPIO_PFR4_P6=0u; }while(0u)

#define FGPIO1PIN_NP46_INITOUT(v)       do{ \
                                            PINCONFIG_SET_REG(FM_DS->SUBOSC_CTL, 0u, 2u, 0u); \
                                            FM_FASTIO->FPDOR4_f.P6=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER4_f.P6=1u; \
                                            bFM_GPIO_DDR4_P6=1u; \
                                            bFM_GPIO_PFR4_P6=0u; }while(0u)

/*---- Fast GPIO bit P47 ----*/
#define FGPIO1PIN_P47_GET               ( FM_FASTIO->FPDIR4_f.P7 )

#define FGPIO1PIN_P47_PUT(v)            ( FM_FASTIO->FPDOR4_f.P7=(v) )

#define FGPIO1PIN_P47_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P47_INITIN(v) \
                                                           : FGPIO1PIN_P47_INITOUT(v) )

#define FGPIO1PIN_P47_INITIN(v)         do{ \
                                            PINCONFIG_SET_REG(FM_DS->SUBOSC_CTL, 0u, 2u, 0u); \
                                            bFM_GPIO_PCR4_P7=(v).bPullup; \
                                            bFM_GPIO_DDR4_P7=0u; \
                                            bFM_GPIO_PFR4_P7=0u; }while(0u)

#define FGPIO1PIN_P47_INITOUT(v)        do{ \
                                            PINCONFIG_SET_REG(FM_DS->SUBOSC_CTL, 0u, 2u, 0u); \
                                            FM_FASTIO->FPDOR4_f.P7=(v).bInitVal; \
                                            FM_GPIO->FPOER4_f.P7=1u; \
                                            bFM_GPIO_DDR4_P7=1u; \
                                            bFM_GPIO_PFR4_P7=0u; }while(0u)

/*---- Fast GPIO bit NP47 ----*/
#define FGPIO1PIN_NP47_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR4_f.P7)) )

#define FGPIO1PIN_NP47_PUT(v)           ( FM_FASTIO->FPDOR4_f.P7=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP47_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP47_INITIN(v) \
                                                           : FGPIO1PIN_NP47_INITOUT(v) )

#define FGPIO1PIN_NP47_INITIN(v)        do{ \
                                            PINCONFIG_SET_REG(FM_DS->SUBOSC_CTL, 0u, 2u, 0u); \
                                            bFM_GPIO_PCR4_P7=(v).bPullup; \
                                            bFM_GPIO_DDR4_P7=0u; \
                                            bFM_GPIO_PFR4_P7=0u; }while(0u)

#define FGPIO1PIN_NP47_INITOUT(v)       do{ \
                                            PINCONFIG_SET_REG(FM_DS->SUBOSC_CTL, 0u, 2u, 0u); \
                                            FM_FASTIO->FPDOR4_f.P7=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER4_f.P7=1u; \
                                            bFM_GPIO_DDR4_P7=1u; \
                                            bFM_GPIO_PFR4_P7=0u; }while(0u)

/*---- Fast GPIO bit P4C ----*/
#define FGPIO1PIN_P4C_GET               ( FM_FASTIO->FPDIR4_f.PC )

#define FGPIO1PIN_P4C_PUT(v)            ( FM_FASTIO->FPDOR4_f.PC=(v) )

#define FGPIO1PIN_P4C_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P4C_INITIN(v) \
                                                           : FGPIO1PIN_P4C_INITOUT(v) )

#define FGPIO1PIN_P4C_INITIN(v)         do{ \
                                            bFM_GPIO_PCR4_PC=(v).bPullup; \
                                            bFM_GPIO_DDR4_PC=0u; \
                                            bFM_GPIO_PFR4_PC=0u; }while(0u)

#define FGPIO1PIN_P4C_INITOUT(v)        do{ \
                                            FM_FASTIO->FPDOR4_f.PC=(v).bInitVal; \
                                            FM_GPIO->FPOER4_f.PC=1u; \
                                            bFM_GPIO_DDR4_PC=1u; \
                                            bFM_GPIO_PFR4_PC=0u; }while(0u)

/*---- Fast GPIO bit NP4C ----*/
#define FGPIO1PIN_NP4C_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR4_f.PC)) )

#define FGPIO1PIN_NP4C_PUT(v)           ( FM_FASTIO->FPDOR4_f.PC=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP4C_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP4C_INITIN(v) \
                                                           : FGPIO1PIN_NP4C_INITOUT(v) )

#define FGPIO1PIN_NP4C_INITIN(v)        do{ \
                                            bFM_GPIO_PCR4_PC=(v).bPullup; \
                                            bFM_GPIO_DDR4_PC=0u; \
                                            bFM_GPIO_PFR4_PC=0u; }while(0u)

#define FGPIO1PIN_NP4C_INITOUT(v)       do{ \
                                            FM_FASTIO->FPDOR4_f.PC=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER4_f.PC=1u; \
                                            bFM_GPIO_DDR4_PC=1u; \
                                            bFM_GPIO_PFR4_PC=0u; }while(0u)

/*---- Fast GPIO bit P4D ----*/
#define FGPIO1PIN_P4D_GET               ( FM_FASTIO->FPDIR4_f.PD )

#define FGPIO1PIN_P4D_PUT(v)            ( FM_FASTIO->FPDOR4_f.PD=(v) )

#define FGPIO1PIN_P4D_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P4D_INITIN(v) \
                                                           : FGPIO1PIN_P4D_INITOUT(v) )

#define FGPIO1PIN_P4D_INITIN(v)         do{ \
                                            bFM_GPIO_PCR4_PD=(v).bPullup; \
                                            bFM_GPIO_DDR4_PD=0u; \
                                            bFM_GPIO_PFR4_PD=0u; }while(0u)

#define FGPIO1PIN_P4D_INITOUT(v)        do{ \
                                            FM_FASTIO->FPDOR4_f.PD=(v).bInitVal; \
                                            FM_GPIO->FPOER4_f.PD=1u; \
                                            bFM_GPIO_DDR4_PD=1u; \
                                            bFM_GPIO_PFR4_PD=0u; }while(0u)

/*---- Fast GPIO bit NP4D ----*/
#define FGPIO1PIN_NP4D_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR4_f.PD)) )

#define FGPIO1PIN_NP4D_PUT(v)           ( FM_FASTIO->FPDOR4_f.PD=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP4D_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP4D_INITIN(v) \
                                                           : FGPIO1PIN_NP4D_INITOUT(v) )

#define FGPIO1PIN_NP4D_INITIN(v)        do{ \
                                            bFM_GPIO_PCR4_PD=(v).bPullup; \
                                            bFM_GPIO_DDR4_PD=0u; \
                                            bFM_GPIO_PFR4_PD=0u; }while(0u)

#define FGPIO1PIN_NP4D_INITOUT(v)       do{ \
                                            FM_FASTIO->FPDOR4_f.PD=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER4_f.PD=1u; \
                                            bFM_GPIO_DDR4_PD=1u; \
                                            bFM_GPIO_PFR4_PD=0u; }while(0u)

/*---- Fast GPIO bit P4E ----*/
#define FGPIO1PIN_P4E_GET               ( FM_FASTIO->FPDIR4_f.PE )

#define FGPIO1PIN_P4E_PUT(v)            ( FM_FASTIO->FPDOR4_f.PE=(v) )

#define FGPIO1PIN_P4E_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P4E_INITIN(v) \
                                                           : FGPIO1PIN_P4E_INITOUT(v) )

#define FGPIO1PIN_P4E_INITIN(v)         do{ \
                                            bFM_GPIO_PCR4_PE=(v).bPullup; \
                                            bFM_GPIO_DDR4_PE=0u; \
                                            bFM_GPIO_PFR4_PE=0u; }while(0u)

#define FGPIO1PIN_P4E_INITOUT(v)        do{ \
                                            FM_FASTIO->FPDOR4_f.PE=(v).bInitVal; \
                                            FM_GPIO->FPOER4_f.PE=1u; \
                                            bFM_GPIO_DDR4_PE=1u; \
                                            bFM_GPIO_PFR4_PE=0u; }while(0u)

/*---- Fast GPIO bit NP4E ----*/
#define FGPIO1PIN_NP4E_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR4_f.PE)) )

#define FGPIO1PIN_NP4E_PUT(v)           ( FM_FASTIO->FPDOR4_f.PE=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP4E_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP4E_INITIN(v) \
                                                           : FGPIO1PIN_NP4E_INITOUT(v) )

#define FGPIO1PIN_NP4E_INITIN(v)        do{ \
                                            bFM_GPIO_PCR4_PE=(v).bPullup; \
                                            bFM_GPIO_DDR4_PE=0u; \
                                            bFM_GPIO_PFR4_PE=0u; }while(0u)

#define FGPIO1PIN_NP4E_INITOUT(v)       do{ \
                                            FM_FASTIO->FPDOR4_f.PE=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER4_f.PE=1u; \
                                            bFM_GPIO_DDR4_PE=1u; \
                                            bFM_GPIO_PFR4_PE=0u; }while(0u)

/*---- Fast GPIO bit P50 ----*/
#define FGPIO1PIN_P50_GET               ( FM_FASTIO->FPDIR5_f.P0 )

#define FGPIO1PIN_P50_PUT(v)            ( FM_FASTIO->FPDOR5_f.P0=(v) )

#define FGPIO1PIN_P50_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P50_INITIN(v) \
                                                           : FGPIO1PIN_P50_INITOUT(v) )

#define FGPIO1PIN_P50_INITIN(v)         do{ \
                                            bFM_GPIO_PCR5_P0=(v).bPullup; \
                                            bFM_GPIO_DDR5_P0=0u; \
                                            bFM_GPIO_PFR5_P0=0u; }while(0u)

#define FGPIO1PIN_P50_INITOUT(v)        do{ \
                                            FM_FASTIO->FPDOR5_f.P0=(v).bInitVal; \
                                            FM_GPIO->FPOER5_f.P0=1u; \
                                            bFM_GPIO_DDR5_P0=1u; \
                                            bFM_GPIO_PFR5_P0=0u; }while(0u)

/*---- Fast GPIO bit NP50 ----*/
#define FGPIO1PIN_NP50_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR5_f.P0)) )

#define FGPIO1PIN_NP50_PUT(v)           ( FM_FASTIO->FPDOR5_f.P0=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP50_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP50_INITIN(v) \
                                                           : FGPIO1PIN_NP50_INITOUT(v) )

#define FGPIO1PIN_NP50_INITIN(v)        do{ \
                                            bFM_GPIO_PCR5_P0=(v).bPullup; \
                                            bFM_GPIO_DDR5_P0=0u; \
                                            bFM_GPIO_PFR5_P0=0u; }while(0u)

#define FGPIO1PIN_NP50_INITOUT(v)       do{ \
                                            FM_FASTIO->FPDOR5_f.P0=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER5_f.P0=1u; \
                                            bFM_GPIO_DDR5_P0=1u; \
                                            bFM_GPIO_PFR5_P0=0u; }while(0u)

/*---- Fast GPIO bit P51 ----*/
#define FGPIO1PIN_P51_GET               ( FM_FASTIO->FPDIR5_f.P1 )

#define FGPIO1PIN_P51_PUT(v)            ( FM_FASTIO->FPDOR5_f.P1=(v) )

#define FGPIO1PIN_P51_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P51_INITIN(v) \
                                                           : FGPIO1PIN_P51_INITOUT(v) )

#define FGPIO1PIN_P51_INITIN(v)         do{ \
                                            bFM_GPIO_PCR5_P1=(v).bPullup; \
                                            bFM_GPIO_DDR5_P1=0u; \
                                            bFM_GPIO_PFR5_P1=0u; }while(0u)

#define FGPIO1PIN_P51_INITOUT(v)        do{ \
                                            FM_FASTIO->FPDOR5_f.P1=(v).bInitVal; \
                                            FM_GPIO->FPOER5_f.P1=1u; \
                                            bFM_GPIO_DDR5_P1=1u; \
                                            bFM_GPIO_PFR5_P1=0u; }while(0u)

/*---- Fast GPIO bit NP51 ----*/
#define FGPIO1PIN_NP51_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR5_f.P1)) )

#define FGPIO1PIN_NP51_PUT(v)           ( FM_FASTIO->FPDOR5_f.P1=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP51_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP51_INITIN(v) \
                                                           : FGPIO1PIN_NP51_INITOUT(v) )

#define FGPIO1PIN_NP51_INITIN(v)        do{ \
                                            bFM_GPIO_PCR5_P1=(v).bPullup; \
                                            bFM_GPIO_DDR5_P1=0u; \
                                            bFM_GPIO_PFR5_P1=0u; }while(0u)

#define FGPIO1PIN_NP51_INITOUT(v)       do{ \
                                            FM_FASTIO->FPDOR5_f.P1=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER5_f.P1=1u; \
                                            bFM_GPIO_DDR5_P1=1u; \
                                            bFM_GPIO_PFR5_P1=0u; }while(0u)

/*---- Fast GPIO bit P52 ----*/
#define FGPIO1PIN_P52_GET               ( FM_FASTIO->FPDIR5_f.P2 )

#define FGPIO1PIN_P52_PUT(v)            ( FM_FASTIO->FPDOR5_f.P2=(v) )

#define FGPIO1PIN_P52_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P52_INITIN(v) \
                                                           : FGPIO1PIN_P52_INITOUT(v) )

#define FGPIO1PIN_P52_INITIN(v)         do{ \
                                            bFM_GPIO_PCR5_P2=(v).bPullup; \
                                            bFM_GPIO_DDR5_P2=0u; \
                                            bFM_GPIO_PFR5_P2=0u; }while(0u)

#define FGPIO1PIN_P52_INITOUT(v)        do{ \
                                            FM_FASTIO->FPDOR5_f.P2=(v).bInitVal; \
                                            FM_GPIO->FPOER5_f.P2=1u; \
                                            bFM_GPIO_DDR5_P2=1u; \
                                            bFM_GPIO_PFR5_P2=0u; }while(0u)

/*---- Fast GPIO bit NP52 ----*/
#define FGPIO1PIN_NP52_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR5_f.P2)) )

#define FGPIO1PIN_NP52_PUT(v)           ( FM_FASTIO->FPDOR5_f.P2=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP52_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP52_INITIN(v) \
                                                           : FGPIO1PIN_NP52_INITOUT(v) )

#define FGPIO1PIN_NP52_INITIN(v)        do{ \
                                            bFM_GPIO_PCR5_P2=(v).bPullup; \
                                            bFM_GPIO_DDR5_P2=0u; \
                                            bFM_GPIO_PFR5_P2=0u; }while(0u)

#define FGPIO1PIN_NP52_INITOUT(v)       do{ \
                                            FM_FASTIO->FPDOR5_f.P2=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER5_f.P2=1u; \
                                            bFM_GPIO_DDR5_P2=1u; \
                                            bFM_GPIO_PFR5_P2=0u; }while(0u)

/*---- Fast GPIO bit P53 ----*/
#define FGPIO1PIN_P53_GET               ( FM_FASTIO->FPDIR5_f.P3 )

#define FGPIO1PIN_P53_PUT(v)            ( FM_FASTIO->FPDOR5_f.P3=(v) )

#define FGPIO1PIN_P53_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P53_INITIN(v) \
                                                           : FGPIO1PIN_P53_INITOUT(v) )

#define FGPIO1PIN_P53_INITIN(v)         do{ \
                                            bFM_GPIO_PCR5_P3=(v).bPullup; \
                                            bFM_GPIO_DDR5_P3=0u; \
                                            bFM_GPIO_PFR5_P3=0u; }while(0u)

#define FGPIO1PIN_P53_INITOUT(v)        do{ \
                                            FM_FASTIO->FPDOR5_f.P3=(v).bInitVal; \
                                            FM_GPIO->FPOER5_f.P3=1u; \
                                            bFM_GPIO_DDR5_P3=1u; \
                                            bFM_GPIO_PFR5_P3=0u; }while(0u)

/*---- Fast GPIO bit NP53 ----*/
#define FGPIO1PIN_NP53_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR5_f.P3)) )

#define FGPIO1PIN_NP53_PUT(v)           ( FM_FASTIO->FPDOR5_f.P3=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP53_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP53_INITIN(v) \
                                                           : FGPIO1PIN_NP53_INITOUT(v) )

#define FGPIO1PIN_NP53_INITIN(v)        do{ \
                                            bFM_GPIO_PCR5_P3=(v).bPullup; \
                                            bFM_GPIO_DDR5_P3=0u; \
                                            bFM_GPIO_PFR5_P3=0u; }while(0u)

#define FGPIO1PIN_NP53_INITOUT(v)       do{ \
                                            FM_FASTIO->FPDOR5_f.P3=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER5_f.P3=1u; \
                                            bFM_GPIO_DDR5_P3=1u; \
                                            bFM_GPIO_PFR5_P3=0u; }while(0u)

/*---- Fast GPIO bit P60 ----*/
#define FGPIO1PIN_P60_GET               ( FM_FASTIO->FPDIR6_f.P0 )

#define FGPIO1PIN_P60_PUT(v)            ( FM_FASTIO->FPDOR6_f.P0=(v) )

#define FGPIO1PIN_P60_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P60_INITIN(v) \
                                                           : FGPIO1PIN_P60_INITOUT(v) )

#define FGPIO1PIN_P60_INITIN(v)         do{ \
                                            PINCONFIG_SET_REG(FM_DS->CEC_CTL, 2u, 2u, 0u); \
                                            bFM_GPIO_PCR6_P0=(v).bPullup; \
                                            bFM_GPIO_DDR6_P0=0u; \
                                            bFM_GPIO_PFR6_P0=0u; }while(0u)

#define FGPIO1PIN_P60_INITOUT(v)        do{ \
                                            PINCONFIG_SET_REG(FM_DS->CEC_CTL, 2u, 2u, 0u); \
                                            FM_FASTIO->FPDOR6_f.P0=(v).bInitVal; \
                                            FM_GPIO->FPOER6_f.P0=1u; \
                                            bFM_GPIO_DDR6_P0=1u; \
                                            bFM_GPIO_PFR6_P0=0u; }while(0u)

/*---- Fast GPIO bit NP60 ----*/
#define FGPIO1PIN_NP60_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR6_f.P0)) )

#define FGPIO1PIN_NP60_PUT(v)           ( FM_FASTIO->FPDOR6_f.P0=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP60_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP60_INITIN(v) \
                                                           : FGPIO1PIN_NP60_INITOUT(v) )

#define FGPIO1PIN_NP60_INITIN(v)        do{ \
                                            PINCONFIG_SET_REG(FM_DS->CEC_CTL, 2u, 2u, 0u); \
                                            bFM_GPIO_PCR6_P0=(v).bPullup; \
                                            bFM_GPIO_DDR6_P0=0u; \
                                            bFM_GPIO_PFR6_P0=0u; }while(0u)

#define FGPIO1PIN_NP60_INITOUT(v)       do{ \
                                            PINCONFIG_SET_REG(FM_DS->CEC_CTL, 2u, 2u, 0u); \
                                            FM_FASTIO->FPDOR6_f.P0=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER6_f.P0=1u; \
                                            bFM_GPIO_DDR6_P0=1u; \
                                            bFM_GPIO_PFR6_P0=0u; }while(0u)

/*---- Fast GPIO bit P61 ----*/
#define FGPIO1PIN_P61_GET               ( FM_FASTIO->FPDIR6_f.P1 )

#define FGPIO1PIN_P61_PUT(v)            ( FM_FASTIO->FPDOR6_f.P1=(v) )

#define FGPIO1PIN_P61_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P61_INITIN(v) \
                                                           : FGPIO1PIN_P61_INITOUT(v) )

#define FGPIO1PIN_P61_INITIN(v)         do{ \
                                            bFM_GPIO_PCR6_P1=(v).bPullup; \
                                            bFM_GPIO_DDR6_P1=0u; \
                                            bFM_GPIO_PFR6_P1=0u; }while(0u)

#define FGPIO1PIN_P61_INITOUT(v)        do{ \
                                            FM_FASTIO->FPDOR6_f.P1=(v).bInitVal; \
                                            FM_GPIO->FPOER6_f.P1=1u; \
                                            bFM_GPIO_DDR6_P1=1u; \
                                            bFM_GPIO_PFR6_P1=0u; }while(0u)

/*---- Fast GPIO bit NP61 ----*/
#define FGPIO1PIN_NP61_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR6_f.P1)) )

#define FGPIO1PIN_NP61_PUT(v)           ( FM_FASTIO->FPDOR6_f.P1=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP61_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP61_INITIN(v) \
                                                           : FGPIO1PIN_NP61_INITOUT(v) )

#define FGPIO1PIN_NP61_INITIN(v)        do{ \
                                            bFM_GPIO_PCR6_P1=(v).bPullup; \
                                            bFM_GPIO_DDR6_P1=0u; \
                                            bFM_GPIO_PFR6_P1=0u; }while(0u)

#define FGPIO1PIN_NP61_INITOUT(v)       do{ \
                                            FM_FASTIO->FPDOR6_f.P1=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER6_f.P1=1u; \
                                            bFM_GPIO_DDR6_P1=1u; \
                                            bFM_GPIO_PFR6_P1=0u; }while(0u)

/*---- Fast GPIO bit P80 ----*/
#define FGPIO1PIN_P80_GET               ( FM_FASTIO->FPDIR8_f.P0 )

#define FGPIO1PIN_P80_PUT(v)            ( FM_FASTIO->FPDOR8_f.P0=(v) )

#define FGPIO1PIN_P80_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P80_INITIN(v) \
                                                           : FGPIO1PIN_P80_INITOUT(v) )

#define FGPIO1PIN_P80_INITIN(v)         do{ \
                                            bFM_GPIO_SPSR_USB0C=0u; \
                                            bFM_GPIO_DDR8_P0=0u; \
                                            bFM_GPIO_PFR8_P0=0u; }while(0u)

#define FGPIO1PIN_P80_INITOUT(v)        do{ \
                                            bFM_GPIO_SPSR_USB0C=0u; \
                                            FM_FASTIO->FPDOR8_f.P0=(v).bInitVal; \
                                            FM_GPIO->FPOER8_f.P0=1u; \
                                            bFM_GPIO_DDR8_P0=1u; \
                                            bFM_GPIO_PFR8_P0=0u; }while(0u)

/*---- Fast GPIO bit NP80 ----*/
#define FGPIO1PIN_NP80_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR8_f.P0)) )

#define FGPIO1PIN_NP80_PUT(v)           ( FM_FASTIO->FPDOR8_f.P0=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP80_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP80_INITIN(v) \
                                                           : FGPIO1PIN_NP80_INITOUT(v) )

#define FGPIO1PIN_NP80_INITIN(v)        do{ \
                                            bFM_GPIO_SPSR_USB0C=0u; \
                                            bFM_GPIO_DDR8_P0=0u; \
                                            bFM_GPIO_PFR8_P0=0u; }while(0u)

#define FGPIO1PIN_NP80_INITOUT(v)       do{ \
                                            bFM_GPIO_SPSR_USB0C=0u; \
                                            FM_FASTIO->FPDOR8_f.P0=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER8_f.P0=1u; \
                                            bFM_GPIO_DDR8_P0=1u; \
                                            bFM_GPIO_PFR8_P0=0u; }while(0u)

/*---- Fast GPIO bit P81 ----*/
#define FGPIO1PIN_P81_GET               ( FM_FASTIO->FPDIR8_f.P1 )

#define FGPIO1PIN_P81_PUT(v)            ( FM_FASTIO->FPDOR8_f.P1=(v) )

#define FGPIO1PIN_P81_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_P81_INITIN(v) \
                                                           : FGPIO1PIN_P81_INITOUT(v) )

#define FGPIO1PIN_P81_INITIN(v)         do{ \
                                            bFM_GPIO_SPSR_USB0C=0u; \
                                            bFM_GPIO_DDR8_P1=0u; \
                                            bFM_GPIO_PFR8_P1=0u; }while(0u)

#define FGPIO1PIN_P81_INITOUT(v)        do{ \
                                            bFM_GPIO_SPSR_USB0C=0u; \
                                            FM_FASTIO->FPDOR8_f.P1=(v).bInitVal; \
                                            FM_GPIO->FPOER8_f.P1=1u; \
                                            bFM_GPIO_DDR8_P1=1u; \
                                            bFM_GPIO_PFR8_P1=0u; }while(0u)

/*---- Fast GPIO bit NP81 ----*/
#define FGPIO1PIN_NP81_GET              ( (uint8_t)(!(FM_FASTIO->FPDIR8_f.P1)) )

#define FGPIO1PIN_NP81_PUT(v)           ( FM_FASTIO->FPDOR8_f.P1=(uint8_t)(!(v)) )

#define FGPIO1PIN_NP81_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NP81_INITIN(v) \
                                                           : FGPIO1PIN_NP81_INITOUT(v) )

#define FGPIO1PIN_NP81_INITIN(v)        do{ \
                                            bFM_GPIO_SPSR_USB0C=0u; \
                                            bFM_GPIO_DDR8_P1=0u; \
                                            bFM_GPIO_PFR8_P1=0u; }while(0u)

#define FGPIO1PIN_NP81_INITOUT(v)       do{ \
                                            bFM_GPIO_SPSR_USB0C=0u; \
                                            FM_FASTIO->FPDOR8_f.P1=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOER8_f.P1=1u; \
                                            bFM_GPIO_DDR8_P1=1u; \
                                            bFM_GPIO_PFR8_P1=0u; }while(0u)

/*---- Fast GPIO bit PE2 ----*/
#define FGPIO1PIN_PE2_GET               ( FM_FASTIO->FPDIRE_f.P2 )

#define FGPIO1PIN_PE2_PUT(v)            ( FM_FASTIO->FPDORE_f.P2=(v) )

#define FGPIO1PIN_PE2_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_PE2_INITIN(v) \
                                                           : FGPIO1PIN_PE2_INITOUT(v) )

#define FGPIO1PIN_PE2_INITIN(v)         do{ \
                                            PINCONFIG_SET_REG(FM_GPIO->SPSR, 2u, 2u, 0u); \
                                            bFM_GPIO_PCRE_P2=(v).bPullup; \
                                            bFM_GPIO_DDRE_P2=0u; \
                                            bFM_GPIO_PFRE_P2=0u; }while(0u)

#define FGPIO1PIN_PE2_INITOUT(v)        do{ \
                                            PINCONFIG_SET_REG(FM_GPIO->SPSR, 2u, 2u, 0u); \
                                            FM_FASTIO->FPDORE_f.P2=(v).bInitVal; \
                                            FM_GPIO->FPOERE_f.P2=1u; \
                                            bFM_GPIO_DDRE_P2=1u; \
                                            bFM_GPIO_PFRE_P2=0u; }while(0u)

/*---- Fast GPIO bit NPE2 ----*/
#define FGPIO1PIN_NPE2_GET              ( (uint8_t)(!(FM_FASTIO->FPDIRE_f.P2)) )

#define FGPIO1PIN_NPE2_PUT(v)           ( FM_FASTIO->FPDORE_f.P2=(uint8_t)(!(v)) )

#define FGPIO1PIN_NPE2_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NPE2_INITIN(v) \
                                                           : FGPIO1PIN_NPE2_INITOUT(v) )

#define FGPIO1PIN_NPE2_INITIN(v)        do{ \
                                            PINCONFIG_SET_REG(FM_GPIO->SPSR, 2u, 2u, 0u); \
                                            bFM_GPIO_PCRE_P2=(v).bPullup; \
                                            bFM_GPIO_DDRE_P2=0u; \
                                            bFM_GPIO_PFRE_P2=0u; }while(0u)

#define FGPIO1PIN_NPE2_INITOUT(v)       do{ \
                                            PINCONFIG_SET_REG(FM_GPIO->SPSR, 2u, 2u, 0u); \
                                            FM_FASTIO->FPDORE_f.P2=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOERE_f.P2=1u; \
                                            bFM_GPIO_DDRE_P2=1u; \
                                            bFM_GPIO_PFRE_P2=0u; }while(0u)

/*---- Fast GPIO bit PE3 ----*/
#define FGPIO1PIN_PE3_GET               ( FM_FASTIO->FPDIRE_f.P3 )

#define FGPIO1PIN_PE3_PUT(v)            ( FM_FASTIO->FPDORE_f.P3=(v) )

#define FGPIO1PIN_PE3_INIT(v)           ( (0==(v).bOutput) ? FGPIO1PIN_PE3_INITIN(v) \
                                                           : FGPIO1PIN_PE3_INITOUT(v) )

#define FGPIO1PIN_PE3_INITIN(v)         do{ \
                                            PINCONFIG_SET_REG(FM_GPIO->SPSR, 2u, 2u, 0u); \
                                            bFM_GPIO_PCRE_P3=(v).bPullup; \
                                            bFM_GPIO_DDRE_P3=0u; \
                                            bFM_GPIO_PFRE_P3=0u; }while(0u)

#define FGPIO1PIN_PE3_INITOUT(v)        do{ \
                                            PINCONFIG_SET_REG(FM_GPIO->SPSR, 2u, 2u, 0u); \
                                            FM_FASTIO->FPDORE_f.P3=(v).bInitVal; \
                                            FM_GPIO->FPOERE_f.P3=1u; \
                                            bFM_GPIO_DDRE_P3=1u; \
                                            bFM_GPIO_PFRE_P3=0u; }while(0u)

/*---- Fast GPIO bit NPE3 ----*/
#define FGPIO1PIN_NPE3_GET              ( (uint8_t)(!(FM_FASTIO->FPDIRE_f.P3)) )

#define FGPIO1PIN_NPE3_PUT(v)           ( FM_FASTIO->FPDORE_f.P3=(uint8_t)(!(v)) )

#define FGPIO1PIN_NPE3_INIT(v)          ( (0==(v).bOutput) ? FGPIO1PIN_NPE3_INITIN(v) \
                                                           : FGPIO1PIN_NPE3_INITOUT(v) )

#define FGPIO1PIN_NPE3_INITIN(v)        do{ \
                                            PINCONFIG_SET_REG(FM_GPIO->SPSR, 2u, 2u, 0u); \
                                            bFM_GPIO_PCRE_P3=(v).bPullup; \
                                            bFM_GPIO_DDRE_P3=0u; \
                                            bFM_GPIO_PFRE_P3=0u; }while(0u)

#define FGPIO1PIN_NPE3_INITOUT(v)       do{ \
                                            PINCONFIG_SET_REG(FM_GPIO->SPSR, 2u, 2u, 0u); \
                                            FM_FASTIO->FPDORE_f.P3=(uint8_t)(!((uint8_t)(v).bInitVal)); \
                                            FM_GPIO->FPOERE_f.P3=1u; \
                                            bFM_GPIO_DDRE_P3=1u; \
                                            bFM_GPIO_PFRE_P3=0u; }while(0u)

/******************************************************************************
   PIN RELOCATION
*******************************************************************************/

/*--- ADTG_6_ADC0 ---*/
#define SetPinFunc_ADTG_6_ADC0(dummy)   do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR09, 12u, 4u,  7u ); \
                                            bFM_GPIO_PFR3_P3 = 1u; \
                                        }while (0u)

/*--- ADTG_6_ADC1 ---*/
#define SetPinFunc_ADTG_6_ADC1(dummy)   do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR09, 16u, 4u,  7u ); \
                                            bFM_GPIO_PFR3_P3 = 1u; \
                                        }while (0u)

/*--- ADTG_6_ADC2 ---*/
#define SetPinFunc_ADTG_6_ADC2(dummy)   do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR09, 20u, 4u,  7u ); \
                                            bFM_GPIO_PFR3_P3 = 1u; \
                                        }while (0u)

/*--- CEC0_0 ---*/
#define SetPinFunc_CEC0_0(dummy)        do{ \
                                            PINCONFIG_SET_REG(FM_DS->CEC_CTL, 0u, 2u, 1u); \
                                        }while (0u)

/*--- CEC1_0 ---*/
#define SetPinFunc_CEC1_0(dummy)        do{ \
                                            PINCONFIG_SET_REG(FM_DS->CEC_CTL, 2u, 2u, 1u); \
                                        }while (0u)

/*--- CROUT_1 ---*/
#define SetPinFunc_CROUT_1(dummy)       do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR00, 1u, 2u,  2u ); \
                                            bFM_GPIO_PFR0_PF = 1u; \
                                        }while (0u)

/*--- INT00_0 ---*/
#define SetPinFunc_INT00_0(dummy)       do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR06, 0u, 2u,  1u ); \
                                            bFM_GPIO_PFR5_P0 = 1u; \
                                        }while (0u)

/*--- INT00_1 ---*/
#define SetPinFunc_INT00_1(dummy)       do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR06, 0u, 2u,  2u ); \
                                            bFM_GPIO_PFR0_P5 = 1u; \
                                        }while (0u)

/*--- INT01_0 ---*/
#define SetPinFunc_INT01_0(dummy)       do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR06, 2u, 2u,  1u ); \
                                            bFM_GPIO_PFR5_P1 = 1u; \
                                        }while (0u)

/*--- INT02_0 ---*/
#define SetPinFunc_INT02_0(dummy)       do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR06, 4u, 2u,  1u ); \
                                            bFM_GPIO_PFR5_P2 = 1u; \
                                        }while (0u)

/*--- INT02_1 ---*/
#define SetPinFunc_INT02_1(dummy)       do{ \
                                            bFM_GPIO_ADE_AN01=0u; \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR06, 4u, 2u,  2u ); \
                                            bFM_GPIO_PFR1_P1 = 1u; \
                                        }while (0u)

/*--- INT03_0 ---*/
#define SetPinFunc_INT03_0(dummy)       do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR06, 6u, 2u,  1u ); \
                                            bFM_GPIO_PFR3_PA = 1u; \
                                        }while (0u)

/*--- INT03_1 ---*/
#define SetPinFunc_INT03_1(dummy)       do{ \
                                            bFM_GPIO_ADE_AN04=0u; \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR06, 6u, 2u,  2u ); \
                                            bFM_GPIO_PFR1_P4 = 1u; \
                                        }while (0u)

/*--- INT03_2 ---*/
#define SetPinFunc_INT03_2(dummy)       do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR06, 6u, 2u,  3u ); \
                                            bFM_GPIO_PFR3_P0 = 1u; \
                                        }while (0u)

/*--- INT04_0 ---*/
#define SetPinFunc_INT04_0(dummy)       do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR06, 8u, 2u,  1u ); \
                                            bFM_GPIO_PFR3_P3 = 1u; \
                                        }while (0u)

/*--- INT04_2 ---*/
#define SetPinFunc_INT04_2(dummy)       do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR06, 8u, 2u,  3u ); \
                                            bFM_GPIO_PFR3_P1 = 1u; \
                                        }while (0u)

/*--- INT05_1 ---*/
#define SetPinFunc_INT05_1(dummy)       do{ \
                                            PINCONFIG_SET_REG(FM_DS->CEC_CTL, 0u, 2u, 0u); \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR06, 10u, 2u,  2u ); \
                                            bFM_GPIO_PFR1_PA = 1u; \
                                        }while (0u)

/*--- INT05_2 ---*/
#define SetPinFunc_INT05_2(dummy)       do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR06, 10u, 2u,  3u ); \
                                            bFM_GPIO_PFR3_P2 = 1u; \
                                        }while (0u)

/*--- INT06_1 ---*/
#define SetPinFunc_INT06_1(dummy)       do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR06, 12u, 2u,  2u ); \
                                            bFM_GPIO_PFR2_P1 = 1u; \
                                        }while (0u)

/*--- INT06_2 ---*/
#define SetPinFunc_INT06_2(dummy)       do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR06, 12u, 2u,  3u ); \
                                            bFM_GPIO_PFR4_PE = 1u; \
                                        }while (0u)

/*--- INT07_2 ---*/
#define SetPinFunc_INT07_2(dummy)       do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR06, 14u, 2u,  3u ); \
                                            bFM_GPIO_PFR5_P3 = 1u; \
                                        }while (0u)

/*--- INT15_1 ---*/
#define SetPinFunc_INT15_1(dummy)       do{ \
                                            PINCONFIG_SET_REG(FM_DS->CEC_CTL, 2u, 2u, 0u); \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR06, 30u, 2u,  2u ); \
                                            bFM_GPIO_PFR6_P0 = 1u; \
                                        }while (0u)

/*--- MI2SCK6_1 ---*/
#define SetPinFunc_MI2SCK6_1(dummy)     do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR38, 4u, 2u,  2u ); \
                                            bFM_GPIO_PFR3_P1 = 1u; \
                                        }while (0u)

/*--- MI2SDI6_1 ---*/
#define SetPinFunc_MI2SDI6_1(dummy)     do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR38, 8u, 2u,  2u ); \
                                            bFM_GPIO_PFR3_P3 = 1u; \
                                        }while (0u)

/*--- MI2SDO6_1 ---*/
#define SetPinFunc_MI2SDO6_1(dummy)     do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR38, 10u, 2u,  2u ); \
                                            bFM_GPIO_PFR3_P2 = 1u; \
                                        }while (0u)

/*--- MI2SMCK6_1_IN ---*/
#define SetPinFunc_MI2SMCK6_1_IN(dummy) do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR38, 0u, 2u,  2u ); \
                                            bFM_GPIO_PFR3_P4 = 1u; \
                                        }while (0u)

/*--- MI2SMCK6_1_OUT ---*/
#define SetPinFunc_MI2SMCK6_1_OUT(dummy)do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR38, 2u, 2u,  2u ); \
                                            bFM_GPIO_PFR3_P4 = 1u; \
                                        }while (0u)

/*--- MI2SWS6_1 ---*/
#define SetPinFunc_MI2SWS6_1(dummy)     do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR38, 6u, 2u,  2u ); \
                                            bFM_GPIO_PFR3_P0 = 1u; \
                                        }while (0u)

/*--- NMIX ---*/
#define SetPinFunc_NMIX(dummy)          do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR00, 0u, 1u,  1u ); \
                                            bFM_GPIO_PFR0_PF = 1u; \
                                        }while (0u)

/*--- RTCCO_0 ---*/
#define SetPinFunc_RTCCO_0(dummy)       do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR00, 4u, 2u,  1u ); \
                                            bFM_GPIO_PFR0_PF = 1u; \
                                        }while (0u)

/*--- RTCCO_1 ---*/
#define SetPinFunc_RTCCO_1(dummy)       do{ \
                                            bFM_GPIO_ADE_AN03=0u; \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR00, 4u, 2u,  2u ); \
                                            bFM_GPIO_PFR1_P3 = 1u; \
                                        }while (0u)

/*--- RTCCO_2 ---*/
#define SetPinFunc_RTCCO_2(dummy)       do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR00, 4u, 2u,  3u ); \
                                            bFM_GPIO_PFR3_PA = 1u; \
                                        }while (0u)

/*--- SCK0_0 ---*/
#define SetPinFunc_SCK0_0(dummy)        do{ \
                                            bFM_GPIO_ADE_AN06=0u; \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR07, 8u, 2u,  1u ); \
                                            bFM_GPIO_PFR2_P3 = 1u; \
                                        }while (0u)

/*--- SCK1_1 ---*/
#define SetPinFunc_SCK1_1(dummy)        do{ \
                                            bFM_GPIO_ADE_AN03=0u; \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR07, 14u, 2u,  2u ); \
                                            bFM_GPIO_PFR1_P3 = 1u; \
                                        }while (0u)

/*--- SCK3_1 ---*/
#define SetPinFunc_SCK3_1(dummy)        do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR07, 26u, 2u,  2u ); \
                                            bFM_GPIO_PFR5_P2 = 1u; \
                                        }while (0u)

/*--- SCK6_1 ---*/
#define SetPinFunc_SCK6_1(dummy)        do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR08, 20u, 2u,  2u ); \
                                            bFM_GPIO_PFR3_P1 = 1u; \
                                        }while (0u)

/*--- SCK7_1 ---*/
#define SetPinFunc_SCK7_1(dummy)        do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR08, 26u, 2u,  2u ); \
                                            bFM_GPIO_PFR4_PC = 1u; \
                                        }while (0u)

/*--- SCS10_1 ---*/
#define SetPinFunc_SCS10_1(dummy)       do{ \
                                            bFM_GPIO_ADE_AN04=0u; \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR22, 4u, 2u,  2u ); \
                                            bFM_GPIO_PFR1_P4 = 1u; \
                                        }while (0u)

/*--- SCS11_1 ---*/
#define SetPinFunc_SCS11_1(dummy)       do{ \
                                            bFM_GPIO_ADE_AN05=0u; \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR22, 6u, 2u,  2u ); \
                                            bFM_GPIO_PFR1_P5 = 1u; \
                                        }while (0u)

/*--- SCS60_1 ---*/
#define SetPinFunc_SCS60_1(dummy)       do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR23, 0u, 2u,  2u ); \
                                            bFM_GPIO_PFR3_P0 = 1u; \
                                        }while (0u)

/*--- SCS61_1 ---*/
#define SetPinFunc_SCS61_1(dummy)       do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR23, 2u, 2u,  2u ); \
                                            bFM_GPIO_PFR3_P4 = 1u; \
                                        }while (0u)

/*--- SI2CSCL6_1 ---*/
#define SetPinFunc_SI2CSCL6_1(dummy)    do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR31, 24u, 2u,  2u ); \
                                            bFM_GPIO_PFR3_P1 = 1u; \
                                        }while (0u)

/*--- SI2CSDA6_1 ---*/
#define SetPinFunc_SI2CSDA6_1(dummy)    do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR31, 26u, 2u,  2u ); \
                                            bFM_GPIO_PFR3_P2 = 1u; \
                                        }while (0u)

/*--- SIN0_0 ---*/
#define SetPinFunc_SIN0_0(dummy)        do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR07, 4u, 2u,  1u ); \
                                            bFM_GPIO_PFR0_P3 = 1u; \
                                        }while (0u)

/*--- SIN0_1 ---*/
#define SetPinFunc_SIN0_1(dummy)        do{ \
                                            bFM_GPIO_ADE_AN04=0u; \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR07, 4u, 2u,  2u ); \
                                            bFM_GPIO_PFR1_P4 = 1u; \
                                        }while (0u)

/*--- SIN1_1 ---*/
#define SetPinFunc_SIN1_1(dummy)        do{ \
                                            bFM_GPIO_ADE_AN01=0u; \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR07, 10u, 2u,  2u ); \
                                            bFM_GPIO_PFR1_P1 = 1u; \
                                        }while (0u)

/*--- SIN3_1 ---*/
#define SetPinFunc_SIN3_1(dummy)        do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR07, 22u, 2u,  2u ); \
                                            bFM_GPIO_PFR5_P0 = 1u; \
                                        }while (0u)

/*--- SIN4_1 ---*/
#define SetPinFunc_SIN4_1(dummy)        do{ \
                                            PINCONFIG_SET_REG(FM_DS->CEC_CTL, 0u, 2u, 0u); \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR08, 4u, 2u,  2u ); \
                                            bFM_GPIO_PFR1_PA = 1u; \
                                        }while (0u)

/*--- SIN6_1 ---*/
#define SetPinFunc_SIN6_1(dummy)        do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR08, 16u, 2u,  2u ); \
                                            bFM_GPIO_PFR3_P3 = 1u; \
                                        }while (0u)

/*--- SIN7_1 ---*/
#define SetPinFunc_SIN7_1(dummy)        do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR08, 22u, 2u,  2u ); \
                                            bFM_GPIO_PFR4_PE = 1u; \
                                        }while (0u)

/*--- SOT0_0 ---*/
#define SetPinFunc_SOT0_0(dummy)        do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR07, 6u, 2u,  1u ); \
                                            bFM_GPIO_PFR0_P1 = 1u; \
                                        }while (0u)

/*--- SOT0_1 ---*/
#define SetPinFunc_SOT0_1(dummy)        do{ \
                                            bFM_GPIO_ADE_AN05=0u; \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR07, 6u, 2u,  2u ); \
                                            bFM_GPIO_PFR1_P5 = 1u; \
                                        }while (0u)

/*--- SOT1_1 ---*/
#define SetPinFunc_SOT1_1(dummy)        do{ \
                                            bFM_GPIO_ADE_AN02=0u; \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR07, 12u, 2u,  2u ); \
                                            bFM_GPIO_PFR1_P2 = 1u; \
                                        }while (0u)

/*--- SOT3_1 ---*/
#define SetPinFunc_SOT3_1(dummy)        do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR07, 24u, 2u,  2u ); \
                                            bFM_GPIO_PFR5_P1 = 1u; \
                                        }while (0u)

/*--- SOT4_1 ---*/
#define SetPinFunc_SOT4_1(dummy)        do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR08, 6u, 2u,  2u ); \
                                            bFM_GPIO_PFR1_PB = 1u; \
                                        }while (0u)

/*--- SOT6_1 ---*/
#define SetPinFunc_SOT6_1(dummy)        do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR08, 18u, 2u,  2u ); \
                                            bFM_GPIO_PFR3_P2 = 1u; \
                                        }while (0u)

/*--- SOT7_1 ---*/
#define SetPinFunc_SOT7_1(dummy)        do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR08, 24u, 2u,  2u ); \
                                            bFM_GPIO_PFR4_PD = 1u; \
                                        }while (0u)

/*--- SUBOUT_0 ---*/
#define SetPinFunc_SUBOUT_0(dummy)      do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR00, 6u, 2u,  1u ); \
                                            bFM_GPIO_PFR0_PF = 1u; \
                                        }while (0u)

/*--- SUBOUT_1 ---*/
#define SetPinFunc_SUBOUT_1(dummy)      do{ \
                                            bFM_GPIO_ADE_AN03=0u; \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR00, 6u, 2u,  2u ); \
                                            bFM_GPIO_PFR1_P3 = 1u; \
                                        }while (0u)

/*--- SUBOUT_2 ---*/
#define SetPinFunc_SUBOUT_2(dummy)      do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR00, 6u, 2u,  3u ); \
                                            bFM_GPIO_PFR3_PA = 1u; \
                                        }while (0u)

/*--- SWCLK ---*/
#define SetPinFunc_SWCLK(dummy)         do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR00, 16u, 1u,  1u ); \
                                            bFM_GPIO_PFR0_P1 = 1u; \
                                        }while (0u)

/*--- SWDIO ---*/
#define SetPinFunc_SWDIO(dummy)         do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR00, 16u, 1u,  1u ); \
                                            bFM_GPIO_PFR0_P3 = 1u; \
                                        }while (0u)

/*--- TIOA0_1_OUT ---*/
#define SetPinFunc_TIOA0_1_OUT(dummy)   do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR04, 2u, 2u,  2u ); \
                                            bFM_GPIO_PFR3_PA = 1u; \
                                        }while (0u)

/*--- TIOA1_1_IN ---*/
#define SetPinFunc_TIOA1_1_IN(dummy)    do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR04, 8u, 2u,  2u ); \
                                            bFM_GPIO_PFR3_PB = 1u; \
                                        }while (0u)

/*--- TIOA1_1_OUT ---*/
#define SetPinFunc_TIOA1_1_OUT(dummy)   do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR04, 10u, 2u,  2u ); \
                                            bFM_GPIO_PFR3_PB = 1u; \
                                        }while (0u)

/*--- TIOA1_2_IN ---*/
#define SetPinFunc_TIOA1_2_IN(dummy)    do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR04, 8u, 2u,  3u ); \
                                            bFM_GPIO_PFR5_P3 = 1u; \
                                        }while (0u)

/*--- TIOA1_2_OUT ---*/
#define SetPinFunc_TIOA1_2_OUT(dummy)   do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR04, 10u, 2u,  3u ); \
                                            bFM_GPIO_PFR5_P3 = 1u; \
                                        }while (0u)

/*--- TIOA2_1_OUT ---*/
#define SetPinFunc_TIOA2_1_OUT(dummy)   do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR04, 18u, 2u,  2u ); \
                                            bFM_GPIO_PFR3_PC = 1u; \
                                        }while (0u)

/*--- TIOA2_2_OUT ---*/
#define SetPinFunc_TIOA2_2_OUT(dummy)   do{ \
                                            PINCONFIG_SET_REG(FM_DS->CEC_CTL, 2u, 2u, 0u); \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR04, 18u, 2u,  3u ); \
                                            bFM_GPIO_PFR6_P0 = 1u; \
                                        }while (0u)

/*--- TIOA5_2_IN ---*/
#define SetPinFunc_TIOA5_2_IN(dummy)    do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR05, 8u, 2u,  3u ); \
                                            bFM_GPIO_PFR0_P5 = 1u; \
                                        }while (0u)

/*--- TIOA5_2_OUT ---*/
#define SetPinFunc_TIOA5_2_OUT(dummy)   do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR05, 10u, 2u,  3u ); \
                                            bFM_GPIO_PFR0_P5 = 1u; \
                                        }while (0u)

/*--- TIOA7_1_IN ---*/
#define SetPinFunc_TIOA7_1_IN(dummy)    do{ \
                                            bFM_GPIO_ADE_AN06=0u; \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR05, 24u, 2u,  2u ); \
                                            bFM_GPIO_PFR2_P3 = 1u; \
                                        }while (0u)

/*--- TIOA7_1_OUT ---*/
#define SetPinFunc_TIOA7_1_OUT(dummy)   do{ \
                                            bFM_GPIO_ADE_AN06=0u; \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR05, 26u, 2u,  2u ); \
                                            bFM_GPIO_PFR2_P3 = 1u; \
                                        }while (0u)

/*--- TIOB0_1_IN ---*/
#define SetPinFunc_TIOB0_1_IN(dummy)    do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR04, 4u, 3u,  2u ); \
                                            bFM_GPIO_PFR3_P0 = 1u; \
                                        }while (0u)

/*--- TIOB2_1_IN ---*/
#define SetPinFunc_TIOB2_1_IN(dummy)    do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR04, 20u, 2u,  2u ); \
                                            bFM_GPIO_PFR3_P2 = 1u; \
                                        }while (0u)

/*--- TIOB2_2_IN ---*/
#define SetPinFunc_TIOB2_2_IN(dummy)    do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR04, 20u, 2u,  3u ); \
                                            bFM_GPIO_PFR6_P1 = 1u; \
                                        }while (0u)

/*--- TIOB7_0_IN ---*/
#define SetPinFunc_TIOB7_0_IN(dummy)    do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR05, 28u, 2u,  1u ); \
                                            bFM_GPIO_PFR0_P3 = 1u; \
                                        }while (0u)

/*--- TIOB7_1_IN ---*/
#define SetPinFunc_TIOB7_1_IN(dummy)    do{ \
                                            bFM_GPIO_ADE_AN07=0u; \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR05, 28u, 2u,  2u ); \
                                            bFM_GPIO_PFR2_P2 = 1u; \
                                        }while (0u)

/*--- UDM0 ---*/
#define SetPinFunc_UDM0(dummy)          do{ \
                                            bFM_GPIO_SPSR_USB0C=1u; \
                                        }while (0u)

/*--- UDP0 ---*/
#define SetPinFunc_UDP0(dummy)          do{ \
                                            bFM_GPIO_SPSR_USB0C=1u; \
                                        }while (0u)

/*--- UHCONX0 ---*/
#define SetPinFunc_UHCONX0(dummy)       do{ \
                                            PINRELOC_SET_EPFR( FM_GPIO->EPFR00, 9u, 1u,  1u ); \
                                            bFM_GPIO_PFR6_P1 = 1u; \
                                        }while (0u)

/*--- WKUP0 ---*/
#define SetPinFunc_WKUP0(dummy)         do{ \
                                            bFM_GPIO_PFR0_PF = 1u; \
                                        }while (0u)

/*--- WKUP1 ---*/
#define SetPinFunc_WKUP1(dummy)         do{ \
                                            bFM_GPIO_ADE_AN01=0u; \
                                            bFM_GPIO_PFR1_P1 = 1u; \
                                        }while (0u)

/*--- WKUP2 ---*/
#define SetPinFunc_WKUP2(dummy)         do{ \
                                            bFM_GPIO_PFR2_P1 = 1u; \
                                        }while (0u)

/*--- WKUP3 ---*/
#define SetPinFunc_WKUP3(dummy)         do{ \
                                            bFM_GPIO_PFR0_P5 = 1u; \
                                        }while (0u)

/*--- X0 ---*/
#define SetPinFunc_X0(dummy)            do{ \
                                            PINCONFIG_SET_REG(FM_GPIO->SPSR, 2u, 2u, 1u); \
                                        }while (0u)

/*--- X0A ---*/
#define SetPinFunc_X0A(dummy)           do{ \
                                            PINCONFIG_SET_REG(FM_DS->SUBOSC_CTL, 0u, 2u, 1u); \
                                        }while (0u)

/*--- X1 ---*/
#define SetPinFunc_X1(dummy)            do{ \
                                            PINCONFIG_SET_REG(FM_GPIO->SPSR, 2u, 2u, 1u); \
                                        }while (0u)

/*--- X1A ---*/
#define SetPinFunc_X1A(dummy)           do{ \
                                            PINCONFIG_SET_REG(FM_DS->SUBOSC_CTL, 0u, 2u, 1u); \
                                        }while (0u)

/******************************************************************************
   ANALOG PINS
*******************************************************************************/

/*--- AN00 ---*/
#define SetPinFunc_AN00(dummy)          do{ \
                                            bFM_GPIO_ADE_AN00=1u; \
                                        }while (0u)

/*--- AN01 ---*/
#define SetPinFunc_AN01(dummy)          do{ \
                                            bFM_GPIO_ADE_AN01=1u; \
                                        }while (0u)

/*--- AN02 ---*/
#define SetPinFunc_AN02(dummy)          do{ \
                                            bFM_GPIO_ADE_AN02=1u; \
                                        }while (0u)

/*--- AN03 ---*/
#define SetPinFunc_AN03(dummy)          do{ \
                                            bFM_GPIO_ADE_AN03=1u; \
                                        }while (0u)

/*--- AN04 ---*/
#define SetPinFunc_AN04(dummy)          do{ \
                                            bFM_GPIO_ADE_AN04=1u; \
                                        }while (0u)

/*--- AN05 ---*/
#define SetPinFunc_AN05(dummy)          do{ \
                                            bFM_GPIO_ADE_AN05=1u; \
                                        }while (0u)

/*--- AN06 ---*/
#define SetPinFunc_AN06(dummy)          do{ \
                                            bFM_GPIO_ADE_AN06=1u; \
                                        }while (0u)

/*--- AN07 ---*/
#define SetPinFunc_AN07(dummy)          do{ \
                                            bFM_GPIO_ADE_AN07=1u; \
                                        }while (0u)

#endif // #ifndef __GPIO_S6E1C3XC_H__


/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/

