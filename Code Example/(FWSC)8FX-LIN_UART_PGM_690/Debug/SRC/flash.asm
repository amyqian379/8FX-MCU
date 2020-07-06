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
 	
 	.SECTION ERASECODE, CODE
 	.EXPORT _EraseStart
;+++++++++++++++++++++++++++++++++++++++
; Command_Process
;  Flash Erase
;	IN	:	EP : Erase Address
;	OUT	:	A  : Return Flag
;				0 : Successed
;				1 : Fail			
;+++++++++++++++++++++++++++++++++++++++
_EraseStart:
	MOVW	A,EP
	PUSHW	A					; Save write address

	SETB 72H:1	//FSR:WRE
	MOVW	A,#0xF000
	ANDW	A
	MOVW	A,#0x0AA8
	ORW		A
	MOVW	EP,A				; 0x0AAA | (address & 0xf000)
	XCHW	A,T
	MOVW	A,#0x0554
	ORW		A
	MOVW	IX,A				; 0x0554 | (address & 0xf000)
	
	MOV		A,#0xAA				; 0x*AAAH <= 0xAA
	MOV		@EP,A

	MOV		A,#0x55				; 0x*554 <= 0x55
	MOV		@IX,A

	MOV		A,#0x80				; 0x*AAAH <= 0x80
	MOV		@EP,A

	MOV		A,#0xAA				; 0x*AAAH <= 0xAA
	MOV		@EP,A

	MOV		A,#0x55				; 0x*554 <= 0x55
	MOV		@IX,A

	POPW	A					; Restore Erase address	
	MOVW 	EP,A
	MOV		A,#30H				; The last data.  	
	mov		@EP,A				; Start Erase
	
	NOP
	NOP
	// clear watchdog
	MOV 0CH, #0x35

EraseDQ3:
	MOV		A,@EP
	AND		A,#0x08				; Check DQ3 ?
	BZ		EraseDQ3	
	
EraseLoop:	

	BBS 72H:4,EraseEnd	//FSR:RDY	
	
	// clear watchdog
	MOV 0CH, #0x35
	
	MOV		A,@EP
	AND		A,#0x20				; Check DQ5?
	BZ		EraseLoop	
	

	BBS 72H:4, EraseEnd	//FSR:RDY
	NOP	
	BBS 72H:4, EraseEnd	//FSR:RDY
	
EraseError:
	MOV		A,#0xF0	
	MOV		0xFF00,A			; Reset Flash	
	MOV		A,#01H				; Set error Flag
	CLRB 72H:2
	RET
	
EraseEnd:
	CLRB 72H:2
	MOV A, #0X00
	RET
	
/************************************************************************/
	.SECTION WRITECODE, CODE
 	.EXPORT _WriteStart	
;==========================================================================
;+++++++++++++++++++++++++++++++++++++++
; Command_Process
;  Flash Write
;	IN	:	EP : Write Address
;			IX : Write Data
;	OUT	:	A  : Return Flag
;				0 : Successed
;				1 : Fail
;+++++++++++++++++++++++++++++++++++++++
_WriteStart:	
	PUSHW	IX					; Save write data
	MOVW	A,EP
	PUSHW	A					; Save write address
		
	SETB 72H:1					; Write Enable
	
	MOVW	A,#0xF000
	ANDW	A
	MOVW	A,#0x0AA8
	ORW		A
	MOVW	EP,A				; 0x0AAA | (address & 0xf000)
	XCHW	A,T
	MOVW	A,#0x0554
	ORW		A
	MOVW	IX,A				; 0x0554 | (address & 0xf000)
	
	MOV		A,#0xAA				; 0xUAAAH <= 0xAA
	MOV		@EP,A
			
	MOV		A,#0x55				; 0xU554 <= 0x55
	MOV		@IX,A
	
	MOV		A,#0xA0				; 0xUAAAH <= 0xA0
	MOV		@EP,A	

	POPW	A			
	MOVW	EP,A				; write address
	POPW	IX
	MOVW	A,IX				; write data
	MOV		@EP,A				; to write flash

	NOP
	NOP
	
WriteLoop:
	BBS 72H:4,WriteEnd
	
	MOV		A,@EP
	AND		A,#0x20				; to check time out?Check DQ5?
	BZ		WriteLoop	
	
	// clear watchdog
	MOV 0CH, #0x35
	
	BBS 72H:4,WriteEnd
	NOP	
	BBS 72H:4,WriteEnd
		
WriteError:
	MOV		A,#0xF0		
	MOV		0xFF00,A			; Reset Flash	
	CLRB 72H:2					; write disable
	MOV		A,#01H				; Set error Flag
	RET
	
WriteEnd:	
	CLRB 72H:2 
	MOV A, #0X00
	RET
;========================================================================== 	
 	
 	
 