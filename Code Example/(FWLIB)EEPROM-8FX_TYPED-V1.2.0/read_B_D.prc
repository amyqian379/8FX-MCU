set variable Block_Addr = %P0
set variable Read_Orignal_Addr = %P1
set variable Read_Offset = %P2
set variable Read_Number = %P3
set variable Update_Flag_Addr = %EVAL(%Read_Orignal_Addr + H'180)
set variable Update_Flag = H'00
set variable Read_Counter = H'00

set variable Read_Data  = H'00
set variable Cell_Addr  = %EVAL(%Block_Addr + H'80)

while 1
     
     set variable Update_Flag = %EVAL(%B(%Update_Flag_Addr))
     if %Update_Flag == H'FF
	set variable Read_Status = H'00
     elseif %Update_Flag == H'FE
	set variable Cell_Addr  = %EVAL(%Block_Addr + H'9B)
	set variable Read_Status = H'01
     elseif %Update_Flag == H'FC
	set variable Cell_Addr  = %EVAL(%Block_Addr + H'B9)
	set variable Read_Status = H'01
     elseif %Update_Flag == H'F8
	set variable Cell_Addr  = %EVAL(%Block_Addr + H'D7)
	set variable Read_Status = H'01
     elseif %Update_Flag == H'F0
	set variable Cell_Addr  = %EVAL(%Block_Addr + H'F5)
	set variable Read_Status = H'01
     elseif %Update_Flag == H'E0
	set variable Cell_Addr  = %EVAL(%Block_Addr + H'113)
	set variable Read_Status = H'01
     elseif %Update_Flag == H'C0
	set variable Cell_Addr  = %EVAL(%Block_Addr + H'131)
	set variable Read_Status = H'01
     elseif %Update_Flag == H'80
	set variable Cell_Addr  = %EVAL(%Block_Addr + H'14F)
	set variable Read_Status = H'01
     elseif %Update_Flag == H'00
	set variable Cell_Addr  = %EVAL(%Block_Addr + H'16D)
	set variable Read_Status = H'01
     else
	set variable Read_Status = H'FF
	printf "    \n"
	printf "***Error*** Read process encountered an error. Invalid updateflag format.\n"
	set variable ReadNum = 0
	break
     endif

     if %EVAL(%Read_Status) == H'00
	set variable Read_Data = %EVAL(%B(%Read_Orignal_Addr))
     elseif %EVAL(%Read_Status) == H'01
	set variable Loop_Counter = H'0A
	while %Loop_Counter != 0
		if %EVAL(%B((%Cell_Addr )+1)) == %EVAL(%Read_Offset & H'007F) && %EVAL(%B(%Cell_Addr )) == H'FC
			set variable Read_Data = %EVAL(%B((%Cell_Addr )+2))
			set variable Read_Status = H'00
			break
		else
			set variable Cell_Addr  = %EVAL(%Cell_Addr  - 3)
			set variable Loop_Counter = %EVAL(%Loop_Counter - 1)
			set variable Read_Status = H'FF
		endif
	endw
	cancel variable Loop_Counter 
	if %EVAL(%Read_Status) == H'FF
		printf "***Error*** Read process encountered an error. Data not found in cell.\n"
		set variable ReadNum = 0
		break
	endif 
     else
	set variable Read_Status = H'FF
	printf "\n Read status error.\n"
	set variable ReadNum = 0
	break
     endif

     if %EVAL(%Read_Data) <H'10
	printf "   0%x", %EVAL(%Read_Data)
     else 
	printf "   %x", %EVAL(%Read_Data)
     endif

     set variable Update_Flag_Addr = %EVAL(%Update_Flag_Addr + 1)
     set variable Read_Orignal_Addr = %EVAL(%Read_Orignal_Addr + 1)
     set variable Read_Offset = %EVAL(%Read_Offset + 1)
     set variable Read_Number = %EVAL(%Read_Number - 1)

     if %EVAL(%Read_Offset & H'000F) == 0 && %EVAL(%Read_Number) != 0
	printf "    \n"
	if %EVAL(%Read_Offset) < H'10
		printf "0"
	endif
	if %EVAL(%Read_Offset) < H'100
		printf "0"
	endif
	printf "0%x ", %EVAL(%Read_Offset)
     endif

     if %EVAL(%Read_Number) == 0
	set variable ReadNum = 0
	break
     endif

     if %EVAL(%Read_Offset & H'007F) == 0
	set variable ReadNum = %EVAL(%Read_Number)
	set variable ReadPara = %EVAL(%Read_Offset)
	break
     endif

endw
     
cancel variable Block_Addr
cancel variable Read_Orignal_Addr
cancel variable Read_Offset
cancel variable Read_Number
cancel variable Update_Flag_Addr
cancel variable Update_Flag
cancel variable Read_Counter

cancel variable Read_Data
cancel variable Cell_Addr

