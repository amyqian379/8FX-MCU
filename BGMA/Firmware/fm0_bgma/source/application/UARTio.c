/* file name: UARTio.c                                              */
/* function description: UART lower level driver                    */
/**********************************************************************/
/* ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU LIMITED. 2010           */
/**********************************************************************/

#include "UARTio.h"
#include "LPCdef.h"

uint8_t send_buf; /* store send data */
uint8_t rev_buf[UART_REV_MAX_SIZE];  /* UART receive max size */
uint8_t *p_wr_buf;  /* read pointer for rev_buf */
uint8_t *p_rd_buf;  /* write pointer for rev_buf */
uint8_t uart_error;       /* uart error flag */
uint8_t Secu16BytesRec=0;	/*number of function received*/  
/**********************************************************************/
/* Function Name: waitus                                              */
/* Description: time delay                                            */
/* Parameters: timer -- time count                                    */
/* Return: none                                                       */
/**********************************************************************/
void waitus(uint32_t timer)
{
    while(timer--);
}

/**********************************************************************/
/* Function Name: wait60us                                            */
/* Description: time delay 60us/timer                                 */
/* Parameters: timer -- time count                                    */
/* Return: none                                                       */
/**********************************************************************/
void wait60us(uint32_t timer)
{
    while(timer--) waitus(100);
}

/**********************************************************************/
/* Function Name: change uart tx pin to gpio                          */
/* Description: hange uart tx pin to gpio and set direction is input  */
/* Parameters: ch : tx channel                                        */
/* Return: none                                                       */
/**********************************************************************/
void MFS_ChangeUARTPinToGPIO(void)
{
    PINRELOC_UnSet_EPFR( FM_GPIO->EPFR07, 12u, 2u,  2u ); 
    bFM_GPIO_PFR1_P2 = 0u;
    PINRELOC_UnSet_EPFR( FM_GPIO->EPFR07, 10u, 2u,  2u );
    bFM_GPIO_PFR1_P1 = 0u;
    Gpio1pin_InitOut( GPIO1PIN_P12, Gpio1pin_InitVal( 1u )); 
}

/**********************************************************************/
/* Function Name: bt0_enable                                           */
/* Description: enable reload timer counter                           */
/* Parameters: one_shot -- select one shot or reload                  */
/*             timer    -- delay time count                           */
/* Return: none                                                       */
/**********************************************************************/
void bt0_enable(uint8_t one_shot, uint32_t timer)
{
    FM_BT0->TMCR_f.FMD = 0;                      /* Reset Base Timer mode */
    FM_BT0->TMCR_f.FMD = 0x03;                  /* set base timer mode to reload timer function*/ 
    FM_BT0->TMCR_f.CKS = 0x02;                  /* Set PCLK/16 as base timer clcok */
    FM_BT0->TMCR_f.T32 = 1;                     /* set 32 bit counter mode */  
    FM_BT0->TMCR_f.EGS = 0;                     /* disable input trigger */
    FM_BT0->TMCR_f.OSEL = 0;                    /* Output polarity setting Rt Polarity Low*/
    FM_BT0->STC_f.TGIE = 0u;                     /* disable input trigger interrupt */
    FM_BT0->STC_f.UDIE = 0u;                     /* disable underflow interrupt */
    if(one_shot)
    {
        FM_BT0->TMCR_f.MDSE = 1;
    }
    else
    {
        FM_BT0->TMCR_f.MDSE = 0;
    }      
    FM_BT0->STC_f.TGIR = 0u;                     /* clear trigger flag */
    FM_BT0->STC_f.UDIR = 0u;                     /* clear underflow flag */
    FM_BT1->PCSR = ((timer*2u) >> 16) & 0xffff;
    FM_BT0->PCSR = ((timer*2u)) & 0xffff;
    FM_BT0->TMCR_f.CTEN = 1u;                    /* Enable bt timer */ 
    FM_BT0->TMCR_f.STRG = 1u;                    /* Start Reload timer by software */
    
}
/**********************************************************************/
/* Function Name: bt0_disable                                         */
/* Description: disable reload timer counter                          */
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
void bt0_disable(void)
{
    FM_BT0->STC_f.UDIR = 0u;                     /* clear underflow flag */
    FM_BT0->TMCR_f.CTEN = 0u;                    /* disable bt timer */
}

/**********************************************************************/
/* Function Name: check_bt0_overflow                                  */
/* Description: check if reload timer overflow                        */
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
uint8_t check_bt0_overflow(void)
{
    return FM_BT0->STC_f.UDIR;                  /* return overflow flag */
}

/**********************************************************************/
/* Function Name: clear_rtl_flag                                      */
/* Description: clear reload timer overflow flag                      */
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
void clear_bt0_flag(void)
{
    FM_BT0->STC_f.UDIR = 0u;                     /* clear underflow flag */
}  

