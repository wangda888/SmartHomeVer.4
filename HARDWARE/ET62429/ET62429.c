#include "ET62429.h"
#include "delay.h"
#include "myiic.h"
#include "usart.h"



void ET1_Col(u8 Channel,u8 Volume)
{
	u8 Dat=0;
	u8 i;
	ET1_DAT(0);
	ET1_CLK(0);
	//Volume(衰减)   
	Volume=87-Volume;
	Dat=(((Volume<<5)&0x60)|((Volume>>2)&0x1f))|0x80;//得到要控制的数值
	printf("Dat1= 0x%X  \r\n",Dat);
	for(i=0;i<2;i++)
	{	
		if(Channel&0x01)ET1_DAT(1);
	  else	ET1_DAT(0);//
		delay_us(2);
		ET1_CLK(1);
		delay_us(5);		
		ET1_DAT(0);delay_us(2);
		ET1_CLK(0);
		delay_us(5);	
		Channel=Channel>>1;		
	}
	
	for(i=0;i<8;i++)
	{		
		if(Dat&0x01)ET1_DAT(1);
	  else	ET1_DAT(0);//ET1_DAT(Dat&0x01)
		delay_us(2);
		ET1_CLK(1);
		delay_us(5);
		ET1_DAT(0);
		delay_us(2);
		ET1_CLK(0);delay_us(5);	
		Dat=Dat>>1;		
	}
	ET1_DAT(1);delay_us(2);
	ET1_CLK(1);
	delay_us(5);
	ET1_CLK(0);//delay_us(5);
	
	
	
}

//
void ET2_Col(u8 Channel,u8 Volume)
{
	u8 Dat=0;
	u8 i;
	ET2_DAT(0);
	ET2_CLK(0);
	//Volume(衰减)   0dB最大 87最小
	Volume=87-Volume;
	Dat=((Volume<<5)&0x60)|((Volume>>2)&0x1f)|0x80;//得到要控制的数值
	printf("Dat2= 0x%x  \r\n",Dat);
for(i=0;i<2;i++)
	{	
		if(Channel&0x01)ET2_DAT(1);
	  else	ET2_DAT(0);//
		delay_us(2);
		ET2_CLK(1);
		delay_us(5);		
		ET2_DAT(0);delay_us(2);
		ET2_CLK(0);
		delay_us(5);	
		Channel=Channel>>1;		
	}
	
	for(i=0;i<8;i++)
	{		
		if(Dat&0x01)ET2_DAT(1);
	  else	ET2_DAT(0);//ET1_DAT(Dat&0x01)
		delay_us(2);
		ET2_CLK(1);
		delay_us(5);
		ET2_DAT(0);
		delay_us(2);
		ET2_CLK(0);delay_us(5);	
		Dat=Dat>>1;		
	}
	ET2_DAT(1);delay_us(2);
	ET2_CLK(1);
	delay_us(5);
	ET2_CLK(0);//delay_us(5);
	
}


//
void ET3_Col(u8 Channel,u8 Volume)
{
	u8 Dat=0;
	u8 i;
	ET3_DAT(0);
	ET3_CLK(0);
	//Volume(衰减)   0dB最大 87最小
	Volume=87-Volume;
	Dat=((Volume<<5)&0x60)|((Volume>>2)&0x1f)|0x80;//得到要控制的数值
	printf("Dat3= 0x%x  \r\n",Dat);
	for(i=0;i<2;i++)
	{	
		if(Channel&0x01)ET3_DAT(1);
	  else	ET3_DAT(0);//
		delay_us(2);
		ET3_CLK(1);
		delay_us(5);		
		ET3_DAT(0);delay_us(2);
		ET3_CLK(0);
		delay_us(5);	
		Channel=Channel>>1;		
	}
	
	for(i=0;i<8;i++)
	{		
		if(Dat&0x01)ET3_DAT(1);
	  else	ET3_DAT(0);//ET1_DAT(Dat&0x01)
		delay_us(2);
		ET3_CLK(1);
		delay_us(5);
		ET3_DAT(0);
		delay_us(2);
		ET3_CLK(0);delay_us(5);	
		Dat=Dat>>1;		
	}
	ET3_DAT(1);delay_us(2);
	ET3_CLK(1);
	delay_us(5);
	ET3_CLK(0);//delay_us(5);	
	
}


//
void ET4_Col(u8 Channel,u8 Volume)
{
	u8 Dat=0;
	u8 i;
	ET4_DAT(0);
	ET4_CLK(0);
	//Volume(衰减)   0dB最大 87最小
	Volume=87-Volume;
	Dat=((Volume<<5)&0x60)|((Volume>>2)&0x1f)|0x80;//得到要控制的数值
	printf("Dat4= 0x%x  \r\n",Dat);
	for(i=0;i<2;i++)
	{	
		if(Channel&0x01)ET4_DAT(1);
	  else	ET4_DAT(0);//
		delay_us(2);
		ET4_CLK(1);
		delay_us(5);		
		ET4_DAT(0);delay_us(2);
		ET4_CLK(0);
		delay_us(5);	
		Channel=Channel>>1;		
	}
	
	for(i=0;i<8;i++)
	{		
		if(Dat&0x01)ET4_DAT(1);
	  else	ET4_DAT(0);//ET1_DAT(Dat&0x01)
		delay_us(2);
		ET4_CLK(1);
		delay_us(5);
		ET4_DAT(0);
		delay_us(2);
		ET4_CLK(0);delay_us(5);	
		Dat=Dat>>1;		
	}
	ET4_DAT(1);delay_us(2);
	ET4_CLK(1);
	delay_us(5);
	ET4_CLK(0);//delay_us(5);
	
}