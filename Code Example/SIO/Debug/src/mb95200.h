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

#ifndef   __MB952XX_H
#  define __MB952XX_H
/*
- Please define __IO_NEAR in LARGE and COMPACT memory model, if the default
  data bank (DTB) is 00. This will result in better performance in these
  models.
- Please define __IO_FAR in SMALL and MEDIUM memory model, if the default
  data bank (DTB) is other than 00. This might be the case in systems with
  external RAM, which are not using internal RAM as default data area.
- Please define neither __IO_NEAR nor __IO_FAR in all other cases. This
  will work with almost all configurations.
*/

#  ifdef  __IO_NEAR
#    ifdef  __IO_FAR
#      error __IO_NEAR and __IO_FAR must not be defined at the same time
#    else
#      define ___IOWIDTH __near
#    endif
#  else
#    ifdef __IO_FAR
#      define ___IOWIDTH __far
#    else                               /* specified by memory model */
#      define ___IOWIDTH
#    endif
#  endif
#  ifdef  __IO_DEFINE
#    define __IO_EXTERN
#    define __IO_EXTENDED volatile ___IOWIDTH
#  else
#    define __IO_EXTERN   extern      /* for data, which can have __io */
#    define __IO_EXTENDED extern volatile ___IOWIDTH
#  endif

typedef unsigned char		IO_BYTE;
typedef unsigned short		IO_WORD;
typedef unsigned long		IO_LWORD;
typedef const unsigned short	IO_WORD_READ;

/* REGISTER BIT STRUCTURES */

typedef union{   /* Port0 */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _P07 :1;
    IO_BYTE _P06 :1;
    IO_BYTE _P05 :1;
    IO_BYTE _P04 :1;
    IO_BYTE _P03 :1;
    IO_BYTE _P02 :1;
    IO_BYTE _P01 :1;
    IO_BYTE _P00 :1;
    #else 
    IO_BYTE _P00 :1;
    IO_BYTE _P01 :1;
    IO_BYTE _P02 :1;
    IO_BYTE _P03 :1;
    IO_BYTE _P04 :1;
    IO_BYTE _P05 :1;
    IO_BYTE _P06 :1;
    IO_BYTE _P07 :1;
    #endif 
  }bit;
 }PDR0STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _P07 :1;
    IO_BYTE _P06 :1;
    IO_BYTE _P05 :1;
    IO_BYTE _P04 :1;
    IO_BYTE _P03 :1;
    IO_BYTE _P02 :1;
    IO_BYTE _P01 :1;
    IO_BYTE _P00 :1;
    #else 
    IO_BYTE _P00 :1;
    IO_BYTE _P01 :1;
    IO_BYTE _P02 :1;
    IO_BYTE _P03 :1;
    IO_BYTE _P04 :1;
    IO_BYTE _P05 :1;
    IO_BYTE _P06 :1;
    IO_BYTE _P07 :1;
    #endif 
  }bit;
 }DDR0STR;
 __IO_EXTERN __io PDR0STR _pdr0;   /* Port0 */
#define PDR0 _pdr0.byte
#define PDR0_P00 _pdr0.bit._P00
#define PDR0_P01 _pdr0.bit._P01
#define PDR0_P02 _pdr0.bit._P02
#define PDR0_P03 _pdr0.bit._P03
#define PDR0_P04 _pdr0.bit._P04
#define PDR0_P05 _pdr0.bit._P05
#define PDR0_P06 _pdr0.bit._P06
#define PDR0_P07 _pdr0.bit._P07
__IO_EXTERN __io DDR0STR _ddr0;  
#define DDR0 _ddr0.byte
#define DDR0_P00 _ddr0.bit._P00
#define DDR0_P01 _ddr0.bit._P01
#define DDR0_P02 _ddr0.bit._P02
#define DDR0_P03 _ddr0.bit._P03
#define DDR0_P04 _ddr0.bit._P04
#define DDR0_P05 _ddr0.bit._P05
#define DDR0_P06 _ddr0.bit._P06
#define DDR0_P07 _ddr0.bit._P07
 
typedef union{   /* Port1    */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _P12 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    #else 
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _P12 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    #endif 
  }bit;
 }PDR1STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _P12 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    #else 
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _P12 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    #endif 
  }bit;
 }DDR1STR;
 __IO_EXTERN __io PDR1STR _pdr1;   /* Port1    */
#define PDR1 _pdr1.byte
#define PDR1_P12 _pdr1.bit._P12
__IO_EXTERN __io DDR1STR _ddr1;  
#define DDR1 _ddr1.byte
#define DDR1_P12 _ddr1.bit._P12

typedef union{   /* WATR */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _SWT3 :1;
    IO_BYTE _SWT2 :1;
    IO_BYTE _SWT1 :1;
    IO_BYTE _SWT0 :1;
    IO_BYTE _MWT3 :1;
    IO_BYTE _MWT2 :1;
    IO_BYTE _MWT1 :1;
    IO_BYTE _MWT0 :1;
    #else 
    IO_BYTE _MWT0 :1;
    IO_BYTE _MWT1 :1;
    IO_BYTE _MWT2 :1;
    IO_BYTE _MWT3 :1;
    IO_BYTE _SWT0 :1;
    IO_BYTE _SWT1 :1;
    IO_BYTE _SWT2 :1;
    IO_BYTE _SWT3 :1;
    #endif 
  }bit;
  struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _SWT :4;
    IO_BYTE _MWT :4;
    #else 
    IO_BYTE _MWT :4;
    IO_BYTE _SWT :4;
    #endif 
  }bitc;
 }WATRSTR;
 __IO_EXTERN __io WATRSTR _watr;   /* WATR */
#define WATR _watr.byte
#define WATR_MWT0 _watr.bit._MWT0
#define WATR_MWT1 _watr.bit._MWT1
#define WATR_MWT2 _watr.bit._MWT2
#define WATR_MWT3 _watr.bit._MWT3
#define WATR_SWT0 _watr.bit._SWT0
#define WATR_SWT1 _watr.bit._SWT1
#define WATR_SWT2 _watr.bit._SWT2
#define WATR_SWT3 _watr.bit._SWT3
#define WATR_MWT _watr.bitc._MWT
#define WATR_SWT _watr.bitc._SWT
typedef union{   /* SYCC */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _SRDY :1;
    IO_BYTE  :1;
    IO_BYTE _DIV1 :1;
    IO_BYTE _DIV0 :1;
    #else 
    IO_BYTE _DIV0 :1;
    IO_BYTE _DIV1 :1;
    IO_BYTE  :1;
    IO_BYTE _SRDY :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    #endif 
  }bit;
  struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE :2;
    IO_BYTE :2;
    IO_BYTE :2;
    IO_BYTE _DIV :2;
    #else 
    IO_BYTE _DIV :2;
    IO_BYTE :2;
    IO_BYTE :2;
    IO_BYTE :2;
    #endif 
  }bitc;
 }SYCCSTR;
 __IO_EXTERN __io SYCCSTR _sycc;   /* SYCC */
#define SYCC _sycc.byte
#define SYCC_DIV0 _sycc.bit._DIV0
#define SYCC_DIV1 _sycc.bit._DIV1
#define SYCC_SRDY _sycc.bit._SRDY
#define SYCC_DIV _sycc.bitc._DIV
typedef union{   /* STBC */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _STP :1;
    IO_BYTE _SLP :1;
    IO_BYTE _SPL :1;
    IO_BYTE _SRST :1;
    IO_BYTE _TMD :1;
    IO_BYTE _SCRDY :1;
    IO_BYTE _MCRDY :1;
    IO_BYTE _MRDY :1;
    #else 
    IO_BYTE _MRDY :1;
    IO_BYTE _MCRDY :1;
    IO_BYTE _SCRDY :1;
    IO_BYTE _TMD :1;
    IO_BYTE _SRST :1;
    IO_BYTE _SPL :1;
    IO_BYTE _SLP :1;
    IO_BYTE _STP :1;
    #endif 
  }bit;
 }STBCSTR;
 __IO_EXTERN __io STBCSTR _stbc;   /* STBC */
#define STBC _stbc.byte
#define STBC_MRDY _stbc.bit._MRDY
#define STBC_MCRDY _stbc.bit._MCRDY
#define STBC_SCRDY _stbc.bit._SCRDY
#define STBC_TMD _stbc.bit._TMD
#define STBC_SRST _stbc.bit._SRST
#define STBC_SPL _stbc.bit._SPL
#define STBC_SLP _stbc.bit._SLP
#define STBC_STP _stbc.bit._STP
typedef union{   /* RSRR */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _EXTS :1;
    IO_BYTE _WDTR :1;
    IO_BYTE _PONR :1;
    IO_BYTE _HWR :1;
    IO_BYTE _SWR :1;
    #else 
    IO_BYTE _SWR :1;
    IO_BYTE _HWR :1;
    IO_BYTE _PONR :1;
    IO_BYTE _WDTR :1;
    IO_BYTE _EXTS :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    #endif 
  }bit;
 }RSRRSTR;
 __IO_EXTERN __io RSRRSTR _rsrr;   /* RSRR */