/**********************************************************************/
/* Function Name: uart_init                                           */
/* Description: initila uart                                          */
/* Parameters: baud_rate -- baud rate setting                         */
/* Return: none                                                       */
/**********************************************************************/
void uart_init(uint8_t Baudrate)
{
    uint32_t u32baudrate;    
    if(Baudrate == UART_BAUD_RATE_62500)
      u32baudrate = UART_BAUDRATE(62500);
    else if(Baudrate == UART_BAUD_RATE_500k)
      u32baudrate = UART_BAUDRATE(500000);  
    else if(Baudrate == UART_BAUD_RATE_125000)
      u32baudrate = UART_BAUDRATE(125000); 
    
    SetPinFunc_SIN1_1();
    SetPinFunc_SOT1_1();
    
    UART_DBG_CH->SCR =  0x80;
    UART_DBG_CH->SMR =  0x01;
    UART_DBG_CH->ESCR = 0x00;
    UART_DBG_CH->BGR = (uint16_t)u32baudrate; 
    UART_DBG_CH->SCR = 0x03;
    UART_DBG_CH->SSR_f.REC = 0x01;
    
    NVIC_ClearPendingIRQ(MFS1_RX_TX_IRQn);
    NVIC_SetPriority(MFS1_RX_TX_IRQn, 1);
    NVIC_EnableIRQ(MFS1_RX_TX_IRQn);
    return;
}

/**********************************************************************/
/* Function Name: uart_send                                           */
/* Description: uart send data process                                */
/* Parameters: DataPtr -- pointer to send data                        */
/*             time_out -- timeout counter                            */
/* Return: none                                                       */
/**********************************************************************/
uint8_t uart_send(uint8_t *DataPtr, uint32_t time_out)
{
    uint8_t  ret = 0;
    if(uart_error) {uart_error = 0; return 1;} /* if error has happened, return NG */
    send_buf = *DataPtr;                        /* store sned data */
    uart_error = 0;                             /* clear uart status */
    p_wr_buf = p_rd_buf = &rev_buf[0];
    UART_DBG_CH->SCR_f.TIE = 1;                 /* enable uart interrupt */
    bt0_enable(1, time_out);                     /* enable one-shot timer */  
    while(1)
    {
        if (uart_error)                         /* uart error occurs */
        {
            uart_error = 0;
            ret = 1;
            break;
        }
        if ( p_wr_buf != p_rd_buf )
        {
	    if( send_buf != *p_rd_buf )
            {
                ret = 1;
            }
            p_rd_buf++;
            if( p_rd_buf == &rev_buf[UART_REV_MAX_SIZE] )
            {
                p_rd_buf = &rev_buf[0];
            }
            break;
        }
        if( check_bt0_overflow() )               /* receive process timeout */
        {
            clear_bt0_flag();
            UART_DBG_CH->SCR_f.RIE = 0;         /* disable uart interrupt */
            UART_DBG_CH->SCR_f.TIE = 0;         /* disable uart interrupt */
            ret = 1;
            break;
        }
    }
    bt0_disable();
    return ret;
}

/**********************************************************************/
/* Function Name: uart_receive                                        */
/* Description: uart receive process                                  */
/* Parameters: DataPtr -- pointer to receive data                     */
/*             time_out -- timeout counter                            */
/*             cnt -- receive number                                  */
/* Return: none                                                       */
/**********************************************************************/
uint8_t uart_receive(uint8_t *DataPtr, uint32_t time_out, uint8_t cnt)
{
    uint8_t  ret = 0;
    uint8_t  timecnt=0;
    if(uart_error) {uart_error = 0; return 1;}  /* if error has happened, return NG */
    uart_error = 0;                             /* clear uart status */
    bt0_enable(0, time_out);                     /* enable dt timer with reload mode */ 
    while(1)
    {
        if( uart_error )                        /* uart error occur? */
        {
            uart_error = 0;
            ret = 1;
            break;
        }
        if( p_wr_buf != p_rd_buf )
        {
            *(DataPtr++) = *(p_rd_buf++);
            cnt--;
            Secu16BytesRec ++;
            if( p_rd_buf == &rev_buf[UART_REV_MAX_SIZE] )
            {
                p_rd_buf = &rev_buf[0];
            }
            if(!cnt){
                break;
            }
            bt0_enable(0,time_out);              /* enable reload timer with reload mode */  
            timecnt = 0;
         }

        if( check_bt0_overflow() )               /* receive process timeout */
        {
            clear_bt0_flag();
            if(timecnt != 14) 
            {
                timecnt++;
                continue;
            }  
            UART_DBG_CH->SCR_f.RIE = 0;         /* disable uart interrupt */
            ret = 0x02;                         /*0x01->0x02indicate time out error janeAdd*/
            break;
        }
    }
    bt0_disable();
    return ret;
}

