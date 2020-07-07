/**********************************************************************/
/* file name: LPCdef.h                                                */
/* function description: BGM adapter headfile.                        */
/**********************************************************************/
/* ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU LIMITED. 2007           */
/**********************************************************************/

#ifndef __BGMA_LPCDEF__
#define __BGMA_LPCDEF__

/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "epcs_common.h"
#include "UARTio.h"
#include "UARTcomm.h"


/*############ BDSU lite REG ADDRESS ############ */
#define BDSU_PCER       0x0000U     /* PC Escape Register */
#define BDSU_PSER       0x0002U     /* PS Escape Register */
#define BDSU_BPR0       0x0004U     /* Break Point Register 0 */
#define BDSU_BPR1       0x0006U     /* Break Point Register 1 */
#define BDSU_SBAR       0x0008U     /* Security Byte Address Register */
#define BDSU_DMR        0x000AU     /* Debug Mode ID Register */
#define BDSU_BCR        0x000CU     /* BDSU Control Register */
#define BDSU_BSTR       0x000DU     /* BDSU Status Register */
#define BDSU_BFR        0x000EU     /* Break Flag Register */
#define BDSU_DCR        0x004CU     /* Wild register enable */
#define BDSU_CRTH       0x0FE4U     /* CRTH[6:5]: CR frequence selection */
#define BDSU_CLKFlag    0x007AU     /* flag for monitor clock up use 1:enable monitor clock up, 0:disable*/
#define BDSU_EXTOSC     0x007BU     /* record the clock user selected*/

/*############ BCR REG define ############ */
#define RSTODIS         0x40U     /* BCR:6 */
#define WDSTP           0x20U     /* BCR:5 */
#define BPE1            0x10U     /* BCR:4 */
#define BPE0            0x08U     /* BCR:3 */
#define UAA             0x02U     /* BCR:1 */
#define SBE             0x01U     /* BCR:0 */


/*############ BFR REG define ############ */
#define EMU             0x10U     /* BFR:4 */
#define SFB             0x08U     /* BFR:3 */
#define SWB             0x04U     /* BFR:2 */
#define BPF1            0x02U     /* BFR:1 */
#define BPF0            0x01U     /* BFR:0 */

/*################# BREAK type define ################*/
#define FORCE_BRK       0x40000000UL
#define STEP_BRK        0x20000000UL
#define SW_BRK          0x10000000UL
#define CODE1_BRK       0x02000000UL
#define CODE0_BRK       0x01000000UL
#define EXE_ERROR       0x00004000UL




/* Const define */
//#define FALSE 0
//#define TRUE  (!FALSE)
#define NORMAL  FALSE
#define ERROR   TRUE
#define EXIT    TRUE
//#define NULL  0U


/* ############register ID############# */
#define A_ID    0x0000U
#define T_ID    0x0001U
#define IX_ID   0x0002U
#define SP_ID   0x0003U
#define EP_ID   0x0004U
#define PS_ID   0x0005U
#define PC_ID   0x0006U
#define R0_ID   0x0010U
#define R1_ID   0x0011U
#define R2_ID   0x0012U
#define R3_ID   0x0013U
#define R4_ID   0x0014U
#define R5_ID   0x0015U
#define R6_ID   0x0016U
#define R7_ID   0x0017U

/* #############user's reg############### */
#define PLLC_ADDR   0x0006U
#define SYCC_ADDR   0x0007U
#define SYCC2_ADDR  0x000DU
#define DEF_SYCC    0x03U//0x0BU//
#define DEF_SYCC2   0xA3U//0xAFU
#define DEF_PLLC    0x00U
#define DEF_SYCC_1_18   0xDBU
#define DEF_SYCC2_1_18  0x03U
#define READ        0x00U
#define WRITE       0x01U

#define SUBCR_CLK_35    0x00U
#define SUB_CLK_35      0x10U
#define MAINCR_CLK_35   0x20U
#define MAIN_CLK_35     0x30U
#define SYCC_DIV_35     0x03U
#define SYCC2_RCS_35    0x30U

#define SUB_CLK_18          0x00U
#define MAIN_CLK_18         0x08U
#define SUBCR_CLK_18        0x10U
#define MAINCR_CLK_18       0x18U
#define MAINCRPLL_CLK_18    0x1CU
#define SYCC_DIV_18         0x03U
#define SYCC_SCS_18         0x1CU

#define PLL_MUL_2        0x00
#define PLL_MUL_25       0x20
#define PLL_MUL_3        0x40
#define PLL_MUL_4        0x60

#define CRTH_DIV    0x60U
#define PSSR            0x25u
#define BRSR            0x26U
#define UART_BRT_UP     0x00U
#define UART_BRT_RCV    0x01U
#define BDSU_SYCC_RAM    0x77U
#define BDSU_SYCC2_RAM    0x79U
#define BDSU_PLLC_RAM    0x76U


