
#include "DataSave.h"
#include "FuncAPI.h"
#include "Func485.h"

#define	DataSaveFlag			0xABCDEF01
#define	DataSaveFlagAddr	0x8007BE0
#define	DataSaveBaseAddr	0x8007B00
#define	SaveDataNum				8
#define MaxFlashAddr			0x8008000


extern Sys_Para systemset;

void S400DataSave(void)
{
	u8  i;
	u32 addr;
	FMC_Unlock();						//½âËø
	
	FMC_ErasePage(DataSaveBaseAddr);
	
	addr = DataSaveBaseAddr;
	//485ADDR
	FMC_ProgramWord(addr, (u32)systemset.softaddr);
	addr += 4;		//WORD
	//channel on/off
	for(i = 0; i<TotalCh; i++)
	{
		FMC_ProgramWord(addr, (u32)ChSta[i]);
		addr += 4;		//WORD
	}
	//volume
	for(i = 0; i<TotalCh; i++)
	{
		FMC_ProgramWord(addr, (u32)Volume[i]);
		addr += 4;		//WORD
	}
	if(*(u32*)DataSaveFlagAddr != DataSaveFlag)
	{
		FMC_ProgramWord(DataSaveFlagAddr, DataSaveFlag);
	}
	
	FMC_Lock();							//ÉÏËø
}

void S400ReadFromFlash(void)
{
	u8  i;
	u32 addr;
	if(*(u32*)DataSaveFlagAddr == DataSaveFlag)
	{
		addr = DataSaveBaseAddr;
		systemset.softaddr = (u8)(*(u32*)addr);
		addr += 4;
		//channel on/off
		for(i = 0; i<TotalCh; i++)
		{
			ChSta[i] = (u8)(*(u32*)addr);
			addr += 4;		//WORD
		}
		//volume
		for(i = 0; i<TotalCh; i++)
		{
			Volume[i] = (u8)(*(u32*)addr);
			if(Volume[i] > 100)
				Volume[i] = (MaxVol/2);
			addr += 4;		//WORD
		}
	}
}

