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
 ** API file
 **
 ** History:
 **   - 2011-10-12  V0.1.0  First Version
 *********************************************************************************************/
 
 

#define MODE_PIN PDR0_P00

typedef union
{
	unsigned char result;
	
	struct
	{
		unsigned char status:1;
		unsigned char type_error:3;
		unsigned char 		:5;
	}bit;
}ACK_ST;

typedef struct
{
	unsigned char command;
	unsigned int address;
	unsigned int datalen;
	unsigned char writedata;
	ACK_ST	Ack;
}REC_DATA;

extern REC_DATA ReciveData;

typedef struct
{
	unsigned char USER_NVR;
	unsigned char access;
	unsigned char reset_H;
	unsigned char reset_L;
	unsigned char NVR_CRTH;
	unsigned char NVR_CRTL;
	unsigned char NVR_CRTDA;
}NVR_RESET;

extern NVR_RESET Specialarea;

extern unsigned char step;
extern unsigned char flag;
extern unsigned char security_result;
extern unsigned char counter;
extern unsigned int datacnt;
extern unsigned int readdatacnt;
extern unsigned int address;
extern unsigned char data;
extern unsigned char result;

void Clear_Para(void);

void LIN_UART_Init(void);
void LIN_Transmit (void);
void LIN_Receive (void);

void Flash_Security(void);
void User_Mode(void);
void Clock_Init(void);

void Command_Receive(void);
void Data_Process(void);
void ACK_To_PC(void);
unsigned char Flash_Erase(unsigned int Address, unsigned char Sector_Chip);
unsigned char Flash_Write(unsigned int Address,unsigned char *Write_Number);
unsigned char Flash_Read(unsigned int Address, unsigned int Read_Count);


extern	EraseStart;
extern	WriteStart;
extern	ReadStart;
 