#define RSRR _rsrr.byte
#define RSRR_SWR _rsrr.bit._SWR
#define RSRR_HWR _rsrr.bit._HWR
#define RSRR_PONR _rsrr.bit._PONR
#define RSRR_WDTR _rsrr.bit._WDTR
#define RSRR_EXTS _rsrr.bit._EXTS
typedef union{   /* TBTC */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _TBIF :1;
    IO_BYTE _TBIE :1;
    IO_BYTE  :1;
    IO_BYTE _TBC3 :1;
    IO_BYTE _TBC2 :1;
    IO_BYTE _TBC1 :1;
    IO_BYTE _TBC0 :1;
    IO_BYTE _TCLR :1;
    #else 
    IO_BYTE _TCLR :1;
    IO_BYTE _TBC0 :1;
    IO_BYTE _TBC1 :1;
    IO_BYTE _TBC2 :1;
    IO_BYTE _TBC3 :1;
    IO_BYTE  :1;
    IO_BYTE _TBIE :1;
    IO_BYTE _TBIF :1;
    #endif 
  }bit;
  struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE :3;
    IO_BYTE _TBC :4;
    #else 
    IO_BYTE :1;
    IO_BYTE _TBC :4;
    #endif 
  }bitc;
 }TBTCSTR;
__IO_EXTERN __io TBTCSTR _tbtc;   /* TBTC */
#define TBTC _tbtc.byte
#define TBTC_TCLR _tbtc.bit._TCLR
#define TBTC_TBC0 _tbtc.bit._TBC0
#define TBTC_TBC1 _tbtc.bit._TBC1
#define TBTC_TBC2 _tbtc.bit._TBC2
#define TBTC_TBC3 _tbtc.bit._TBC3
#define TBTC_TBIE _tbtc.bit._TBIE
#define TBTC_TBIF _tbtc.bit._TBIF
#define TBTC_TBC _tbtc.bitc._TBC
typedef union{   /* WPCR */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _WTIF :1;
    IO_BYTE _WTIE :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _WTC2 :1;
    IO_BYTE _WTC1 :1;
    IO_BYTE _WTC0 :1;
    IO_BYTE _WCLR :1;
    #else 
    IO_BYTE _WCLR :1;
    IO_BYTE _WTC0 :1;
    IO_BYTE _WTC1 :1;
    IO_BYTE _WTC2 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _WTIE :1;
    IO_BYTE _WTIF :1;
    #endif 
  }bit;
  struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE :4;
    IO_BYTE _WTC :3;
    #else 
    IO_BYTE :1;
    IO_BYTE _WTC :3;
    #endif 
  }bitc;
 }WPCRSTR;
__IO_EXTERN __io WPCRSTR _wpcr;   /* WPCR */
#define WPCR _wpcr.byte
#define WPCR_WCLR _wpcr.bit._WCLR
#define WPCR_WTC0 _wpcr.bit._WTC0
#define WPCR_WTC1 _wpcr.bit._WTC1
#define WPCR_WTC2 _wpcr.bit._WTC2
#define WPCR_WTIE _wpcr.bit._WTIE
#define WPCR_WTIF _wpcr.bit._WTIF
#define WPCR_WTC _wpcr.bitc._WTC
__IO_EXTERN __io IO_BYTE _wdtc;
#define WDTC _wdtc    /* WDTC */
///////////
typedef union{   /* SYCC2 */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _RCM1 :1;
    IO_BYTE _RCM0 :1;
    IO_BYTE _RCS1 :1;
    IO_BYTE _RCS0 :1;
    IO_BYTE _SOSCE :1;
    IO_BYTE _MOSCE :1;
    IO_BYTE _SCRE :1;
    IO_BYTE _MCRE :1;
    #else 
    IO_BYTE _MCRE :1;
    IO_BYTE _SCRE :1;
    IO_BYTE _MOSCE :1;
    IO_BYTE _SOSCE :1;
    IO_BYTE _RCS0 :1;
    IO_BYTE _RCS1 :1;
    IO_BYTE _RCM0 :1;
    IO_BYTE _RCM1 :1;
    #endif 
  }bit;
  struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _RCM :2;
    IO_BYTE _RCS :2;
    IO_BYTE :2;
    IO_BYTE :2;
    #else 
    IO_BYTE :2;
    IO_BYTE :2;
    IO_BYTE _RCS :2;
    IO_BYTE _RCM :2;
    #endif 
  }bitc;
 }SYCC2STR;
 __IO_EXTERN __io SYCC2STR _sycc2; /* SYCC2 */
#define SYCC2 _sycc2.byte
#define SYCC2_MCRE _sycc2.bit._MCRE
#define SYCC2_SCRE _sycc2.bit._SCRE
#define SYCC2_MOSCE _sycc2.bit._MOSCE
#define SYCC2_SOSCE _sycc2.bit._SOSCE
#define SYCC2_RCS0 _sycc2.bit._RCS0
#define SYCC2_RCS1 _sycc2.bit._RCS1
#define SYCC2_RCM0 _sycc2.bit._RCM0
#define SYCC2_RCM1 _sycc2.bit._RCM1
#define SYCC2_RCS _sycc2.bitc._RCS
#define SYCC2_RCM _sycc2.bitc._RCM
//

typedef union{   /* Port6 */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _P64 :1;
    IO_BYTE _P63 :1;
    IO_BYTE _P62 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    #else 
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _P62 :1;
    IO_BYTE _P63 :1;
    IO_BYTE _P64 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    #endif 
  }bit;
 }PDR6STR;
typedef union{  
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _P64 :1;
    IO_BYTE _P63 :1;
    IO_BYTE _P62 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    #else 
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _P62 :1;
    IO_BYTE _P63 :1;
    IO_BYTE _P64 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    #endif 
  }bit;
 }DDR6STR;
 __IO_EXTERN __io PDR6STR _pdr6;   /* Port6 */
#define PDR6 _pdr6.byte
#define PDR6_P62 _pdr6.bit._P62
#define PDR6_P63 _pdr6.bit._P63
#define PDR6_P64 _pdr6.bit._P64
__IO_EXTERN __io DDR6STR _ddr6;  
#define DDR6 _ddr6.byte
#define DDR6_P62 _ddr6.bit._P62
#define DDR6_P63 _ddr6.bit._P63
#define DDR6_P64 _ddr6.bit._P64
typedef union{   /* PortF */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _PF2 :1;
    IO_BYTE _PF1 :1;
    IO_BYTE _PF0 :1;
    #else 
    IO_BYTE _PF0 :1;
    IO_BYTE _PF1 :1;
    IO_BYTE _PF2 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    #endif 
  }bit;
 }PDRFSTR;
typedef union{  
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _PF2 :1;
    IO_BYTE _PF1 :1;
    IO_BYTE _PF0 :1;
    #else 
    IO_BYTE _PF0 :1;
    IO_BYTE _PF1 :1;
    IO_BYTE _PF2 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    #endif 
  }bit;
 }DDRFSTR;
 __IO_EXTERN __io PDRFSTR _pdrf;   /* PortF */
#define PDRF _pdrf.byte
#define PDRF_PF0 _pdrf.bit._PF0
#define PDRF_PF1 _pdrf.bit._PF1
#define PDRF_PF2 _pdrf.bit._PF2
__IO_EXTERN __io DDRFSTR _ddrf;  
#define DDRF _ddrf.byte
#define DDRF_PF0 _ddrf.bit._PF0
#define DDRF_PF1 _ddrf.bit._PF1
#define DDRF_PF2 _ddrf.bit._PF2
typedef union{   /* PortG */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _PG2 :1;
    IO_BYTE _PG1 :1;
    IO_BYTE  :1;
    #else 
    IO_BYTE  :1;
    IO_BYTE _PG1 :1;
    IO_BYTE _PG2 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    #endif 
  }bit;
 }PDRGSTR;
typedef union{  
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _PG2 :1;
    IO_BYTE _PG1 :1;
    IO_BYTE  :1;
    #else 
    IO_BYTE  :1;
    IO_BYTE _PG1 :1;
    IO_BYTE _PG2 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    #endif 
  }bit;
 }DDRGSTR;
 __IO_EXTERN __io PDRGSTR _pdrg;   /* PortG */
#define PDRG _pdrg.byte
#define PDRG_PG1 _pdrg.bit._PG1
#define PDRG_PG2 _pdrg.bit._PG2
__IO_EXTERN __io DDRGSTR _ddrg;  
#define DDRG _ddrg.byte
#define DDRG_PG1 _ddrg.bit._PG1
#define DDRG_PG2 _ddrg.bit._PG2
typedef union{   /* PUL0 */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _P07 :1;
    IO_BYTE _P06 :1;
    IO_BYTE _P05 :1;
    IO_BYTE _P04 :1;
    IO_BYTE _P03 :1;
    IO_BYTE _P02 :1;
    IO_BYTE _P01 :1;
    IO_BYTE _P00 :1;
    #else 
    IO_BYTE _P00 :1;
    IO_BYTE _P01 :1;
    IO_BYTE _P02 :1;
    IO_BYTE _P03 :1;
    IO_BYTE _P04 :1;
    IO_BYTE _P05 :1;
    IO_BYTE _P06 :1;
    IO_BYTE _P07 :1;
    #endif 
  }bit;
 }PUL0STR;
__IO_EXTERN __io PUL0STR _pul0;   /* PUL0 */
#define PUL0 _pul0.byte
#define PUL0_P00 _pul0.bit._P00
#define PUL0_P01 _pul0.bit._P01
#define PUL0_P02 _pul0.bit._P02
#define PUL0_P03 _pul0.bit._P03
#define PUL0_P04 _pul0.bit._P04
#define PUL0_P05 _pul0.bit._P05
#define PUL0_P06 _pul0.bit._P06
#define PUL0_P07 _pul0.bit._P07
typedef union{   /* PULG */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _PG2 :1;
    IO_BYTE _PG1 :1;
    IO_BYTE  :1;
    #else 
    IO_BYTE  :1;
    IO_BYTE _PG1 :1;
    IO_BYTE _PG2 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    #endif 
  }bit;
 }PULGSTR;
 __IO_EXTERN __io PULGSTR _pulg;   /* PULG */
