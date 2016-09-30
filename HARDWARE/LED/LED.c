#include "LED.h"


void LED_Init(void)
{
	
	GPIO_InitPara  GPIO_InitStructure;
		
	RCC_AHBPeriphClock_Enable(RCC_AHBPERIPH_GPIOA, ENABLE);	 //使能PA端口时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_8|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_15;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUT; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;		 //IO口速度为50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OTYPE_PP;			//推完输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PUPD_PULLUP;		//上拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
	GPIO_ResetBits(GPIOA,GPIO_PIN_8|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_15);				 
}

void AUX_Init(void)
{
	GPIO_InitPara  GPIO_InitStructure;
		
	RCC_AHBPeriphClock_Enable(RCC_AHBPERIPH_GPIOB, ENABLE);	 //使能PB端口时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_10|GPIO_PIN_11;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUT; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;		 //IO口速度为50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OTYPE_PP;			//推完输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PUPD_PULLUP;		//上拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
	GPIO_ResetBits(GPIOB,GPIO_PIN_10|GPIO_PIN_11);	
}



//onoff=1为亮，onoff=0为暗
void LED_ONOFF(u8 led,u8 onoff)
{
	switch (led)
	{
		case 0 :		//全亮
			if(onoff)	
			{
				LED1(0);//低电平亮
				LED2(0);
				LED3(0);
				LED4(0);
			}
			else
			{
				LED1(1);
				LED2(1);
				LED3(1);
				LED4(1);
			}
			break;
		case 1 :
			if(onoff)		//为1是亮
			{
				LED1(0);
				LED2(1);
				LED3(1);
				LED4(1);
			}
			else
				LED1(1);
			break;
		case 2 :
			if(onoff)		//为1是亮
			{
				LED1(1);
				LED2(0);
				LED3(1);
				LED4(1);
			}
			else
				LED2(1);
			break;
		case 3 :
			if(onoff)		//为1是亮
			{
				LED1(1);
				LED2(1);
				LED3(0);
				LED4(1);
			}
			else
				LED3(1);
			break;
		case 4 :
			if(onoff)		//为1是亮
			{
				LED1(1);
				LED2(1);
				LED3(1);
				LED4(0);
			}
			else
				LED4(1);
			break;

	}
		
}
