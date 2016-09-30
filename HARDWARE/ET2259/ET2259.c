#include "ET2259.h"
#include "myiic.h"
#include "FuncAPI.h"
#include "delay.h"
#include "ET62429.h"

void ChanSwitch(u8 ch, u8 sta)
{
	if(ch == 0)
	{
		(sta == ChON)?GPIO_SetBits(GPIOA,CH0PIN):GPIO_ResetBits(GPIOA,CH0PIN);
	}
	else if(ch ==1)
	{
		(sta == ChON)?GPIO_SetBits(GPIOA,CH1PIN):GPIO_ResetBits(GPIOA,CH1PIN);
	}
	else if(ch ==2)
	{
		(sta == ChON)?GPIO_SetBits(GPIOA,CH2PIN):GPIO_ResetBits(GPIOA,CH2PIN);
	}
	else if(ch ==3)
	{
		(sta == ChON)?GPIO_SetBits(GPIOA,CH3PIN):GPIO_ResetBits(GPIOA,CH3PIN);
	}
}

void	PE_PA_Init(void)
{
	GPIO_InitPara  GPIO_InitStructure;
		
	RCC_AHBPeriphClock_Enable(RCC_AHBPERIPH_GPIOA, ENABLE);	 //使能PA端口时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUT; 		 //推挽输出
	GPIO_InitStructure.GPIO_OType = GPIO_OTYPE_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PUPD_PULLUP;
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOA
	
	GPIO_SetBits(GPIOA, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7);
}


//写入一个字节到ET2259_1中
void Write2259_1(u8 address,u8 ch,u8 ch1,u8 ch2)
{
	
	IIC_Start_1();
	IIC_Send_Byte_1(address);
	IIC_Ack_1();
	IIC_Send_Byte_1(ch);
  IIC_Ack_1();
	IIC_Send_Byte_1(ch1);
  IIC_Ack_1();
	IIC_Send_Byte_1(ch2);
  IIC_Ack_1();
	IIC_Stop_1();
	delay_ms(5);
}

void Write_code2259_1(u8 ch,u8 address) 
{
	
	IIC_Start_1();
	IIC_Send_Byte_1(address);
	IIC_Ack_1();
  IIC_Send_Byte_1(ch);
  IIC_Ack_1();
	IIC_Stop_1();
	delay_ms(5);
}


//写入一个字节到ET2259_2中
void Write2259_2(u8 address,u8 ch,u8 ch1,u8 ch2)
{
	
	IIC_Start_2();
	IIC_Send_Byte_2(address);
	IIC_Ack_2();
	IIC_Send_Byte_2(ch);
  IIC_Ack_2();
	IIC_Send_Byte_2(ch1);
  IIC_Ack_2();
	IIC_Send_Byte_2(ch2);
  IIC_Ack_2();
	IIC_Stop_2();
	delay_ms(5);
}

void Write_code2259_2(u8 ch,u8 address) 
{
	IIC_Start_2();
	IIC_Send_Byte_2(address);
	IIC_Ack_2();
  IIC_Send_Byte_2(ch);
  IIC_Ack_2();
	IIC_Stop_2();
	delay_ms(5);
}



//写入一个字节到ET2259_3中
void Write2259_3(u8 address,u8 ch,u8 ch1,u8 ch2)
{
	
	IIC_Start_3();
	IIC_Send_Byte_3(address);
	IIC_Ack_3();
	IIC_Send_Byte_3(ch);
  IIC_Ack_3();
	IIC_Send_Byte_3(ch1);
  IIC_Ack_3();
	IIC_Send_Byte_3(ch2);
  IIC_Ack_3();
	IIC_Stop_3();
	delay_ms(5);
}

void Write_code2259_3(u8 ch,u8 address) 
{
	IIC_Start_3();
	IIC_Send_Byte_3(address);
	IIC_Ack_3();
  IIC_Send_Byte_3(ch);
  IIC_Ack_3();
	IIC_Stop_3();
	delay_ms(5);
}



//写入一个字节到ET2259_4中
void Write2259_4(u8 address,u8 ch,u8 ch1,u8 ch2)
{
	
	IIC_Start_4();
	IIC_Send_Byte_4(address);
	IIC_Ack_4();
	IIC_Send_Byte_4(ch);
  IIC_Ack_4();
	IIC_Send_Byte_4(ch1);
  IIC_Ack_4();
	IIC_Send_Byte_4(ch2);
  IIC_Ack_4();
	IIC_Stop_4();
	delay_ms(5);
}