#define PULG _pulg.byte
#define PULG_PG1 _pulg.bit._PG1
#define PULG_PG2 _pulg.bit._PG2
typedef union{   /* T01CR1 */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _STA :1;
    IO_BYTE _HO :1;
    IO_BYTE _IE :1;
    IO_BYTE _IR :1;
    IO_BYTE _BF :1;
    IO_BYTE _IF :1;
    IO_BYTE _SO :1;
    IO_BYTE _OE :1;
    #else 
    IO_BYTE _OE :1;
    IO_BYTE _SO :1;
    IO_BYTE _IF :1;
    IO_BYTE _BF :1;
    IO_BYTE _IR :1;
    IO_BYTE _IE :1;
    IO_BYTE _HO :1;
    IO_BYTE _STA :1;
    #endif 
  }bit;
 }T01CR1STR;
 __IO_EXTERN __io T01CR1STR _t01cr1;   /* T01CR1 */
#define T01CR1 _t01cr1.byte
#define T01CR1_OE _t01cr1.bit._OE
#define T01CR1_SO _t01cr1.bit._SO
#define T01CR1_IF _t01cr1.bit._IF
#define T01CR1_BF _t01cr1.bit._BF
#define T01CR1_IR _t01cr1.bit._IR
#define T01CR1_IE _t01cr1.bit._IE
#define T01CR1_HO _t01cr1.bit._HO
#define T01CR1_STA _t01cr1.bit._STA
typedef union{   /* T00CR1 */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _STA :1;
    IO_BYTE _HO :1;
    IO_BYTE _IE :1;
    IO_BYTE _IR :1;
    IO_BYTE _BF :1;
    IO_BYTE _IF :1;
    IO_BYTE _SO :1;
    IO_BYTE _OE :1;
    #else 
    IO_BYTE _OE :1;
    IO_BYTE _SO :1;
    IO_BYTE _IF :1;
    IO_BYTE _BF :1;
    IO_BYTE _IR :1;
    IO_BYTE _IE :1;
    IO_BYTE _HO :1;
    IO_BYTE _STA :1;
    #endif 
  }bit;
 }T00CR1STR;
 __IO_EXTERN __io T00CR1STR _t00cr1;   /* T00CR1 */
#define T00CR1 _t00cr1.byte
#define T00CR1_OE _t00cr1.bit._OE
#define T00CR1_SO _t00cr1.bit._SO
#define T00CR1_IF _t00cr1.bit._IF
#define T00CR1_BF _t00cr1.bit._BF
#define T00CR1_IR _t00cr1.bit._IR
#define T00CR1_IE _t00cr1.bit._IE
#define T00CR1_HO _t00cr1.bit._HO
#define T00CR1_STA _t00cr1.bit._STA
typedef union{   /* T11CR1 */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _STA :1;
    IO_BYTE _HO :1;
    IO_BYTE _IE :1;
    IO_BYTE _IR :1;
    IO_BYTE _BF :1;
    IO_BYTE _IF :1;
    IO_BYTE _SO :1;
    IO_BYTE _OE :1;
    #else 
    IO_BYTE _OE :1;
    IO_BYTE _SO :1;
    IO_BYTE _IF :1;
    IO_BYTE _BF :1;
    IO_BYTE _IR :1;
    IO_BYTE _IE :1;
    IO_BYTE _HO :1;
    IO_BYTE _STA :1;
    #endif 
  }bit;
 }T11CR1STR;
 __IO_EXTERN __io T11CR1STR _t11cr1;   /* T11CR1 */
#define T11CR1 _t11cr1.byte
#define T11CR1_OE _t11cr1.bit._OE
#define T11CR1_SO _t11cr1.bit._SO
#define T11CR1_IF _t11cr1.bit._IF
#define T11CR1_BF _t11cr1.bit._BF
#define T11CR1_IR _t11cr1.bit._IR
#define T11CR1_IE _t11cr1.bit._IE
#define T11CR1_HO _t11cr1.bit._HO
#define T11CR1_STA _t11cr1.bit._STA
typedef union{   /* T10CR1 */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _STA :1;
    IO_BYTE _HO :1;
    IO_BYTE _IE :1;
    IO_BYTE _IR :1;
    IO_BYTE _BF :1;
    IO_BYTE _IF :1;
    IO_BYTE _SO :1;
    IO_BYTE _OE :1;
    #else 
    IO_BYTE _OE :1;
    IO_BYTE _SO :1;
    IO_BYTE _IF :1;
    IO_BYTE _BF :1;
    IO_BYTE _IR :1;
    IO_BYTE _IE :1;
    IO_BYTE _HO :1;
    IO_BYTE _STA :1;
    #endif 
  }bit;
  struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE :1;
    IO_BYTE _SL1 :2;
    IO_BYTE :2;
    IO_BYTE _SL0 :2;
    #else 
    IO_BYTE :1;
    IO_BYTE _SL0 :2;
    IO_BYTE :2;
    IO_BYTE _SL1 :2;
    #endif 
  }bitc; 
  
 }T10CR1STR;
 __IO_EXTERN __io T10CR1STR _t10cr1;   /* T10CR1 */
#define T10CR1 _t10cr1.byte
#define T10CR1_OE _t10cr1.bit._OE
#define T10CR1_SO _t10cr1.bit._SO
#define T10CR1_IF _t10cr1.bit._IF
#define T10CR1_BF _t10cr1.bit._BF
#define T10CR1_IR _t10cr1.bit._IR
#define T10CR1_IE _t10cr1.bit._IE
#define T10CR1_HO _t10cr1.bit._HO
#define T10CR1_STA _t10cr1.bit._STA
typedef union{   /* EIC10 */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _EIR1 :1;
    IO_BYTE _SL11 :1;
    IO_BYTE _SL10 :1;
    IO_BYTE _EIE1 :1;
    IO_BYTE _EIR0 :1;
    IO_BYTE _SL01 :1;
    IO_BYTE _SL00 :1;
    IO_BYTE _EIE1 :1;
    #else 
    IO_BYTE _EIE0 :1;
    IO_BYTE _SL00 :1;
    IO_BYTE _SL01 :1;
    IO_BYTE _EIR0 :1;
    IO_BYTE _EIE1 :1;
    IO_BYTE _SL10 :1;
    IO_BYTE _SL11 :1;
    IO_BYTE _EIR1 :1;
    #endif 
  }bit;
  struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE :1;
    IO_BYTE _SL1 :2;
    IO_BYTE :2;
    IO_BYTE _SL0 :2;
    #else 
    IO_BYTE :1;
    IO_BYTE _SL0 :2;
    IO_BYTE :2;
    IO_BYTE _SL1 :2;
    #endif 
  }bitc;
 }EIC10STR;
 __IO_EXTERN __io EIC10STR _eic10;   /* EIC10 */
#define EIC10 _eic10.byte
#define EIC10_EIE0 _eic10.bit._EIE0
#define EIC10_SL00 _eic10.bit._SL00
#define EIC10_SL01 _eic10.bit._SL01
#define EIC10_EIR0 _eic10.bit._EIR0
#define EIC10_EIE1 _eic10.bit._EIE1
#define EIC10_SL10 _eic10.bit._SL10
#define EIC10_SL11 _eic10.bit._SL11
#define EIC10_EIR1 _eic10.bit._EIR1
#define EIC10_SL0 _eic10.bitc._SL0
#define EIC10_SL1 _eic10.bitc._SL1
typedef union{   /* EIC20 */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _EIR1 :1;
    IO_BYTE _SL11 :1;
    IO_BYTE _SL10 :1;
    IO_BYTE _EIE1 :1;
    IO_BYTE _EIR0 :1;
    IO_BYTE _SL01 :1;
    IO_BYTE _SL00 :1;
    IO_BYTE _EIE1 :1;
    #else 
    IO_BYTE _EIE0 :1;
    IO_BYTE _SL00 :1;
    IO_BYTE _SL01 :1;
    IO_BYTE _EIR0 :1;
    IO_BYTE _EIE1 :1;
    IO_BYTE _SL10 :1;
    IO_BYTE _SL11 :1;
    IO_BYTE _EIR1 :1;
    #endif 
  }bit;
  struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE :1;
    IO_BYTE _SL1 :2;
    IO_BYTE :2;
    IO_BYTE _SL0 :2;
    #else 
    IO_BYTE :1;
    IO_BYTE _SL0 :2;
    IO_BYTE :2;
    IO_BYTE _SL1 :2;
    #endif 
  }bitc;
 }EIC20STR;
 __IO_EXTERN __io EIC20STR _eic20;   /* EIC20 */
#define EIC20 _eic20.byte
#define EIC20 _eic20.byte
#define EIC20_EIE0 _eic20.bit._EIE0
#define EIC20_SL00 _eic20.bit._SL00
#define EIC20_SL01 _eic20.bit._SL01
#define EIC20_EIR0 _eic20.bit._EIR0
#define EIC20_EIE1 _eic20.bit._EIE1
#define EIC20_SL10 _eic20.bit._SL10
#define EIC20_SL11 _eic20.bit._SL11
#define EIC20_EIR1 _eic20.bit._EIR1
#define EIC20_SL0 _eic20.bitc._SL0
#define EIC20_SL1 _eic20.bitc._SL1
typedef union{   /* EIC30 */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _EIR1 :1;
    IO_BYTE _SL11 :1;
    IO_BYTE _SL10 :1;
    IO_BYTE _EIE1 :1;
    IO_BYTE _EIR0 :1;
    IO_BYTE _SL01 :1;
    IO_BYTE _SL00 :1;
    IO_BYTE _EIE1 :1;
    #else 
    IO_BYTE _EIE0 :1;
    IO_BYTE _SL00 :1;
    IO_BYTE _SL01 :1;
    IO_BYTE _EIR0 :1;
    IO_BYTE _EIE1 :1;
    IO_BYTE _SL10 :1;
    IO_BYTE _SL11 :1;
    IO_BYTE _EIR1 :1;
    #endif 
  }bit;
  struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE :1;
    IO_BYTE _SL1 :2;
    IO_BYTE :2;
    IO_BYTE _SL0 :2;
    #else 
    IO_BYTE :1;
    IO_BYTE _SL0 :2;
    IO_BYTE :2;
    IO_BYTE _SL1 :2;
    #endif 
  }bitc;
 }EIC30STR;
 __IO_EXTERN __io EIC30STR _eic30;   /* EIC30 */