/* #############MONITOR status############### */
#define MCU_BREAK   0x00U   /* MCU_BREAK indicate the MCU is ready for command */
#define MCU_RUN     0x01U   /* MCU_RUN indicate the MCU is running in user mode */
#define RC2_ERROR   0x02U   /* RC2_ERROR indicate the RC2 error happened */
#define CR_FINE     0x04U   /* trimming CR has been done, CR clock is OK */
#define CLKUP_ON    0x08U   /* clock up mode flag */
#define MON_START   0x10U   /* MON_START indicate the monitor started */
#define TRIMMING    0x20U   /* TRIMMING indicate the BGMA is doing trim process */
#define BRTUP_ON    0x40U   /* baud rate up flag */

/* #############POWER status################## */
#define RST_ERROR    0x01U   /* RST_ERROR indicate the reset error happened in monitor mode */
#define USER_RST     0x02U   /* USER_RST indicate MCU is in reset state */
#define LOWPOWERIDT  0x04U   /* LOWPOWERIDT indicate tar MCU power off in monitor mode */
#define LOW_POWER    0x08U   /* LOW_POWER indicate the UVCC low interrupt happened */
#define OVER_CURRENT 0x10U   /* OVER_CURRENT indicate the output current is greater than max value */
/* ##############HOST IF command define############## */
#define START_MON       0x0000U
#define EXIT_MON        0x0100U
#define INIT_MON        0x0200U
#define BGMA_POW        0x1928U
#define WRITE_REG       0x2000U
#define READ_REG        0x2100U
#define READ_REGLIST    0x2200U
#define WRITE_MEM       0x3000U
#define READ_MEM        0x3100U
#define ERASE_FLASH     0x3600U
#define READ_BRK_STAT   0x4000U
#define EXE_MCU         0x4100U
#define RESET_MCU       0x4200U
#define ABORT_MCU       0x4300U
#define SET_BRK         0x5000U
#define DEL_BRK         0x5100U
#define SET_RCK_ADR     0xA128U
#define READ_RCK_SMDAT  0xA228U
#define TRIM_CR         0xE026U
#define USER_CMD        0xE126U
#define LOAD_ENV        0xF400U
#define CNG_ADPT_MODE   0xFE00U
#define LOAD_ADPT_ENV   0xFF00U

/* ################USER define################ */
#define CR_OK           0x00U      /* trim value ok. not need trimming */
#define TRIM_OK         0x01U      /* rough trimming passed */
#define TRIM_FAIL       0xFFU      /* rough trimming can not pass */
#define CR_OK_ACK       0x51U      /* target return for cr ok */
#define TRIM_OK_ACK     0xA1U      /* target return for trim ok */
#define CR_RETRY_TIME   0x07D0U    /* command retry time */

/* for host IF EXE_MCU */
#define MASK_EXETYPE    0x0FU      /* Bit3-0: Execute type */
#define MASK_WATCHDOG   0x02U      /* Bit1: Watchdog timer mode */
#define STEP            0x01U      /* execute in step mode */
#define CONTINUOUS      0x00U      /* execute in continuous mode */
#define W_DOG_EN        0x00U      /* watch dog enable */
#define W_DOG_DIS       0x02U      /* watch dog disable */

/* for host IF WRITE_MEM and READ_MEM */
#define USER_RAM        0x00U      /* W/R user RAM/IO */
#define EMU_RAM         0x01U      /* W/R emulator RAM/IO */
#define FLASH           0xFFU      /* Write Flash */

/* for host IF SET_BRK and DEL_BRK */
#define BP0             0x00U      /* break point 0 */
#define BP1             0x01U      /* break point 1 */

/* for host IF SET_RCK_ADR */
#define RCK_MAX_SIZE    0x10       /* real time RAM monitor max length */ 

/* for host IF READ_RCK_SMDAT */
#define EXECUTE_STATE   0x00
#define BREAK_STATE     0x80
#define READ_BYTE       0x00
#define READ_HWORD      0x01

/* for modify_BCR() function */
#define SET_RSTODIS     0x01U      /* set BCR:RSTODIS */
#define CLR_RSTODIS     0x00U      /* clear BCR:RSTODIS */

/* for host IF READ_MEM and WRITE_MEM */
#if 0 /* for 0.35um LPC */
#define MAX_WRITE_LEN   0x000000F1UL   /* max overflow write length */
#define MAX_READ_LEN    0x000000F9UL   /* max overflow read length */
#endif
#define MAX_WRITE_LEN   0x000001EDUL   /* max overflow write length */
#define MAX_READ_LEN    0x000001F5UL   /* max overflow read length */

