/**********************************************************************/
/* file name: hostif.c                                                */
/* function description: BGM adapter host interface.                  */
/**********************************************************************/
/* ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU LIMITED. 2007           */
/**********************************************************************/
//#include "frameio.h"
#include "version.h"
#include "LPCdef.h"

void HostIF_Init(void);
uint8_t trim_cr(UART_COMMAND* cmd);
uint8_t RegBuff_Init(UART_COMMAND* cmd);
static uint8_t clock_setting(UART_COMMAND* cmd, uint8_t ReadWrite);
uint8_t get_baud_rate(UART_COMMAND* cmd);
uint8_t uart_baudrate_up(UART_COMMAND* cmd, uint8_t up_flag);
static uint8_t read_user_reg(uint16_t* ReadRegData, uint16_t ReadRegID);
static uint8_t read_general_reglist(uint16_t TempPS, uint16_t* offset);
static uint8_t write_user_reg(uint16_t WriteRegData, uint16_t WriteRegID);
static uint8_t read_BDSU_reg(UART_COMMAND *cmd, uint16_t BDSUAddress);
static uint8_t write_BDSU_reg(UART_COMMAND *cmd, uint16_t BDSUAddress);
static uint8_t modify_RSTODIS(UART_COMMAND* cmd, uint8_t flag);
static void proc_start_mon(void);
static void proc_exit_mon(void);
static void proc_init_mon(void);
static void proc_set_clk(void);
static void proc_bgma_pow(void);
static void proc_write_reg(void);
static void proc_read_reg(void);
static void proc_read_reglist(void);
static void proc_write_mem(void);
static void proc_read_mem(void);
static void proc_erase_flash(void);
static void proc_read_brk_stat(void);
static void proc_exe_mcu(void);
static void proc_reset_mcu(void);
static void proc_abort_mcu(void);
static void proc_set_rck_adr(void);
static void proc_read_rck_smdat(void);
static void proc_set_brk(void);
static void proc_del_brk(void); 
static void proc_trim_cr(void);
static void proc_user_cmd(void);
static void proc_load_env(void);
static void proc_cng_adpt_mode(void);
static void proc_load_adpt_env(void);
static void proc_other(void);
static void rlt1_enable(uint8_t one_shot, uint32_t timer);
static void rlt1_disable(void);
static uint8_t check_rlt1_overflow(void);
static void clear_rtl1_flag(void);

uint8_t monitor_state;
uint8_t power_state;
uint8_t run_fn;
uint8_t CR_state;
uint8_t tar_SYCC;
uint8_t tar_SYCC2;
uint8_t tar_PLLC;
uint8_t tar_baud_rate;
uint8_t mainOSC_freq;
uint32_t delay_time;
uint16_t retry_counter;
uint8_t rck_length;
uint16_t rck_adr[RCK_MAX_SIZE];
uint8_t rck_read_type[RCK_MAX_SIZE];
uint8_t version_num;
uint8_t level_num;
uint8_t release_num;
uint8_t bgma_upload_flag;
uint8_t ReservUserClk_SYCC;
uint8_t ReservUserClk_SYCC2;
uint8_t ReservUserClk_PLLC;
uint8_t FlagForGoTime=0;
uint8_t ResetFlag=0;
uint8_t Read16_Flag=0;
uint8_t BRFlag1M=0;
uint8_t MianCLKPLLFlaf=0;

    /* main clock frequency table */
const uint8_t freq[4] = {
            0x01U, 0x04U, 0x08U, 0x10U
};

    /* clock divide table */
const uint8_t DIV_table[4] = {
            0x01U, 0x04U, 0x08U, 0x10U
/*SYCC[1:0]:  00     01     10     11 */
};

    /* register address table */
const uint16_t MON_REG[24] = { 
    0x008EU, 0x008CU, 0x0088U, 0x008AU, 0x0086U, 0x0002U, 0x0000U,
    /* A,       T,       IX,      SP,      EP,      PS,      PC, */
    0, 0, 0, 0, 0, 0, 0, 0, 0,      /* Reserved */
    0x0100U, 0x0101U, 0x0102U, 0x0103U, 0x0104U, 0x0105U, 0x0106U, 0x0107U
    /* R0,      R1,      R2,      R3,      R4,      R5,      R6,      R7,*/
};

    /* initial register value(for RESET_MCU using) */
const uint16_t INIT_REG_VALUE[7] = { 
    0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0000U, 0x0030U, 0x0000U 
    /* A,       T,       IX,      SP,      EP,     PSER,    PCER, */
}; /* PCER value not be used, PCER will be set to reset entry after reset */

/* table of command process */
CMDTBL const commandtable[] = {
    { 0x0000U, proc_start_mon,},
    { 0x0100U, proc_exit_mon,},
    { 0x0200U, proc_init_mon,},
    { 0x1826U, proc_set_clk,},
    { 0x1928U, proc_bgma_pow},
    { 0x2000U, proc_write_reg,},
    { 0x2100U, proc_read_reg,},
    { 0x2200U, proc_read_reglist,},
    { 0x3000U, proc_write_mem,},
    { 0x3100U, proc_read_mem,},
    { 0x3600U, proc_erase_flash,},
    { 0x4000U, proc_read_brk_stat,},
    { 0x4100U, proc_exe_mcu,},
    { 0x4200U, proc_reset_mcu,},
    { 0x4300U, proc_abort_mcu,},
    { 0x5000U, proc_set_brk,},
    { 0x5100U, proc_del_brk,},
    { 0xA128U, proc_set_rck_adr,},
    { 0xA228U, proc_read_rck_smdat,},
    { 0xE026U, proc_trim_cr,},
    { 0xE126U, proc_user_cmd,},
    { 0xF400U, proc_load_env,},
    { 0xFE00U, proc_cng_adpt_mode,},
    { 0xFF00U, proc_load_adpt_env,},
    { 0xFFFFU, proc_other,},
};


/** hostI/F proc **/
/**********************************************************************/
/* Function Name: proc_other                                          */
/* Description: process the USB command which contains invalid FC     */
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
static void proc_other(void)                        /* command error */
{
    set_errcode(COMERR);
    return ;
}

/**********************************************************************/
/* Function Name: proc_start_mon                                      */
/* Description: process the start monitor command from USB            */
/*              read ENV and return the value to PC                   */
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
static void proc_start_mon(void)
{
    UART_COMMAND cmd;
    uint16_t offset;

    /**leak UVCC power*/
    //bFM_GPIO_DDR1_P1 = 0;  //SI->P11
    //bFM_GPIO_DDR5_P0 = 0;  //RSTMX->P50
    bFM0P_GPIO_ADE_AN01 = 0;  // Disable pin ADC function
    Gpio1pin_InitIn ( GPIO1PIN_P11, Gpio1pin_InitPullup( 0u ) );  // SI pin
    Gpio1pin_InitIn ( GPIO1PIN_P50, Gpio1pin_InitPullup( 0u ) );  // RSTMX pin
    /**end************/

    power_state &= ~USER_RST;  /* clear user reset flag at the beginning of monitor */
    monitor_state &= ~CLKUP_ON;  /* set clock up mode off at the beginning of monitor */
    monitor_state |= MON_START;  /* monitor start, monitor will stop in EXIT_MON */
    if(version_num == VER_35) {
        tar_SYCC = DEF_SYCC;     
        tar_SYCC2 = DEF_SYCC2;   /* set clock mode as default */
        tar_PLLC = DEF_PLLC;
    } else if(version_num == VER_1_18) {
        tar_SYCC = DEF_SYCC_1_18;     
        tar_SYCC2 = DEF_SYCC2_1_18;   /* set clock mode as default */
        tar_PLLC = DEF_PLLC;
    }

    put_normal();            /* USBbuf[FRMOUT_ENUM] = 0 */
    RegBuff_Init(&cmd);

    /* PST FC 00 -------- set address */
    cmd.FC = BGMA_PST;
    SET_UARTCMD_ADDR(cmd,MONITOR_INFO_ADDR);
    if (uart_communication(&cmd) != NORMAL) {
        set_errcode(cmd.RC);
        return ;                     /* process end if error occurred */
    }
    
    /* read monitor version,level and release number */
    cmd.FC = BGMA_DRD;
    for (offset=0; offset<MONITOR_INFO_NUM; offset++){
        /* DRD XX XX -------- read ENV */
        if (uart_communication(&cmd) != NORMAL){     /* error occurred in communication */
            set_errcode(cmd.RC);
            return ;                /* process end if error occurred */
        } 
        if(offset == 0) version_num = cmd.AddrL;
        else if(offset == 1) level_num = cmd.AddrL;
        else if(offset == 2) release_num = cmd.AddrL;
        put_paramb(offset, cmd.AddrL);          /* cmd.AddrL = read value */
    }  
    put_frmlen(MONITOR_INFO_NUM);              /* set USBfrmlen */

    return ;
}

/**********************************************************************/
/* Function Name: proc_exit_mon                                       */
/* Description: process the exit monitor command from USB             */
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
static void proc_exit_mon(void)
{
    monitor_state &= ~MON_START; /* EMU stop */
    put_normal();
    if(IO_UVCCM_IN){
       if(IO_POUTEN_IN) IO_POUTEN_OUT = 0; /* if power supply is enabled, disable power supply */
    }
    if(!VER_2_18(version_num)) FlagForGoTime = 3; /*clear first go flag janeAdd */

    /**leak UVCC power*/
    bFM_GPIO_PDOR1_P1 = 0; //SI->P11
    bFM_GPIO_DDR1_P1 = 1;  //SI->P11

    IO_RSTMX_OUT = 0;      //RSTMX->P50
    bFM_GPIO_DDR5_P0 = 1;  //RSTMX->P50
    /**end************/
    return ;
}

/**********************************************************************/
/* Function Name: proc_init_mon                                       */
/* Description: process the initial monitor command from USB          */
/*              clear the BCR, BSTR and BFR register                  */
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
static void proc_init_mon(void)
{
    UART_COMMAND cmd;
    uint16_t InitData;
    uint8_t i;

    put_normal();
    /* set initial value */
    InitData = 0x0000U;
    /* clear BPR0 (Break Point Register) */
    SET_UARTCMD_ADDR(cmd,InitData);
    if (write_BDSU_reg(&cmd,BDSU_BPR0) !=NORMAL){
        set_errcode(cmd.RC);
        return ;
    }
    /* clear BPR1 */
    SET_UARTCMD_ADDR(cmd,InitData);
    if (write_BDSU_reg(&cmd,BDSU_BPR1) !=NORMAL){   
        set_errcode(cmd.RC);
        return ;
    }
    /* clear BCR,BSTR,BFR 3bytes */
    for (i=0; i<3; i++){
        SET_UARTCMD_ADDR(cmd,InitData);
        if (write_BDSU_reg(&cmd,BDSU_BCR+i) != NORMAL){
            set_errcode(cmd.RC);
            return ;
        }
    }

    bgma_upload_flag = 1; /* indicate upload process begin */
    if((monitor_state & CLKUP_ON) != CLKUP_ON){ /* if clock up is not enable, clock up automatically */
        if (clock_up(&cmd)){ 
            set_errcode(cmd.RC);
            return;
        }
        delay_time = 0x0000U;          /* recover delay time */
        if(version_num == VER_35){
            tar_SYCC = DEF_SYCC;     
            tar_SYCC2 = DEF_SYCC2;   /* set clock mode as default */
            tar_PLLC = DEF_PLLC;
        }
        else if(version_num == VER_1_18){
            tar_SYCC = DEF_SYCC_1_18;     
            tar_SYCC2 = DEF_SYCC2_1_18;   /* set clock mode as default */
            tar_PLLC = DEF_PLLC;
        }
    }
    
    if(uart_baudrate_up(&cmd, UART_BRT_UP)){ /* baud rate up */
        set_errcode(cmd.RC);
        return;
    }
    return ;
}

/**********************************************************************/
/* Function Name: write_clkup_OSC                                        */
/* Description: write user OSC to 0x7b                */
/* Parameters: cmd -- address of the command                          */
/*              DOSC -- the user selected OSC                  */
/* Return: communication status                                       */
/**********************************************************************/
uint8_t write_clkup_OSC(UART_COMMAND* cmd, uint8_t DOSC)
{
   cmd->FC = BGMA_PST;
   SET_PUARTCMD_ADDR(cmd, BDSU_EXTOSC);
   if (uart_communication(cmd) != NORMAL) return cmd->RC;
   cmd->FC = BGMA_DWR;
   cmd->AddrH = 0;
   cmd->AddrL = DOSC;
   if (uart_communication(cmd) != NORMAL) return cmd->RC;
   
    return NORMAL;
}
/**********************************************************************/
/* Function Name: write_clkup_enable                                        */
/* Description: write user OSC to 0x7b                */
/* Parameters: cmd -- address of the command                          */
/*             SFlag -- 1: enable clock up                            */
/*                   -- 0: disable clock up                           */
/* Return: communication status                                       */
/**********************************************************************/
uint8_t write_clkup_enable(UART_COMMAND* cmd, uint8_t SFlag)
{
   uint8_t Dat;
   
   cmd->FC = BGMA_PST;
   SET_PUARTCMD_ADDR(cmd, BDSU_CLKFlag);
   if (uart_communication(cmd) != NORMAL) return cmd->RC;
   cmd->FC = BGMA_DRD;
   if (uart_communication(cmd) != NORMAL) return cmd->RC;
   Dat = cmd->AddrL;
   
   if(SFlag==0x03){
       Dat |= 0x05;        //bit2 for baud rate flag
       BRFlag1M = 1;       //500k
   } else if(SFlag==0x01){
       Dat &= ~0x04;       //bit2 for baud rate flag
       Dat |= 0x01;
       BRFlag1M = 0;       //1M
   } else if(SFlag==0x10){
       Dat &= ~0x01;       
       Dat |= 0x04;        //bit2 for baud rate flag
       BRFlag1M = 1;       //500k
   } else{
       Dat &= ~0x05;       //bit2 for baud rate flag
       BRFlag1M =1;        //500k
   }
   cmd->FC = BGMA_PST;
   SET_PUARTCMD_ADDR(cmd,BDSU_CLKFlag);
   if (uart_communication(cmd) != NORMAL) return cmd->RC;
   cmd->FC = BGMA_DWR;
   cmd->AddrH = 0;
   cmd->AddrL = Dat;
   if (uart_communication(cmd) != NORMAL) return cmd->RC;
   
    return NORMAL;
}