#define EIC30 _eic30.byte
#define EIC30_EIE0 _eic30.bit._EIE0
#define EIC30_SL00 _eic30.bit._SL00
#define EIC30_SL01 _eic30.bit._SL01
#define EIC30_EIR0 _eic30.bit._EIR0
#define EIC30_EIE1 _eic30.bit._EIE1
#define EIC30_SL10 _eic30.bit._SL10
#define EIC30_SL11 _eic30.bit._SL11
#define EIC30_EIR1 _eic30.bit._EIR1
#define EIC30_SL0 _eic30.bitc._SL0
#define EIC30_SL1 _eic30.bitc._SL1
typedef union{   /* SCR */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _PEN :1;
    IO_BYTE _P :1;
    IO_BYTE _SBL :1;
    IO_BYTE _CL :1;
    IO_BYTE _AD :1;
    IO_BYTE _CRE :1;
    IO_BYTE _RXE :1;
    IO_BYTE _TXE :1;
    #else 
    IO_BYTE _TXE :1;
    IO_BYTE _RXE :1;
    IO_BYTE _CRE :1;
    IO_BYTE _AD :1;
    IO_BYTE _CL :1;
    IO_BYTE _SBL :1;
    IO_BYTE _P :1;
    IO_BYTE _PEN :1;
    #endif 
  }bit;
 }SCRSTR;
 __IO_EXTERN __io SCRSTR _scr;   /* SCR */
#define SCR _scr.byte
#define SCR_TXE _scr.bit._TXE
#define SCR_RXE _scr.bit._RXE
#define SCR_CRE _scr.bit._CRE
#define SCR_AD _scr.bit._AD
#define SCR_CL _scr.bit._CL
#define SCR_SBL _scr.bit._SBL
#define SCR_P _scr.bit._P
#define SCR_PEN _scr.bit._PEN
typedef union{   /* SMR */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _MD1 :1;
    IO_BYTE _MD0 :1;
    IO_BYTE _OTO :1;
    IO_BYTE _EXT :1;
    IO_BYTE _REST :1;
    IO_BYTE _UPCL :1;
    IO_BYTE _SCKE :1;
    IO_BYTE _SOE :1;
    #else 
    IO_BYTE _SOE :1;
    IO_BYTE _SCKE :1;
    IO_BYTE _UPCL :1;
    IO_BYTE _REST :1;
    IO_BYTE _EXT :1;
    IO_BYTE _OTO :1;
    IO_BYTE _MD0 :1;
    IO_BYTE _MD1 :1;
    #endif 
  }bit;
  struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _MD :2;
    #else 
    IO_BYTE :6;
    IO_BYTE _MD :2;
    #endif 
  }bitc;
 }SMRSTR;
 __IO_EXTERN __io SMRSTR _smr;   /* SMR */
#define SMR _smr.byte
#define SMR_SOE _smr.bit._SOE
#define SMR_SCKE _smr.bit._SCKE
#define SMR_UPCL _smr.bit._UPCL
#define SMR_REST _smr.bit._REST
#define SMR_EXT _smr.bit._EXT
#define SMR_OTO _smr.bit._OTO
#define SMR_MD0 _smr.bit._MD0
#define SMR_MD1 _smr.bit._MD1
#define SMR_MD _smr.bitc._MD
typedef union{   /* SSR */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _PE :1;
    IO_BYTE _ORE :1;
    IO_BYTE _FRE :1;
    IO_BYTE _RDRF :1;
    IO_BYTE _TDRE :1;
    IO_BYTE _BDS :1;
    IO_BYTE _RIE :1;
    IO_BYTE _TIE :1;
    #else 
    IO_BYTE _TIE :1;
    IO_BYTE _RIE :1;
    IO_BYTE _BDS :1;
    IO_BYTE _TDRE :1;
    IO_BYTE _RDRF :1;
    IO_BYTE _FRE :1;
    IO_BYTE _ORE :1;
    IO_BYTE _PE :1;
    #endif 
  }bit;
 }SSRSTR;
 __IO_EXTERN __io SSRSTR _ssr;   /* SSR */
#define SSR _ssr.byte
#define SSR_TIE _ssr.bit._TIE
#define SSR_RIE _ssr.bit._RIE
#define SSR_BDS _ssr.bit._BDS
#define SSR_TDRE _ssr.bit._TDRE
#define SSR_RDRF _ssr.bit._RDRF
#define SSR_FRE _ssr.bit._FRE
#define SSR_ORE _ssr.bit._ORE
#define SSR_PE _ssr.bit._PE

__IO_EXTERN __io IO_BYTE _rdr;
#define RDR _rdr    /* RDR */
__IO_EXTERN __io IO_BYTE _tdr;
#define TDR _tdr    /* TDR */

typedef union{   /* ESCR */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _LBIE :1;
    IO_BYTE _LBD :1;
    IO_BYTE _LBL1 :1;
    IO_BYTE _LBL0 :1;
    IO_BYTE _SOPE :1;
    IO_BYTE _SIOP :1;
    IO_BYTE _CCO :1;
    IO_BYTE _SCES :1;
    #else 
    IO_BYTE _SCES :1;
    IO_BYTE _CCO :1;
    IO_BYTE _SIOP :1;
    IO_BYTE _SOPE :1;
    IO_BYTE _LBL0 :1;
    IO_BYTE _LBL1 :1;
    IO_BYTE _LBD :1;
    IO_BYTE _LBIE :1;
    #endif 
  }bit;
  struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE :2;
    IO_BYTE _LBL :2;
    #else 
    IO_BYTE :4;
    IO_BYTE _LBL :2;
    #endif 
  }bitc;
 }ESCRSTR;
 __IO_EXTERN __io ESCRSTR _escr;   /* ESCR */
#define ESCR _escr.byte
#define ESCR_SCES _escr.bit._SCES
#define ESCR_CCO _escr.bit._CCO
#define ESCR_SIOP _escr.bit._SIOP
#define ESCR_SOPE _escr.bit._SOPE
#define ESCR_LBL0 _escr.bit._LBL0
#define ESCR_LBL1 _escr.bit._LBL1
#define ESCR_LBD _escr.bit._LBD
#define ESCR_LBIE _escr.bit._LBIE
#define ESCR_LBL _escr.bitc._LBL
typedef union{   /* ECCR */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE  :1;
    IO_BYTE _LBR :1;
    IO_BYTE _MS :1;
    IO_BYTE _SCDE :1;
    IO_BYTE _SSM :1;
    IO_BYTE  :1;
    IO_BYTE _RBI :1;
    IO_BYTE _TBI :1;
    #else 
    IO_BYTE _TBI :1;
    IO_BYTE _RBI :1;
    IO_BYTE  :1;
    IO_BYTE _SSM :1;
    IO_BYTE _SCDE :1;
    IO_BYTE _MS :1;
    IO_BYTE _LBR :1;
    IO_BYTE  :1;
    #endif 
  }bit;
 }ECCRSTR;
 __IO_EXTERN __io ECCRSTR _eccr;   /* ECCR */
#define ECCR _eccr.byte
#define ECCR_TBI _eccr.bit._TBI
#define ECCR_RBI _eccr.bit._RBI
#define ECCR_SSM _eccr.bit._SSM
#define ECCR_SCDE _eccr.bit._SCDE
#define ECCR_MS _eccr.bit._MS
#define ECCR_LBR _eccr.bit._LBR
typedef union{   /* ADC1 */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _ANS3 :1;
    IO_BYTE _ANS2 :1;
    IO_BYTE _ANS1 :1;
    IO_BYTE _ANS0 :1;
    IO_BYTE _ADI :1;
    IO_BYTE _ADMV :1;
    IO_BYTE _ADMVX :1;
    IO_BYTE _AD :1;
    #else 
    IO_BYTE _AD :1;
    IO_BYTE _ADMVX :1;
    IO_BYTE _ADMV :1;
    IO_BYTE _ADI :1;
    IO_BYTE _ANS0 :1;
    IO_BYTE _ANS1 :1;
    IO_BYTE _ANS2 :1;
    IO_BYTE _ANS3 :1;
    #endif 
  }bit;
  struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _ANS :4;
    #else 
    IO_BYTE :4;
    IO_BYTE _ANS :4;
    #endif 
  }bitc;
 }ADC1STR;
 __IO_EXTERN __io ADC1STR _adc1;   /* ADC1 */
