/* FFMC-8FX Commodity HEADER FILE    
---------------------------------------------------------------------------*/
/* ==========================                                                */
/* SOFTUNE WORKBENCH FORMAT                                                  */
/* C-DEFINITIONS FOR IO-SYMBOLS                                              */
/* $Id: mb95200.h,v 1.0 2008/03/12  */
/* THIS SAMPLE CODE IS PROVIDED AS IS AND IS SUBJECT TO ALTERATIONS. FUJITSU */
/* MICROELECTRONICS ACCEPTS NO RESPONSIBILITY OR LIABILITY FOR ANY ERRORS OR */
/* ELIGIBILITY FOR ANY PURPOSES.                                             */
/*            (C) Fujitsu Microelectronics (Shanghai) Co., LTD.              */
/*---------------------------------------------------------------------------
/* ***************************************************************************** */
/* The following software is for demonstration purposes only.                */
/* It is not fully tested, nor validated in order to fullfill                */
/* its task under all circumstances. Therefore, this software                */
/* or any part of it must only be used in an evaluation                      */
/* laboratory environment.                                                   */
/* This software is subject to the rules of our standard DISCLAIMER          */
/* ***************************************************************************** */
/*                                                                           */
 .PROGRAM MB95200
 .TITLE   MB95200

;------------------------
; IO-AREA DEFINITIONS :
;------------------------



 .section IOBASE, IO, locate=0x0  ; /* Port0 */
 .GLOBAL __pdr0,     __ddr0,     __pdr1,     __ddr1,     __watr,    __sycc
 .GLOBAL __stbc,     __rsrr,     __tbtc,     __wpcr,     __wdtc,    __sycc2
 .GLOBAL __pdr6,     __ddr6,     __pdrf,     __ddrf,     __pdrg,    __ddrg      
 .GLOBAL __pul0,     __pulg,     __t01cr1,   __t00cr1,   __t11cr1,  __t10cr1
 .GLOBAL __eic10,    __eic20,    __eic30,    __scr,      __smr,     __ssr
 .GLOBAL __rdr,      __tdr,      __escr,     __eccr,     __adc1,    __adc2
 .GLOBAL __addh,     __addl,     __fsr,      __wren,     __wror,    __ilr0
 .GLOBAL __ilr1,     __ilr2,     __ilr3,     __ilr4,     __ilr5

__pdr0   .res.b 1             ;000000  /* Port0 */
PDR0    .equ 0x0000
__ddr0   .res.b 1             ;000001
DDR0    .equ 0x0001
__pdr1   .res.b 1             ;000002  /* Port1    */
PDR1    .equ 0x0002
__ddr1   .res.b 1             ;000003
DDR1    .equ 0x0003
 .org 0x5
__watr   .res.b 1             ;000005  /* WATR */
WATR    .equ 0x0005
 .org 0x7
__sycc   .res.b 1             ;000007  /* SYCC */
SYCC    .equ 0x0007
__stbc   .res.b 1             ;000008  /* STBC */
STBC    .equ 0x0008
__rsrr   .res.b 1             ;000009  /* RSRR */
RSRR    .equ 0x0009
__tbtc   .res.b 1             ;00000A  /* TBTC */
TBTC    .equ 0x000A
__wpcr   .res.b 1             ;00000B  /* WPCR */
WPCR    .equ 0x000B
__wdtc   .res.b 1             ;00000C  /* WDTC */
WDTC    .equ 0x000C
__sycc2  .res.b 1             ;00000D  /* SYCC2 */
SYCC2   .equ 0x000D
 .org 0x16
__pdr6    .res.b 1            ;000016
PDR6     .equ 0x0016 
__ddr6    .res.b 1            ;000017
DDR6     .equ 0x0017
 .org 0x28
