/**********************************************************************/
/* file name: UARTcomm.c                                              */
/* function description: UART communication interface.                */
/**********************************************************************/
/* ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU LIMITED. 2007           */
/**********************************************************************/
#include "UARTcomm.h"
#include "LPCdef.h"

uint8_t t_ret_1,t_ret_2,t_ret_3,t_ret_4,t_ret_5; /* for uart test */
uint8_t ram_mon_flag;

/**********************************************************************/
/* Function Name: uart_put                                            */
/* Description: send a data to target MCU                             */
/*              leave some delay for target doing other operation     */
/* Parameters: *DataPtr ---address of the send data                   */
/*             timer ---delay time = 50us*timer                       */
/* Return: ---communication status                                    */
/**********************************************************************/
uint8_t uart_put(uint8_t *cmd, uint32_t timer, uint8_t put_cnt)
{
    uint8_t i;
    uint8_t sum = 0;
    uint8_t ret = 0;
    Secu16BytesRec = 0;/*use for 16bytes security error*/

    if(put_cnt == 1)
    {
        UART_DBG_CH->SCR_f.RIE = 1;/* enable RX enable */
        wait60us((uint32_t)timer);	   /* delay 50us*timer for target operation */
        if( ret = uart_send((uint8_t*)cmd, UART_SEND_TIMEOUT_TIMER) )	/* send a data to target */
        {
	    return ret;
        }
	return ret;
    }
    else if(put_cnt == 4)
    {
        UART_DBG_CH->SCR_f.RIE = 1;/* enable RX enable */
        for(i=0; i<put_cnt-1; i++)
        {
            wait60us((uint32_t)timer);	   /* delay 60us*timer for target operation */
            if(ret = uart_send((uint8_t*)cmd, UART_SEND_TIMEOUT_TIMER))	/* send a data to target */
            {
                return ret;
            }
            sum += *cmd;
            cmd++;
        }
        wait60us((uint32_t)timer);	   /* delay 50us*timer for target operation */
        uart_send(&sum, UART_SEND_TIMEOUT_TIMER);	/* send a data to target */
        return ret;
    }
    else/*8 bytes*/
    {
        UART_DBG_CH->SCR_f.RIE = 1;/* enable RX enable */
        for(i=0; i<put_cnt-1; i++)
        {		
            wait60us((uint32_t)timer);	   /* delay 60us*timer for target operation */
            if(ret = uart_send((uint8_t*)cmd, UART_SEND_TIMEOUT_TIMER))	/* send a data to target */
            {
                return ret;
            }
            sum += *cmd;
            cmd++;				
        }
        wait60us((uint32_t)timer);	   /* delay 50us*timer for target operation */
        uart_send(&sum, UART_SEND_TIMEOUT_TIMER);	/* send a data to target */
        return ret;
    }

}

/**********************************************************************/
/* Function Name: uart_get                                            */
/* Description: receice a data from target MCU                        */
/*              leave some delay for target doing other operation     */
/* Parameters: *DataPtr ---address of the received data               */
/*             timer ---delay time = 50us*timer                      */
/* Return: ---communication status                                    */
/**********************************************************************/
uint8_t uart_get(uint8_t *cmd, uint32_t timer, uint8_t get_cnt)
{
    uint8_t fc,sum,ret=0,i;
    uint8_t tempDataPtr[18];
    wait60us(timer);	  /* delay 50us*timer for target operation */
		
    if(ret = uart_receive(&tempDataPtr[0], UART_REV_TIMEOUT_TIMER, get_cnt))  /* receive a data to target */
    {	
        if((ret == 2)&&(Read16_Flag == 1))
        {
            *(cmd++);
            for(i=0;i<16;i++)
            {
                *(cmd++) = tempDataPtr[i ];
            }
        }
        return ret;
    }
    UART_DBG_CH->SCR_f.RIE = 0;/* disable RX enable */
    if(get_cnt == 1)
    {
        if (*cmd != 0x27)
        {
            *(cmd+3) = tempDataPtr[0];
        }
        else
        {
            *(cmd+9)=tempDataPtr[0];
        }
        return ret;   
    }
    else if(get_cnt == 4)
    {
        fc = *(cmd++);
        *(cmd++) = tempDataPtr[0];
        *(cmd++) = tempDataPtr[1];
        sum = tempDataPtr[2];
        if(sum != (uint8_t)(fc + tempDataPtr[0] + tempDataPtr[1])) ret = 1;
        *cmd = tempDataPtr[3];
        return ret;
    }
    else if(get_cnt == 18)  /* type D*/
    {
        fc = *(cmd++);
        for(i=0;i<16;i++)
        {
            *(cmd++) = tempDataPtr[i + 0];
        }
			
        sum = tempDataPtr[16];
        if(sum != (uint8_t)(fc + tempDataPtr[0]+tempDataPtr[1]+tempDataPtr[2]+tempDataPtr[3]
                                     + tempDataPtr[4]+tempDataPtr[5]+tempDataPtr[6]+tempDataPtr[7]+tempDataPtr[8]
                                     + tempDataPtr[9]+tempDataPtr[10]+tempDataPtr[11]+tempDataPtr[12]+tempDataPtr[13]
                                     + tempDataPtr[14]+tempDataPtr[15])) 
        {
            ret = 1;
        }
			
        *cmd = tempDataPtr[17];
        return ret;
    }
    return ret;
}