/**********************************************************************/
/* Function Name: proc_set_clk                                        */
/* Description: process the set clock command from USB                */
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
static void proc_set_clk(void)
{
    uint16_t offset;
    uint8_t ClkUpMode;
    UART_COMMAND cmd;
    
    put_normal();
    offset = 0;
    ClkUpMode = get_paramb(offset++);  /* get clock up mode */
    mainOSC_freq = get_paramb(offset);
    if (ClkUpMode & 0x01) {
        monitor_state |= CLKUP_ON; /* ClkUpMode:0 =1 means ClockUp ON */
        if (clock_up(&cmd)){ 
            set_errcode(cmd.RC);
            return;
        }
        delay_time = 0x0000U;          /* recover delay time */
        if(version_num == VER_35){
            tar_SYCC = DEF_SYCC;     
            tar_SYCC2 = DEF_SYCC2;   /* set clock mode as default */
            tar_PLLC = DEF_PLLC;
        }
        else if(version_num == VER_1_18){
            tar_SYCC = DEF_SYCC_1_18;     
            tar_SYCC2 = DEF_SYCC2_1_18;   /* set clock mode as default */
            tar_PLLC = DEF_PLLC;
        }
    }
    else monitor_state &= ~CLKUP_ON; /* ClkUpMode:0 =0 means ClockUp OFF */

    if(VER_2_18(version_num)) {
        write_clkup_OSC(&cmd, mainOSC_freq);
        ClkUpMode &= 0x03;
        write_clkup_enable(&cmd,ClkUpMode);
    }

    return ;
}

/**********************************************************************/
/* Function Name: proc_bgma_pow                                       */
/* Description: process the power supply command from USB             */
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
static void proc_bgma_pow(void)
{
    uint16_t offset;
    uint8_t PowerType,OperationFlag;

    put_normal();
    offset = 0;
    offset++;  /* ignore reserve byte */
    PowerType = get_paramb(offset);
   
    if(PowerType == 0x00)
    {
        if(IO_UVCCM_IN)/* if UVCC is high, disable power supply */
        {   
            IO_POUTEN_OUT = 0;
        }
        else
        {
            if(IO_POUTEN_IN)
                IO_POUTEN_OUT = 0;
        }
        OperationFlag = 0;
    } 
    else if(PowerType == 0x01)
    {
        if(!IO_UVCCM_IN) /* if UVCC is low, enable power supply */
        {
            IO_POUTEN_OUT = 1;
            OperationFlag = 0;
            rlt1_enable(1, BGMA_POWER_TIMEOUT_TIMER); /* set 50ms as timeout time for power on process */
            while((power_state & LOW_POWER) == LOW_POWER)
            {
                if(IO_UVCCM_IN)
                {
                    power_on_init();
                    /**leak UVCC power*/
                    bFM_GPIO_DDR1_P1 = 0;  //SI->P11
                    bFM_GPIO_DDR5_P0 = 0;  //RSTMX->P50
                   /**end************/
                   break;
                }
                if(check_rlt1_overflow()) /* 50ms, power on process timeout */
                {  
                    rlt1_disable();
                   set_errcode(VCCERR);
                   return;
                }
            }
            rlt1_disable();
        } 
        else
        {
           OperationFlag = 1;
        }
    } 
    else 
    {
        set_errcode(PARAER);
        return;
    }
    offset = 0;
    put_paramb(offset,OperationFlag);      /* return frame: OperationFlag*/
    put_frmlen(sizeof(OperationFlag));
    return;
}

/**********************************************************************/
/* Function Name: proc_write_reg                                      */
/* Description: process the write register command from USB           */
/*              write data to desired register                        */
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
static void proc_write_reg(void)
{                                          /* need modified later */
    uint8_t WriteState;
    uint16_t offset;
    uint32_t WriteRegID;
    uint16_t WriteNumber;
    uint32_t WriteData;
    
    offset = 0;
    put_normal();
    WriteRegID = get_paramw(offset);       /* get register ID */
    offset += sizeof(uint32_t);
    
    WriteNumber = get_paramh(offset);
    if (WriteNumber != 0x01U){             /* only one register should be written */
        set_errcode(PARAER);               /* parameter error */
        return ;
    }
    offset += sizeof(uint16_t);
    
    WriteData = get_paramw(offset);        /* get write data */
    WriteState = write_user_reg((uint16_t)WriteData,(uint16_t)WriteRegID);
    if (WriteState != NORMAL){
        set_errcode(WriteState);
        return ;
    } else {
        offset = 0;
        put_paramh(offset,WriteNumber);      /* return frame: write number */
        put_frmlen(sizeof(WriteNumber));
        return ;
    }
}

/**********************************************************************/
/* Function Name: proc_read_reg                                       */
/* Description: process the read register command from USB            */
/*              read data from desired register                       */
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
static void proc_read_reg(void)
{
    uint8_t ReadState;
    uint16_t offset;
    uint32_t ReadRegID;
    uint16_t ReadNumber;
    uint16_t ReadRegData;/* should be unsigned long type in return frame */
    
    offset = 0;
    put_normal();
    ReadRegID = get_paramw(offset);        /* get register ID */
    offset += sizeof(uint32_t);
    
    ReadNumber = get_paramh(offset);
    if (ReadNumber != 0x01U){          /* only one register should be read */
        set_errcode(PARAER);               /* parameter error */
        return ;
    }
    ReadState = read_user_reg(&ReadRegData,(uint16_t)ReadRegID);
    if (ReadState != NORMAL){
        set_errcode(ReadState);
        return ;
    } else {
        offset = 0;
        put_paramh(offset,ReadNumber);        /* return read number */
        offset += sizeof(uint16_t);
        put_paramw(offset,(uint32_t)ReadRegData);      /* return read value */
        offset += sizeof(uint32_t);
        put_frmlen(offset);
        return ;
    }
}

/**********************************************************************/
/* Function Name: proc_read_reglist                                   */
/* Description: process the read register list command from USB       */
/*              read data from all registers                          */
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
static void proc_read_reglist(void)
{
    uint8_t ReadState;
    uint16_t offset;             /* for read data from USBbufer */
    uint16_t ReadRegID;          /* number we should read */
    uint16_t ReadRegData;        /* temp readed data */
    uint16_t TempPS;             /* temp PS value for R0~R7 */

    //wait60us(1);
    offset = 0;
    put_normal();
    offset++;                          /* ignore flag */
    if (get_paramh(offset) != REG_LIST_NUM){    /* read reg number must be (15) */
        set_errcode(PARAER);
        return ;
    }
    
    offset = sizeof(uint16_t);
    for (ReadRegID=A_ID; ReadRegID<=PC_ID; ReadRegID++){   /* read all register */
        ReadState = read_user_reg(&ReadRegData,ReadRegID);
        if (ReadState != NORMAL){
            set_errcode(ReadState);
            return ;
        }
        put_paramw(offset,(uint32_t)ReadRegData);
        offset += sizeof(uint32_t);
        if (ReadRegID == PS_ID) TempPS = ReadRegData; /* record PS value */
    }
    ReadState = read_general_reglist(TempPS,&offset);
    if (ReadState != NORMAL){
            set_errcode(ReadState);
            return ;
        }
    put_paramh(0,REG_LIST_NUM);   /* put read register number: 15 */
    put_frmlen(offset);
    return ;
}

/**********************************************************************/
/* Function Name: DefClkWriteRead                                      */
/* Description: save the user clock to global variable and      */
/*            feedback global variable value to user read   */
/* Parameters: ReadWrite--read 0, write 1                            */
/*             SyccPll--operation address               */
/*             WriteDat--write to global variable data      */
/* Return: none                                                       */
/**********************************************************************/
uint8_t DefClkWriteRead(uint8_t ReadWrite, uint32_t SyccPll, uint8_t WriteDat)
{
    switch(SyccPll)
    {
        case SYCC_ADDR:
            if(ReadWrite == READ)
                return tar_SYCC;
            else
                tar_SYCC = WriteDat;
        break;
        case SYCC2_ADDR:
            if(ReadWrite == READ)
                return tar_SYCC2;
            else{
                tar_SYCC2 = WriteDat;
                if((monitor_state & CLKUP_ON) == CLKUP_ON)MianCLKPLLFlaf = 0x01;}
        break;
        case PLLC_ADDR:
            if(ReadWrite == READ)
                return tar_PLLC;
            else{
                if(((tar_SYCC2 & 0x30)!= 0x30)&&((tar_SYCC2 & 0x04)!= 0x04))
                    tar_PLLC = WriteDat;
                if(((monitor_state & CLKUP_ON) == CLKUP_ON)&&(MianCLKPLLFlaf == 0x01))
                    MianCLKPLLFlaf = 0x02;}
        break;
    }
    
    
    return NORMAL;
}

/**********************************************************************/
/* Function Name: BdsuRamClkWrRead                                      */
/* Description: save the user clock to global variable and      */
/*            feedback global variable value to user read   */
/* Parameters: ReadWrite--read 0, write 1                            */
/*             SyccPll--operation address               */
/*             WrReadDat--write to BDSU RAM     */
/* Return: none                                                       */
/**********************************************************************/
uint8_t BdsuRamClkWrRead(uint8_t ReadWrite, uint32_t SyccPll, uint8_t *WrReadDat)
{
	UART_COMMAND cmd;

	cmd.FC = BGMA_PST;
	
	switch(SyccPll){
		case SYCC_ADDR:
			SET_UARTCMD_ADDR(cmd,BDSU_SYCC_RAM);
		break;
		case SYCC2_ADDR:
			SET_UARTCMD_ADDR(cmd,BDSU_SYCC2_RAM);
		break;
		case PLLC_ADDR:
			SET_UARTCMD_ADDR(cmd,BDSU_PLLC_RAM);
		break;
	}
	if (uart_communication(&cmd) != NORMAL) return cmd.RC;
	
	if (ReadWrite == READ) cmd.FC = BGMA_DRD;
	else if (ReadWrite == WRITE) {    /* set SYCC to debug mode */
		cmd.FC = BGMA_DWR;
		cmd.AddrH = 0;
		cmd.AddrL = *WrReadDat;
	}else return PARAER;
	if (uart_communication(&cmd) != NORMAL) return cmd.RC;
	if (ReadWrite == READ) *WrReadDat = cmd.AddrL;/* store user SYCC */

	cmd.FC = BGMA_PST;
	SET_UARTCMD_ADDR(cmd,(uint16_t)(SyccPll+1));   /* set start address */
	/* PST xx xx -------- set read address */
	if (uart_communication(&cmd) != NORMAL){
		set_errcode(cmd.RC);
		return 1;
	}

	return NORMAL;
}

