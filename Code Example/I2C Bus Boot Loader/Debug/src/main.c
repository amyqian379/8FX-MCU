/*********************************************************************************************/
/*               (C) Fujitsu Semiconductor Design(ChengDu) (FSDC)                            */
/*                                                                                           */
/* The following software deliverable is intended for and must only be                       */
/* used for reference and in an evaluation laboratory environment.                           */
/* It is provided on an as-is basis without charge and is subject to                         */
/* alterations.                                                                              */
/* It is the user's obligation to fully test the software in its                             */
/* environment and to ensure proper functionality, qualification and                         */
/* compliance with component specifications.                                                 */
/*                                                                                           */
/* In the event the software deliverable includes the use of open                            */
/* source components, the provisions of the governing open source                            */
/* license agreement shall apply with respect to such software                               */
/* deliverable.                                                                              */
/* FSDC does not warrant that the deliverables do not infringe any                           */
/* third party intellectual property right (IPR). In the event that                          */
/* the deliverables infringe a third party IPR it is the sole                                */
/* responsibility of the customer to obtain necessary licenses to                            */
/* continue the usage of the deliverable.                                                    */
/*                                                                                           */
/* To the maximum extent permitted by applicable law FSDC disclaims all                      */
/* warranties, whether express or implied, in particular, but not                            */
/* limited to, warranties of merchantability and fitness for a                               */
/* particular purpose for which the deliverable is not designated.                           */
/*                                                                                           */
/* To the maximum extent permitted by applicable law, FSDC's liability                       */
/* is restricted to intentional misconduct and gross negligence.                             */
/* FSDC is not liable for consequential damages.                                             */
/*********************************************************************************************/
/** \file main.c
 **
 ** main file
 **
 ** History:
 **   - 2011-10-12  V0.1.0  First Version
 *********************************************************************************************/
#include"mb95630.h"
#include"API.h"

// define variable
REC_DATA ReciveData;
NVR_RESET Specialarea;

unsigned char step;  // used for switch the process during receiving command, handling data,returing data
unsigned char counter; // used for calculating command
unsigned int  datacnt; // used for calculating the number of writing data
unsigned int readdatacnt;//used for calculating the number of reading data
unsigned int address; // used for save the address of flash operation
unsigned char data;// used for save the data of flash writing operation
unsigned char result;// used for save the result of flash operation
unsigned char Flag_Timeout; // flag for time-out when flash writing or flash Reading
unsigned char t1,t2,t3,t4; // used for time-out of receiving command
unsigned char Read_Flag;
// test
unsigned char data_store[3], m;
unsigned long Tout;

// declaration
#pragma segment CODE=program, attr=CODE, locate=0x1000	

void Boot_main(void)
{	
	Clear_Para();			// clear global variable
	Clock_Init();			// system clock setting 
	I2C_Init();
	
	AIDRL = 0xFF; 			// Port input enabled
	WDTC = 0x35;		 	// clear watchdog
	
	DDR0_P00 = 0;
/*********************************************************************************************/	
	if(MODE_PIN)			// enter PGM mode
	{
		step = 1;			// command receive status					
	}
	else					// enter user normal mode
	{
		User_Mode();
	}
	while(1)
	{
	    WDTC = 0x35;// clear watchdog
		switch(step)
		{
			case 1 : Communication();
					 break;
			case 2 : Data_Process();
					 break;			
		}
	}
}

void Clear_Para(void)
{
	ReciveData.command = 0x00;
	ReciveData.address = 0x00;
	ReciveData.datalen = 0x00;
	ReciveData.writedata = 0x00;
	ReciveData.Ack.result = 0x00;

	step = 0;
	counter = 0;
	datacnt = 0;
	readdatacnt = 0;
	address = 0;
	data = 0;
	result = 0;
	Flag_Timeout = 0;
	t1 = 0;
	t2 = 0;
	t3 = 0;
	t4 = 0;
	Read_Flag = 0;
	m=0;
	Tout = 0;
}
/*********************************************************************************************/
/*Module name:   Clock_Init                                                                  */
/*Function description: initialize clock                                                     */
/*********************************************************************************************/
void Clock_Init(void)
{
	SYCC = 0xFC;		// source clock, no divide, main CR PLL clock mode
	PLLC = 0x20;		// Main CR clock *2.5 = 4MHZ*2.5=10MHZ
	PLLC_MPEN = 1;		// Enables the main CR PLL clock
	while(!PLLC_MPRDY);
}