#define MONITOR_INFO_ADDR   0xFC00U    /* monitor information start address */
#define MONITOR_INFO_NUM    0x03U      /* monitor information number */
#define RAM_START_ADDR      0x0090U    /* RAM code entry address */
#define CR_TRIM_CMD         0x55AAU    /* cr trimming command */

#define REG_LIST_NUM        0x0FU      /* 15 registers in register list */

#define ERASE_WAIT_TIME     0x00U    /* wait 350ms*0xAA for erase handling */
#define TIME_OUT_ERROR      0x05U    /* erase RC status */
#define FRAME_ERROR         0x01U    /* erase RC status */

#define WAITMS_1000MS       0x00180000U    /* pull DBG pin to low for 1 second */
#define WAITMS_13MS         0x00005000U    /* wait 13ms for high voltage stable */
#define WAITMS_50MS         0x00014000U    /* wait 50ms for target MCU operation */
#define WAITMS_683US        0x00000400U    /* wait 683us for target MCU break */
#define WAITMS_2636US       0x00001000U     /* wait 3ms for target MCU trimming */

#define MAX_OPER_DELAY      0x0800U    /* max wait time for target operation */

#define NO_BREAK            0x00U    /* read break state in MCU_RUN mode */
#define HAVE_BREAK          0x80U    /* read break state in MCU_BREAK mode */

#define CMD_TYPE_A          0x00U    /* command type A */
#define CMD_TYPE_B          0x01U    /* command type B */

#define RESET_VECTOR        0xFFFE   /* reset entry vector */


/* UART1 interrupt level */
#define UART1_INT_LEVEL            19
#define UVCC_DETECT_INT_LEVEL      18
#define RSTX_DETECT_INT_LEVEL      18
#define POUTFLX_DETECT_INT_LEVEL   18

/* Real time monitor wait RC2 timeout */
#define RT_MOM_WAIT_RC2_TIMER     60000

/* BGMA power timeout */
#define BGMA_POWER_TIMEOUT_TIMER  50000

/* #############UART status################## */
#define UART_SEND           0x02U
#define UART_ERROR          0x08U

/* Receive byte type */
#define REV_1_BYTE          0x01U
#define REV_2_BYTE          0x02U
#define REV_4_BYTE          0x04U
#define REV_8_BYTE          0x08U
#define REV_16_BYTE         0x10U


/* BGMA IO define */
#define IO_LED_RED         Gpio1pin_Get( GPIO1PIN_P3B ) 
#define IO_LED_GREEN       Gpio1pin_Get( GPIO1PIN_P3C )
#define IO_POUTFLX         Gpio1pin_Get( GPIO1PIN_P4E )
#define IO_RSTX            Gpio1pin_Get( GPIO1PIN_P52 )
#define IO_RSTMX           Gpio1pin_Get( GPIO1PIN_P50 )
#define IO_UVCCM           Gpio1pin_Get( GPIO1PIN_P51 )
#define IO_UART_OE         Gpio1pin_Get( GPIO1PIN_P53 ) 
#define IO_POUTEN          Gpio1pin_Get( GPIO1PIN_P10 )

#define IO_UVCCM_IN         bFM_GPIO_PDIR5_P1
#define IO_UVCCM_OUT        bFM_GPIO_PDOR5_P1
#define IO_POUTEN_IN        bFM_GPIO_PDIR1_P0
#define IO_POUTEN_OUT       bFM_GPIO_PDOR1_P0
#define IO_RSTMX_IN         bFM_GPIO_PDIR5_P0
#define IO_RSTMX_OUT        bFM_GPIO_PDOR5_P0

/* Monitor program version */
#define Ver_Num3        3
#define Ver_Num4        4
#define VER_2_18(a) ((Ver_Num3==a)||(Ver_Num4==a))
#define VER_35        1
#define VER_1_18      2
//#define VER_2_18      3

/* ###################### */
/* frame format (Lv2)                         Hostif IN BUFFER*/
                           /* Hostif [0]   [1]   [2]  */
#define FRMIN_FC    0      /*         |     |     |     |   */
#define FRMIN_BODY  2      /*        FC1   FC2   BODY */
    
/*                         Hostif OUT BUFFER                  */
                           /* USBbuf [0]   [1]   [2]  */
#define FRMOUT_ENUM 0      /*         |     |     |   */
#define FRMOUT_BODY 1      /*        ENUM  BODY  BODY */
    
/* error frame format */
#define FRMOUT_ECODE    (FRMOUT_BODY+0)
#define FRMOUT_EFLAG    (FRMOUT_BODY+1)
#define FRMOUT_ELEN1    (FRMOUT_BODY+3)
#define FRMOUT_EADRS    (FRMOUT_BODY+3)
#define FRMOUT_ELEN2    (FRMOUT_BODY+7)
    