/**********************************************************************/
/* Function Name: UserRead_CLK                                       */
/* Description: process the read memory command from USB              */
/*              read data from memory                                 */
/* Parameters: Add--operation address                            */
/*             Offset--buffer offset                    */
/*             HAddDat--cmd.AddrH                   */
/*             LAddDat--cmd.AddrL                   */
/* Return: none                                                       */
/**********************************************************************/
static void UserRead_CLKDis(uint32_t Add, uint32_t Offset, uint8_t HAddDat, uint8_t LAddDat)
{
	UART_COMMAND cmd;
	uint8_t DatAdd1,DatAdd2;
	
	if(!VER_2_18(version_num)){
		if((Add == PLLC_ADDR)&&(((monitor_state & CLKUP_ON) == CLKUP_ON)||(((monitor_state & CLKUP_ON) != CLKUP_ON)&&(FlagForGoTime == 1)))){
			put_paramb(Offset++,DefClkWriteRead(READ,Add,0));
			put_paramb(Offset,DefClkWriteRead(READ,(Add+1),0));}
		else if(((Add == SYCC_ADDR)||(Add == SYCC2_ADDR))&&(((monitor_state & CLKUP_ON) == CLKUP_ON)||(((monitor_state & CLKUP_ON) != CLKUP_ON)&&(FlagForGoTime == 1)))){
			put_paramb(Offset++,DefClkWriteRead(READ,Add,0));
			put_paramb(Offset,LAddDat);}
		else if((((Add+1) == SYCC_ADDR)||((Add+1) == SYCC2_ADDR)||((Add+1) == PLLC_ADDR))
			&&(((monitor_state & CLKUP_ON) == CLKUP_ON)||(((monitor_state & CLKUP_ON) != CLKUP_ON)&&(FlagForGoTime == 1)))){
			put_paramb(Offset++,HAddDat);  /* cmd.AddrH = read value */
			put_paramb(Offset,DefClkWriteRead(READ,(Add+1),0));}
		else{			
			put_paramb(Offset++,HAddDat);  /* cmd.AddrH = read value */
        	put_paramb(Offset,LAddDat);}  /* cmd.AddrL = read value */
	}
	else if(VER_2_18(version_num)){
		if((Add == PLLC_ADDR)&&(((monitor_state & CLKUP_ON) == CLKUP_ON)||(((monitor_state & CLKUP_ON) != CLKUP_ON)&&(ResetFlag == 1)))){
			if (BdsuRamClkWrRead(READ,Add,&DatAdd1) != NORMAL){
            set_errcode(TARERR);       /* set error code */
            return ;}
			if (BdsuRamClkWrRead(READ,(Add+1),&DatAdd2) != NORMAL){
            set_errcode(TARERR);       /* set error code */
            return ;}
			cmd.FC = BGMA_PST;
			SET_UARTCMD_ADDR(cmd,(uint16_t)(Add+2));   /* set start address */
	/* PST xx xx -------- set read address */
			if (uart_communication(&cmd) != NORMAL){
				set_errcode(cmd.RC);
				return ;
			}
			put_paramb(Offset++,DatAdd1);
			put_paramb(Offset,DatAdd2);}
		else if(((Add == SYCC_ADDR)||(Add == SYCC2_ADDR))&&(((monitor_state & CLKUP_ON) == CLKUP_ON)||(((monitor_state & CLKUP_ON) != CLKUP_ON)&&(ResetFlag == 1)))){
			if (BdsuRamClkWrRead(READ,Add,&DatAdd1) != NORMAL){
            set_errcode(TARERR);       /* set error code */
            return ;}
			cmd.FC = BGMA_PST;
			SET_UARTCMD_ADDR(cmd,(uint16_t)(Add+2));   /* set start address */
	/* PST xx xx -------- set read address */
			if (uart_communication(&cmd) != NORMAL){
				set_errcode(cmd.RC);
				return ;
			}
			put_paramb(Offset++,DatAdd1);
			put_paramb(Offset,LAddDat);}
		else if((((Add+1) == SYCC_ADDR)||((Add+1) == SYCC2_ADDR)||((Add+1) == PLLC_ADDR))
			&&(((monitor_state & CLKUP_ON) == CLKUP_ON)||(((monitor_state & CLKUP_ON) != CLKUP_ON)&&(ResetFlag == 1)))){
			if (BdsuRamClkWrRead(READ,(Add+1),&DatAdd2) != NORMAL){
            set_errcode(TARERR);       /* set error code */
            return ;}
			cmd.FC = BGMA_PST;
			SET_UARTCMD_ADDR(cmd,(uint16_t)(Add+2));   /* set start address */
	/* PST xx xx -------- set read address */
			if (uart_communication(&cmd) != NORMAL){
				set_errcode(cmd.RC);
				return ;
			}
			put_paramb(Offset++,HAddDat);  /* cmd.AddrH = read value */
			put_paramb(Offset,DatAdd2);}
		else{			
			put_paramb(Offset++,HAddDat);  /* cmd.AddrH = read value */
        	put_paramb(Offset,LAddDat);}  /* cmd.AddrL = read value */
	}
}

/**********************************************************************/
/* Function Name: UserRead_CLKDisOne                                       */
/* Description: process the read memory command from USB              */
/*              read data from memory                                 */
/* Parameters: Add--operation address                            */
/*             Offset--buffer offset                    */
/*             LAddDat--cmd.AddrL               */
/*             MFlag--0:Normal read; 1:RCK read                 */
/* Return: none                                                       */
/**********************************************************************/
static void UserRead_CLKDisOne(uint32_t Add, uint32_t Offset, uint8_t LAddDat, uint8_t MFlag)
{
    uint8_t BdsuRamDat;
    
    if(MFlag == 1)
        put_paramb(Offset++,0x00);
    if((!VER_2_18(version_num))&&((Add == SYCC_ADDR)||(Add == SYCC2_ADDR)||(Add == PLLC_ADDR))
                    &&(((monitor_state & CLKUP_ON) == CLKUP_ON)||(((monitor_state & CLKUP_ON) != CLKUP_ON)&&(FlagForGoTime == 1))))
                    put_paramb(Offset,DefClkWriteRead(READ,Add,0));
                else if((VER_2_18(version_num))&&((Add == SYCC_ADDR)||(Add == SYCC2_ADDR)||(Add == PLLC_ADDR))
                    &&(((monitor_state & CLKUP_ON) == CLKUP_ON)||(((monitor_state & CLKUP_ON) != CLKUP_ON)&&(ResetFlag == 1)))){
                    if (BdsuRamClkWrRead(READ,Add,&BdsuRamDat) != NORMAL){
                        set_errcode(TARERR);       /* set error code */
                        return ;
                    }
                    put_paramb(Offset,BdsuRamDat);
                }
                else
                    put_paramb(Offset,LAddDat);  /* cmd.AddrL = read value */
}

/**********************************************************************/
/* Function Name: proc_write_mem                                      */
/* Description: process the write memory command from USB             */
/*              write data to memory                                  */
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
static void proc_write_mem(void)
{
    UART_COMMAND cmd,cmd1;
    UART_COMMAND_8 cmd8;
    uint16_t offset;
    uint32_t StartAddress;
    uint32_t WriteNumber;
    uint8_t TempDCR;
    uint16_t TempCounter,i;
    uint8_t j;
    uint8_t ExtendedCommand;
    uint8_t WriteState;
    uint8_t WR8TemperaPara;
    uint8_t *ReadDToCMD8;
    uint32_t StartAddrTrack=0;
    uint8_t BDSWrit;
	
    offset = 0;
    put_normal();
    TempDCR = 0;
    WriteState = NORMAL;
    /* ignore memory data size + attribution */
    offset += sizeof(uint8_t) + sizeof(uint8_t);
    StartAddress = get_paramw(offset);  /* get start address */
    offset += sizeof(uint32_t);
	
    WriteNumber = get_paramw(offset);
    if(WriteNumber == 0x00)
    {
        offset = 0;
        put_paramw(offset, WriteNumber);
        offset += sizeof(uint32_t);
        put_frmlen(offset);
        return ;
    }
    if ( (WriteNumber > MAX_WRITE_LEN)||((StartAddress + WriteNumber) > 0x00010000UL) )
    {
        set_errcode(OVRFLW);
        return ;      
    }
    offset += sizeof(uint32_t) + (uint16_t)WriteNumber;
    ExtendedCommand = get_paramb(offset);
    offset -= (uint16_t)WriteNumber;                /* point to the write data */
    
    if ( ExtendedCommand == 0xFFU )
    {
        if ( read_BDSU_reg(&cmd,BDSU_DCR) != NORMAL )
        {
            set_errcode(cmd.RC);    /* read DCR: wild register control bit */
            return ;
        }
        if ( cmd.AddrL & 0x01U )
        {
            TempDCR = 0x01U;    /* wild register has been set */
            cmd.AddrH = 0;
            cmd.AddrL = 0;
            if ( write_BDSU_reg(&cmd,BDSU_DCR) != NORMAL )
            {
                set_errcode(cmd.RC);
                return ;
            }
        }
        if ( modify_RSTODIS(&cmd,SET_RSTODIS) != NORMAL )  /* set BCR bit6 */
        {
            set_errcode(cmd.RC);
            return ;          
        }
    }

    cmd.FC = BGMA_PST;
    SET_UARTCMD_ADDR(cmd,(uint16_t)StartAddress);
    /* PST XX XX -------- set start address */
    if ( uart_communication(&cmd) != NORMAL )
    {
        set_errcode(cmd.RC);
        WriteState = cmd.RC;
        modify_RSTODIS(&cmd,CLR_RSTODIS);/* clear BCR bit6 */
        return ;
    }
    
    switch (ExtendedCommand){
        case 0x00U:                            /* write RAM&IO user */
            cmd.FC = BGMA_WR;
            break;
		
        case 0x01U:                            /* write RAM&IO emu */
            cmd.FC = BGMA_DWR;
            break;
		
        case 0xFFU:                            /* write flash */
            TempCounter = (uint16_t)WriteNumber;
            if ( TempCounter%2 )
            {
                cmd.FC = BGMA_FWR;
                cmd.AddrH = 0;
                cmd.AddrL = get_paramb(offset++);
                if ( uart_communication(&cmd) != NORMAL )
                {
                    if (cmd.RC == WRTERR)
                    {
                        set_erradrs(cmd.RC,StartAddress);    /* set error address */
                    }
                    else
                    {
                         set_errcode(cmd.RC);
                    }
                    WriteState = cmd.RC;
                    break; 
                }
                TempCounter--;
                StartAddrTrack = 1;
            }
            if ( (TempCounter / 8)&&(VER_2_18(version_num)) ) /*jane  16 bytes data write*/
            {
                WR8TemperaPara = TempCounter / 8;
                cmd8.FC = BGMA_FWR8;
                for( i=0; i<WR8TemperaPara; i++ )
                {
                    ReadDToCMD8 = &(cmd8.Data0);
                    for( j=0;j<8;j++ )
                    { 
                        *(ReadDToCMD8++) = get_paramb(offset++);
                    }
                    if ( uart_communication_8(&cmd8) != NORMAL )
                    {
                        if ( cmd8.RC == WRTERR )
                        {
                            set_erradrs(cmd8.RC,(StartAddress+j+StartAddrTrack));    /* set error address */
                        }
                        else
                        {
                            set_errcode(cmd8.RC);
                        }
                        WriteState = cmd8.RC;
                        TempCounter = 0;/*jane add for that after write error the 2bytes operation will be done */ 
                        break;
                    }
                    TempCounter -= REV_8_BYTE;
                    StartAddrTrack += REV_8_BYTE;
                }
            }
            TempCounter /=2;
            cmd.FC = BGMA_FWR_2;
            for ( i=0; i<TempCounter; i++ )
            {
                cmd.AddrH = get_paramb(offset++);
                cmd.AddrL = get_paramb(offset++);
                /* WR/DWR xx xx -------- write data */
                if ( uart_communication(&cmd) != NORMAL )
                {
                    if ( cmd.RC == WRTERR )
                    {
                        set_erradrs(cmd.RC,(StartAddress+StartAddrTrack));    /* set error address */
                    }
                    else
                    {
                        set_errcode(cmd.RC);
                    }
                    WriteState = cmd.RC;
                    break;                  
                }
                StartAddrTrack += REV_2_BYTE;
            }
            break;
 
        default:
            set_errcode(PARAER);
            return ;
    }
	
    if ((ExtendedCommand==0x00U) || (ExtendedCommand==0x01U))
    {
        cmd.AddrH = 0;
        for( i=0; i<WriteNumber; i++ )
        {
            if( ExtendedCommand == 0x00 )
            {
                cmd.FC = BGMA_WR;
            }
            cmd.AddrL = get_paramb(offset++);
            /* WR/DWR xx xx -------- write data */
            if( (ExtendedCommand==0x00U)&&(((StartAddress+i) == SYCC_ADDR)||((StartAddress+i) == SYCC2_ADDR)||((StartAddress+i) == PLLC_ADDR))
                &&(((monitor_state & CLKUP_ON) == CLKUP_ON)||(((monitor_state & CLKUP_ON) != CLKUP_ON)&&((FlagForGoTime == 1)||(ResetFlag == 1)))) )
            {
                if( !VER_2_18(version_num) )
                {
                    DefClkWriteRead(WRITE,(StartAddress+i),get_paramb(offset-1));
                }
                else if ( VER_2_18(version_num) )
                {
                    BDSWrit = get_paramb(offset-1);
                    if ( BdsuRamClkWrRead(WRITE,(StartAddress+i),&BDSWrit) != NORMAL )
                    {
                        set_errcode(cmd.RC);       /* set error code */
                        return;
                    }                  
                }
            }
            else
            {
                if((ExtendedCommand==0x01U)&&((StartAddress+i)==BDSU_BCR)&&(cmd.AddrL & 0x04))
                {
                    if((VER_2_18(version_num))|| ((version_num == VER_1_18) && (level_num == 2)))
                    {
                        if(uart_baudrate_up(&cmd1, UART_BRT_RCV))
                        {
                            set_errcode(cmd.RC);
                            return ; 
                        }                      
                    }
                }
                if ( uart_communication(&cmd) != NORMAL )
                {
                    if (cmd.RC == WRTERR)
                    {
                        set_erradrs(cmd.RC,StartAddress+i);    /* set error address */
                    }
                    else
                    {
                        set_errcode(cmd.RC);
                    }
                    WriteState = cmd.RC;
                    break;
                }
                if(( ExtendedCommand==0x01U)&&((StartAddress+i)==BDSU_BCR)&&(cmd.AddrL & 0x04) )
                {
                    if((VER_2_18(version_num))|| ((version_num == VER_1_18) && (level_num == 2)))
                    {
                        if(uart_baudrate_up(&cmd1, UART_BRT_UP))
                        {
                            set_errcode(cmd.RC);
                            return;
                        }
                    }
                }
            }
        } 
    }
    
    if ( WriteState == NORMAL )    /* completed with normal */
    {
        offset = 0;
        put_paramw(offset, WriteNumber);
        offset += sizeof(uint32_t);
        put_frmlen(offset);
    }
    
    if (ExtendedCommand == 0xFFU)  /* write flash */
    {
        if ( modify_RSTODIS(&cmd,CLR_RSTODIS) != NORMAL )  /* clear BCR bit6 */  
        {
            set_errcode(cmd.RC);
        }
        if ( TempDCR == 0x01U )
        {
            cmd.AddrH = 0;
            cmd.AddrL = 0x01U;
            if ( write_BDSU_reg(&cmd,BDSU_DCR) != NORMAL )
            {
                set_errcode(cmd.RC);
                return;
            }
        }
    }
    return;
}