#define ADC1 _adc1.byte
#define ADC1_AD _adc1.bit._AD
#define ADC1_ADMVX _adc1.bit._ADMVX
#define ADC1_ADMV _adc1.bit._ADMV
#define ADC1_ADI _adc1.bit._ADI
#define ADC1_ANS0 _adc1.bit._ANS0
#define ADC1_ANS1 _adc1.bit._ANS1
#define ADC1_ANS2 _adc1.bit._ANS2
#define ADC1_ANS3 _adc1.bit._ANS3
#define ADC1_ANS _adc1.bitc._ANS
typedef union{   /* ADC2 */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _AD8 :1;
    IO_BYTE _TIM1 :1;
    IO_BYTE _TIM0 :1;
    IO_BYTE _ADCK :1;
    IO_BYTE _ADIE :1;
    IO_BYTE _EXT :1;
    IO_BYTE _CKDIV1 :1;
    IO_BYTE _CKDIV0 :1;
    #else 
    IO_BYTE _CKDIV0 :1;
    IO_BYTE _CKDIV1 :1;
    IO_BYTE _EXT :1;
    IO_BYTE _ADIE :1;
    IO_BYTE _ADCK :1;
    IO_BYTE _TIM0 :1;
    IO_BYTE _TIM1 :1;
    IO_BYTE _AD8 :1;
    #endif 
  }bit;
  struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE :1;
    IO_BYTE _TIM :2;
    #else 
    IO_BYTE :5;
    IO_BYTE _TIM :2;
    #endif 
  }bitc;
 }ADC2STR;
 __IO_EXTERN __io ADC2STR _adc2;   /* ADC2 */
#define ADC2 _adc2.byte
#define ADC2_CKDIV0 _adc2.bit._CKDIV0
#define ADC2_CKDIV1 _adc2.bit._CKDIV1
#define ADC2_EXT _adc2.bit._EXT
#define ADC2_ADIE _adc2.bit._ADIE
#define ADC2_ADCK _adc2.bit._ADCK
#define ADC2_TIM0 _adc2.bit._TIM0
#define ADC2_TIM1 _adc2.bit._TIM1
#define ADC2_AD8 _adc2.bit._AD8
#define ADC2_TIM _adc2.bitc._TIM
typedef union{   /* ADD */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _SAR9 :1;
    IO_BYTE _SAR8 :1;
    #else 
    IO_BYTE _SAR8 :1;
    IO_BYTE _SAR9 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    #endif 
  }bit;
 }ADDHSTR;
typedef union{  
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _SAR7 :1;
    IO_BYTE _SAR6 :1;
    IO_BYTE _SAR5 :1;
    IO_BYTE _SAR4 :1;
    IO_BYTE _SAR3 :1;
    IO_BYTE _SAR2 :1;
    IO_BYTE _SAR1 :1;
    IO_BYTE _SAR0 :1;
    #else 
    IO_BYTE _SAR0 :1;
    IO_BYTE _SAR1 :1;
    IO_BYTE _SAR2 :1;
    IO_BYTE _SAR3 :1;
    IO_BYTE _SAR4 :1;
    IO_BYTE _SAR5 :1;
    IO_BYTE _SAR6 :1;
    IO_BYTE _SAR7 :1;
    #endif 
  }bit;
 }ADDLSTR;
 __IO_EXTERN __io ADDHSTR _addh;   /* ADD */
#define ADDH _addh.byte
#define ADDH_SAR8 _addh.bit._SAR8
#define ADDH_SAR9 _addh.bit._SAR9
__IO_EXTERN __io ADDLSTR _addl;  
#define ADDL _addl.byte
#define ADDL_SAR0 _addl.bit._SAR0
#define ADDL_SAR1 _addl.bit._SAR1
#define ADDL_SAR2 _addl.bit._SAR2
#define ADDL_SAR3 _addl.bit._SAR3
#define ADDL_SAR4 _addl.bit._SAR4
#define ADDL_SAR5 _addl.bit._SAR5
#define ADDL_SAR6 _addl.bit._SAR6
#define ADDL_SAR7 _addl.bit._SAR7
typedef union{   /* FSR */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _RDYIRQ :1;
    IO_BYTE _RDY :1;
    IO_BYTE  :1;
    IO_BYTE _IRQEN :1;
    IO_BYTE _WRE :1;
    IO_BYTE  :1;
    #else 
    IO_BYTE  :1;
    IO_BYTE _WRE :1;
    IO_BYTE _IRQEN :1;
    IO_BYTE  :1;
    IO_BYTE _RDY :1;
    IO_BYTE _RDYIRQ :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    #endif 
  }bit;
 }FSRSTR;
 __IO_EXTERN __io FSRSTR _fsr;   /* FSR */
#define FSR _fsr.byte
#define FSR_WRE _fsr.bit._WRE
#define FSR_IRQEN _fsr.bit._IRQEN
#define FSR_RDY _fsr.bit._RDY
#define FSR_RDYIRQ _fsr.bit._RDYIRQ
typedef union{   /* WREN */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _EN2 :1;
    IO_BYTE _EN1 :1;
    IO_BYTE _EN0 :1;
    #else 
    IO_BYTE _EN0 :1;
    IO_BYTE _EN1 :1;
    IO_BYTE _EN2 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    #endif 
  }bit;
 }WRENSTR;
 __IO_EXTERN __io WRENSTR _wren;   /* WREN */
#define WREN _wren.byte
#define WREN_EN0 _wren.bit._EN0
#define WREN_EN1 _wren.bit._EN1
#define WREN_EN2 _wren.bit._EN2
typedef union{   /* WROR */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _DRR2 :1;
    IO_BYTE _DRR1 :1;
    IO_BYTE _DRR0 :1;
    #else 
    IO_BYTE _DRR0 :1;
    IO_BYTE _DRR1 :1;
    IO_BYTE _DRR2 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    #endif 
  }bit;
 }WRORSTR;
 __IO_EXTERN __io WRORSTR _wror;   /* WROR */
#define WROR _wror.byte
#define WROR_DRR0 _wror.bit._DRR0
#define WROR_DRR1 _wror.bit._DRR1
#define WROR_DRR2 _wror.bit._DRR2
typedef union{   /* ILR0 */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _L031 :1;
    IO_BYTE _L030 :1;
    IO_BYTE _L021 :1;
    IO_BYTE _L020 :1;
    IO_BYTE _L011 :1;
    IO_BYTE _L010 :1;
    IO_BYTE _L001 :1;
    IO_BYTE _L000 :1;
    #else 
    IO_BYTE _L000 :1;
    IO_BYTE _L001 :1;
    IO_BYTE _L010 :1;
    IO_BYTE _L011 :1;
    IO_BYTE _L020 :1;
    IO_BYTE _L021 :1;
    IO_BYTE _L030 :1;
    IO_BYTE _L031 :1;
    #endif 
  }bit;
  struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _L03 :2;
    IO_BYTE _L02 :2;
    IO_BYTE _L01 :2;
    IO_BYTE _L00 :2;
    #else 
    IO_BYTE _L00 :2;
    IO_BYTE _L01 :2;
    IO_BYTE _L02 :2;
    IO_BYTE _L03 :2;
    #endif 
  }bitc;
 }ILR0STR;
__IO_EXTERN __io ILR0STR _ilr0;   /* ILR0 */
#define ILR0 _ilr0.byte
#define ILR0_L000 _ilr0.bit._L000
#define ILR0_L001 _ilr0.bit._L001
#define ILR0_L010 _ilr0.bit._L010
#define ILR0_L011 _ilr0.bit._L011
#define ILR0_L020 _ilr0.bit._L020
#define ILR0_L021 _ilr0.bit._L021
#define ILR0_L030 _ilr0.bit._L030
#define ILR0_L031 _ilr0.bit._L031
#define ILR0_L00 _ilr0.bitc._L00
#define ILR0_L01 _ilr0.bitc._L01
#define ILR0_L02 _ilr0.bitc._L02
#define ILR0_L03 _ilr0.bitc._L03
typedef union{   /* ILR1 */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _L071 :1;
    IO_BYTE _L070 :1;
    IO_BYTE _L061 :1;
    IO_BYTE _L060 :1;
    IO_BYTE _L051 :1;
    IO_BYTE _L050 :1;
    IO_BYTE _L041 :1;
    IO_BYTE _L040 :1;
    #else 
    IO_BYTE _L040 :1;
    IO_BYTE _L041 :1;
    IO_BYTE _L050 :1;
    IO_BYTE _L051 :1;
    IO_BYTE _L060 :1;
    IO_BYTE _L061 :1;
    IO_BYTE _L070 :1;
    IO_BYTE _L071 :1;
    #endif 
  }bit;
  struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _L07 :2;
    IO_BYTE _L06 :2;
    IO_BYTE _L05 :2;
    IO_BYTE _L04 :2;
    #else 
    IO_BYTE _L04 :2;
    IO_BYTE _L05 :2;
    IO_BYTE _L06 :2;
    IO_BYTE _L07 :2;
    #endif 
  }bitc;
 }ILR1STR;
__IO_EXTERN __io ILR1STR _ilr1;   /* ILR1 */
#define ILR1 _ilr1.byte
#define ILR1_L040 _ilr1.bit._L040
#define ILR1_L041 _ilr1.bit._L041
#define ILR1_L050 _ilr1.bit._L050
#define ILR1_L051 _ilr1.bit._L051
#define ILR1_L060 _ilr1.bit._L060
#define ILR1_L061 _ilr1.bit._L061
#define ILR1_L070 _ilr1.bit._L070
#define ILR1_L071 _ilr1.bit._L071
#define ILR1_L04 _ilr1.bitc._L04
#define ILR1_L05 _ilr1.bitc._L05
#define ILR1_L06 _ilr1.bitc._L06
#define ILR1_L07 _ilr1.bitc._L07
typedef union{   /* ILR2 */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _L111 :1;
    IO_BYTE _L110 :1;
    IO_BYTE _L101 :1;
    IO_BYTE _L100 :1;
    IO_BYTE _L091 :1;
    IO_BYTE _L090 :1;
    IO_BYTE _L081 :1;
    IO_BYTE _L080 :1;
    #else 
    IO_BYTE _L080 :1;
    IO_BYTE _L081 :1;
    IO_BYTE _L090 :1;
    IO_BYTE _L091 :1;
    IO_BYTE _L100 :1;
    IO_BYTE _L101 :1;
    IO_BYTE _L110 :1;
    IO_BYTE _L111 :1;
    #endif 
  }bit;
  struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _L11 :2;
    IO_BYTE _L10 :2;
    IO_BYTE _L09 :2;
    IO_BYTE _L08 :2;
    #else 
    IO_BYTE _L08 :2;
    IO_BYTE _L09 :2;
    IO_BYTE _L10 :2;
    IO_BYTE _L11 :2;
    #endif 
  }bitc;
 }ILR2STR;
 __IO_EXTERN __io ILR2STR _ilr2;   /* ILR2 */
