
/*
*********************************************************************************************************
*                                           INCLUDE FILES
*********************************************************************************************************
*/
#ifndef _FUNCAPI_H_
#define	_FUNCAPI_H_
#include "sys.h"
#include "usart.h"	 

#define	TotalCh		4
#define	MaxCh			3
#define	MaxVol		100

#define	ChON			1
#define	ChOFF			0

extern u8 Volume[];
extern u8 ChSta[];

u8 SetChVol(u8 channel, u8 Vol);
u8 AddStepChVol(u8 channel);		//Ôö¼Ó
u8 SubStepChVol(u8 channel);
u8 SetTotalVol(u8 Vol);
u8 SetChOnOff(u8 Channel, u8 Sta);

#endif