/**********************************************************************/
/* Function Name: proc_read_mem                                       */
/* Description: process the read memory command from USB              */
/*              read data from memory                                 */
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
static void proc_read_mem(void)
{
    UART_COMMAND cmd;
    UART_COMMAND_16 cmd16;
    uint16_t offset;
    uint32_t StartAddress;
    uint32_t ReadNumber;
    uint16_t TempCounter;
    uint8_t i;
    uint8_t ExtendedCommand;
    uint8_t WR16TemperaPara;
    uint16_t end_address = 0xFFFF;
    uint32_t Readaddress;
    
    offset = 0;
    put_normal();
    /* ignore mem data size + attribution */
    offset += sizeof(uint8_t) + sizeof(uint8_t);
    StartAddress = get_paramw(offset);      /* get the start address */
    offset +=sizeof(uint32_t);
    ReadNumber = get_paramw(offset);
    if((ReadNumber > MAX_READ_LEN)||((StartAddress + ReadNumber) > 0x00010000UL))
    {
        set_errcode(OVRFLW);
        return ;
    }
	
    offset += sizeof(uint32_t);
    ExtendedCommand = get_paramb(offset);
	
    cmd.FC = BGMA_PST;
    SET_UARTCMD_ADDR(cmd,(uint16_t)StartAddress);   /* set start address */
    /* PST xx xx -------- set read address */
    if (uart_communication(&cmd) != NORMAL)
    {
        set_errcode(cmd.RC);
        return ;
    }
	
    offset = 0;
    offset += sizeof(uint32_t);
    TempCounter = (uint16_t)ReadNumber;
    switch (ExtendedCommand){
        case 0x00U:
            Readaddress = StartAddress;
            if( TempCounter%2 )  /* read 1 byte first if ReadNumber is odd type */
            { 
                cmd.FC = BGMA_RD;              /* read RAM&IO user */
                if (uart_communication(&cmd) != NORMAL)
                {
                    set_errcode(cmd.RC);       /* set error code */
                    return ;
            	}			
                UserRead_CLKDisOne(Readaddress,offset,cmd.AddrL,0);
                offset++;
                TempCounter--;
                Readaddress ++;
            }
            if((TempCounter / 16)&&(VER_2_18(version_num))&&(Readaddress > REV_16_BYTE))  /*for 0x06 0x07 and 0x0d default value read janeAdd*/ 
            {
                WR16TemperaPara = TempCounter / 16;
                cmd16.FC = BGMA_RD16; 
                Read16_Flag = 1;
                for (i=0; i<WR16TemperaPara; i++) /* read RAM&IO user */
                {
                    /* read 16 bytes mem */
                    if ( uart_communication_16(&cmd16) != NORMAL )
                    {
                        set_errcode(cmd16.RC);   /* set error code */
                        TempCounter = 0;
                        Read16_Flag = 0;
                        return ;
                    }
                    put_param16(offset,&(cmd16.Data0));  /* cmd.AddrH = read value */
                    offset += REV_16_BYTE;
                    TempCounter -= REV_16_BYTE;
                    Readaddress += REV_16_BYTE;
                }
                Read16_Flag = 0;
            }
            TempCounter /= 2; 
            cmd.FC = BGMA_RD_2;                     /* read RAM&IO user */
            for ( i=0; i<TempCounter; i++ )
            {
                /* RD/DRD xx xx -------- read mem */
                if ( uart_communication(&cmd) != NORMAL )
                {
                    set_errcode(cmd.RC);   /* set error code */
                    return ;
                }
                /****return default sycc sycc2 and pll value*****************************/
                UserRead_CLKDis(Readaddress,offset,cmd.AddrH,cmd.AddrL);
                offset += 2;
                Readaddress += 2;
            }
            if( bgma_upload_flag == 1 )
            {
                if( (uint16_t)(StartAddress+ReadNumber-1) == end_address )
                {
                    bgma_upload_flag = 0;
                    if( VER_2_18(version_num) )
                    {
                        ResetFlag = 1;/*for clock read janeAdd*/
                    }
                    if( !VER_2_18(version_num) )
                    {
                        FlagForGoTime = 1;
                    }
                    if( (version_num == VER_35)|| ((version_num == VER_1_18) && (level_num == 1)) ) /*jane add*/
                    {
                        if( uart_baudrate_up(&cmd, UART_BRT_RCV) )
                        {
                            set_errcode(cmd.RC);
                            return;
                        }
                    }
                }
            }
            break;

        case 0x01U:
            cmd.FC = BGMA_DRD;                      /* read RAM&IO emu */
            for ( i=0; i<(uint8_t)ReadNumber; i++ )
            {
                /* RD/DRD xx xx -------- read mem */
                if ( uart_communication(&cmd) != NORMAL )
                {
                    set_errcode(cmd.RC);   /* set error code */
                    return ;
                }
                put_paramb(offset++,cmd.AddrL);  /* cmd.AddrL = read value */
            }
            break;
            
        default:
            set_errcode(PARAER);
            return;
    }
    put_frmlen(offset);    /* set frame length */
    offset = 0;
    put_paramw(offset,ReadNumber);     /* set read number */
    return ;
}

/**********************************************************************/
/* Function Name: proc_erase_flash                                    */
/* Description: process the erase flash command from USB              */
/*              do flash erase or sector erase                        */
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
static void proc_erase_flash(void)
{
    UART_COMMAND cmd;
    uint32_t SectorAddress;
    uint16_t offset;
    uint8_t TempDCR;
    uint8_t cnt;
    uint8_t EraseState;
    uint8_t UartState;
    
    offset = 0;
    put_normal();
    TempDCR = 0;
    EraseState = NORMAL;
    
    if ( read_BDSU_reg(&cmd,BDSU_DCR) != NORMAL )  /* read DCR: wild register control bit */
    {
        set_errcode(cmd.RC);
        return ;
    }
    
    if ( cmd.AddrL & 0x01U )
    {
        TempDCR = 0x01U;    /* wild register has been set */
        cmd.AddrH = 0;
        cmd.AddrL = 0;
        if ( write_BDSU_reg(&cmd,BDSU_DCR) != NORMAL )
        {
            set_errcode(cmd.RC);
            return ;
        }
    }

    if ( modify_RSTODIS(&cmd,SET_RSTODIS) != NORMAL ) /* set BCR bit6 */
    {
        set_errcode(cmd.RC);
        return ;
    }
    
    cmd.FC = BGMA_FER;
    if ( get_paramb(offset) )  /* sector erase */
    {
        offset += sizeof(uint8_t);
        /* ignore control type */
        SectorAddress = get_paramw(offset); 
        SET_UARTCMD_ADDR(cmd,SectorAddress);
        // TempSUM = cmd.FC+cmd.AddrH+cmd.AddrL;
    }
    else  /* chip erase */
    {
        cmd.AddrH = 0;
        cmd.AddrL = 0;
        // TempSUM = cmd.FC+cmd.AddrH+cmd.AddrL;
    }
    /* FER xx xx -------- erase mem */
    cnt = CMD_RETRY;   /* use offset as retry counter */
    
    while (1)
    {
        /*uart_timer_start();*/
        if ( uart_put((uint8_t*)&cmd,delay_time,4) )
        {
            if ( !cnt )
            {
                EraseState=TARERR;
                break;   /* retry end */
            }
            cnt--;
            sendbrk(UART_BREAK_TIMER);
            continue;
        }
        EraseState = NORMAL;
        break;
    }
    
    if ( EraseState != NORMAL )  /* UART communication error */
    {
        set_errcode(EraseState);
        modify_RSTODIS(&cmd,CLR_RSTODIS);
        return ;
    }
    
    /* a long time delay needed for waiting RC */ 
    while (1)
    {
        /*uart_timer_start();*/
        UartState = erase_get(&EraseState);
        if ( UartState == NORMAL )
        {
            if ( EraseState != NORMAL )
            {
                set_errcode(EraseState);
            }
            break;
        }
        else if ( UartState == FRAME_ERROR )
        {
            set_errcode(TARERR); /* UART communication error,set TARERR */
            sendbrk(UART_BREAK_TIMER);
            break;
        }
        else if ( UartState == TIME_OUT_ERROR )
        {
            set_errcode(ERSERR);
            break;
        }
    }
    
    if ( modify_RSTODIS(&cmd,CLR_RSTODIS) != NORMAL )  /* clear BCR bit6 */
    {
        set_errcode(cmd.RC);
        return ;
    }
    
    if ( TempDCR == 0x01U )
    {
        cmd.AddrH = 0;
        cmd.AddrL = 0x01U;
        if ( write_BDSU_reg(&cmd,BDSU_DCR) != NORMAL )
        {
            set_errcode(cmd.RC);
            return ;
        }
    }
    
    return;
}

/**********************************************************************/
/* Function Name: proc_read_brk_stat                                  */
/* Description: process the read break status command from USB        */
/*              read the status of break points                       */
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
static void proc_read_brk_stat(void)
{
    UART_COMMAND cmd;
    uint16_t offset;
    uint32_t BrkFactor;
    uint16_t Read_PC;
    uint8_t Read_BFR;
	
    offset = 0;
    Read_PC = 0;
    put_normal();
    if ((monitor_state & MCU_RUN) == MCU_RUN)
    {
        /* in free run mode, return 00 00 ff ff ff ff 00 00 00 00 */
        put_paramb(offset++,NO_BREAK);            /* status == RUN */
        put_paramw(offset,0xFFFFFFFFUL);
        offset += sizeof(uint32_t);
        put_paramw(offset,0);
        offset += sizeof(uint32_t);
        put_frmlen(offset);
	} 
    else 
    {
        if (read_BDSU_reg(&cmd,BDSU_PCER) != NORMAL)    /* read PC */
        {
            set_errcode(cmd.RC);
            return ;
        }
        GET_UARTCMD_ADDR(cmd,Read_PC);  /* store PCER value */
        if (read_BDSU_reg(&cmd,BDSU_BFR) != NORMAL)  /* read BFR */
        {
            set_errcode(cmd.RC);
            return ;
        }
        Read_BFR = cmd.AddrL; /* store BFR value */
        put_paramb(offset++,HAVE_BREAK);        /* status == BREAK */
        put_paramw(offset,(uint32_t)Read_PC);     /* PCER */
        offset += sizeof(uint32_t);
        BrkFactor = 0;
        if ((monitor_state & RC2_ERROR) == RC2_ERROR)
        {
            BrkFactor |= EXE_ERROR;     /* set bit14 to indecate RC2 error */
            monitor_state &= ~RC2_ERROR;  /* clead RC2_ERROR flag */
        }
		
        if (Read_BFR & EMU)    BrkFactor |= FORCE_BRK;    /* force break */
        if (Read_BFR & SFB)    BrkFactor |= STEP_BRK;     /* step break */
        if (Read_BFR & SWB)    BrkFactor |= SW_BRK;       /* software break */
        if (Read_BFR & BPF1)   BrkFactor |= CODE1_BRK;   /* code break 1 */
        if (Read_BFR & BPF0)   BrkFactor |= CODE0_BRK;   /* code break 2 */
        put_paramw(offset,BrkFactor);                  /* break factor */
        offset += sizeof(uint32_t);
        put_frmlen(offset);
    }
    return ;
}

/**********************************************************************/
/* Function Name: proc_exe_mcu                                        */
/* Description: process the execute mcu command from USB              */
/*              force the target MCU running in free run mode         */
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
static void proc_exe_mcu(void)
{
    UART_COMMAND cmd;
    uint8_t ReadBCR;
    uint8_t ExecuteType;
    uint8_t WatchDogFlag;
    uint16_t offset;
    uint8_t ClockSetState; 
    
    /*reserve user clock*/
    if( VER_2_18(version_num) )
    {
        ResetFlag = 0;
    }
    if( !VER_2_18(version_num) )
    {
        FlagForGoTime++;
        if( FlagForGoTime != 0x02 )
        {
            FlagForGoTime=3;    /*avoid first go*/
        }
        else if(FlagForGoTime == 2)  /*the first time enter into go command janeAdd*/
        {
            if ( (monitor_state & CLKUP_ON) != CLKUP_ON )
            {
                if ( clock_setting(&cmd,WRITE) )  /* recover clock setting to uers mode */
                {
                    set_errcode(cmd.RC);
                    return ; 
                }
            }
        }
    }
    /*execute MCU GO*/
    offset = 0;
    put_normal();
    if ( (power_state & RST_ERROR) == RST_ERROR )
    {
        set_errcode(URIERR);
        power_state &= ~RST_ERROR;
        return ;
    }
    
    if (read_BDSU_reg(&cmd,BDSU_BCR) != NORMAL)  /* read BCR */
    {
        set_errcode(cmd.RC);
        return ;
    }
    ReadBCR = cmd.AddrL;   /* store BCR */
    ExecuteType = get_paramb(offset);      /* continuous:00 or step:01 */
    
    switch (ExecuteType & MASK_EXETYPE){
        case CONTINUOUS:
            ReadBCR &= ~SBE;
            break;

        case STEP:
            ReadBCR |= SBE;
            break;
		
        default:
            set_errcode(PARAER);
            return ;
    }
    cmd.AddrH = 0;
    cmd.AddrL = ReadBCR;
    if (write_BDSU_reg(&cmd,BDSU_BCR) != NORMAL)  /*write BCR */
    {
        set_errcode(cmd.RC);
        return ;
    }
    
    WatchDogFlag = get_paramb(++offset);
    if ( (WatchDogFlag & MASK_WATCHDOG) == W_DOG_EN )
    {
        /* Watchdog timer enable */
        ReadBCR &= ~WDSTP;
    }
    else
    {
        /* Watchdog timer disable */
        ReadBCR |= WDSTP;
    }
    
    cmd.AddrH = 0;
    cmd.AddrL = ReadBCR;
    if (write_BDSU_reg(&cmd,BDSU_BCR) != NORMAL)  /*write BCR */
    {
        set_errcode(cmd.RC);
        return ;
    }
    
    /* clear BFR */
    SET_UARTCMD_ADDR(cmd,0);
    if (write_BDSU_reg(&cmd,BDSU_BFR) != NORMAL)  /* write 00h to BFR */
    {
        set_errcode(cmd.RC);
        return ;
    }
    
    /*every go command reserve user clock*/
    if(!VER_2_18(version_num))  /*janeAdd*/
    {
        if ((monitor_state & CLKUP_ON) == CLKUP_ON)
        {
            ClockSetState = clock_setting(&cmd,WRITE); 
            if (ClockSetState != NORMAL)  /* recover clock setting to uers mode */
            {
                set_errcode(cmd.RC);
                return ; 
            }
        }
    }
    
    cmd.FC = BGMA_GO;                       /* write GO */
    /* GO xx xx -------- go command */
    if (uart_communication(&cmd) != NORMAL)
    {
        set_errcode(cmd.RC);
        return ;
    }
    
    monitor_state |= MCU_RUN;    /* set MCU_RUN flag */
    UART_DBG_CH->SCR_f.RIE = 1;  /* enable uart interrupt */ 
    p_rd_buf = p_wr_buf = &rev_buf[0];
    return ;
}