void Write_code2259_4(u8 address,u8 ch) 
{
	IIC_Start_4();
	IIC_Send_Byte_4(address);
	IIC_Ack_4();
  IIC_Send_Byte_4(ch);
  IIC_Ack_4();
	IIC_Stop_4();
	delay_ms(5);
}



void	All_InitSet(u8 add,u8 ch,u8 ch1)
{
	Write_code2259_1(add,ch);
	Write_code2259_1(add,ch1);
	
	Write_code2259_2(add,ch);
	Write_code2259_2(add,ch1);
	
	Write_code2259_3(add,ch);
	Write_code2259_3(add,ch1);
	
	Write_code2259_4(add,ch);
	Write_code2259_4(add,ch1);

}

void Volume1_Write(u8 Vol)
{
		u8  Temp_H,Temp_L;
	
#ifndef ET2259	
	Temp_H=(Vol/10)|0xe0;
	Temp_L=(Vol%10)|0xd0;
	Write2259_1(0x88,0x74,Temp_L,Temp_H);
#else
	ET1_Col(0x00,Vol);
#endif	
}

void Volume2_Write(u8 Vol)
{
	u8  Temp_H,Temp_L;

#ifndef ET2259		
	Temp_H=(Vol/10)|0xe0;
	Temp_L=(Vol%10)|0xd0;
	Write2259_2(0x88,0x74,Temp_L,Temp_H);
#else 
		ET2_Col(0x00,Vol);
#endif
}

void Volume3_Write(u8 Vol)
{
	u8  Temp_H,Temp_L;
	
#ifndef ET2259	
	Temp_H=(Vol/10)|0xe0;
	Temp_L=(Vol%10)|0xd0;
	Write2259_3(0x88,0x74,Temp_L,Temp_H);
#else
	ET3_Col(0x00,Vol);
#endif
}

void Volume4_Write(u8 Vol)
{
	u8  Temp_H,Temp_L;
	
#ifndef ET2259	
	Temp_H=(Vol/10)|0xe0;
	Temp_L=(Vol%10)|0xd0;
	Write2259_4(0x88,0x74,Temp_L,Temp_H);
#else 
	ET4_Col(0x00,Vol);
#endif
}

////模块1
//void Volume1_Write(u8 Vol)
//{
//	u8  Temp_H,Temp_L;
//	
//	Temp_H=(Vol/10)|0xe0;
//	Temp_L=(Vol%10)|0xd0;
//	
//	IIC_Start_1();
//	IIC_Send_Byte_1(0x88);
//	if(IIC_Wait_Ack_1()==0)
//	{
//		IIC_Send_Byte_1(Temp_H);
//		IIC_Ack_1();
//		IIC_Send_Byte_1(Temp_L);
//		IIC_Ack_1();		
//	}
//	IIC_Stop_1();
//}

////模块2 
//void Volume2_Write(u8 Vol)
//{
//	u8  Temp_H,Temp_L;
//	
//	Temp_H=(Vol/10)|0xe0;
//	Temp_L=(Vol%10)|0xd0;
//	
//	IIC_Start_2();
//	IIC_Send_Byte_2(0x88);
//	if(IIC_Wait_Ack_2()==0)
//	{
//		IIC_Send_Byte_2(Temp_H);
//		IIC_Ack_2();
//		IIC_Send_Byte_2(Temp_L);
//		IIC_Ack_2();		
//	}
//	IIC_Stop_2();
//}

////模块3 
//void Volume3_Write(u8 Vol)
//{
//	u8  Temp_H,Temp_L;
//	
//	Temp_H=(Vol/10)|0xe0;
//	Temp_L=(Vol%10)|0xd0;
//	
//	IIC_Start_3();
//	IIC_Send_Byte_3(0x88);
//	if(IIC_Wait_Ack_3()==0)
//	{
//		IIC_Send_Byte_3(Temp_H);
//		IIC_Ack_3();
//		IIC_Send_Byte_3(Temp_L);
//		IIC_Ack_3();		
//	}
//	IIC_Stop_3();
//}


////模块4
//void Volume4_Write(u8 Vol)
//{
//	u8  Temp_H,Temp_L;
//	
//	Temp_H=(Vol/10)|0xe0;
//	Temp_L=(Vol%10)|0xd0;
//	
//	IIC_Start_4();
//	IIC_Send_Byte_4(0x88);
//	if(IIC_Wait_Ack_4()==0)
//	{
//		IIC_Send_Byte_4(Temp_H);
//		IIC_Ack_4();
//		IIC_Send_Byte_4(Temp_L);
//		IIC_Ack_4();		
//	}
//	IIC_Stop_4();
//}