/*********************************************************************************************/
/*Module name:   I2C_Init                                                                    */
/*Function Name: I2C initialization                                                          */
/*Parameter:     None                                                                        */
/*return:        None                                                                        */
/*Function description: initialize I2C function in order to communication with FTDI chip,    */
/*                      receive the data from PC side when erase or program,                 */
/*                      read back flash data to transmit to PC side when read.               */
/*********************************************************************************************/
void I2C_Init(void)
{
    DDR6_P60 = 0;       // P60-->SDA ,input in slave mode
    DDR6_P61 = 0;       // P61-->SCL ,input in slave mode
    
    ICCR0_EN  = 0; 		// clear I2C interface
    ICCR0_CS4 = 0;		// set clock divider 'm' => 5
    ICCR0_CS3 = 0;
    ICCR0_CS2 = 0;		// set clock divider 'n' => 4
    ICCR0_CS1 = 0;
    ICCR0_CS0 = 0;		// Fsck = MCLK / (m * n +2) => 10MHz/(5*4 +2) = 10MHz/22 = 455kHz
     
    ICCR0_EN  = 1;		// enable I2C interface
     
    IBCR00    = 0x00;	// disable address acknowledge bit, 
    					// transfer completion interrupt after nine cycles,
    					// disable the mcu standby-mode wakeup function(WUE)
    					// disable stop detection interrupt
        
    IBCR10    = 0x08;	// disable bus error interrupt requests
    					// disable data ACK(DACKE)
    					// disable general call address ACK
    					// disable data transfer completion interrupt requests
    					
    IAAR0 	  = 0x18;	// set slave address 

}
/*********************************************************************************************/
/*Module name:   Communication                                                               */
/*Function description: master communicate with slave for receiving command and transmit ACK */
/*                      or data.                                                             */
/*********************************************************************************************/
void Communication(void)
{
	if(IBCR00_SPF == 1) /* stop condition detected ? */
	{
		IBCR00_SPF = 0; /* stop condition detection flag clear */
	}

	if(IBCR10_INT == 1)
	{
		WDTC = 0x35;// clear watchdog
		if(IBSR0_TRX)
		{
			ACK_To_PC();	// transmit data or ACK to master side
		}
		else
		{
			Command_Receive();	// receive the command from master side
			IBCR10_INT = 0;
		}
		
	}	

	if(IBCR10_BER != 0)
	{
			IBCR10_BER = 0;
	}
}
/*********************************************************************************************/
/*Module name:   User_Mode                                                                   */
/*Function description: enter user normal mode                                               */
/*********************************************************************************************/
void User_Mode(void)
{
	unsigned char read_buffer1,read_buffer2;
	unsigned int startaddress;
	
	read_buffer1 = Flash_Read(0xFFB8,1);
	read_buffer2 = Flash_Read(0xFFB9,1);
	startaddress = read_buffer1 << 8;
	startaddress |= read_buffer2;
	
	if(startaddress != 0)
	{
		#pragma asm
				JMP @A
		#pragma endasm
	}
	else
	{
		while(1);
	}
}

/*********************************************************************************************/
/*Module name:   Command_Receive                                                             */
/*Function description: MCU will wait until finish to receive 5bytes command                 */
/*********************************************************************************************/
void Command_Receive(void)
{
	slave_receive();
	
	if(counter == 5)
	{
		step = 2;
 		counter = 0;
	}
		
}