/**********************************************************************/
/* Function Name: proc_reset_mcu                                      */
/* Description: process the reset mcu command from USB                */
/*              reset the target MCU                                  */
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
static void proc_reset_mcu(void)
{
    UART_COMMAND cmd;
    uint8_t WriteState;
    put_normal();
    
    if(VER_2_18(version_num))    ResetFlag = 1;
    if( (version_num == VER_1_18 && level_num == 2)||(VER_2_18(version_num)) )
    {
        if( uart_baudrate_up(&cmd, UART_BRT_RCV) )
        {
            set_errcode(cmd.RC);
            return ; 
        }
      
    }
	
    bFM0P_EXTI_ENIR_EN0  = 0;  // Disable rtsmx external interrupt
    //IO_RSTX = 1;
    //IO_PDR4.bit.P44 = 0;    /* disable RST signal input */
    cmd.FC = BGMA_RST;
    /* RST xx xx -------- reset command */
    if (uart_communication(&cmd) != NORMAL)
    {
        set_errcode(cmd.RC);
        //IO_PDR4.bit.P44 = 1;    /* enable RST signal input */
        return ;
    } 
    
    WriteState = RegBuff_Init(&cmd);
    if ( WriteState != NORMAL ) 
    {
        set_errcode(WriteState);
    }
    
    if( version_num == VER_35 )
    {
        tar_SYCC = DEF_SYCC;     
        tar_SYCC2 = DEF_SYCC2;   /* set clock mode as default */
        tar_PLLC = DEF_PLLC;
    }
    else if( (version_num == VER_1_18) )
    {
        tar_SYCC = DEF_SYCC_1_18;
        tar_SYCC2 = DEF_SYCC2_1_18;   /* set clock mode as default */
        tar_PLLC = DEF_PLLC;      
    }
	
    //IO_PDR4.bit.P44 = 1;    /* enable RST signal input */
    //IO_RSTX = 0;
	
    bFM0P_EXTI_ENIR_EN0  = 1;  // Enable rtsmx external interrupt
    if( (version_num == VER_1_18 && level_num == 2)||(VER_2_18(version_num)) )
    {
        if( uart_baudrate_up(&cmd, UART_BRT_UP) )
        {
            set_errcode(cmd.RC);
            return ; 
        }
    }
    return ;
}

/**********************************************************************/
/* Function Name: proc_abort_mcu                                      */
/* Description: process the abort mcu command from USB                */
/*              force the target MCU abort from the free run mode     */
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
static void proc_abort_mcu(void)
{
    put_normal();
    /* DBG pin keep low about 683us */
    send_break();
}

/**********************************************************************/
/* Function Name: proc_set_rck_adr                                    */
/* Description: process set ram monitor address                       */
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
static void proc_set_rck_adr(void)
{
    uint16_t offset = 0;
    uint8_t cnt;
    put_normal();
    rck_length = get_paramb(offset);
    if(rck_length > RCK_MAX_SIZE)
    {
        set_errcode(PARAER);  /* the length exceed max size */
        rck_length = 0;
        return;
    }
    offset += sizeof(uint8_t);
    for(cnt=0; cnt<RCK_MAX_SIZE; cnt++)
    {
        rck_read_type[cnt] = get_paramb(offset); /* store data type */
        offset++;
        rck_adr[cnt] = get_paramh(offset); /* store data address */
        offset +=  sizeof(uint16_t);
    }
    return;
}

/**********************************************************************/
/* Function Name: proc_read_rck_smdat                                 */
/* Description: process ram monitor command from USB                  */
/*              read ram data from target MCU                         */
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
static void proc_read_rck_smdat(void)
{
    UART_COMMAND cmd;
    uint8_t mcu_state, ReadBCR, ClockSetState, cnt;
    uint16_t read_data, offset,wait_cnt = 0;
    if(rck_length == 0 || rck_length > RCK_MAX_SIZE)
    {
        rck_length = 0;
        offset = 0;
        put_normal();
	if((monitor_state & MCU_RUN) == MCU_RUN)
          mcu_state = EXECUTE_STATE;
        else 
          mcu_state = BREAK_STATE;
        put_paramb(offset++, mcu_state);
		put_paramb(offset++, 0);
        put_frmlen(offset);
        return;
    }
    
    /* if MCU is running, force break */
    if((monitor_state & MCU_RUN) == MCU_RUN)
    {
        mcu_state = EXECUTE_STATE;
        rlt1_enable(0,RT_MOM_WAIT_RC2_TIMER); 
        send_break();
        while((monitor_state & MCU_RUN) == MCU_RUN)
        {
            check_break_stat(&cmd);
            if(check_rlt1_overflow())
            {
                clear_rtl1_flag();
                if(wait_cnt<20)/* set 1.2s as timeout time to wait RC2 */
                { 
                    wait_cnt++;
                    continue;
                }
                rlt1_disable();
                set_errcode(TARERR); 
                return;
            }
        }
        rlt1_disable();
        if((monitor_state & RC2_ERROR) == RC2_ERROR)
        {
            set_errcode(MCUBUSY);  /* return MCU busy frame to host */
            return;
        }
    }
    else
    {
        mcu_state = BREAK_STATE;
    }
    /************ Read RAM data **********/
    offset = 0;
    put_normal();
    put_paramb(offset, mcu_state);
    offset++;
    put_paramb(offset, rck_length);
    offset++;
    for(cnt=0; cnt<rck_length; cnt++)
    {
        cmd.FC = BGMA_PST;
        SET_UARTCMD_ADDR(cmd,rck_adr[cnt]);
        if(uart_communication(&cmd) != NORMAL)
        {
            set_errcode(cmd.RC);
            return ;
        }
        if(rck_read_type[cnt] & 0x01U)
            cmd.FC = BGMA_RD_2;
        else
            cmd.FC = BGMA_RD;
        if(uart_communication(&cmd) != NORMAL)
        {
            set_errcode(cmd.RC);
            return ;
        }
        GET_UARTCMD_ADDR(cmd,read_data);
        if(rck_read_type[cnt] & 0x01U)
            UserRead_CLKDis(rck_adr[cnt],offset,(read_data>>8),(read_data&0x0FF));
        else
            UserRead_CLKDisOne(rck_adr[cnt],offset,(read_data&0x0FF),1);
        //put_paramh(offset, read_data);
        offset += sizeof(uint16_t);
    }
    put_frmlen(offset);
    /* Return in break status */
    if(mcu_state == BREAK_STATE) 
      return;
    /************* Execute MCU ***********/
    if((power_state & RST_ERROR) == RST_ERROR)
    {
        set_errcode(URIERR);
        power_state &= ~RST_ERROR;
        return ;
    }
    if(read_BDSU_reg(&cmd,BDSU_BCR) != NORMAL)/* read BCR */
    {   
        set_errcode(cmd.RC);
        return ;
    }
    ReadBCR = cmd.AddrL;   /* store BCR */
    ReadBCR &= ~SBE;
    cmd.AddrH = 0;
    cmd.AddrL = ReadBCR;
    if(write_BDSU_reg(&cmd,BDSU_BCR) != NORMAL)/*write BCR */
    {  
        set_errcode(cmd.RC);
        return ;
    }
    
    /* clear BFR */
    SET_UARTCMD_ADDR(cmd,0);
    if(write_BDSU_reg(&cmd,BDSU_BFR) != NORMAL)/* write 00h to BFR */
    {  
        set_errcode(cmd.RC);
        return ;
    }

    if(!VER_2_18(version_num))/*janeAdd*/
    {
      if ((monitor_state & CLKUP_ON) == CLKUP_ON)
      {
          ClockSetState = clock_setting(&cmd,WRITE); 
          if (ClockSetState != NORMAL)/* recover clock setting to uers mode */
          {  
            set_errcode(cmd.RC);
            return ; 
          }
      }
    }
    cmd.FC = BGMA_GO;                       /* write GO */
    /* GO xx xx -------- go command */
    if (uart_communication(&cmd) != NORMAL)
    {
        set_errcode(cmd.RC);
        return ;
    }
    monitor_state |= MCU_RUN;    /* set MCU_RUN flag */
    UART_DBG_CH->SCR_f.RIE = 1;  /* enable uart interrupt */
    p_rd_buf = p_wr_buf = &rev_buf[0];
    return ;
}

/**********************************************************************/
/* Function Name: proc_set_brk                                        */
/* Description: process the set break command from USB                */
/*              set break points address                              */
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
static void proc_set_brk(void)
{
    UART_COMMAND cmd;
    uint8_t ReadBCR, BreakPointNum;
    uint32_t BreakAddress;
    uint16_t offset, BreakPointID;    /* point to break point type flag */
    
    put_normal();
    offset = 0;
    BreakAddress = get_paramw(offset);
    offset += sizeof(uint32_t);
    if (get_paramb(offset)) 
    {
        set_errcode(PARAER);   /* break type != code type */
        return ;
    }
    
    BreakPointNum = get_paramb(++offset);  /* read break point number */
    switch (BreakPointNum)
    {
        case BP0:        /* break point 0 */
        BreakPointID = BDSU_BPR0;
        break;
        
        case BP1:        /* break point 1 */
        BreakPointID = BDSU_BPR1;
        break;
        
        default:
        set_errcode(PARAER);
        return ;
    }
    
    SET_UARTCMD_ADDR(cmd,(uint16_t)BreakAddress); /* set write value */
    if(write_BDSU_reg(&cmd,BreakPointID) != NORMAL)/* write BP0/BP1 */
    {   
        set_errcode(cmd.RC);
        return ;
    }  /* write break address to BDSU */
    
    if (read_BDSU_reg(&cmd,BDSU_BCR) != NORMAL)/* read BCR */
    {   
        set_errcode(cmd.RC);
        return ;
    }
    ReadBCR = cmd.AddrL;/* store BCR value */
    
    if(BreakPointNum == BP1) 
      ReadBCR |= BPE1;  /* set BCR:BPE1 */
    else 
      ReadBCR |= BPE0;  /* set BCR:BPE0 */
    cmd.AddrL = ReadBCR;
    if(write_BDSU_reg(&cmd,BDSU_BCR) != NORMAL)/* write BCR */
    {   
        set_errcode(cmd.RC);
        return ;
    }
    return ;
}

/**********************************************************************/
/* Function Name: proc_del_brk                                        */
/* Description: process the delete break command from USB             */
/*              delate break points                                   */
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
static void proc_del_brk(void)
{
    UART_COMMAND cmd;
    uint8_t ReadBCR, BreakPointNum;
    uint16_t offset=0, BreakPointID;
    put_normal();
     /* point to break point type flag */
    offset += sizeof(uint32_t);
    if (get_paramb(offset)) 
    {   
        set_errcode(PARAER);        /* break type != code break type */
        return ;
    }
    BreakPointNum = get_paramb(++offset);  /* read break point number */
    switch (BreakPointNum)
    {
        case BP0:        /* break point 0 */
        BreakPointID = BDSU_BPR0;
        break;
        
        case BP1:        /* break point 1 */
        BreakPointID = BDSU_BPR1;
        break;
        
        default:
        set_errcode(PARAER);
        return;
    }
    
    SET_UARTCMD_ADDR(cmd,0x0000U); /* set write value = 0x0000 */
    if(write_BDSU_reg(&cmd,BreakPointID) != NORMAL)/* write BP0/BP1 */
    {   
        set_errcode(cmd.RC);
        return ;
    } /* clear break address (write 0x0000 to BP0/BP1) */
    
    if(read_BDSU_reg(&cmd,BDSU_BCR) != NORMAL)/* read BCR */
    {    
        set_errcode(cmd.RC);
        return ;
    }
    ReadBCR = cmd.AddrL;
    
    if(BreakPointNum == BP1) 
        ReadBCR &= ~BPE1;         /* clear BPE1 */
    else 
        ReadBCR &= ~BPE0;         /* clear BPE0 */
    cmd.AddrL = ReadBCR;
    if(write_BDSU_reg(&cmd,BDSU_BCR) != NORMAL)/* write BCR */
    {    
        set_errcode(cmd.RC);
        return ;
    }
    return ;
}

/**********************************************************************/
/* Function Name: proc_trim_cr                                        */
/* Description: process the trim CR command from USB                  */
/*              trim the CR oscillator of the target MCU              */
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
static void proc_trim_cr(void)/* not confirmed, just for monitor testing */
{                         
    uint32_t offset;
    offset = 0;
    put_normal();
    if ((monitor_state & CR_FINE) == CR_FINE)/* CR is ok*/ 
    { 
        put_paramb(offset, CR_state);
        put_frmlen(++offset);
    }else{
        monitor_state |= TRIMMING;
        retry_counter =0;
        set_errcode(NOWTRIM);
    }
    return;
}