/**********************************************************************/
/* Function Name: cr_put                                              */
/* Description: send trim data                                        */
/* Parameters: *cmd ---address of cmd                                 */
/*             timer --- interval time                                */
/* Return: ---communication status                                    */
/**********************************************************************/
void cr_put(UART_COMMAND* cmd, uint32_t timer)
{
    p_wr_buf = p_rd_buf = &rev_buf[0];
    UART_DBG_CH->SCR_f.RIE = 1;/* enable RX enable */
    SET_PUARTCMD_ADDR(cmd,CR_TRIM_CMD);
    uart_send(&(cmd->AddrH), UART_SEND_TIMEOUT_TIMER);   /* send a data to target */
    waitus(timer);
    uart_send(&(cmd->AddrL), UART_SEND_TIMEOUT_TIMER);  /* send a data to target */
}

/**********************************************************************/
/* Function Name: cr_get                                              */
/* Description: receice cr trim result                                */
/* Parameters: *DataPtr ---address of the received data               */
/* Return: ---communication status                                    */
/**********************************************************************/
uint8_t cr_get(void* DataPtr)
{
    uint8_t ret;
    ret = cr_receive((uint8_t*)DataPtr);  /* receive a data to target */ 
    UART_DBG_CH->SCR_f.RIE = 0;/* disable RX enable */
    return ret;
}

/**********************************************************************/
/* Function Name: erase_get                                           */
/* Description: receice cr ersae result                               */
/* Parameters: *DataPtr ---address of the received data               */
/* Return: ---communication status                                    */
/**********************************************************************/
uint8_t erase_get(void* DataPtr)
{
    uint8_t ret;
    ret = erase_receive((uint8_t*)DataPtr, UART_ERASE_TIMER, 1);  /* receive a data to target */
    UART_DBG_CH->SCR_f.RIE = 0;/* disable RX enable */
    return ret;
}

/**********************************************************************/
/* Function Name: send_break                                          */
/* Description: send break and delay                                  */
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
void send_break(void)
{
    sendbrk(UART_BREAK_TIMER);
    waitus(WAITMS_683US);
}

/**********************************************************************/
/* Function Name: uart_communication                                  */
/* Description: send commands to target MCU (contains 2 commands type)*/
/*              Type A: send FC, AddrH, AddrL and SUM, receiving RC   */
/*              Type B: send FC, receiving AddrH, AddrL, SUM and RC   */
/* Parameters: *cmd ---address of the command                         */
/* Return: ---communication status                                    */
/**********************************************************************/
uint8_t uart_communication(UART_COMMAND *cmd)
{
    uint32_t cnt;
    cnt = CMD_RETRY;   /* retry times */
    cmd->RC = NORMAL;
    if (!(cmd->FC & 0x80)) 
    {
        /* type A */
        while (1) 
        {
            cmd->FC&=0x7F;
            //sum=cmd->FC+cmd->AddrH+cmd->AddrL;
            /*uart_timer_start();*/
            if ((t_ret_1 = uart_put((uint8_t*)cmd,delay_time,4))||
                (t_ret_5 = uart_get((uint8_t*)cmd,0,1))) 
            {
                if (!cnt)  /* short delay fail */
                {            
                    if (delay_time >= MAX_OPER_DELAY)
                    {
                        cmd->RC = TARERR;
                        delay_time = 0x0000U;   /*recover delay_time */
                        break;
                    }
                    if (delay_time == 0) delay_time++;
                    delay_time *= 2;   /* delay_time */
                    cnt = CMD_RETRY;   /* reset retry times */
                    send_break();
                    continue;
                }   /* retry end */
                cnt--;
                send_break();
                continue;   /* retry */
            }
            break;   /* communication success */
        }
    }
    else  /* type B */
    {
        while (1) 
        {
            /*uart_timer_start();*/
            if ((t_ret_1 = uart_put((uint8_t*)cmd,delay_time, 1))||
                (t_ret_2 = uart_get((uint8_t*)cmd,0,4))) 
            {
                if(!ram_mon_flag)
                {
                    if (!cnt) 
                    {
                        cmd->RC=TARERR;break;
                    }  /* retry end */
                    cnt--;
                    send_break();
                    continue;  /* retry */
                }
                else
                {
                    if (!cnt) 
                    {            /* short delay fail */
                        if (delay_time >= MAX_OPER_DELAY)
                        {
                            cmd->RC = TARERR;
                            delay_time = 0x0000U;   /*recover delay_time */
                            break;
                        }
                        if (delay_time == 0) delay_time++;
                        delay_time *= 2;   /* delay_time */
                        cnt = CMD_RETRY;   /* reset retry times */
                        send_break();
                        continue;
                    }   /* retry end */
                    cnt--;
                    send_break();
                    continue;   /* retry */
                }
            }
            break;   /* communication success */
        }
    }
    return cmd->RC;   /* 'cmd->RC' indicate the communication status */
}

