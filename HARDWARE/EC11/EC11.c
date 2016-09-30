#include "EC11.h"
#include "LED.h"
#include "ET2259.h"
#include "delay.h"
#include "usart.h"
#include "FuncAPI.h"
#include "EC11.h"

volatile extern u8 EC11_Num1,EC11_Num2,EC11_Num3,EC11_Num4;
u8 Sound_Status=0;

void EC11_Init(void)
{
	GPIO_InitPara  GPIO_InitStructure;
	
	RCC_AHBPeriphClock_Enable(RCC_AHBPERIPH_GPIOA | RCC_AHBPERIPH_GPIOB, ENABLE);	 //ʹ��PB�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_3| GPIO_PIN_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_IN; 		 //��������
  GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;		 //IO���ٶ�Ϊ50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OTYPE_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PUPD_PULLUP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //ʹ��PB�˿�ʱ��	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_IN; 		 //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;		 //IO���ٶ�Ϊ50MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PUPD_PULLUP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //ʹ��PB�˿�ʱ��	
}


void EC11KEY_Scan(void)
{
	
	
	if(EC11_KEY==0)
	{
		while(EC11_KEY==0);
		Sound_Status++;
		if(Sound_Status==5)Sound_Status=0;
		LED_ONOFF(Sound_Status,1);			
	}
}


u16 EC11_Cor(void)
{
	static u8 EC_A,EC_B;//�������������洢��һ�ε���ʱ���������������ŵĵ�ƽ
	static u8 ST=0;			//�����洢��ǰ�Ƿ�����������Ŷ�Ϊ�ߵ�ƽ״̬
	u8 res=0;
	
	if(EC11_A&&EC11_B)ST=1;	//�ж��������Ƿ��Ǹߵ�ƽ
	
	if(ST==1)								//���Ǹߵ�ƽ
	{
		if(EC11_A==0&&EC11_B==0)//�ж����������Ƿ��ǵ͵�ƽ
		{
			if(EC_B)
			{
				ST=0;
				res=EC11_DOWN;
				printf("EC11_DOWN EC11_DOWN EC11_DOWN EC11_DOWN\r\n");
			}
			if(EC_A)
			{
				ST=0;
				res=EC11_UP;
				printf("EC11_UP EC11_UP EC11_UP EC11_UP EC11_UP\r\n");				
			}
		}
	}	
	EC_A=EC11_A;
	EC_B=EC11_B;
	
	return res;
}


void EC11_KEYC(void)
{
	u8 temp_rot,i;
	
	EC11KEY_Scan();
	switch(Sound_Status)
	{
	 case All:	////ģʽ1
		 temp_rot=EC11_Cor();
		 if(temp_rot==EC11_UP)
		 {
			 for(i = 0; i<4; i++)
			 {
				 Volume[i]=Volume[i]+5;
				 if(Volume[i]>MaxVol)
					 Volume[i]=MaxVol;
			 }
			 for(i = 0; i<4; i++)
			 SetChVol(i, Volume[i]);
		 }
		 else if(temp_rot==EC11_DOWN)
		 {
			 for(i = 0; i<4; i++)
			 {
				 if(Volume[i]!=0)
					 Volume[i]=Volume[i]-5;	
			 }
			 for(i = 0; i<4; i++)
			SetChVol(i, Volume[i]);
		 }
		 temp_rot=0;
		 break;
	 case ETVol1:	////ģʽ2
		 temp_rot=EC11_Cor(); 
		 if(temp_rot==EC11_UP)
		 {
			 Volume[0]=Volume[0]+5; if(Volume[0]>MaxVol) Volume[0]=MaxVol;
			 SetChVol(0, Volume[0]);
		 }
		 else if(temp_rot==EC11_DOWN)
		 {
			 if(Volume[0]!=0)Volume[0]=Volume[0]-5;
			 SetChVol(0, Volume[0]);
		 }
		 temp_rot=0;
		 break;
	 case ETVol2:	////ģʽ3
		 temp_rot=EC11_Cor(); 
		 if(temp_rot==EC11_UP)
		 {
			 Volume[1]=Volume[1]+5; if(Volume[1]>MaxVol) Volume[1]=MaxVol;
			 SetChVol(1, Volume[1]);
		 }
		 else if(temp_rot==EC11_DOWN)
		 {
			 if(Volume[1]!=0)Volume[1]=Volume[1]-5;
			 SetChVol(1, Volume[1]);
		 }
		 temp_rot=0;
		 break;
	 case ETVol3:	////ģʽ4
		 temp_rot=EC11_Cor(); 
		 if(temp_rot==EC11_UP)
		 {
			 Volume[2]=Volume[2]+5; if(Volume[2]>MaxVol) Volume[2]=MaxVol;
			 SetChVol(2, Volume[2]);
		 }
		 else if(temp_rot==EC11_DOWN)
		 {
			 if(Volume[2]!=0)Volume[2]=Volume[2]-5;
			 SetChVol(2, Volume[2]);
		 } 
		 temp_rot=0;
		 break;
	 case ETVol4:	////ģʽ5
		 temp_rot=EC11_Cor(); 
		 if(temp_rot==EC11_UP)
		 {
			 Volume[3]=Volume[3]+5; if(Volume[3]>MaxVol) Volume[3]=MaxVol;
			 SetChVol(3, Volume[3]);			 
		 }
		 else if(temp_rot==EC11_DOWN)
		 {
			 if(Volume[3]!=0)Volume[3]=Volume[3]-5;
			 SetChVol(3, Volume[3]);			 
		 }
		 temp_rot=0;
		 break;
	}
}