#define CMD_RETRY   1        /* UART communication retry times 3 */
    
/* monitor_state indicate the current status of the monitor  */
extern uint8_t monitor_state;
/* power_state indicate the current power status of the target MCU  */
extern uint8_t power_state;
/* CR_state indicate the CR clock state */
extern uint8_t CR_state;
/* tar_SYCC indicate SYCC value in target MCU */
extern uint8_t tar_SYCC;
/* tar_SYCC2 indicate SYCC2 value in target MCU */
extern uint8_t tar_SYCC2;
/* mainOSC_freq indicate main clock freq */
extern uint8_t mainOSC_freq;
/* delay_flag indicate the short/long delay for target operation */
extern uint32_t delay_time;
/* retry_counter indicate trim retry times */
extern uint16_t retry_counter;

/* indicate ram monitor function is enterred */
extern uint8_t ram_mon_flag;
/* indicate it is in upload process */
extern uint8_t bgma_upload_flag;
/*MCU version*/
extern uint8_t version_num;
/*MCU level*/
extern uint8_t level_num;
/*save user setting SYCC*/
extern uint8_t ReservUserClk_SYCC;
/*save user setting SYCC2*/
extern uint8_t ReservUserClk_SYCC2;
/*save user setting PLLC*/
extern uint8_t ReservUserClk_PLLC;
/*flag for reset operation*/
extern uint8_t ResetFlag;
/*flag for 16byte read*/
extern uint8_t Read16_Flag;
/*flag for baud rate 0-1M, 1-500K*/
extern uint8_t BRFlag1M;


extern uint8_t get_paramb(uint16_t offset);
extern uint16_t get_paramh(uint16_t offset);
extern uint32_t get_paramw(uint16_t offset);
extern void put_paramb(uint16_t offset, uint8_t data);
extern void put_paramh(uint16_t offset, uint16_t data);
extern void put_paramw(uint16_t offset, uint32_t data);
extern void put_param16(uint16_t offset, uint8_t  *data);
extern void put_frmlen(uint16_t len);
extern void put_normal(void);
extern uint8_t set_errcode(uint8_t err);
extern uint8_t set_erradrs(uint8_t err, uint16_t adrs);
extern uint8_t* get_usbbuf_pointer(void);
extern uint16_t get_usbbuf_size(void);
extern void set_usbbuf_pointer(uint8_t* pUSBbuf);
extern void HostIF_Init(void);
extern uint8_t trim_cr(UART_COMMAND* cmd);
extern uint8_t clock_up(UART_COMMAND* cmd);
extern uint8_t RegBuff_Init(UART_COMMAND* cmd);
extern void check_break_stat(UART_COMMAND* cmd);
extern void power_on_init(void);

/* command process table */
typedef struct __cmdtbl {    /* construct the command table */
    uint16_t fc;       /* command ID */
    void (*func)();  /* command process function entry address */
} CMDTBL;                    /* structure name: CMDTBL */

/* creat table of command process */
extern CMDTBL const commandtable[];

/* for C-Compiler V03L11's issue */
#define USE_CC_L11

// CMD.AddrH,AddrL <== 16bit data
#ifdef USE_CC_L11
#define SET_UARTCMD_ADDR(CMD, DATA) if(0) ; else{uint16_t tmp= DATA;\
    CMD.AddrH = tmp >> 8; CMD.AddrL = tmp & 0xFFU;}
#else /* USE_CC_L11 */
#define SET_UARTCMD_ADDR(CMD, DATA) \
    CMD.AddrH = DATA >> 8; CMD.AddrL = DATA & 0xFFU
#endif /* USE_CC_L11 */

// pCMD->AddrH,AddrL <== 16bit data
#ifdef USE_CC_L11
#define SET_PUARTCMD_ADDR(pCMD, DATA) if(0) ; else {uint16_t tmp= DATA;\
    pCMD->AddrH = tmp >> 8; pCMD->AddrL = tmp & 0xFFU;}
#else /* USE_CC_L11 */
#define SET_PUARTCMD_ADDR(pCMD, DATA) \
    pCMD->AddrH = DATA >> 8; pCMD->AddrL = DATA & 0xFFU
#endif /* USE_CC_L11 */

// 16bit data <== CMD.AddrH,AddrL
#define GET_UARTCMD_ADDR(CMD, DATA) \
    DATA = (uint32_t)CMD.AddrH<<8 | (uint32_t)CMD.AddrL

// 16bit data <== pCMD->AddrH,AddrL
#define GET_PUARTCMD_ADDR(pCMD, DATA) \
    DATA = (uint32_t)pCMD->AddrH<<8 | (uint32_t)pCMD->AddrL

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __BGMA_LPCDEF__ */

/* [] END OF FILE */

