history record:
ver01r02l02--changed mb95f636 2nd 0.18um mcu sycc, sycc2 and pll special deal parameter transfer              error. add a char parameter to replace int transfer parameter
ver01r02l03--add soft ware reset when PC detect noise or can not communication normally
ver01r02l04--add version number 4 for monitor code version 04
ver01r02l05--add reset target MCU before power supply to avoid supply power fail
ver01r02l06--change reset position for fix MB95564 cann't work condition
/****ver01r02l07*****************************************************/
20130117--1. pull P05 and P11 to low, when system interrupt detect UVCC is low 
		  2. before pull low, change two pin direction to output
		  3. resume pin direction to input when system detect UVCC is high/*, and set P11 to high*/
20130121--1. write pin =0 before set pin direction to output 
		  2. write IO_RSTX = 1; when detect UVCC is high to resume RSTIN status
	/*ver01r02l07-02*/
20130128--1. cancel P05 and P11 direction set at EPCS DATA part 
	/*ver01r02l07-03*/
20130131--1. cancel P11 bgma_io_initial() initial direction input set to avoid power on pull up pulse 
	  2. cancel all ealier RSTIN=0 operation, replace of P05 and P11 pull low to leak UVCC power
	  3. add P05 and P11 pull low at proc_exit_mon() to avoid BGMA power supply leak voltage
	  4.resume P05 and P11 direction at proc_start_mon()
/********************************************************/