/**********************************************************************/
/* Function Name: uart_communication_16                                */
/* Description: send continue 16 bytes commands to target MCU (contains 2 commands type)*/
/*              Type D1: send FC, Data0.....Data15 and SUM, receiving RC   */
/*              Type D2: send FC, receiving Data0.....Data15, SUM and RC   */
/* Parameters: *cmd16 ---address of the command                         */
/* Return: ---communication status                                    */
/**********************************************************************/
uint8_t uart_communication_16(UART_COMMAND_16 *cmd16)
{
    uint32_t cnt;
    cnt = CMD_RETRY;   /* retry times */
    cmd16->RC = NORMAL;
    if ((cmd16->FC & 0x20))  /* tyge monitor 2-18 which need 16 byte read and write */
    { 
        /* type D */
        if ((cmd16->FC & 0x80))  
        {		
            while (1) 
            {
                /*uart_timer_start();*/
            	if ((t_ret_1 = uart_put((uint8_t*)cmd16,delay_time, 1))||
                	(t_ret_2 = uart_get((uint8_t*)cmd16,0,18))) 
                {
                    if(t_ret_2 == 0x02)
                    {
                        if((Secu16BytesRec == 4)&&(cmd16->Data3 == SECERR))
                        {
                            cmd16->RC = SECERR;
                            Secu16BytesRec = 0;
                            break;
                        }
                    }
                    if(!ram_mon_flag)
                    {
                        if (!cnt) 
                        {
                            cmd16->RC=TARERR;break;
                    	}  /* retry end */
                    	cnt--;
                    	send_break();
                    	continue;  /* retry */
                    }
                    else
                    {
                        if (!cnt) 
                        {            /* short delay fail */
                            if (delay_time >= MAX_OPER_DELAY)
                            {
                                cmd16->RC = TARERR;
                                delay_time = 0x0000U;   /*recover delay_time */
                                break;
                            }
                            if (delay_time == 0) delay_time++;
                            delay_time *= 2;   /* delay_time */
                            cnt = CMD_RETRY;   /* reset retry times */
                            send_break();
                            continue;
                        }   /* retry end */
                        cnt--;
                        send_break();
                        continue;   /* retry */
                    }
            	}
                break;   /* communication success */
            }
        }
    }
    return cmd16->RC;   /* 'cmd->RC' indicate the communication status */
}

/**********************************************************************/
/* Function Name: uart_communication_8                                */
/* Description: send continue 8 bytes commands to target MCU (contains 2 commands type)*/
/*              Type D3: send FC, Data0.....Data7 and SUM, receiving RC   */
/* Parameters: *cmd8 ---address of the command                        */
/* Return: ---communication status                                    */
/**********************************************************************/
uint8_t uart_communication_8(UART_COMMAND_8 *cmd8)
{
    uint32_t cnt;
    cnt = CMD_RETRY;   /* retry times */
    cmd8->RC = NORMAL;
    if ((cmd8->FC & 0x20))  /* tyge monitor 2-18 which need 16 byte read and write */
    { 
        /* type E */
        if (!(cmd8->FC & 0x80))
        {
            while (1) 
            {
                /*uart_timer_start();*/
                if ((t_ret_1 = uart_put((uint8_t*)cmd8,delay_time, 10))||//18
                    (t_ret_2 = uart_get((uint8_t*)cmd8,0,1))) 
                {
                    if(!ram_mon_flag)
                    {
                        if (!cnt) 
                        {
                            cmd8->RC=TARERR;break;
                    	}  /* retry end */
                        cnt--;
                        send_break();
                        continue;  /* retry */
                    }
                    else
                    {
                        if (!cnt)  /* short delay fail */
                        {            
                            if (delay_time >= MAX_OPER_DELAY)
                            {
                                cmd8->RC = TARERR;
                                delay_time = 0x0000U;   /*recover delay_time */
                                break;
                            }
                            if (delay_time == 0) delay_time++;
                            delay_time *= 2;   /* delay_time */
                            cnt = CMD_RETRY;   /* reset retry times */
                            send_break();
                            continue;
                    	}   /* retry end */
                        cnt--;
                        send_break();
                        continue;   /* retry */
                    }
                }
                break;   /* communication success */
            }		
        return cmd8->RC;   /* 'cmd->RC' indicate the communication status */
	}
    }
    /* chma added */
    return ERROR; 
}


