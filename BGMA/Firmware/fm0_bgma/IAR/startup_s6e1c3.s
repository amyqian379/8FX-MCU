/*******************************************************************************
* Copyright 2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
* CYPRESS PROVIDES THIS SOFTWARE "AS IS" AND MAKES NO WARRANTY
* OF ANY KIND, EXPRESS OR IMPLIED, WITH REGARD TO THIS SOFTWARE,
* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
* MERCHANTABILITY, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
* PURPOSE.
*******************************************************************************/

                MODULE  ?cstartup

                ;; Forward declaration of sections.
                SECTION CSTACK:DATA:NOROOT(3)

                SECTION .intvec:CODE:NOROOT(2)

                EXTERN  __iar_program_start
                EXTERN  SystemInit
                PUBLIC  __vector_table

                DATA
__vector_table  DCD     sfe(CSTACK)               ; Top of Stack
		        DCD     Reset_Handler             ; Reset
                DCD     NMI_Handler               ; NMI
                DCD     HardFault_Handler         ; Hard Fault
                DCD     MemManage_Handler         ; MPU Fault
                DCD     BusFault_Handler          ; Bus Fault
                DCD     UsageFault_Handler        ; Usage Fault
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall
                DCD     DebugMon_Handler          ; Debug Monitor
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV
                DCD     SysTick_Handler           ; SysTick

; Numbered IRQ handler vectors

