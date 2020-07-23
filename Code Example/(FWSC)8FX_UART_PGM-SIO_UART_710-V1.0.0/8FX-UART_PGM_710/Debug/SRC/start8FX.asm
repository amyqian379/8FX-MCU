;==========================================================================
; F2MC-8FX Family SOFTUNE C Compiler sample startup routine,
; ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU LIMITED 2008
; LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU LIMITED
;==========================================================================
;  Sample program for initialization
;--------------------------------------------------------------------------
		.PROGRAM	start
		.TITLE		start
;--------------------------------------------------------------------------
; variable define declaration
;--------------------------------------------------------------------------		
;#define HWD_DISABLE			; if define this, Hard Watchdog will disable.

;--------------------------------------------------------------------------
; external declaration of symbols
;--------------------------------------------------------------------------
		.EXPORT		__start
		.IMPORT		_Boot_main
		.IMPORT		LMEMTOMEM
		.IMPORT		LMEMCLEAR
		.IMPORT		_RAM_INIT
		.IMPORT		_ROM_INIT
		.IMPORT		_RAM_DIRINIT
		.IMPORT		_ROM_DIRINIT
		
		.IMPORT		_EraseStart
		.IMPORT		_WriteStart
		.IMPORT		_RAM_ERASECODE
		.IMPORT		_ROM_ERASECODE
		.IMPORT		_RAM_WRITECODE
		.IMPORT		_ROM_WRITECODE  

		
;--------------------------------------------------------------------------
; definition to stack area
;--------------------------------------------------------------------------
		.SECTION	STACK,    STACK,    ALIGN=1
		.RES.B		32-2
STACK_TOP:
		.RES.B		2
		
;--------------------------------------------------------------------------
; definition to start address of data, const and code section
;--------------------------------------------------------------------------
		.SECTION	DIRDATA,  DIR,      ALIGN=1
		.SECTION	DIRINIT,  DIR,      ALIGN=1
		.SECTION	DATA,     DATA,     ALIGN=1
		.SECTION	INIT,     DATA,     ALIGN=1
		.SECTION	ERASECODE,  CODE,   ALIGN=1
		.SECTION	WRITECODE,  CODE,   ALIGN=1
		
		.SECTION	DATA,     DATA,     ALIGN=1
Erase_size:
	.RES.B	2
		.SECTION	DATA,     DATA,     ALIGN=1
Write_size:
	.RES.B	2
	
;--------------------------------------------------------------------------
; code area
;--------------------------------------------------------------------------
		.SECTION	CODE,     CODE,     ALIGN=1

__start:
;--------------------------------------------------------------------------
; set stack pointer
;--------------------------------------------------------------------------		
		MOVW	A, #290H
		MOVW	SP, A
		
		MOV 0CH, #0x35
;--------------------------------------------------------------------------
; set register bank is 0
;--------------------------------------------------------------------------
		MOVW	A, PS
		MOVW	A, #0x07FF
		ANDW	A
		MOVW	PS, A

;--------------------------------------------------------------------------
; set ILM to the lowest level(3)
;--------------------------------------------------------------------------
		MOVW	A, PS
		MOVW	A, #0x0030
		ORW	A
		MOVW	PS, A

;--------------------------------------------------------------------------
; copy initial value *CONST(ROM) section to *INIT(RAM) section
;--------------------------------------------------------------------------
#macro		ICOPY	src_addr, dest_addr, src_section
		MOVW	EP, #\src_addr
		MOVW	A,  #\dest_addr
		MOVW	A,  #SIZEOF (\src_section)
		CALL	LMEMTOMEM
#endm

;		ICOPY	_ROM_INIT,	_RAM_INIT,	INIT
;		ICOPY	_ROM_DIRINIT,	_RAM_DIRINIT,	DIRINIT
//		ICOPY	_ROM_RAMCODE,	_RAM_RAMCODE,	RAMCODE

;--------------------------------------------------------------------------
; zero clear of *VAR section
;--------------------------------------------------------------------------
#macro		FILL0	src_section
		MOVW	A, #\src_section
		MOVW	A, #SIZEOF (\src_section)
		CALL	LMEMCLEAR
#endm

;		FILL0	DIRDATA
;		FILL0	DATA
		
/*move erase code */		
		PUSHW	IX
		MOVW	EP,	#_ROM_ERASECODE
		MOVW	IX,	#_RAM_ERASECODE
		MOVW	A,	#sizeof (ERASECODE)


		MOVW	Erase_size,	A
LOOP:
;	PUSHW	A
	MOV	A,	@EP
	MOV	@IX,	A
	INCW	EP
	INCW	IX
	MOVW	A,	Erase_size
	DECW	A
	MOVW	Erase_size,	A
	MOVW	A,	#0
	CMPW	A
	BZ	LOOP_OVER
	// clear watchdog
	MOV 0CH, #0x35
	JMP	LOOP		
LOOP_OVER:
	POPW	IX

/*move write code */		
		PUSHW	IX
		MOVW	EP,	#_ROM_WRITECODE
		MOVW	IX,	#_RAM_WRITECODE
		MOVW	A,	#sizeof (WRITECODE)


		MOVW	Write_size,	A
LOOP1:
;	PUSHW	A
	MOV	A,	@EP
	MOV	@IX,	A
	INCW	EP
	INCW	IX
	MOVW	A,	Write_size
	DECW	A
	MOVW	Write_size,	A
	MOVW	A,	#0
	CMPW	A
	BZ	LOOP1_OVER
	// clear watchdog
	MOV 0CH, #0x35
	JMP	LOOP1		
LOOP1_OVER:
	POPW	IX
	
;--------------------------------------------------------------------------
; call main routine
;--------------------------------------------------------------------------
		
		CALL	_Boot_main
end:		JMP	end

;--------------------------------------------------------------------------
; Hard Watchdog
;--------------------------------------------------------------------------
#ifdef	HWD_DISABLE
		.SECTION  WDT, CONST, LOCATE=H'FFBE
      		.DATA.W   0xA596
#endif
;--------------------------------------------------------------------------
; reset vector
;--------------------------------------------------------------------------
		.SECTION	RESET,    CONST,    LOCATE=0xFFFC
		.DATA.B		0xFF
		.DATA.B		0
		.DATA.H		__start

		.END	__start