__pdrf   .res.b 1             ;000028  /* PortF */
PDRF    .equ 0x0028
__ddrf   .res.b 1             ;000029
DDRF    .equ 0x0029
__pdrg   .res.b 1             ;00002A  /* PortG */
PDRG    .equ 0x002A
__ddrg   .res.b 1             ;00002B
DDRG    .equ 0x002B
__pul0   .res.b 1             ;00002C  /* PUL0 */
PUL0    .equ 0x002C
 .org 0x35
__pulg   .res.b 1             ;000035  /* PULG */
PULG    .equ 0x0035
__t01cr1   .res.b 1             ;000036  /* T01CR1 */
T01CR1    .equ 0x0036
__t00cr1   .res.b 1             ;000037  /* T00CR1 */
T00CR1    .equ 0x0037
__t11cr1   .res.b 1             ;000038  /* T11CR1 */
T11CR1    .equ 0x0038
__t10cr1   .res.b 1             ;000039  /* T10CR1 */
T10CR1    .equ 0x0039
 .org 0x49
__eic10   .res.b 1             ;000049  /* EIC10 */
EIC10    .equ 0x0049
__eic20   .res.b 1             ;00004A  /* EIC20 */
EIC20    .equ 0x004A
__eic30   .res.b 1             ;00004B  /* EIC30 */
EIC30    .equ 0x004B
 .org 0x50
__scr   .res.b 1             ;000050  /* SCR */
SCR    .equ 0x0050
__smr   .res.b 1             ;000051  /* SMR */
SMR    .equ 0x0051
__ssr   .res.b 1             ;000052  /* SSR */
SSR    .equ 0x0052
__rdr   .res.b 1             ;000053  /* RDR */
RDR    .equ 0x0053
 .org 0x53
__tdr   .res.b 1             ;000053  /* RDR */
TDR    .equ 0x0053
__escr   .res.b 1             ;000054  /* ESCR */
ESCR    .equ 0x0054
__eccr   .res.b 1             ;000055  /* ECCR */
ECCR    .equ 0x0055
 .org 0x6C
__adc1   .res.b 1             ;00006C  /* ADC1 */
ADC1    .equ 0x006C
__adc2   .res.b 1             ;00006D  /* ADC2 */
ADC2    .equ 0x006D
__addh   .res.b 1             ;00006E  /* ADD */
ADDH    .equ 0x006E
__addl   .res.b 1             ;00006F
ADDL    .equ 0x006F
 .org 0x72
__fsr   .res.b 1             ;000072  /* FSR */
FSR    .equ 0x0072
 .org 0x76
__wren   .res.b 1             ;000076  /* WREN */
WREN    .equ 0x0076
__wror   .res.b 1             ;000077  /* WROR */
WROR    .equ 0x0077
 .org 0x79
__ilr0   .res.b 1             ;000079  /* ILR0 */
ILR0    .equ 0x0079
__ilr1   .res.b 1             ;00007A  /* ILR1 */
ILR1    .equ 0x007A
__ilr2   .res.b 1             ;00007B  /* ILR2 */
ILR2    .equ 0x007B
__ilr3   .res.b 1             ;00007C  /* ILR3 */
ILR3    .equ 0x007C
__ilr4   .res.b 1             ;00007D  /* ILR4 */
ILR4    .equ 0x007D
__ilr5   .res.b 1             ;00007E  /* ILR5 */
ILR5    .equ 0x007E

 .section IOXTND, DATA, locate=0xF80  ; /* WRAR0 */
 .GLOBAL __wrarh0,   __wrarl0,   __wrdr0,    __wrarh1,   __wrarl1,   __wrdr1
 .GLOBAL __wrarh2,   __wrarl2,   __wrdr2,    __t01cr0,   __t00cr0,   __t0dr
 .GLOBAL __t01dr,    __t00dr,    __tmcr0,    __t11cr0,   __t10cr0,   __t1dr
 .GLOBAL __t11dr,    __t10dr,    __tmcr1,    __bgr,      __bgr1,     __bgr0
 .GLOBAL __aidrl,    __crth,     __crtl,     __sysc,     __cmcr,     __cmdr
 .GLOBAL __wdth,     __wdtl,     __ilsr