/**********************************************************************/
/* Function Name: proc_user_cmd                                       */
/* Description: process the user command from USB                     */
/*              force the target MCU to run the RAM code              */
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
static void proc_user_cmd(void)
{
    UART_COMMAND cmd;
    uint8_t CommandType;
    uint16_t offset;
    uint16_t IxValue;
    
    offset = 0;
    put_normal();
    CommandType = get_paramb(offset);
    IxValue = get_paramh(++offset);
    switch (CommandType)
    {
        case CMD_TYPE_A:
        cmd.FC = BGMA_CMD_A;
        SET_UARTCMD_ADDR(cmd,IxValue);
        break;
        
        case CMD_TYPE_B:
        cmd.FC = BGMA_CMD_B;
        break;
        
        default:
        set_errcode(PARAER);
        return;
    }
    /* 0A 00 90 -------- jump ram command */
    if (uart_communication(&cmd) != NORMAL){
        set_errcode(cmd.RC);
        return ;
    }
    if (cmd.FC == BGMA_CMD_B)
    {
        GET_UARTCMD_ADDR(cmd,IxValue);
        offset = 0;
        put_paramh(offset,IxValue);
        offset +=sizeof(uint16_t);
        put_frmlen(offset);
    }
    return ;
}

/**********************************************************************/
/* Function Name: proc_load_env                                       */
/* Description: process the load ENV command from USB                 */
/*              send the ENV information to PC                        */
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
static void proc_load_env(void)
{
    UART_COMMAND cmd;
    uint8_t i;
    uint16_t offset = 0;
    
    put_normal();
    put_paramh(offset,0xFFFFU);
    offset += sizeof(uint16_t);
    put_paramb(offset++,0xFFU);
    put_paramh(offset,AID);
    offset += sizeof(uint16_t);
    cmd.FC = BGMA_PST;
    SET_UARTCMD_ADDR(cmd,MONITOR_INFO_ADDR);   
    /* PST FC 00 -------- set ENV address */
    if(uart_communication(&cmd) != NORMAL)
    {
        set_errcode(cmd.RC);
        return ;
    }
    cmd.FC = BGMA_DRD;
    for(i=0;i<MONITOR_INFO_NUM;i++)
    {
        /* DRD xx xx -------- read ENV infomation */
        if(uart_communication(&cmd) != NORMAL)
        {
              set_errcode(cmd.RC);
              return ;
        }
        put_paramb(offset++,cmd.AddrL);  /* set ENV infomation to return frame */
    }
    put_paramh(offset,CMN_ID);          /* set CMN-ID to return frame */
    offset += sizeof(uint16_t);
    put_paramb(offset++,CVER);          /* set CVER to return frame */
    put_paramb(offset++,CLVL);          /* set CLVL to return frame */
    put_paramb(offset++,CREL);          /* set CREL to return frame */
    put_frmlen(offset);
    return ;
}

/**********************************************************************/
/* Function Name: proc_cng_adpt_mode                                  */
/* Description: process the configure adapter mode command from USB   */
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
static void proc_cng_adpt_mode(void)
{
    uint16_t offset= 0;
    put_normal();
    if (get_paramh(offset) != AID)      /* adapt ID != 0220 */
    {    
        set_errcode(PARAER);
        return ;
    }
    return ;
}

/**********************************************************************/
/* Function Name: proc_load_adpt_env                                  */
/* Description: process the load adapter ENV command from USB         */
/*              send adapter ENV information to PC                    */
/* Parameters: none                                                   */
/* Return:     none                                                   */
/**********************************************************************/
static void proc_load_adpt_env(void)
{
    uint16_t offset;
    
    offset = 0;
    put_normal();
    put_paramb(offset++,NUM);          /* NUM */
    put_paramh(offset,AID);             /* ADPT ID */
    offset += sizeof(uint16_t);
    put_paramb(offset++,VER);           /* ADPT version */
    put_paramb(offset++,LVL);           /* ADPT level */
    put_paramb(offset++,REL);           /* ADPT release */
    put_frmlen(offset);
    return ;
}

/* proc_* service functions */
/**********************************************************************/
/* Function Name: HostIF_Init                                         */
/* Description: indicate the target MCU is ready for receiving command*/
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
void HostIF_Init(void)
{
    retry_counter = 0x0000U;
    CR_state = NORMAL;
    monitor_state = 0; /* 00000000b ;initialize mcu_state after BGMA power on */
               /*           ||||||++-----MCU break mode*/
               /*           |||||++------no RC2 error detected*/
               /*           ||||++-------CR clock not trimmed*/
               /*           |||++--------clock up off*/
               /*           ||++---------monitor didn't start*/
               /*           |++----------not in trimming process*/
    power_state = 0; /* 00000000b ;initialize mcu_state after BGMA power on */
               /*           ||||++-----no reset error*/
               /*           |||++------reset not happen*/
               /*           ||++-------no need low power indication*/
               /*           |++--------power normal*/
}

/**********************************************************************/
/* Function Name: RegBuff_Init                                        */
/* Description: initial register buffer if received RC2 is "0x00"     */
/* Parameters: *cmd--- address of command                             */
/* Return: initialize state                                           */
/**********************************************************************/
uint8_t RegBuff_Init(UART_COMMAND* cmd)
{
   uint16_t i;
   uint16_t ResetEntry;
   uint8_t CommState;
   
   CommState = NORMAL;
   for (i=A_ID; i<=PS_ID; i++) {
       CommState = write_user_reg(INIT_REG_VALUE[i],i); /* write register */
       if (CommState != NORMAL){
           return CommState;
       }
   }
   
   cmd->FC = BGMA_PST;
   SET_PUARTCMD_ADDR(cmd,RESET_VECTOR);             /* read data from 0xFFFE */
   if (uart_communication(cmd) != NORMAL){
       CommState = cmd->RC;
       return CommState;
   }
   cmd->FC = BGMA_RD_2;
   if (uart_communication(cmd) != NORMAL){
       CommState = cmd->RC;
       return CommState;
   }
   GET_PUARTCMD_ADDR(cmd, ResetEntry);            /* get reset entry address */
   CommState = write_user_reg(ResetEntry,PC_ID); /* set PC_Buffer */
   if (CommState != NORMAL){
       return CommState;
   }
    return NORMAL;
}

/**********************************************************************/
/* Function Name: read_user_reg                                       */
/* Description: read one register value from target                   */
/* Parameters: *ReadRegData ---point of read data                     */
/*             ReadRegID ---ID number of the required register        */
/* Return: ---communication status                                    */
/**********************************************************************/
static uint8_t read_user_reg(uint16_t* ReadRegData, uint16_t ReadRegID)
{
    UART_COMMAND cmd;

    cmd.RC = NORMAL;
    cmd.FC = BGMA_PST;

    //if ((ReadRegID >= A_ID) && (ReadRegID <= PC_ID)){
    if (ReadRegID <= PC_ID){
        SET_UARTCMD_ADDR(cmd,MON_REG[ReadRegID]);
    }
    else if ((ReadRegID >= R0_ID) && (ReadRegID <= R7_ID)){  /* read r0~r7,PSER must be read out first */ 
        SET_UARTCMD_ADDR(cmd,MON_REG[PS_ID]);      /* get PSER address */
    }
    else return PARAER;
   
    /* PST XX XX -------- set register address */
    if (uart_communication(&cmd) != NORMAL) return cmd.RC;

    /* DRD XX XX -------- read register high byte */
    cmd.FC = BGMA_DRD;
    if (uart_communication(&cmd) != NORMAL) return cmd.RC;
    *ReadRegData = (uint16_t)cmd.AddrL<<8;

    /* DRD XX XX -------- read register low byte */
    if (uart_communication(&cmd) != NORMAL) return cmd.RC;
    *ReadRegData |= (uint16_t)cmd.AddrL;

    if (ReadRegID == SP_ID) *ReadRegData += 4;   /* SP+4 */

    if ((ReadRegID >= R0_ID) && (ReadRegID <= R7_ID)){   /* read R0~R7 */
        cmd.FC = BGMA_PST;
        *ReadRegData >>= 8;
        *ReadRegData &= 0x00F8U;   /* (PS & 0x00F8) */
        *ReadRegData += MON_REG[ReadRegID];/* (PS & 0x00F8) + 0x010X */
        SET_UARTCMD_ADDR(cmd,*ReadRegData);
        
        /* PST XX XX -------- set register address */
        if (uart_communication(&cmd) != NORMAL) return cmd.RC;
        
        /* RD XX XX -------- read one byte data */
        cmd.FC = BGMA_RD;
        if (uart_communication(&cmd) != NORMAL) return cmd.RC;
        *ReadRegData = (uint16_t)cmd.AddrL&0xFFU;
    }

    return NORMAL;
}

/**********************************************************************/
/* Function Name: read_general_reglist                                */
/* Description: read R0 ~ R7 from target                              */
/* Parameters: TempPS ---current PS value                             */
/*             offset ---USB buffer offset for store R0 ~ R7          */
/* Return: ---communication status                                    */
/**********************************************************************/
static uint8_t read_general_reglist(uint16_t TempPS, uint16_t* offset)
{
   UART_COMMAND cmd;
   uint16_t i;
   uint8_t RxValue;
   
   cmd.RC = NORMAL;
   cmd.FC = BGMA_PST;
   
   TempPS >>= 8;
   TempPS &= 0x00F8U;   /* (PS & 0x00F8) */
   TempPS += MON_REG[R0_ID];/* (PS & 0x00F8) + 0x0100 */
   SET_UARTCMD_ADDR(cmd,TempPS);
       
   /* PST XX XX -------- set register address */
   if (uart_communication(&cmd) != NORMAL) return cmd.RC;
       
   for (i=R0_ID; i<=R7_ID; i++){
       /* RD XX XX -------- read one byte data */
       cmd.FC = BGMA_RD;
       if (uart_communication(&cmd) != NORMAL) return cmd.RC;
       RxValue = cmd.AddrL;
       put_paramw(*offset,(uint32_t)RxValue);
       *offset += sizeof(uint32_t);
   }
   
    return NORMAL;
}

/**********************************************************************/
/* Function Name: write_user_reg                                      */
/* Description: write one data to target register                     */
/* Parameters: WriteRegData ---write data                             */
/*             WriteRegID ---ID number of the required register       */
/* Return: ---communication status                                    */
/**********************************************************************/
static uint8_t write_user_reg(uint16_t WriteRegData, uint16_t WriteRegID)
{
    UART_COMMAND cmd;
    uint16_t TempWriteAddr;
    uint8_t ReadState;
   
    cmd.RC = NORMAL;
    //if ((WriteRegID>=A_ID) && (WriteRegID <=PC_ID)){
    if (WriteRegID <=PC_ID){
        if (WriteRegID == SP_ID) WriteRegData -= 4;  /* SP - 4 */
        SET_UARTCMD_ADDR(cmd,MON_REG[WriteRegID]);
        cmd.FC = BGMA_PST;
        /* PST xx xx -------- set write address */
        if (uart_communication(&cmd) != NORMAL) return cmd.RC;
        
        cmd.FC = BGMA_DWR;
        cmd.AddrH = 0; 
        cmd.AddrL = WriteRegData>>8;
        /* DWR xx xx -------- write higher byte */
        if (uart_communication(&cmd) != NORMAL) return cmd.RC;
        
        cmd.FC = BGMA_DWR;
        cmd.AddrH = 0; 
        cmd.AddrL = WriteRegData & 0xFFU;
        /* DWR xx xx -------- write lower byte */
        if (uart_communication(&cmd) != NORMAL) return cmd.RC;
        
        return NORMAL;
   } else if ((WriteRegID >= R0_ID) && (WriteRegID <= R7_ID)){    /* read r0~r7,PSER must be read out first */ 
       ReadState = read_user_reg(&TempWriteAddr, PS_ID); /* read PS value */
       if (ReadState != NORMAL) return ReadState; /* read PS error */
       
       TempWriteAddr = (TempWriteAddr>>8)&0x00F8U;
       TempWriteAddr += MON_REG[WriteRegID]; /* get R0~R7 address */
       cmd.FC = BGMA_PST;
       SET_UARTCMD_ADDR(cmd,TempWriteAddr);
       
       /* PST xx xx -------- set write address */
       if (uart_communication(&cmd) != NORMAL) return cmd.RC;
       
       cmd.FC = BGMA_WR;
       cmd.AddrH = 0;
       cmd.AddrL = WriteRegData & 0xFFU;
       /* WR xx xx -------- write one byte */
       if (uart_communication(&cmd) != NORMAL) return cmd.RC;
       
       return NORMAL;
   } else return PARAER;
}

/**********************************************************************/
/* Function Name: write_BDSU_reg                                      */
/* Description: write BDSU register                                   */
/*              cmd->AddrH and cmd->AddrL stored the written data     */
/* Parameters: *cmd ---address of the command                         */
/*             BDSUAddress ---write register address                  */
/* Return: ---communication status                                    */
/**********************************************************************/
static uint8_t write_BDSU_reg(UART_COMMAND *cmd, uint16_t BDSUAddress)
{
    uint16_t WriteValue = 0;
    GET_PUARTCMD_ADDR(cmd,WriteValue);  /* get write data */
    
    cmd->FC = BGMA_PST;
    SET_PUARTCMD_ADDR(cmd,BDSUAddress);
   /* PST 00 xx -------- set register address */
   if (uart_communication(cmd) != NORMAL) return cmd->RC;
   
   if (BDSUAddress < BDSU_BCR){
       cmd->FC = BGMA_DWR;
       cmd->AddrH = 0;
       cmd->AddrL = WriteValue>>8;
       /* DWR 00 xx -------- write higher byte */
       if (uart_communication(cmd) != NORMAL) return cmd->RC;
   }
    
   cmd->FC = BGMA_DWR;
   cmd->AddrH = 0;
   cmd->AddrL = WriteValue & 0xFFU;
   /* DWR 00 xx -------- write lower byte */
   if (uart_communication(cmd) != NORMAL) return cmd->RC;
    return NORMAL;
}  

