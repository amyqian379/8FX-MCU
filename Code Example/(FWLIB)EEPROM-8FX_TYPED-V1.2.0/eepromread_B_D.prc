cmd entry=SetupFlashUpload

set variable ReadPara = %P0
set variable ReadNum = %P1

printf "    \n"
printf "Now check E2PROM status....\n"
set variable BlockAddr = H'1000
set variable EpromSize = H'FFFF

while %EVAL(%BlockAddr) != H'2000
	if %EVAL(%B(%BlockAddr + H'170)) ==H'E0
		set variable BlockSize = %EVAL(%B(%BlockAddr + H'173))
		if %BlockSize == H'01          
			set variable EpromSize = H'10       
		elseif %BlockSize == H'02
			set variable EpromSize = H'20
		elseif %BlockSize == H'04
			set variable EpromSize = H'40
		elseif %BlockSize == H'08
			set variable EpromSize = H'80
		elseif %BlockSize == H'10
			set variable EpromSize = H'100
		elseif %BlockSize == H'20
			set variable EpromSize = H'200
		else 
			set variable EpromSize = H'FFFF
		endif
		cancel variable BlockSize	
		break
	else
		set variable BlockAddr = %EVAL(%BlockAddr + H'200)
	endif
endw

if %EVAL(%BlockAddr) == H'2000 || %EVAL(%EpromSize) == H'FFFF
	printf "E2PROM is unavailable or not initialized.\n"
	cancel variable/all
	quit
endif

printf " E2PROM is OK, E2PROM size : %dB.\n", %EVAL(%EpromSize)

if %NP == 2
	if %EVAL(%ReadPara + %ReadNum) > %EVAL(%EpromSize)
		printf "***Error***  Read parameter overflow.\n"
		cancel variable/all
		quit
	endif
	printf " now reading, please wait....\n"
elseif %NP == 0
	set variable ReadPara = H'0000
	set variable ReadNum = %EVAL(%EpromSize)
	printf " Read the whole E2PROM may takes long time, please wait a moment....\n"
else
	printf "***Error*** Invalid input command.\n"
	cancel variable/all
	quit
endif

if %EVAL(%EpromSize) == H'200
	if %EVAL(%ReadPara) < H'180
		set variable BlockAddr = %EVAL(%BlockAddr - H'200)
	endif
	if %EVAL(%ReadPara) < H'100
		set variable BlockAddr = %EVAL(%BlockAddr - H'200)
	endif
	if %EVAL(%ReadPara) < H'80
		set variable BlockAddr = %EVAL(%BlockAddr - H'200)
	endif
endif

if %EVAL(%EpromSize) == H'100
	if %EVAL(%ReadPara) < H'80
		set variable BlockAddr = %EVAL(%BlockAddr - H'200)
	endif
endif

cancel variable EpromSize

set variable ReadStartAddr = %EVAL(%BlockAddr + (%ReadPara & H'007F))
set variable ReadOffset = %EVAL(%ReadPara)
set variable Read_Status = H'00

if %EVAL(%ReadNum) == 0
	if %Read_Status == H'00
		printf "    \n"
		printf "    Read complete."
	endif
	cancel variable/all
	quit
endif

printf "    \n"
print "Address +0 ----------------------------------------------------------------------- +F\n"
if %EVAL(%ReadPara) <H'10
	printf "0"
endif
if %EVAL(%ReadPara) <H'100
	printf "0"
endif
printf "0%x ",%ReadPara

batch read_B_D.prc, %EVAL(%BlockAddr), %EVAL(%ReadStartAddr), %EVAL(%ReadOffset), %EVAL(%ReadNum)
set variable BlockAddr = %EVAL(%BlockAddr + H'200)
set variable ReadStartAddr = %EVAL(%BlockAddr)
set variable ReadOffset = %EVAL(%ReadPara)

if %EVAL(%ReadNum) == 0
	if %Read_Status == H'00
		printf "    \n"
		printf "    Read complete."
	endif
	cancel variable/all
	quit
endif

batch read_B_D.prc, %EVAL(%BlockAddr), %EVAL(%ReadStartAddr), %EVAL(%ReadOffset), %EVAL(%ReadNum)
set variable BlockAddr = %EVAL(%BlockAddr + H'200)
set variable ReadStartAddr = %EVAL(%BlockAddr)
set variable ReadOffset = %EVAL(%ReadPara)

if %EVAL(%ReadNum) == 0
	if %Read_Status == H'00
		printf "    \n"
		printf "    Read complete."
	endif
	cancel variable/all
	quit
endif

batch read_B_D.prc, %EVAL(%BlockAddr), %EVAL(%ReadStartAddr), %EVAL(%ReadOffset), %EVAL(%ReadNum)
set variable BlockAddr = %EVAL(%BlockAddr + H'200)
set variable ReadStartAddr = %EVAL(%BlockAddr)
set variable ReadOffset = %EVAL(%ReadPara)

if %EVAL(%ReadNum) == 0
	if %Read_Status == H'00
		printf "    \n"
		printf "    Read complete."
	endif
	cancel variable/all
	quit
endif

batch read_B_D.prc, %EVAL(%BlockAddr), %EVAL(%ReadStartAddr), %EVAL(%ReadOffset), %EVAL(%ReadNum)

if %EVAL(%ReadNum) == 0
	if %Read_Status == H'00
		printf "    \n"
		printf "    Read complete."
	endif
	cancel variable/all
	quit
endif


cancel variable/all