/*********************************************************************************************/
/*Module name:   slave_receive                                                               */
/*Function description: Receive 5bytes data including command,High address, Low address,     */
/*                      2bytes data length from PC side.                                     */
/*********************************************************************************************/
void slave_receive(void)
{	
	switch(Flag_Timeout)
	{
		case 1 : t1 ++;
				 if(t1 > 8)
				 {
				 	t1 = 0;
				 	return;
				 }
				 break;
		case 2 : t2 ++;
				 if(t2 > 8)
				 {
				 	t2 = 0;
				 	return;
				 }
				 break;
		case 3 : t3 ++;
				 if(t3 > 8)
				 {
				 	t3 = 0;
				 	return;
				 }
				 break;
		case 4 : t4 ++;
				 if(t4 > 8)
				 {
				 	t4 = 0;
				 	return;
				 }
				 break;
	   default : break;			
	}
	
	if(IBCR10_INT != 0)/* data receive completed ? */
	{
	    if (IBSR0_FBT)
	    {

	   		 __wait_nop();
	   		 counter = 0;
	    }
	    else
	    {
			counter ++;
		}
		switch(counter)
		{
			case 1 : ReciveData.command = IDDR0;
					 Flag_Timeout = 1;		
					 break;
			case 2 : ReciveData.address = IDDR0;	
					 Flag_Timeout = 2;		 
					 break;
			case 3 : ReciveData.address <<= 8;
					 ReciveData.address |= IDDR0;
					 Flag_Timeout = 3;	
					 break;
			case 4 : ReciveData.datalen = IDDR0;
					 Flag_Timeout = 4;	
					 break;
			case 5 : ReciveData.datalen <<= 8;
					 ReciveData.datalen |= IDDR0;    	
					 t1 = 0;
    				 t2 = 0;
    				 t3 = 0;
    				 t4 = 0;
    				 Flag_Timeout = 0;
					 break;
		}

	}
	WDTC = 0x35;// clear watchdog
	
}
/*********************************************************************************************/
/*Module name:   Data_Process                                                                */
/*Function description: according to the received command, execute flash erasing operation¡¢ */
/*                      flash writing operation¡¢flash reading operation                     */
/*                      status = 0(OK), status = 1(NG)                                       */
/*********************************************************************************************/
void Data_Process(void)
{
	unsigned int buffer = 0;
	unsigned char i;
	unsigned int temp;
	unsigned char buffer1,buffer2;
	unsigned char delay;
	unsigned int F_Timeout = 0;
	unsigned char flag = 0;
	unsigned char R_flag = 0;
	unsigned char writeerror = 0;
	unsigned char cnt128 = 0;
	
	WDTC = 0x35;// clear watchdog
	switch(ReciveData.command)
	{
		case 0x01 : // erasing operation
					if(ReciveData.address >= 0x8000)
					{
						// save NVR value and reset vector value
						Specialarea.reset_H = Flash_Read(0xFFFE,1);
						Specialarea.reset_L = Flash_Read(0xFFFF,1);
						Specialarea.NVR_CRTDA = Flash_Read(0xFFBB,1);
						Specialarea.NVR_CRTH = Flash_Read(0xFFBC,1);
						Specialarea.NVR_CRTL = Flash_Read(0xFFBD,1);
						
						WDTC = 0x35;// clear watchdog

					}
					if(Flash_Erase(ReciveData.address,0x30))
					{
						// if erasing is failed,MCU will return NG signal to PC side.
						// erasing is NG
						ReciveData.Ack.result = 0x90;			// status: 1, type_error:001 	
					}
					else
					{
						// write back NVR value and reset vector value
						if(ReciveData.address >= 0x8000)
						{   
							Flash_Write(0xFFFE, &Specialarea.reset_H);
							Flash_Write(0xFFFF, &Specialarea.reset_L);
							Flash_Write(0xFFBB, &Specialarea.NVR_CRTDA);
							Flash_Write(0xFFBC, &Specialarea.NVR_CRTH);
							Flash_Write(0xFFBD, &Specialarea.NVR_CRTL);
							
							WDTC = 0x35;// clear watchdog
						}	
						ReciveData.Ack.result = 0x00;				// erasing is OK
																	// status: 0	
					}
					WDTC = 0x35;// clear watchdog
					step = 1;	
					break;
		case 0x02 : // writing operation	
					while(datacnt < ReciveData.datalen)
					{
						while(!IBCR10_INT)	// wait that1-byte data (including an acknowledge) transfer has been completed
						{
							F_Timeout++;
							if(F_Timeout > 30000) // set time out
							{
								F_Timeout = 0;
								ReciveData.Ack.result = 0xF0;		// status: 1(NG), type_error:111(time-out error)
								WDTC = 0x35;// clear watchdog
								flag = 1;
								break;
							}
						}
						if(flag)
						{
							flag = 0;
							break;
						}
						WDTC = 0x35;// clear watchdog
						F_Timeout = 0;
						
						if (IBSR0_FBT)
	    				{
	   		 				IBCR10_INT = 0;	// Clears transfer completion interrupt request flag bit
	   		 				continue;
	    				}
	    				// receive data
						ReciveData.writedata = IDDR0;
						temp = ReciveData.address+datacnt;
						
						if((temp >= 0xFFB8) && (temp <= 0xFFBD))
						{
							datacnt++;
							IBCR10_INT = 0;// Clears transfer completion interrupt request flag bit
							continue;
						}
						else if(temp >= 0xFFFE)
						{
							if(temp == 0xFFFE)
							{
								Flash_Write(0xFFB8,&ReciveData.writedata);
							}
							else if(temp == 0xFFFF)
							{
								Flash_Write(0xFFB9,&ReciveData.writedata);
							}
							datacnt++;
							IBCR10_INT = 0;// Clears transfer completion interrupt request flag bit
							continue;
						}
						else
						{
							WDTC = 0x35;// clear watchdog
							
							buffer += Flash_Write(ReciveData.address+datacnt, &ReciveData.writedata);	// 0 : OK, 1:failed
							if(buffer != 0)
							{
								writeerror = 1;
								break;
							}
							datacnt++;
						}
						WDTC = 0x35;// clear watchdog	
						IBCR10_INT = 0;	// Clears transfer completion interrupt request flag bit
					}
					
					if(writeerror)
					{
						writeerror = 0;
						datacnt = 0;
						// return NG signal to PC side
						ReciveData.Ack.result = 0xB0;		// status: 1, type_error:010
						step = 1;
						break;
					}
					if(buffer == 0)
					{
						// return OK signal to PC side
						ReciveData.Ack.result = 0x00;		// writing is ok
															// status: 0
					}
					else
					{
						// return NG signal to PC side
						ReciveData.Ack.result = 0xB0;		// status: 1, type_error:010
					}
					datacnt = 0;
					WDTC = 0x35;// clear watchdog
					//IBCR10_INT = 0;	// Clears transfer completion interrupt request flag bit
					step = 1;
					break;
		case 0x04 : // reading operation
					if((IBCR00_SPF == 1)&&(Read_Flag == 1)) /* stop condition detected ? */
					{
						IBCR00_SPF = 0; /* stop condition detection flag clear */
						Read_Flag = 0;
						step = 1;
					}
//					if(IBCR10_INT == 1)
					while(!IBCR10_INT)
					{
						Tout++;
						if(Tout > 3000000) // set time out
						{
							Tout = 0;
							ReciveData.Ack.result = 0xF0;		// status: 1(NG), type_error:111(time-out error)
							WDTC = 0x35;// clear watchdog
							R_flag = 1;
							break;
						}

					}
					if(R_flag)
					{
						R_flag =0;
						step = 1;
						break;
						
					}
					if(IBSR0_TRX)
					{
						IDDR0 = Flash_Read(ReciveData.address++,1);
	
 						while (IBCR10_INT == 0);         // look if transfer is in process
 						//IBCR10_INT = 0;
 						while(IBSR0_LRB == 1); 	// wait until Acknowledgment detected 
 							
 						Read_Flag = 1; 
 						IBCR00_SPF = 0; 
					}
					else
					{
						if(IBCR10_INT != 0)/* data receive completed ? */
						{
							data_store[m++] = IDDR0;/* data read */
						}
					}
					if(m == 3)
        			{
        				ReciveData.address = data_store[1];
        				ReciveData.address <<= 8;
        				ReciveData.address |= data_store[2];

        				m=0;
        			}
					IBCR10_INT = 0;						
					break;
		  default :	//ReciveData.Ack.result = 0x8F;		// command error, status: 1(NG), type_error:1***1111
		  			step = 1; // re-receive the right command	
		  			break;			
	}
}

