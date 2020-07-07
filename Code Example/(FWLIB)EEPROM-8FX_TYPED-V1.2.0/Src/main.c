#include "mb95630.h"
#include "F2MC_8FX_EEPROM.h"

/*----------------------------- SUB ROUTINES --------------------------------*/
void MCU_initialization()
{
	__DI();

	/*system clock*/
	SYCC=0xD8;		//MCLK = source clock = 8Mhz (Main CR)

	InitIrqLevels();	// initialise Interrupt level register and IRQ vector table
	__EI();
}

void vDelay (unsigned int ii)
{
	while(ii--) {
		__wait_nop();
		__wait_nop();
		__wait_nop();
	}
}

/*----------------------------- MAIN ROUTINE --------------------------------*/
unsigned int add=0;
void main()
{
	unsigned int ucRet;
	unsigned char cData=0, wData=0,rData=0,OverflowF=0;
	unsigned int i=0;
//	unsigned int add=0;
	MCU_initialization();
	DDR6_P64 = 1;
	DDR0_P05 = 1;
	ucRet = EEPROM_Check(E2P_64B, &cData);
	
	if (ucRet==OK) {
		if (cData ==DEFINE || cData ==REDEFINE) {
			ucRet = EEPROM_Define(E2P_64B);
		} else if (cData ==RESTORE) {
			ucRet = EEPROM_Restore();
		}
		if (ucRet==NG) {
			while (1) {
				__wait_nop();
			}
		} else if (ucRet==BUSY) {
			__wait_nop();
		}
	} else if (ucRet ==NG) {
		while (1) {
			__wait_nop();
		}
	}
	while (1) {
		
		ucRet = EEPROM_B_Write(add,wData,&OverflowF);
		if (ucRet == OK) {
			ucRet = EEPROM_B_Read(i,&rData);
			if (ucRet == NG) {
				while (1) {
					__wait_nop();
				}
			} else if (ucRet == 4) {	//parameter error
				while (1) {
					__wait_nop();
				}
			}
			DDR0_P05 = ~DDR0_P05;
			i++;
			add++;
			wData++;
		} else if (ucRet==2 && OverflowF==6) {	// overflow
			vDelay(1000);
		} else if (ucRet == 3) {	// LPM
			while (1) {
				__wait_nop();
			}
		} else if (ucRet == 1) {	// NG
			while (1) {
				__wait_nop();
			}
		}
		else {
			__wait_nop();
		}
		if (i == 127)
		{
		__wait_nop();
		PDR6_P64 =~PDR6_P64;
		}
		
		if (add == 64) {
			i = 0;
			add=0;
			wData=0;
			
		}
	}
}
