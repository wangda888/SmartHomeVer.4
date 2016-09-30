/* Includes ------------------------------------------------------------------*/
#include "sys.h"
#include "delay.h"
#include "LED.h"
#include "EC11.h"
#include "usart.h"
#include "myiic.h"
#include "ET2259.h"
#include "func485.h"
#include "uart3.h"
#include "FuncAPI.h"
#include "ET62429.h"

extern u8 Sound_Status;

//#define TEST

void	RCC_Init(void){}

u8 test[8]={0xaa,0xff,0x01,0x01,0x12,0x11,0xaa,0xff};
int main(void)
{
	u8 i;
	
	delay_init(72);	//延时函数初始化
	EC11_Init();		//EC11初始化
	NVIC_PRIGroup_Enable(NVIC_PRIGROUP_3);
	uart_init(115200);	//串口初始化
	Uart485_Init(9600);//485 Init
	LoadStart();
	AUX_Init();
	LED_Init();		//LED初始化
	IIC_Init_1();			//IIC初始化
	IIC_Init_2();
	IIC_Init_3();
	IIC_Init_4();	
	PE_PA_Init();			//功放IO口初始化
	delay_ms(500);
//	while(1)
//	{
//		LED_ONOFF(0,1);
//		delay_ms(1000);
//		LED_ONOFF(0,0);
//		delay_ms(1000);
//	}
//		Volume1_Write(30);
//		Volume2_Write(30);
//		Volume3_Write(30);
//		Volume4_Write(30);
//while(1);
#ifndef ET2259
	All_InitSet(0x88,0xf0,0x74);
#endif
	for(i = 0; i<TotalCh; i++)
	{
		SetChOnOff(i, ChSta[i]);
		SetChVol(i, Volume[i]);
	}	 
	while(1)
	{	 

#ifdef TEST 
		EC11KEY_Scan();
		EC11_KEYC();
#endif
		process485();
	}
}



/******************* (C) COPYRIGHT 2015 GigaDevice *****END OF FILE****/