/**********************************************************************/
/* Function Name: sendbrk                                             */
/* Description: uart send break process                               */
/* Parameters: time_out -- break width                                */
/* Return: none                                                       */
/**********************************************************************/
void sendbrk(uint32_t time_out)
{
    UART_DBG_CH->SCR_f.TXE = 0;/* Disable send */
    UART_DBG_CH->SCR_f.RXE = 0;/* Disable Receive */
    UART_DBG_CH->SCR_f.RIE = 0;/* disable RX enable */
    bt0_enable(1, time_out);
    
    /* Shift UART to GPIO */
    MFS_ChangeUARTPinToGPIO();
    /* Pull L SO pin */
    Gpio1pin_Put( GPIO1PIN_P12, 0u);
    
    while(!check_bt0_overflow());

    /* Pull H SO pin */
    Gpio1pin_Put( GPIO1PIN_P12, 1u);
   // PORT1_DDR0_DDR04 = 1;
    /* Shift GPIO to UART */
    SetPinFunc_SIN1_1();
    SetPinFunc_SOT1_1();

    if((version_num == VER_35)||((version_num == VER_1_18) && (level_num == 1)))
    {
    	if(bgma_upload_flag) /* in upload process, if break occur, recover the baud rate */
        {
            if(UART_DBG_CH->BGR != UART_BAUDRATE(62500))// if baud rate 62500?
            {
                UART_DBG_CH->BGR = UART_BAUDRATE(62500);
            }
        }
    }
	
    UART_DBG_CH->SCR_f.TXE = 1;/* enable send */
    UART_DBG_CH->SCR_f.RXE = 1;/* enable Receive */
    UART_DBG_CH->SCR_f.RIE = 1;/* enable RX enable */
    
    return;
}

/**********************************************************************/
/* Function Name: erase_receive                                       */
/* Description: receive earse command RC                              */
/* Parameters: DataPtr -- pointer to receive data                     */
/*             time_out -- timeout counter                            */
/* Return: none                                                       */
/**********************************************************************/
uint8_t erase_receive(uint8_t *DataPtr, uint32_t time_out, uint8_t cnt)
{
    uint8_t  ret = 0;
    uint32_t timecnt=0;
    if(uart_error) {uart_error = 0; return 1;}  /* if error has happened, return NG */
    uart_error = 0;                             /* clear uart status */
    bt0_enable(0, time_out);                     /* enable dual timer with reload mode */
    while(1)
    {
        if(uart_error)                          /* uart error occur? */
        {
            uart_error = 0;
            ret = 1;
            break;
        }
        if(p_wr_buf != p_rd_buf)
        {
            *(DataPtr++) = *(p_rd_buf++);
            cnt--;
            if(p_rd_buf == &rev_buf[UART_REV_MAX_SIZE])
            {
                p_rd_buf = &rev_buf[0];
            }
            if(!cnt)
            {
                break;
            }
            bt0_enable(0, time_out);                     /* enable dual timer with reload mode */
            timecnt = 0;
            break;
        }
        if( check_bt0_overflow() )               /* receive process timeout */
        {
            clear_bt0_flag();
            if(timecnt != 6000) 
            {
                timecnt++;
                continue;
            }  
            UART_DBG_CH->SCR_f.RIE = 0;         /* disable RX enable */
            ret = 0x01;
            break;
        }
    }
    bt0_disable();
    return ret;
}

/**********************************************************************/
/* Function Name: cr_receive                                          */
/* Description: receive cr trimming command RC                        */
/* Parameters: DataPtr -- pointer to receive data                     */
/* Return: none                                                       */
/**********************************************************************/
uint8_t cr_receive(uint8_t *DataPtr)
{
    uint8_t cr_rev,ret;
    ret = uart_receive(&cr_rev, UART_CR_TIMEOUT_TIMER, 1);
    *DataPtr = cr_rev;
    return ret;
}

/**********************************************************************/
/* Function Name: MFS0_RX_TX_IRQHandler                                   */
/* Description: uart send receive interrupt                                */
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
void MFS1_RX_TX_IRQHandler(void)
{
    if ( UART_DBG_CH->SSR_f.RDRF) //RX interrupt
    {
        UART_DBG_CH->SCR_f.TIE = 0;  /* disable uart interrupt */
        UART_DBG_CH->SCR_f.TIE = 0;  /* dummy, for time delay */
        
        if ( UART_DBG_CH->SSR_f.FRE || UART_DBG_CH->SSR_f.ORE )  /* frame or overrun error occur? */
        {
            uart_error = 1;
            UART_DBG_CH->SSR_f.REC = 1;
            UART_DBG_CH->SCR_f.RIE = 0;
            *p_wr_buf = UART_DBG_CH->RDR;
        }
        
        else
        {
            *p_wr_buf = UART_DBG_CH->RDR;
            if((p_wr_buf+1  == p_rd_buf) || (p_wr_buf-UART_REV_MAX_SIZE+1 == p_rd_buf)) /* ring buffer is full */
            {
                UART_DBG_CH->SCR_f.RIE = 0;
                uart_error = 1;
            }
            else
            {
                p_wr_buf++;
                if(p_wr_buf == &rev_buf[UART_REV_MAX_SIZE])
                {
                    p_wr_buf = &rev_buf[0];
                }
            }
        }
    }
    
    else  //TX interrupt
    {
        UART_DBG_CH->SCR_f.TIE = 0;  /* disable uart interrupt */
        UART_DBG_CH->RDR = send_buf;
    }
    return;              
}