; Note: renaming to device dependent ISR function names are done in
;       pdl.h (section "IRQ name definition for all type MCUs"

                DCD     CSV_SWDT_LVD_IRQHandler
                DCD     MFS0_RX_TX_IRQHandler
                DCD     MFS1_RX_TX_IRQHandler
                DCD     Dummy
                DCD     MFS3_RX_TX_IRQHandler
                DCD     MFS4_RX_TX_IRQHandler
                DCD     Dummy
                DCD     MFS6_RX_TX_I2CSLAVE_IRQHandler
                DCD     MFS7_RX_TX_IRQHandler
                DCD     ADC0_IRQHandler
                DCD     USB0_F_ED123_IRQHandler
                DCD     USB0_F_ED450I_IRQHandler
                DCD     USB0_F_ED0O_ST_IRQHandler
                DCD     USB0_H_IRQHandler
                DCD     TIM_IRQHandler
                DCD     WC_RTC_DT_IRQHandler
                DCD     EXINT0_1_IRQHandler
                DCD     EXINT2_3_IRQHandler
                DCD     EXINT4_5_IRQHandler
                DCD     EXINT6_7_IRQHandler
                DCD     EXINT8_IRQHandler
                DCD     Dummy
                DCD     EXINT12_13_IRQHandler
                DCD     EXINT15_IRQHandler
                DCD     BT0_4_IRQHandler
                DCD     BT1_5_IRQHandler
                DCD     BT2_6_IRQHandler
                DCD     BT3_7_IRQHandler
                DCD     HDMICEC0_1_IRQHandler
                DCD     SMCIF1_FLASHIF_IRQHandler
                DCD     DSTC_IRQHandler


                THUMB
; Dummy Exception Handlers (infinite loops which can be modified)

                PUBWEAK Reset_Handler
                SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler

;No FPU                LDR.W R0, =0xE000ED88            ; CPACR is located at address 0xE000ED88
;No FPU                LDR R1, [R0]                     ; Read CPACR
;No FPU                ORR R1, R1, #(0xF << 20)         ; Set bits 20-23 to enable CP10 and CP11 coprocessors
;No FPU                STR R1, [R0]                     ; Write back the modified value to the CPACR

                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__iar_program_start
                BX      R0
                
                PUBWEAK NMI_Handler
                SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
                B       NMI_Handler

                PUBWEAK HardFault_Handler
                SECTION .text:CODE:REORDER:NOROOT(1)
HardFault_Handler
                B       HardFault_Handler

                PUBWEAK MemManage_Handler
                SECTION .text:CODE:REORDER:NOROOT(1)
MemManage_Handler
                B       MemManage_Handler

                PUBWEAK BusFault_Handler
                SECTION .text:CODE:REORDER:NOROOT(1)
BusFault_Handler
                B       BusFault_Handler

                PUBWEAK UsageFault_Handler
                SECTION .text:CODE:REORDER:NOROOT(1)
UsageFault_Handler
                B       UsageFault_Handler

                PUBWEAK SVC_Handler
                SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
                B       SVC_Handler

                PUBWEAK DebugMon_Handler
                SECTION .text:CODE:REORDER:NOROOT(1)
DebugMon_Handler
                B       DebugMon_Handler

                PUBWEAK PendSV_Handler
                SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
                B       PendSV_Handler

                PUBWEAK SysTick_Handler
                SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
                B       SysTick_Handler

                
                PUBWEAK CSV_SWDT_LVD_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
CSV_SWDT_LVD_IRQHandler
                B       CSV_SWDT_LVD_IRQHandler

                PUBWEAK MFS0_RX_TX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
MFS0_RX_TX_IRQHandler
                B       MFS0_RX_TX_IRQHandler

                PUBWEAK MFS1_RX_TX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
MFS1_RX_TX_IRQHandler
                B       MFS1_RX_TX_IRQHandler

                PUBWEAK MFS3_RX_TX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
MFS3_RX_TX_IRQHandler
                B       MFS3_RX_TX_IRQHandler

                PUBWEAK MFS4_RX_TX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
MFS4_RX_TX_IRQHandler
                B       MFS4_RX_TX_IRQHandler

                PUBWEAK MFS6_RX_TX_I2CSLAVE_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
MFS6_RX_TX_I2CSLAVE_IRQHandler
                B       MFS6_RX_TX_I2CSLAVE_IRQHandler

                PUBWEAK MFS7_RX_TX_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
MFS7_RX_TX_IRQHandler
                B       MFS7_RX_TX_IRQHandler

                PUBWEAK ADC0_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
ADC0_IRQHandler
                B       ADC0_IRQHandler

                PUBWEAK USB0_F_ED123_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
USB0_F_ED123_IRQHandler
                B       USB0_F_ED123_IRQHandler

                PUBWEAK USB0_F_ED450I_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
USB0_F_ED450I_IRQHandler
                B       USB0_F_ED450I_IRQHandler

                PUBWEAK USB0_F_ED0O_ST_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
USB0_F_ED0O_ST_IRQHandler
                B       USB0_F_ED0O_ST_IRQHandler

                PUBWEAK USB0_H_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
USB0_H_IRQHandler
                B       USB0_H_IRQHandler

                PUBWEAK TIM_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
TIM_IRQHandler
                B       TIM_IRQHandler

                PUBWEAK WC_RTC_DT_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
WC_RTC_DT_IRQHandler
                B       WC_RTC_DT_IRQHandler

                PUBWEAK EXINT0_1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
EXINT0_1_IRQHandler
                B       EXINT0_1_IRQHandler

                PUBWEAK EXINT2_3_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
EXINT2_3_IRQHandler
                B       EXINT2_3_IRQHandler

                PUBWEAK EXINT4_5_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
EXINT4_5_IRQHandler
                B       EXINT4_5_IRQHandler

                PUBWEAK EXINT6_7_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
EXINT6_7_IRQHandler
                B       EXINT6_7_IRQHandler

                PUBWEAK EXINT8_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
EXINT8_IRQHandler
                B       EXINT8_IRQHandler

                PUBWEAK EXINT12_13_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
EXINT12_13_IRQHandler
                B       EXINT12_13_IRQHandler

                PUBWEAK EXINT15_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
EXINT15_IRQHandler
                B       EXINT15_IRQHandler

                PUBWEAK BT0_4_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
BT0_4_IRQHandler
                B       BT0_4_IRQHandler

                PUBWEAK BT1_5_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
BT1_5_IRQHandler
                B       BT1_5_IRQHandler

                PUBWEAK BT2_6_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
BT2_6_IRQHandler
                B       BT2_6_IRQHandler

                PUBWEAK BT3_7_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
BT3_7_IRQHandler
                B       BT3_7_IRQHandler

                PUBWEAK HDMICEC0_1_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
HDMICEC0_1_IRQHandler
                B       HDMICEC0_1_IRQHandler

                PUBWEAK SMCIF1_FLASHIF_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
SMCIF1_FLASHIF_IRQHandler
                B       SMCIF1_FLASHIF_IRQHandler

                PUBWEAK DSTC_IRQHandler
                SECTION .text:CODE:REORDER:NOROOT(1)
DSTC_IRQHandler
                B       DSTC_IRQHandler




                PUBWEAK Dummy
                SECTION .text:CODE:REORDER:NOROOT(1)
Dummy
                B       Dummy

                END
