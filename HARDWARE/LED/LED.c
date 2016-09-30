#include "LED.h"


void LED_Init(void)
{
	
	GPIO_InitPara  GPIO_InitStructure;
		
	RCC_AHBPeriphClock_Enable(RCC_AHBPERIPH_GPIOA, ENABLE);	 //ʹ��PA�˿�ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_8|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_15;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUT; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;		 //IO���ٶ�Ϊ50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OTYPE_PP;			//�������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PUPD_PULLUP;		//����
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
	GPIO_ResetBits(GPIOA,GPIO_PIN_8|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_15);				 
}

void AUX_Init(void)
{
	GPIO_InitPara  GPIO_InitStructure;
		
	RCC_AHBPeriphClock_Enable(RCC_AHBPERIPH_GPIOB, ENABLE);	 //ʹ��PB�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_10|GPIO_PIN_11;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUT; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;		 //IO���ٶ�Ϊ50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OTYPE_PP;			//�������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PUPD_PULLUP;		//����
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
	GPIO_ResetBits(GPIOB,GPIO_PIN_10|GPIO_PIN_11);	
}



//onoff=1Ϊ����onoff=0Ϊ��
void LED_ONOFF(u8 led,u8 onoff)
{
	switch (led)
	{
		case 0 :		//ȫ��
			if(onoff)	
			{
				LED1(0);//�͵�ƽ��
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
			if(onoff)		//Ϊ1����
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
			if(onoff)		//Ϊ1����
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
			if(onoff)		//Ϊ1����
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
			if(onoff)		//Ϊ1����
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
