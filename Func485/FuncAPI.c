#include "FuncAPI.h"
#include "ET2259.h"
#include "DataSave.h"

#define		InitVol	 (MaxVol/2)

#define		HardMaxVol	87

u8 ChSta[TotalCh]  = {ChON, ChON, ChON, ChON};
u8 Volume[TotalCh] = {InitVol, InitVol, InitVol, InitVol};

u8 SetChVol(u8 channel, u8 Vol)
{
	u8 tempvol;
	if((channel > MaxCh)||(Vol > MaxVol))
	{
		return 1;
	}
	
	if(Volume[channel] != Vol)
	{
		Volume[channel] = Vol;
		S400DataSave();
	}
	
	tempvol = (u8)((1.0 - (float)Vol/100.0)*(float)HardMaxVol);
//	tempvol = 79-tempvol;
	
	if(tempvol > HardMaxVol)
		tempvol = HardMaxVol;
	
	printf("ch: %d, Vol: %d:%d\r\n", channel, Vol, tempvol);
	
	if(channel == 0)
	{
		Volume1_Write(tempvol);
		Volume1_Write(tempvol);
	}
	else if(channel == 1)
	{
		Volume2_Write(tempvol);
		Volume2_Write(tempvol);
	}
	else if(channel == 2)
	{
		Volume3_Write(tempvol);
		Volume3_Write(tempvol);
	}
	else if(channel == 3)
	{
		Volume4_Write(tempvol);
		Volume4_Write(tempvol);
	}

	return 0;
}

#define 	STEP		6

u8 SubStepChVol(u8 channel)		//增加
{
	u8 vol;
	if(channel > MaxCh)
	{
		return 1;
	}
	if(Volume[channel] > STEP)
		vol = Volume[channel] - STEP;
	else
		vol = 0;
	
	SetChVol(channel, vol);
	
	return 0;
}

//声音最大值为72， 0时实际声音最大，72时没有声音
u8 AddStepChVol(u8 channel)
{
	u8 vol;
	if(channel > MaxCh)
	{
		return 1;
	}
	if(Volume[channel] < (MaxVol - STEP))
		vol = Volume[channel] + STEP;
	else
		vol = MaxVol;
	SetChVol(channel, vol);
	
	return 0;
}

u8 SetTotalVol(u8 Vol)
{
	u8 i;
	if(Vol > MaxVol)
		return 1;
	
	for(i = 0; i<4; i++)
		SetChVol(i, Vol);
	
	return 0;
}

u8 SetChOnOff(u8 Channel, u8 Sta)
{
	if((Channel > MaxCh)||(Sta > 1))
	{
		return 1;
	}
	
	printf("ch: %d, Sta: %d\r\n", Channel, Sta);

	if(ChSta[Channel] != Sta)
	{
		ChSta[Channel] = Sta;
		S400DataSave();
	}
	
	ChanSwitch(Channel, Sta);
	
	return 0;
}