/**********************************************************************/
/* Function Name: read_BDSU_reg                                       */
/* Description: read BDSU register                                    */
/*              cmd->AddrH and cmd->AddrL will return the read data   */
/* Parameters: *cmd ---address of the command                         */
/*             BDSUAddress ---read  register address                  */
/* Return: ---communication status                                    */
/**********************************************************************/
static uint8_t read_BDSU_reg(UART_COMMAND *cmd, uint16_t BDSUAddress)
{     
	uint8_t ReadValue;
	ReadValue = 0;
	cmd->FC = BGMA_PST;
	SET_PUARTCMD_ADDR(cmd,BDSUAddress);
	
	/* PST xx xx -------- set register address */
	if (uart_communication(cmd) != NORMAL)  
	{
		return cmd->RC;
	}

	cmd->FC = BGMA_DRD;
	if (BDSUAddress < BDSU_BCR){
		/* DRD xx xx -------- read higher byte */
		if (uart_communication(cmd) != NORMAL) 
		{
			return cmd->RC;
		}
		ReadValue = cmd->AddrL;   /* store the BDSU higher byte */
	}
	/* DRD xx xx -------- read lower byte */
	if (uart_communication(cmd) != NORMAL) 
	{	
	    return cmd->RC;
	}
	
	cmd->AddrH = ReadValue; /* return the BDSU higher byte */
	return NORMAL;
}

/**********************************************************************/
/* Function Name: modify_RSTODIS                                      */
/* Description: modify the value of BCR register                      */
/* Parameters: *cmd ---address of the command                         */
/*             flag ---flag = 0: clrb BCR:6. flag = 1: setb BCR:6     */
/* Return: ---communication status                                    */
/**********************************************************************/
static uint8_t modify_RSTODIS(UART_COMMAND* cmd, uint8_t flag)
{           
    /* flag = 0: clrb BCR:6. flag = 1: setb BCR:6 */
    uint8_t ReadBCR;
    
    if (read_BDSU_reg(cmd,BDSU_BCR) != NORMAL) return cmd->RC;  /* read BCR */
    ReadBCR = cmd->AddrL;
    if (flag == SET_RSTODIS) ReadBCR |= RSTODIS;
    else if (flag == CLR_RSTODIS) ReadBCR &= ~RSTODIS;
    cmd->AddrL = ReadBCR;
    if (write_BDSU_reg(cmd,BDSU_BCR) != NORMAL) return cmd->RC; /* write BCR */
    
    return NORMAL;
}

/**********************************************************************/
/* Function Name:   clock_setting                                     */
/* Description: read user mode clock setting, change clock setting    */
/*              change clock setting to improve performance           */
/* Parameters: *cmd---address of the command                          */
/*             ReadWrite---read or write clock mode parameter         */
/* Return: clock setting result                                       */
/**********************************************************************/
static uint8_t clock_setting(UART_COMMAND* cmd, uint8_t ReadWrite)
{
    uint8_t TempSycc2;

    if((version_num == VER_1_18)||(version_num == VER_35)) {
    /*******************for PLL modify*********************/
    /*******************clear MOSCE *********************/
        if (ReadWrite == WRITE){
            cmd->FC = BGMA_PST;
            SET_PUARTCMD_ADDR(cmd,SYCC2_ADDR);
            if (uart_communication(cmd) != NORMAL) return cmd->RC;
            cmd->FC = BGMA_RD;
            if (uart_communication(cmd) != NORMAL) return cmd->RC;
            TempSycc2 = cmd->AddrL;
            TempSycc2 &= 0xfb; //clear MOSCE

            cmd->FC = BGMA_PST;
            SET_PUARTCMD_ADDR(cmd,SYCC2_ADDR);
            if (uart_communication(cmd) != NORMAL) return cmd->RC;
            cmd->FC = BGMA_WR;
            cmd->AddrH = 0;
            cmd->AddrL = TempSycc2;
            if (uart_communication(cmd) != NORMAL) return cmd->RC;
        }
       
        /* Read or write PLLC Register */
        cmd->FC = BGMA_PST;
        SET_PUARTCMD_ADDR(cmd,PLLC_ADDR);
        if (uart_communication(cmd) != NORMAL) return cmd->RC;
        if (ReadWrite == READ) cmd->FC = BGMA_RD;
        else if (ReadWrite == WRITE) {    /* set SYCC2 to debug mode */
            cmd->FC = BGMA_WR;
            cmd->AddrH = 0;
            cmd->AddrL = tar_PLLC;
        }else return PARAER;
        if (uart_communication(cmd) != NORMAL) return cmd->RC;
        if (ReadWrite == READ) tar_PLLC = cmd->AddrL; /* store user SYCC2 */
    }
    
    /* Read or write SYCC Register */
    cmd->FC = BGMA_PST;
    SET_PUARTCMD_ADDR(cmd,SYCC_ADDR);
    if (uart_communication(cmd) != NORMAL) return cmd->RC;
    if (ReadWrite == READ) cmd->FC = BGMA_RD;
    else if (ReadWrite == WRITE) {    /* set SYCC to debug mode */
        cmd->FC = BGMA_WR;
        cmd->AddrH = 0;
        cmd->AddrL = tar_SYCC;
    }else return PARAER;
    if (uart_communication(cmd) != NORMAL) return cmd->RC;
    if (ReadWrite == READ) tar_SYCC = cmd->AddrL;/* store user SYCC */
   
    /* Read or write SYCC2 register */
    cmd->FC = BGMA_PST;
    SET_PUARTCMD_ADDR(cmd,SYCC2_ADDR);
    if (uart_communication(cmd) != NORMAL) return cmd->RC;
    if (ReadWrite == READ) cmd->FC = BGMA_RD;
    else if (ReadWrite == WRITE) {    /* set SYCC2 to debug mode */
        cmd->FC = BGMA_WR;
        cmd->AddrH = 0;
        cmd->AddrL = tar_SYCC2;
    }else return PARAER;
    if (uart_communication(cmd) != NORMAL) return cmd->RC;
    if (ReadWrite == READ) tar_SYCC2 = cmd->AddrL; /* store user SYCC2 */
   
    if((version_num == VER_1_18)||(version_num == VER_35)) {
        if(((monitor_state & CLKUP_ON) == CLKUP_ON)&&(MianCLKPLLFlaf == 0x02)){
            /* Read or write PLLC Register */
            cmd->FC = BGMA_PST;
            SET_PUARTCMD_ADDR(cmd,PLLC_ADDR);
            if (uart_communication(cmd) != NORMAL) return cmd->RC;
            if (ReadWrite == READ) cmd->FC = BGMA_RD;
            else if (ReadWrite == WRITE) {    /* set SYCC2 to debug mode */
                cmd->FC = BGMA_WR;
                cmd->AddrH = 0;
                cmd->AddrL = tar_PLLC;
            }else return PARAER;
            if (uart_communication(cmd) != NORMAL) return cmd->RC;
            if (ReadWrite == READ) tar_PLLC = cmd->AddrL; /* store user SYCC2 */
        }
    }
    return NORMAL;
}

/**********************************************************************/
/* Function Name:   clock_up                                          */
/* Description: select a suitable clock mode according to             */
/*              the currect use's clock seting                        */
/* Parameters: none                                                   */
/* Return: communication status                                       */
/**********************************************************************/
uint8_t clock_up(UART_COMMAND* cmd)
{
    uint8_t up_flag;
    uint8_t tar_CRTH;
    uint8_t temp_SYCC;
    uint8_t temp_SYCC2;
    uint8_t temp_PLLC;
    uint8_t ClockSetState;
    uint8_t temp_para;
   
    up_flag = FALSE;
    ClockSetState = clock_setting(cmd,READ); 
    if (ClockSetState != NORMAL)  return cmd->RC; /* read clock setting mode */

    /* Read BDSU_CRTH register */
    cmd->FC = BGMA_PST;     /* read main CR freq mode */
    SET_PUARTCMD_ADDR(cmd,BDSU_CRTH);
    if (uart_communication(cmd) != NORMAL) return cmd->RC;
    cmd->FC = BGMA_RD;  /* read BDSU_CRTH vlaue in cmd->RC */
    if (uart_communication(cmd) != NORMAL) return cmd->RC;

    tar_CRTH = cmd->AddrL;       /* tar_CRTH[6:5] = main CR freq mode */
    temp_SYCC = tar_SYCC;
    temp_SYCC2 = tar_SYCC2;
    if((version_num == VER_1_18)||(version_num == VER_35)) temp_PLLC = tar_PLLC;

    if(version_num == VER_35){
        switch (tar_SYCC2 & SYCC2_RCS_35){ /* tar_SYCC2[5:4]= current Clock Selection */
            case SUBCR_CLK_35:   /* tar MCU runs into sub CR clock mode */
                tar_SYCC2 &= 0x0FU; 
                tar_SYCC2 |= (MAINCR_CLK_35); /* set tar_SYCC2[5:4] to select main CR */
                if (!(tar_CRTH & CRTH_DIV))   /* tar_CRTH[6:5]=00B, main CR = 1M */
                    tar_SYCC &= 0xFCU;        /* set DIV=00B */
                else tar_SYCC = (tar_SYCC & 0xFCU) + 0x02U;  /* set DIV = 10B */
                up_flag = TRUE;               /* needs clock up */
                break;
            case SUB_CLK_35:     /* tar MCU runs in sub clock mode */
                tar_SYCC2 &= 0x0FU; 
                tar_SYCC2 |= (MAINCR_CLK_35); /* set tar_SYCC2[5:4] to select main CR */
                if (!(tar_CRTH & CRTH_DIV))   /* main CR = 1M */
                    tar_SYCC &= 0xFCU;        /* set DIV=00B */
                else tar_SYCC = (tar_SYCC & 0xFCU) + 0x02U;  /* set DIV = 10B */
                up_flag = TRUE;    
                break;
           case MAINCR_CLK_35: /* tar MCU runs in main CR clock mode */
                if (!(tar_CRTH & CRTH_DIV)){    /* main CR = 1M */
                    tar_SYCC &= 0xFCU;       /* set DIV=00B */
                    up_flag = TRUE;
                }else if((tar_SYCC & 0x03)>0x02){/* 8M, 10M, 12.5M/8 */
                    tar_SYCC = tar_SYCC & 0xFCU + 0x02;       /* set DIV=10B */
                    up_flag = TRUE;
                }
                break;
            case MAIN_CLK_35:   /* tar MCU runs into main clock mode */
                temp_para = DIV_table[tar_SYCC & SYCC_DIV_35]/mainOSC_freq;
                if (temp_para >= 0x01U){   /* freq<0.5MHz */
                    if (mainOSC_freq > freq[2]) /* 8MHz<mainOSC<=16MHz */
                        tar_SYCC = (tar_SYCC & 0xFCU) + 0x02U;     /* set DIV=10B */
                    else if (mainOSC_freq > freq[1]) /* 4MHz<mainOSC<=8MHz */
                        tar_SYCC = (tar_SYCC & 0xFCU) + 0x01U;     /* set DIV=01B */
                    else tar_SYCC &= 0xFCU;     /* set DIV=00B */
                    up_flag = TRUE;
                }
                break;
            default:
                return NORMAL;
        }
    } else if(version_num == VER_1_18){
        switch (tar_SYCC & SYCC_SCS_18){ /* tar_SYCC2[4:2]= current Clock Selection */
            case SUBCR_CLK_18:   /* tar MCU runs into sub CR clock mode */
                tar_SYCC &= ~0x1CU; 
                tar_SYCC |= MAINCR_CLK_18; /* set tar_SYCC2[4:2] to select main CR */
                tar_SYCC = tar_SYCC & 0xFCU;  /* set DIV = 10B */
                up_flag = TRUE;               /* needs clock up */
                break;
           case SUB_CLK_18:     /* tar MCU runs in sub clock mode */
                tar_SYCC &= ~0x1CU; 
                tar_SYCC |= MAINCR_CLK_18; /* set tar_SYCC2[4:2] to select main CR */
                tar_SYCC = tar_SYCC & 0xFCU;;  /* set DIV = 10B */
                up_flag = TRUE;    
                break;
           case MAINCR_CLK_18: /* tar MCU runs in main CR clock mode */
                if((tar_SYCC & 0x03)>0x00){ /* div > 0 */
                    tar_SYCC = tar_SYCC & 0xFCU;       /* set DIV=00 */
                    up_flag = TRUE;
                }
                break;
           case MAIN_CLK_18:   /* tar MCU runs into main clock mode */
                temp_para = (4*DIV_table[tar_SYCC & SYCC_DIV_18])/mainOSC_freq; 
                if (temp_para >= 0x01U){   /* freq<0.5MHz */
                    if (mainOSC_freq >= freq[2]) /* 8MHz<=mainOSC<=16MHz */
                        tar_SYCC = tar_SYCC & 0xFCU;     /* set DIV=00B */
                    else {                /* mainOSC<8MHz */
                        tar_SYCC &= ~0x1CU; 
                        tar_SYCC |= MAINCR_CLK_18; /* set tar_SYCC2[4:2] to select main CR */
                        tar_SYCC = tar_SYCC & 0xFCU;  /* set DIV = 00B */
                    }
                    up_flag = TRUE;
                }
                break;
            case MAINCRPLL_CLK_18:
                if((tar_SYCC & 0x03)>0x00){ /* div > 0 */
                    if((tar_SYCC & 0x03 == 0x01) /* DIV = 0x01(/4), PLL = 0x60(*4), no need clock up */
                        && (tar_PLLC & PLL_MUL_4 == PLL_MUL_4)) 
                        break;
                    tar_SYCC = tar_SYCC & 0xFCU;       /* set DIV=00 */
                    up_flag = TRUE;
                }
                break;
            default:
                return NORMAL;
        }
    }
   
    if (up_flag == TRUE){   /* clock needs change */
       ClockSetState = clock_setting(cmd,WRITE); 
       tar_SYCC = temp_SYCC;
       tar_SYCC2 = temp_SYCC2;
       if((version_num == VER_1_18)||(version_num == VER_35)) tar_PLLC = temp_PLLC;
       if (ClockSetState != NORMAL)  return cmd->RC;/* recover clock setting to uers mode */
    }
    return NORMAL;
}