__wrarh0   .res.b 1             ;000F80  /* WRAR0 */
WRARH0    .equ 0x0F80
__wrarl0   .res.b 1             ;000F81
WRARL0    .equ 0x0F81
__wrdr0   .res.b 1             ;000F82  /* WRDR0 */
WRDR0    .equ 0x0F82
__wrarh1   .res.b 1             ;000F83  /* WRAR1 */
WRARH1    .equ 0x0F83
__wrarl1   .res.b 1             ;000F84
WRARL1    .equ 0x0F84
__wrdr1   .res.b 1             ;000F85  /* WRDR1 */
WRDR1    .equ 0x0F85
__wrarh2   .res.b 1             ;000F86  /* WRAR2 */
WRARH2    .equ 0x0F86
__wrarl2   .res.b 1             ;000F87
WRARL2    .equ 0x0F87
__wrdr2   .res.b 1             ;000F88  /* WRDR2 */
WRDR2    .equ 0x0F88
 .org 0xF92
__t01cr0   .res.b 1             ;000F92  /* T01CR0 */
T01CR0    .equ 0x0F92
__t00cr0   .res.b 1             ;000F93  /* T00CR0 */
T00CR0    .equ 0x0F93
__t0dr   .res.b 2             ;000F94  /* T01DR */
T0DR    .equ 0x0F94
 .org 0xF94
__t01dr   .res.b 1             ;000F94
T01DR    .equ 0x0F94
__t00dr   .res.b 1             ;000F95
T00DR    .equ 0x0F95
__tmcr0   .res.b 1             ;000F96  /* TMCR0 */
TMCR0    .equ 0x0F96
__t11cr0   .res.b 1             ;000F97  /* T11CR0 */
T11CR0    .equ 0x0F97
__t10cr0   .res.b 1             ;000F98  /* T10CR0 */
T10CR0    .equ 0x0F98
__t1dr   .res.b 2             ;000F99  /* T01DR */
T1DR    .equ 0x0F99
 .org 0xF99
__t11dr   .res.b 1             ;000F99
T11DR    .equ 0x0F99
__t10dr   .res.b 1             ;000F9A  /* T00DR */
T10DR    .equ 0x0F9A
__tmcr1   .res.b 1             ;000F9B  /* TMCR0 */
TMCR1    .equ 0x0F9B
 .org 0xFBC
__bgr   .res.b 2             ;000FBC  /* BGR */
BGR    .equ 0x0FBC
 .org 0xFBC
__bgr1   .res.b 1             ;000FBC
BGR1    .equ 0x0FBC
__bgr0   .res.b 1             ;000FBD
BGR0    .equ 0x0FBD
 .org 0xFC3
__aidrl   .res.b 1             ;000FC3  /* AIDRL */
AIDRL    .equ 0x0FC3
 .org 0xFE4
__crth   .res.b 1             ;000FE4  /* CRTH */
CRTH    .equ 0x0FE4
__crtl   .res.b 1             ;000FE5  /* CRTL */
CRTL    .equ 0x0FE5
 .org 0xFE8
__sysc   .res.b 1
SYSC    .equ 0x0FE8           ;000FE8  /* SYSC */
__cmcr   .res.b 1
CMCR    .equ 0xFE9            ;000FE9  /* CMCR */
__cmdr   .res.b 1
CMDR    .equ 0xFEA            ;000FEA  /* CMDR */
__wdth   .res.b 1
WDTH    .equ 0xFEB            ;000FEB  /* WDTH */
__wdtl   .res.b 1
WDTL    .equ 0xFEC            ;000FEC  /* WDTL */
 .org 0xFEE
__ilsr   .res.b 1             ;000FEE  /* ILSR */
ILSR    .equ 0x0FEE

 .end