#define ILR2 _ilr2.byte
#define ILR2_L080 _ilr2.bit._L080
#define ILR2_L081 _ilr2.bit._L081
#define ILR2_L090 _ilr2.bit._L090
#define ILR2_L091 _ilr2.bit._L091
#define ILR2_L100 _ilr2.bit._L100
#define ILR2_L101 _ilr2.bit._L101
#define ILR2_L110 _ilr2.bit._L110
#define ILR2_L111 _ilr2.bit._L111
#define ILR2_L08 _ilr2.bitc._L08
#define ILR2_L09 _ilr2.bitc._L09
#define ILR2_L10 _ilr2.bitc._L10
#define ILR2_L11 _ilr2.bitc._L11
typedef union{   /* ILR3 */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _L151 :1;
    IO_BYTE _L150 :1;
    IO_BYTE _L141 :1;
    IO_BYTE _L140 :1;
    IO_BYTE _L131 :1;
    IO_BYTE _L130 :1;
    IO_BYTE _L121 :1;
    IO_BYTE _L120 :1;
    #else 
    IO_BYTE _L120 :1;
    IO_BYTE _L121 :1;
    IO_BYTE _L130 :1;
    IO_BYTE _L131 :1;
    IO_BYTE _L140 :1;
    IO_BYTE _L141 :1;
    IO_BYTE _L150 :1;
    IO_BYTE _L151 :1;
    #endif 
  }bit;
  struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _L15 :2;
    IO_BYTE _L14 :2;
    IO_BYTE _L13 :2;
    IO_BYTE _L12 :2;
    #else 
    IO_BYTE _L12 :2;
    IO_BYTE _L13 :2;
    IO_BYTE _L14 :2;
    IO_BYTE _L15 :2;
    #endif 
  }bitc;
 }ILR3STR;
 __IO_EXTERN __io ILR3STR _ilr3;   /* ILR3 */
#define ILR3 _ilr3.byte
#define ILR3_L120 _ilr3.bit._L120
#define ILR3_L121 _ilr3.bit._L121
#define ILR3_L130 _ilr3.bit._L130
#define ILR3_L131 _ilr3.bit._L131
#define ILR3_L140 _ilr3.bit._L140
#define ILR3_L141 _ilr3.bit._L141
#define ILR3_L150 _ilr3.bit._L150
#define ILR3_L151 _ilr3.bit._L151
#define ILR3_L12 _ilr3.bitc._L12
#define ILR3_L13 _ilr3.bitc._L13
#define ILR3_L14 _ilr3.bitc._L14
#define ILR3_L15 _ilr3.bitc._L15
typedef union{   /* ILR4 */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _L191 :1;
    IO_BYTE _L190 :1;
    IO_BYTE _L181 :1;
    IO_BYTE _L180 :1;
    IO_BYTE _L171 :1;
    IO_BYTE _L170 :1;
    IO_BYTE _L161 :1;
    IO_BYTE _L160 :1;
    #else 
    IO_BYTE _L160 :1;
    IO_BYTE _L161 :1;
    IO_BYTE _L170 :1;
    IO_BYTE _L171 :1;
    IO_BYTE _L180 :1;
    IO_BYTE _L181 :1;
    IO_BYTE _L190 :1;
    IO_BYTE _L191 :1;
    #endif 
  }bit;
  struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _L19 :2;
    IO_BYTE _L18 :2;
    IO_BYTE _L17 :2;
    IO_BYTE _L16 :2;
    #else 
    IO_BYTE _L16 :2;
    IO_BYTE _L17 :2;
    IO_BYTE _L18 :2;
    IO_BYTE _L19 :2;
    #endif 
  }bitc;
 }ILR4STR;
 __IO_EXTERN __io ILR4STR _ilr4;   /* ILR4 */
#define ILR4 _ilr4.byte
#define ILR4_L160 _ilr4.bit._L160
#define ILR4_L161 _ilr4.bit._L161
#define ILR4_L170 _ilr4.bit._L170
#define ILR4_L171 _ilr4.bit._L171
#define ILR4_L180 _ilr4.bit._L180
#define ILR4_L181 _ilr4.bit._L181
#define ILR4_L190 _ilr4.bit._L190
#define ILR4_L191 _ilr4.bit._L191
#define ILR4_L16 _ilr4.bitc._L16
#define ILR4_L17 _ilr4.bitc._L17
#define ILR4_L18 _ilr4.bitc._L18
#define ILR4_L19 _ilr4.bitc._L19
typedef union{   /* ILR5 */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _L231 :1;
    IO_BYTE _L230 :1;
    IO_BYTE _L221 :1;
    IO_BYTE _L220 :1;
    IO_BYTE _L211 :1;
    IO_BYTE _L210 :1;
    IO_BYTE _L201 :1;
    IO_BYTE _L200 :1;
    #else 
    IO_BYTE _L200 :1;
    IO_BYTE _L201 :1;
    IO_BYTE _L210 :1;
    IO_BYTE _L211 :1;
    IO_BYTE _L220 :1;
    IO_BYTE _L221 :1;
    IO_BYTE _L230 :1;
    IO_BYTE _L231 :1;
    #endif 
  }bit;
  struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _L23 :2;
    IO_BYTE _L22 :2;
    IO_BYTE _L21 :2;
    IO_BYTE _L20 :2;
    #else 
    IO_BYTE _L20 :2;
    IO_BYTE _L21 :2;
    IO_BYTE _L22 :2;
    IO_BYTE _L23 :2;
    #endif 
  }bitc;
 }ILR5STR;
 __IO_EXTERN __io ILR5STR _ilr5;   /* ILR5 */
#define ILR5 _ilr5.byte
#define ILR5_L200 _ilr5.bit._L200
#define ILR5_L201 _ilr5.bit._L201
#define ILR5_L210 _ilr5.bit._L210
#define ILR5_L211 _ilr5.bit._L211
#define ILR5_L220 _ilr5.bit._L220
#define ILR5_L221 _ilr5.bit._L221
#define ILR5_L230 _ilr5.bit._L230
#define ILR5_L231 _ilr5.bit._L231
#define ILR5_L20 _ilr5.bitc._L20
#define ILR5_L21 _ilr5.bitc._L21
#define ILR5_L22 _ilr5.bitc._L22
#define ILR5_L23 _ilr5.bitc._L23

__IO_EXTENDED IO_BYTE _wrarh0;
#define WRARH0 _wrarh0    /* WRAR0 */
__IO_EXTENDED IO_BYTE _wrarl0;
#define WRARL0 _wrarl0   
__IO_EXTENDED IO_BYTE _wrdr0;
#define WRDR0 _wrdr0    /* WRDR0 */
__IO_EXTENDED IO_BYTE _wrarh1;
#define WRARH1 _wrarh1    /* WRAR1 */
__IO_EXTENDED IO_BYTE _wrarl1;
#define WRARL1 _wrarl1   
__IO_EXTENDED IO_BYTE _wrdr1;
#define WRDR1 _wrdr1    /* WRDR1 */
__IO_EXTENDED IO_BYTE _wrarh2;
#define WRARH2 _wrarh2    /* WRAR2 */
__IO_EXTENDED IO_BYTE _wrarl2;
#define WRARL2 _wrarl2   
__IO_EXTENDED IO_BYTE _wrdr2;
#define WRDR2 _wrdr2    /* WRDR2 */

typedef union{   /* T01CR0 */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _IFE :1;
    IO_BYTE _C2 :1;
    IO_BYTE _C1 :1;
    IO_BYTE _C0 :1;
    IO_BYTE _F3 :1;
    IO_BYTE _F2 :1;
    IO_BYTE _F1 :1;
    IO_BYTE _F0 :1;
    #else 
    IO_BYTE _F0 :1;
    IO_BYTE _F1 :1;
    IO_BYTE _F2 :1;
    IO_BYTE _F3 :1;
    IO_BYTE _C0 :1;
    IO_BYTE _C1 :1;
    IO_BYTE _C2 :1;
    IO_BYTE _IFE :1;
    #endif 
  }bit;
  struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE :1;
    IO_BYTE _C :3;
    IO_BYTE _F :4;
    #else 
    IO_BYTE _F :4;
    IO_BYTE _C :3;
    #endif 
  }bitc;
 }T01CR0STR;
 __IO_EXTENDED T01CR0STR _t01cr0;   /* T01CR0 */