/**********************************************************************/
/* Function Name: get_baud_rate                                       */
/* Description: get baud rate of target MCU                           */
/* Parameters: cmd -- address of the command                          */
/* Return: communication status                                       */
/**********************************************************************/
uint8_t get_baud_rate(UART_COMMAND* cmd)
{
   cmd->FC = BGMA_PST;
   SET_PUARTCMD_ADDR(cmd,BRSR);
   if (uart_communication(cmd) != NORMAL) return cmd->RC;
   cmd->FC = BGMA_DRD;
   if (uart_communication(cmd) != NORMAL) return cmd->RC;
    return NORMAL;
}

/**********************************************************************/
/* Function Name: get_baud_rate                                       */
/* Description: modify baud rate of target MCU                        */
/* Parameters: cmd -- address of the command                          */
/*             up-flag -- indicate baud rate up/down                  */
/* Return: communication status                                       */
/**********************************************************************/
uint8_t modify_baud_rate(UART_COMMAND* cmd, uint8_t up_flag)
{
    /* Write BRSR Register */
    cmd->FC = BGMA_PST;
    SET_PUARTCMD_ADDR(cmd,BRSR);
    if (uart_communication(cmd) != NORMAL) return cmd->RC;
    cmd->FC = BGMA_DWR;
    cmd->AddrH = 0;
    cmd->AddrL = tar_baud_rate;
    cmd->FC&=0x7F;
    /*sum=cmd->FC+cmd->AddrH+cmd->AddrL;*/
    if(uart_put((uint8_t*)cmd, delay_time, 4)) return cmd->RC;

    if(version_num == VER_35){
        if(up_flag == UART_BRT_UP) UART_DBG_CH->BGR = UART_BAUDRATE(125000); /* 62500<->125000 */
        else UART_DBG_CH->BGR = UART_BAUDRATE(62500); 
    } else if((version_num == VER_1_18 )||(BRFlag1M == 1)){
        if(up_flag == UART_BRT_UP) UART_DBG_CH->BGR = UART_BAUDRATE(500000); /* 62500<->500k */
        else UART_DBG_CH->BGR = UART_BAUDRATE(62500);
    } else if((VER_2_18(version_num))&&(BRFlag1M == 0)){
        if(up_flag == UART_BRT_UP){ 
            UART_DBG_CH->BGR = UART_BAUDRATE(1000000); /* 62500<->1M */
            //UART1_UART1_SCR1_UPCL = 1; /*restart the UART*/
        } else UART_DBG_CH->BGR = UART_BAUDRATE(62500);
    }

    if(uart_get((uint8_t*)cmd, 0, 1)) return cmd->RC;
    Secu16BytesRec = 0;/*use for 16bytes security error*/
    return NORMAL;
}

/* Write PSSR register */
uint8_t write_FUAM(UART_COMMAND* cmd)
{
    cmd->FC = BGMA_PST;
    SET_PUARTCMD_ADDR(cmd,PSSR);
    if (uart_communication(cmd) != NORMAL) return cmd->RC;
    cmd->FC = BGMA_DWR;
    cmd->AddrH = 0;
    cmd->AddrL = 0x0c;
    if (uart_communication(cmd) != NORMAL) return cmd->RC;
    return NORMAL;
}

/**********************************************************************/
/* Function Name: uart_baudrate_up                                    */
/* Description: implement baud rate modificaction                     */
/* Parameters: cmd -- address of the command                          */
/*             up-flag -- indicate baud rate up/down                  */
/* Return: communication status                                       */
/**********************************************************************/
uint8_t uart_baudrate_up(UART_COMMAND* cmd, uint8_t up_flag)
{
    uint8_t tempbaudrate;

    if(up_flag == UART_BRT_UP){
        if(get_baud_rate(cmd)) return cmd->RC;
        tar_baud_rate = cmd->AddrL;
        tempbaudrate = tar_baud_rate;
        if(version_num == VER_35) {
            if(tar_baud_rate == 0x02) return NORMAL; /* already set to 12500, return */
            tar_baud_rate = tar_baud_rate >> 1; /* set target MCU to 125000 */
        }
        else if((version_num == VER_1_18 )||(BRFlag1M == 1)) {
            if(tar_baud_rate == 0x02) return NORMAL; /* already set to 500k, return */
            else if(tar_baud_rate == 0x01)tar_baud_rate = tar_baud_rate << 1; 
            else tar_baud_rate = tar_baud_rate >> 3; /* set target MCU to 500k */
        }
        else if((VER_2_18(version_num))&&(BRFlag1M == 0)) {
            if(tar_baud_rate == 0x01) return NORMAL; /* already set to 1m, return */
            else if(tar_baud_rate == 0x02) tar_baud_rate = tar_baud_rate >> 1;
            else tar_baud_rate = tar_baud_rate >> 4; /* set target MCU to 1m */
            write_FUAM(cmd);
        }
   
        if(modify_baud_rate(cmd, up_flag)) return cmd->RC;

        if(get_baud_rate(cmd)) return cmd->RC;
        tar_baud_rate = cmd->AddrL;
        if(version_num == VER_35)   tar_baud_rate = tar_baud_rate << 1; /* recover to 62500 */
        else if((version_num == VER_1_18)||(BRFlag1M == 1)){ 
            if(tempbaudrate == 0x01)tar_baud_rate = tar_baud_rate >> 1;
            else tar_baud_rate = tar_baud_rate << 3;}
        else if((VER_2_18(version_num))&&(BRFlag1M == 0)){
            if(tempbaudrate == 0x02)tar_baud_rate = tar_baud_rate << 1;
            else tar_baud_rate = tar_baud_rate << 4;}

        if(tar_baud_rate == tempbaudrate){
            return NORMAL;
        }
            
        cmd->RC = TARERR;
        return ERROR; 
    }else{
        if(get_baud_rate(cmd)) return cmd->RC;
        tar_baud_rate = cmd->AddrL;
        tempbaudrate = tar_baud_rate;
        if(version_num == VER_35) {
            if(tar_baud_rate == 0x04) return NORMAL; /* already recover to 62500 */
            tar_baud_rate = tar_baud_rate << 1; /* set target MCU to 62500 */
        }
        else if((version_num == VER_1_18)||(BRFlag1M == 1)) {
            if(tar_baud_rate == 0x10) return NORMAL;  /* already recover to 62500 */
            tar_baud_rate = tar_baud_rate << 3; /* set target MCU to 62500 */
        }
        else if((VER_2_18(version_num))&&(BRFlag1M == 0)) {
            if(tar_baud_rate == 0x10) return NORMAL;  /* already recover to 62500 */
            tar_baud_rate = tar_baud_rate << 4; /* set target MCU to 62500 */
        }
        if(modify_baud_rate(cmd, up_flag)) return cmd->RC;

        if(get_baud_rate(cmd)) return cmd->RC;
        tar_baud_rate = cmd->AddrL;
        if(version_num == VER_35) tar_baud_rate = tar_baud_rate >> 1; /* set target MCU to 62500 */
        else if((version_num == VER_1_18)||(BRFlag1M == 1)) tar_baud_rate = tar_baud_rate >> 3; /* set target MCU to 62500 */
        else if((VER_2_18(version_num))&&(BRFlag1M == 0)) tar_baud_rate = tar_baud_rate >> 4; /* set target MCU to 62500 */

        if(tar_baud_rate == tempbaudrate)
            return NORMAL;

        cmd->RC = TARERR;
        return ERROR;
    }
}


/**********************************************************************/
/* Function Name:   trim_cr                                           */
/* Description: send trim command one time                            */
/* Parameters: *cmd---address of the command                          */
/* Return: trim result                                                */
/**********************************************************************/
uint8_t trim_cr(UART_COMMAND* cmd)
{           /* not confirmed, just for monitor testing */
    cmd->RC = NORMAL;
    cr_put(cmd,WAITMS_2636US);
            /* system clock is 32.768KHz/2, baud rate 62500kbps */
            /* delay time need 2790us, so 2790us-160us = 2636us */
    if(cr_get(&(cmd->RC))) return ERROR;
    else {
        switch (cmd->RC){
            case CR_OK_ACK:
            CR_state = CR_OK;
            break;
            
            case TRIM_OK_ACK:
            CR_state = TRIM_OK;
            break;
            
            default:
            CR_state = TRIM_FAIL;
            break;
        }
        return NORMAL;
    }
}

/**********************************************************************/
/* Function Name:   check_break_stat                                  */
/* Description: check if break happens                                */
/* Parameters: *cmd---address of the command                          */
/* Return: NONE                                                       */
/**********************************************************************/
void check_break_stat(UART_COMMAND* cmd)
{
    uint8_t uartdata;
    if (uart_error){            /* received error RC2 */
        uart_error = 0;
        waitus(WAITMS_50MS);
        monitor_state &= ~MCU_RUN;         /* clear MCU_RUN flag set to MCU_BREAK */
        monitor_state |= RC2_ERROR;        /* set RC2_ERROR flag */
        if ((monitor_state & CLKUP_ON) == CLKUP_ON) {/* clock up enable */
            clock_up(cmd);
            delay_time = 0x0000U;          /* recover delay time */
        }
        
    }
    else if (p_rd_buf != p_wr_buf){       /* SSD:RDRF=1,RC2 received */
        uartdata = *p_rd_buf;
        p_rd_buf++;
        waitus(WAITMS_50MS);
        if (uartdata == 0x01U) {       /* RC2 is OK */
            monitor_state &= ~MCU_RUN;     /* clear MCU_RUN flag set to MCU_BREAK */
        }
        else if (uartdata == 0x00){    /* received error RC2 */
            monitor_state &= ~MCU_RUN;     /* clear MCU_RUN flag */
            if (RegBuff_Init(cmd) != NORMAL)
                monitor_state |= RC2_ERROR;
        } else {
            monitor_state &= ~MCU_RUN;     /* clear MCU_RUN flag set to MCU_BREAK */
            monitor_state |= RC2_ERROR;    /* set RC2_ERROR flag */
            sendbrk(UART_BREAK_TIMER);
        }
        if ((monitor_state & CLKUP_ON) == CLKUP_ON) {/* clock up enable */
            if (clock_up(cmd)) monitor_state |= RC2_ERROR;
            delay_time = 0x0000U;          /* recover delay time */
			MianCLKPLLFlaf = 0;				//clear flag
        }
    }
    return;
}

/**********************************************************************/
/* Function Name: rlt1_enable                                          */
/* Description: enable reload timer counter                           */
/* Parameters: one_shot -- select one shot or reload                  */
/*             timer    -- delay time count                           */
/* Return: none                                                       */
/**********************************************************************/
void rlt1_enable(uint8_t one_shot, uint32_t timer)
{
    FM_BT2->TMCR_f.FMD = 0;                      /* Reset Base Timer mode */
    FM_BT2->TMCR_f.FMD = 0x03;                  /* set base timer mode to reload timer function*/ 
    FM_BT2->TMCR_f.CKS = 0x02;                  /* Set PCLK/16 as base timer clcok */
    FM_BT2->TMCR_f.T32 = 1;                     /* set 32 bit counter mode */  
    FM_BT2->TMCR_f.EGS = 0;                     /* disable input trigger */
    FM_BT2->TMCR_f.OSEL = 0;                    /* Output polarity setting Rt Polarity Low*/
    FM_BT2->STC_f.TGIE = 0u;                     /* disable input trigger interrupt */
    FM_BT2->STC_f.UDIE = 0u;                     /* disable underflow interrupt */
    if(one_shot)
    {
        FM_BT2->TMCR_f.MDSE = 1;
    }
    else
    {
        FM_BT2->TMCR_f.MDSE = 0;
    }
    FM_BT2->STC_f.TGIR = 0u;                     /* clear trigger flag */
    FM_BT2->STC_f.UDIR = 0u;                     /* clear underflow flag */
    FM_BT3->PCSR = ((timer*2u) >> 16) & 0xffff;
    FM_BT2->PCSR = ((timer*2u)) & 0xffff;
    FM_BT2->TMCR_f.CTEN = 1u;                    /* Enable bt timer */ 
    FM_BT2->TMCR_f.STRG = 1u;                    /* Start Reload timer by software */
}

/**********************************************************************/
/* Function Name: rlt1_disable                                         */
/* Description: disable reload timer counter                          */
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
void rlt1_disable(void)
{
    FM_BT2->STC_f.UDIR = 0u;                     /* clear underflow flag */
    FM_BT2->TMCR_f.CTEN = 0u;                    /* disable bt timer */
}

/**********************************************************************/
/* Function Name: check_rlt1_overflow                                  */
/* Description: check if reload timer overflow                        */
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
uint8_t check_rlt1_overflow(void)
{
    return FM_BT2->STC_f.UDIR;                  /* return overflow flag */
}

/**********************************************************************/
/* Function Name: clear_rtl1_flag                                      */
/* Description: clear reload timer overflow flag                      */
/* Parameters: none                                                   */
/* Return: none                                                       */
/**********************************************************************/
void clear_rtl1_flag(void)
{
    FM_BT2->STC_f.UDIR = 0u;                     /* clear underflow flag */
}  