/*********************************************************************************************/
/*Module name:   ACK_To_PC                                                                   */
/*Function description: return ACK signal of flash erasing operation¡¢flash writing operation*/
/*                      flash reading operation to PC side                                   */
/*********************************************************************************************/
void ACK_To_PC(void)
{
	slave_transmit();
	step = 1;
}

/*********************************************************************************************/
/*Module name:   slave_transmit                                                              */
/*Function Name: slave_transmit                                                              */
/*Parameter:     None                                                                        */
/*return:        None                                                                        */
/*Function description: slave transmit mode slave receive mode                               */
/*********************************************************************************************/
void slave_transmit(void)
{		
	IDDR0 = ReciveData.Ack.result;
 	while (IBCR10_INT == 0);         // look if transfer is in process
 	IBCR10_INT = 0;					// Clears transfer completion interrupt request flag bit
 	while(IBSR0_LRB == 1); 	// wait until Acknowledgment detected  
 	IBCR10_INT = 0;	
 	
	ReciveData.command = 0x00;
	ReciveData.address = 0x00;
	ReciveData.datalen = 0x00;
	ReciveData.writedata = 0x00;
	ReciveData.Ack.result = 0x00;
}

/*********************************************************************************************/
/*Module name:   Flash_Erase                                                                 */
/*Function description: flash erasing operation                                              */
/*Return: 1--OK                                                                              */
/*        0--NG                                                                              */
/*********************************************************************************************/
unsigned char Flash_Erase(unsigned int Address, unsigned char Sector_Chip)
{
	unsigned char temp;	
	address = Address;
	SWRE0 = 0x07;
	WDTC = 0x35;// clear watchdog	
#pragma asm
	MOVW A, _address		// set erase address
	MOVW EP,A
	CALL _EraseStart		// Start erase subroutine
	MOV	 _result,A			// Reture the result for flash erase
	POPW IX
#pragma endasm 	
	
	return result; 
}
/*********************************************************************************************/
/*Module name:   Flash_Write                                                                 */
/*Function description: flash writing operation, just write 1byte data each time             */
/*Return: 1--OK                                                                              */
/*        0--NG                                                                              */
/*********************************************************************************************/
unsigned char Flash_Write(unsigned int Address,unsigned char *Write_Data)
{			
	address = Address;
	data = *Write_Data;
	SWRE0 = 0x07;
#pragma asm
;	MOVW A, SP
;	MOVW IX, A
	PUSHW IX
	MOV  A,_data			// set write data 
	MOVW IX,A
	MOVW A, _address		// set write address 
	MOVW EP,A
	CALL _WriteStart		// Start Flash write subroutine
	MOV	 _result,A			// Reture the result for flash write
	POPW IX
#pragma endasm
	return result;

}
/*********************************************************************************************/
/*Module name:   Flash_Read                                                                  */
/*Function description: flash reading operation                                              */
/*Return: 1--OK                                                                              */
/*        0--NG                                                                              */
/*********************************************************************************************/
unsigned char Flash_Read(unsigned int Address, unsigned int Read_Count)
{		
	unsigned char u;
    u = *(unsigned char *)Address;
    return u;
}