#define T01CR0 _t01cr0.byte
#define T01CR0_F0 _t01cr0.bit._F0
#define T01CR0_F1 _t01cr0.bit._F1
#define T01CR0_F2 _t01cr0.bit._F2
#define T01CR0_F3 _t01cr0.bit._F3
#define T01CR0_C0 _t01cr0.bit._C0
#define T01CR0_C1 _t01cr0.bit._C1
#define T01CR0_C2 _t01cr0.bit._C2
#define T01CR0_IFE _t01cr0.bit._IFE
#define T01CR0_F _t01cr0.bitc._F
#define T01CR0_C _t01cr0.bitc._C
typedef union{   /* T00CR0 */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _IFE :1;
    IO_BYTE _C2 :1;
    IO_BYTE _C1 :1;
    IO_BYTE _C0 :1;
    IO_BYTE _F3 :1;
    IO_BYTE _F2 :1;
    IO_BYTE _F1 :1;
    IO_BYTE _F0 :1;
    #else 
    IO_BYTE _F0 :1;
    IO_BYTE _F1 :1;
    IO_BYTE _F2 :1;
    IO_BYTE _F3 :1;
    IO_BYTE _C0 :1;
    IO_BYTE _C1 :1;
    IO_BYTE _C2 :1;
    IO_BYTE _IFE :1;
    #endif 
  }bit;
  struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE :1;
    IO_BYTE _C :3;
    IO_BYTE _F :4;
    #else 
    IO_BYTE _F :4;
    IO_BYTE _C :3;
    #endif 
  }bitc;
 }T00CR0STR;
 __IO_EXTENDED T00CR0STR _t00cr0;   /* T00CR0 */
#define T00CR0 _t00cr0.byte
#define T00CR0_F0 _t00cr0.bit._F0
#define T00CR0_F1 _t00cr0.bit._F1
#define T00CR0_F2 _t00cr0.bit._F2
#define T00CR0_F3 _t00cr0.bit._F3
#define T00CR0_C0 _t00cr0.bit._C0
#define T00CR0_C1 _t00cr0.bit._C1
#define T00CR0_C2 _t00cr0.bit._C2
#define T00CR0_IFE _t00cr0.bit._IFE
#define T00CR0_F _t00cr0.bitc._F
#define T00CR0_C _t00cr0.bitc._C
__IO_EXTENDED IO_WORD _t0dr;
#define T0DR _t0dr    /* T01DR */
__IO_EXTENDED IO_BYTE _t01dr;
#define T01DR _t01dr   
__IO_EXTENDED IO_BYTE _t00dr;
#define T00DR _t00dr  
typedef union{   /* TMCR0 */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _T01 :1;
    IO_BYTE _T00 :1;
    IO_BYTE _IIS :1;
    IO_BYTE _MOD :1;
    IO_BYTE _FE11 :1;
    IO_BYTE _FE10 :1;
    IO_BYTE _FE01 :1;
    IO_BYTE _FE00 :1;
    #else 
    IO_BYTE _FE00 :1;
    IO_BYTE _FE01 :1;
    IO_BYTE _FE10 :1;
    IO_BYTE _FE11 :1;
    IO_BYTE _MOD :1;
    IO_BYTE _IIS :1;
    IO_BYTE _T00 :1;
    IO_BYTE _T01 :1;
    #endif 
  }bit;
  struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE :4;
    IO_BYTE _FE1 :2;
    IO_BYTE _FE0 :2;
    #else 
    IO_BYTE _FE0 :2;
    IO_BYTE _FE1 :2;
    #endif 
  }bitc;
 }TMCR0STR;
 __IO_EXTENDED TMCR0STR _tmcr0;   /* TMCR0 */
#define TMCR0 _tmcr0.byte
#define TMCR0_FE00 _tmcr0.bit._FE00
#define TMCR0_FE01 _tmcr0.bit._FE01
#define TMCR0_FE10 _tmcr0.bit._FE10
#define TMCR0_FE11 _tmcr0.bit._FE11
#define TMCR0_MOD _tmcr0.bit._MOD
#define TMCR0_IIS _tmcr0.bit._IIS
#define TMCR0_T00 _tmcr0.bit._T00
#define TMCR0_T01 _tmcr0.bit._T01
#define TMCR0_FE0 _tmcr0.bitc._FE0
#define TMCR0_FE1 _tmcr0.bitc._FE1
typedef union{   /* T11CR0 */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _IFE :1;
    IO_BYTE _C2 :1;
    IO_BYTE _C1 :1;
    IO_BYTE _C0 :1;
    IO_BYTE _F3 :1;
    IO_BYTE _F2 :1;
    IO_BYTE _F1 :1;
    IO_BYTE _F0 :1;
    #else 
    IO_BYTE _F0 :1;
    IO_BYTE _F1 :1;
    IO_BYTE _F2 :1;
    IO_BYTE _F3 :1;
    IO_BYTE _C0 :1;
    IO_BYTE _C1 :1;
    IO_BYTE _C2 :1;
    IO_BYTE _IFE :1;
    #endif 
  }bit;
  struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE :1;
    IO_BYTE _C :3;
    IO_BYTE _F :4;
    #else 
    IO_BYTE _F :4;
    IO_BYTE _C :3;
    #endif 
  }bitc;
 }T11CR0STR;
 __IO_EXTENDED T11CR0STR _t11cr0;   /* T11CR0 */
#define T11CR0 _t11cr0.byte
#define T11CR0_F0 _t11cr0.bit._F0
#define T11CR0_F1 _t11cr0.bit._F1
#define T11CR0_F2 _t11cr0.bit._F2
#define T11CR0_F3 _t11cr0.bit._F3
#define T11CR0_C0 _t11cr0.bit._C0
#define T11CR0_C1 _t11cr0.bit._C1
#define T11CR0_C2 _t11cr0.bit._C2
#define T11CR0_IFE _t11cr0.bit._IFE
#define T11CR0_F _t11cr0.bitc._F
#define T11CR0_C _t11cr0.bitc._C
typedef union{   /* T10CR0 */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _IFE :1;
    IO_BYTE _C2 :1;
    IO_BYTE _C1 :1;
    IO_BYTE _C0 :1;
    IO_BYTE _F3 :1;
    IO_BYTE _F2 :1;
    IO_BYTE _F1 :1;
    IO_BYTE _F0 :1;
    #else 
    IO_BYTE _F0 :1;
    IO_BYTE _F1 :1;
    IO_BYTE _F2 :1;
    IO_BYTE _F3 :1;
    IO_BYTE _C0 :1;
    IO_BYTE _C1 :1;
    IO_BYTE _C2 :1;
    IO_BYTE _IFE :1;
    #endif 
  }bit;
  struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE :1;
    IO_BYTE _C :3;
    IO_BYTE _F :4;
    #else 
    IO_BYTE _F :4;
    IO_BYTE _C :3;
    #endif 
  }bitc;
 }T10CR0STR;
 __IO_EXTENDED T10CR0STR _t10cr0;   /* T10CR0 */
#define T10CR0 _t10cr0.byte
#define T10CR0_F0 _t10cr0.bit._F0
#define T10CR0_F1 _t10cr0.bit._F1
#define T10CR0_F2 _t10cr0.bit._F2
#define T10CR0_F3 _t10cr0.bit._F3
#define T10CR0_C0 _t10cr0.bit._C0
#define T10CR0_C1 _t10cr0.bit._C1
#define T10CR0_C2 _t10cr0.bit._C2
#define T10CR0_IFE _t10cr0.bit._IFE
#define T10CR0_F _t10cr0.bitc._F
#define T10CR0_C _t10cr0.bitc._C
__IO_EXTENDED IO_WORD _t1dr;
#define T1DR _t1dr    /* T10DR */
__IO_EXTENDED IO_BYTE _t11dr;
#define T11DR _t11dr    /* T11DR */
__IO_EXTENDED IO_BYTE _t10dr;
#define T10DR _t10dr    /* T10DR */
typedef union{   /* TMCR1 */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _T01 :1;
    IO_BYTE _T00 :1;
    IO_BYTE _IIS :1;
    IO_BYTE _MOD :1;
    IO_BYTE _FE11 :1;
    IO_BYTE _FE10 :1;
    IO_BYTE _FE01 :1;
    IO_BYTE _FE00 :1;
    #else 
    IO_BYTE _FE00 :1;
    IO_BYTE _FE01 :1;
    IO_BYTE _FE10 :1;
    IO_BYTE _FE11 :1;
    IO_BYTE _MOD :1;
    IO_BYTE _IIS :1;
    IO_BYTE _T00 :1;
    IO_BYTE _T01 :1;
    #endif 
  }bit;
  struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE :4;
    IO_BYTE _FE1 :2;
    IO_BYTE _FE0 :2;
    #else 
    IO_BYTE _FE0 :2;
    IO_BYTE _FE1 :2;
    #endif 
  }bitc;
 }TMCR1STR;
 __IO_EXTENDED TMCR1STR _tmcr1;   /* TMCR1 */
#define TMCR1 _tmcr1.byte
#define TMCR1_FE00 _tmcr1.bit._FE00
#define TMCR1_FE01 _tmcr1.bit._FE01
#define TMCR1_FE10 _tmcr1.bit._FE10
#define TMCR1_FE11 _tmcr1.bit._FE11
#define TMCR1_MOD _tmcr1.bit._MOD
#define TMCR1_IIS _tmcr1.bit._IIS
#define TMCR1_T00 _tmcr1.bit._T00
#define TMCR1_T01 _tmcr1.bit._T01
#define TMCR1_FE0 _tmcr1.bitc._FE0
#define TMCR1_FE1 _tmcr1.bitc._FE1
__IO_EXTENDED IO_WORD _bgr;
#define BGR _bgr    /* BGR */
__IO_EXTENDED IO_BYTE _bgr1;
#define BGR1 _bgr1   
__IO_EXTENDED IO_BYTE _bgr0;
#define BGR0 _bgr0   
///////////
typedef union{   /* AIDRL */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _P05 :1;
    IO_BYTE _P04 :1;
    IO_BYTE _P03 :1;
    IO_BYTE _P02 :1;
    IO_BYTE _P01 :1;
    IO_BYTE _P00 :1;
    #else 
    IO_BYTE _P00 :1;
    IO_BYTE _P01 :1;
    IO_BYTE _P02 :1;
    IO_BYTE _P03 :1;
    IO_BYTE _P04 :1;
    IO_BYTE _P05 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    #endif 
  }bit;
 }AIDRLSTR;
 __IO_EXTENDED AIDRLSTR _aidrl;   /* AIDRL */
#define AIDRL _aidrl.byte
#define AIDRL_P00 _aidrl.bit._P00
#define AIDRL_P01 _aidrl.bit._P01
#define AIDRL_P02 _aidrl.bit._P02
#define AIDRL_P03 _aidrl.bit._P03
#define AIDRL_P04 _aidrl.bit._P04
#define AIDRL_P05 _aidrl.bit._P05



typedef union{   /* CRTH */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE  :1;
    IO_BYTE _CRSEL1 :1;
    IO_BYTE _CRSEL0 :1;
    IO_BYTE _CRTH4 :1;
    IO_BYTE _CRTH3 :1;
    IO_BYTE _CRTH2 :1;
    IO_BYTE _CRTH1 :1;
    IO_BYTE _CRTH0:1;
    #else 
    IO_BYTE _CRTH0 :1;
    IO_BYTE _CRTH1 :1;
    IO_BYTE _CRTH2 :1;
    IO_BYTE _CRTH3 :1;
    IO_BYTE _CRTH4 :1;
    IO_BYTE _CRSEL0 :1;
    IO_BYTE _CRSEL1 :1;
    IO_BYTE  :1;
    #endif 
  }bit;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE :1;
    IO_BYTE _CRSEL :2;
    IO_BYTE _CRTH :5;
    #else 
    IO_BYTE _CRTH :5;
    IO_BYTE _CRSEL :2;
    #endif 
  }bitc;
 }CRTHSTR;
 __IO_EXTENDED CRTHSTR _crth;   /* CRTH */
#define CRTH _crth.byte
#define CRTH_CRTH0 _crth.bit._CRTH0
#define CRTH_CRTH1 _crth.bit._CRTH1
#define CRTH_CRTH2 _crth.bit._CRTH2
#define CRTH_CRTH3 _crth.bit._CRTH3
#define CRTH_CRTH4 _crth.bit._CRTH4
#define CRTH_CRSEL0 _crth.bit._CRCEL0
#define CRTH_CRSEL1 _crth.bit._CRCEL1
#define CRTH_CRTH _crth.bitc._CRTH
#define CRTH_CRSEL _crth.bitc._CRSEL
typedef union{   /* CRTL */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _CRTL4 :1;
    IO_BYTE _CRTL3 :1;
    IO_BYTE _CRTL2 :1;
    IO_BYTE _CRTL1 :1;
    IO_BYTE _CRTL0 :1;
    #else 
    IO_BYTE _CRTL0 :1;
    IO_BYTE _CRTL1 :1;
    IO_BYTE _CRTL2 :1;
    IO_BYTE _CRTL3 :1;
    IO_BYTE _CRTL4 :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    #endif 
  }bit;
 }CRTLSTR;
 __IO_EXTENDED IO_BYTE _crtl;/* CRTL */
#define CRTL _crtl 
#define CRTL_CRTL0 _crtl.bit._CRTL0
#define CRTL_CRTL1 _crtl.bit._CRTL1
#define CRTL_CRTL2 _crtl.bit._CRTL2
#define CRTL_CRTL3 _crtl.bit._CRTL3
#define CRTL_CRTL4 _crtl.bit._CRTL4

typedef union{   /* SYSC */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _PGSEL :1;
    IO_BYTE _PFSEL :1;
    IO_BYTE _EXCK1 :1;
    IO_BYTE _EXCK0 :1;
    IO_BYTE _EC0SL :1;
    IO_BYTE  :1;
    IO_BYTE _RSTOE :1;
    IO_BYTE _RSTEN:1;
    #else 
    IO_BYTE _RSTEN :1;
    IO_BYTE _RSTOE :1;
    IO_BYTE  :1;
    IO_BYTE _EC0SL :1;
    IO_BYTE _EXCK0 :1;
    IO_BYTE _EXCK1 :1;
    IO_BYTE _PFSEL :1;
    IO_BYTE _PGSEL :1;
    #endif 
  }bit;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE :2;
    IO_BYTE _EXCK :2;
    #else 
    IO_BYTE :4;
    IO_BYTE _EXCK :2;
    #endif 
  }bitc;
 }SYSCSTR;
 
 __IO_EXTENDED SYSCSTR _sysc;   /* SYSC */
#define SYSC _sysc.byte
#define SYSC_RSTEN _sysc.bit._RSTEN
#define SYSC_RSTOE _sysc.bit._RSTOE
#define SYSC_EC0SL _sysc.bit._EC0SL
#define SYSC_EXCK0 _sysc.bit._EXCK0
#define SYSC_EXCK1 _sysc.bit._EXCK1
#define SYSC_PFSEL _sysc.bit._PFSEL
#define SYSC_PGSEL _sysc.bit._PGSEL
#define SYSC_EXCK  _sysc.bitc_EXCK

typedef union{   /* CMCR */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE _CMCSEL :1;
    IO_BYTE _TBTSEL2 :1;
    IO_BYTE _TBTSEL1 :1;
    IO_BYTE _TBTSEL0 :1;
    IO_BYTE _CMCEN :1;
    #else 
    IO_BYTE _CMCEN :1;
    IO_BYTE _TBTSEL0 :1;
    IO_BYTE _TBTSEL1 :1;
    IO_BYTE _TBTSEL2 :1;
    IO_BYTE _CMCSEL :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    IO_BYTE  :1;
    #endif 
  }bit;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE :4;
    IO_BYTE _TBTSEL :3;
    #else 
    IO_BYTE :1;
    IO_BYTE _TBTSEL :3;
    #endif 
  }bitc;
 }CMCRSTR;
__IO_EXTENDED CMCRSTR _cmcr;   /* CMCR */
#define CMCR _cmcr.byte
#define CMCR_CMCEN _cmcr.bit._CMCEN
#define CMCR_TBTSEL0 _cmcr.bit._TBTSEL0
#define CMCR_TBTSEL1 _cmcr.bit._TBTSEL1
#define CMCR_TBTSEL2 _cmcr.bit._TBTSEL2
#define CMCR_CMCSEL _cmcr.bit._CMCSEL
#define CMCR_TBTSEL _cmcr.bitc._TBTSEL
__IO_EXTENDED IO_BYTE _cmdr;/* CMDR */
#define CMDR _cmdr
typedef union{   /* WDT */
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _WDTH7 :1;
    IO_BYTE _WDTH6 :1;
    IO_BYTE _WDTH5 :1;
    IO_BYTE _WDTH4 :1;
    IO_BYTE _WDTH3 :1;
    IO_BYTE _WDTH2 :1;
    IO_BYTE _WDTH1 :1;
    IO_BYTE _WDTH0 :1;
    #else    
    IO_BYTE _WDTH0 :1;
    IO_BYTE _WDTH1 :1;
    IO_BYTE _WDTH2 :1;
    IO_BYTE _WDTH3 :1;
    IO_BYTE _WDTH4 :1;
    IO_BYTE _WDTH5 :1;
    IO_BYTE _WDTH6 :1;
    IO_BYTE _WDTH7 :1;
    #endif
  }bit;
 }WDTHSTR;      /*WDTH*/
typedef union{  
    IO_BYTE	byte;
    struct{
    #if   defined(__BITFIELD_ORDER_MSB__)
    IO_BYTE _WDTL7 :1;
    IO_BYTE _WDTL6 :1;
    IO_BYTE _WDTL5 :1;
    IO_BYTE _WDTL4 :1;
    IO_BYTE _WDTL3 :1;
    IO_BYTE _WDTL2 :1;
    IO_BYTE _WDTL1 :1;
    IO_BYTE _WDTL0 :1;
    #else    
    IO_BYTE _WDTL0 :1;
    IO_BYTE _WDTL1 :1;
    IO_BYTE _WDTL2 :1;
    IO_BYTE _WDTL3 :1;
    IO_BYTE _WDTL4 :1;
    IO_BYTE _WDTL5 :1;
    IO_BYTE _WDTL6 :1;
    IO_BYTE _WDTL7 :1;
    #endif
  }bit;
 }WDTLSTR;  /*WDTL*/
__IO_EXTERN __io WDTHSTR _wdth;   /* WDT */
#define WDTH _wdth.byte
#define WDTH_WDTH0 _wdth.bit._WDTH0
#define WDTH_WDTH1 _wdth.bit._WDTH1
#define WDTH_WDTH2 _wdth.bit._WDTH2
#define WDTH_WDTH3 _wdth.bit._WDTH3
#define WDTH_WDTH4 _wdth.bit._WDTH4
#define WDTH_WDTH5 _wdth.bit._WDTH5
#define WDTH_WDTH6 _wdth.bit._WDTH6
#define WDTH_WDTH7 _wdth.bit._WDTH7
__IO_EXTERN __io WDTLSTR _wdtl;  
#define WDTL _wdtl.byte
#define WDTL_WDTL0 _wdtl.bit._WDTL0
#define WDTL_WDTL1 _wdtl.bit._WDTL1
#define WDTL_WDTL2 _wdtl.bit._WDTL2
#define WDTL_WDTL3 _wdtl.bit._WDTL3
#define WDTL_WDTL4 _wdtl.bit._WDTL4
#define WDTL_WDTL5 _wdtl.bit._WDTL5
#define WDTL_WDTL6 _wdtl.bit._WDTL6
#define WDTL_WDTL7 _wdtl.bit._WDTL7

__IO_EXTENDED IO_BYTE _ilsr;
#define ILSR _ilsr    /* ILSR */
   

#  undef ___IOWIDTH
#endif                   /* __MB952XX_H */
