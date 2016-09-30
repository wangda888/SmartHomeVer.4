#include "sys.h"
#include "usart.h"	  
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_UCOS
#include "includes.h"					//ucos ʹ��	  
#endif
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/8/18
//�汾��V1.5
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//********************************************************************************
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
//V1.4�޸�˵��
//1,�޸Ĵ��ڳ�ʼ��IO��bug
//2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
//3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
//V1.5�޸�˵��
//1,�����˶�UCOSII��֧��
////////////////////////////////////////////////////////////////////////////////// 	  
 

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->STR&0X40)==0);//ѭ������,ֱ���������   
    USART1->TDTR = (u8) ch;      
	return ch;
}
#endif 

/*ʹ��microLib�ķ���*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/
 
#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	  

//��ʼ��IO ����1 
//bound:������
void uart_init(u32 bound){
    //GPIO�˿�����
	GPIO_InitPara GPIO_InitStructure;
	USART_InitPara USART_InitStructure;
	NVIC_InitPara NVIC_InitStructure;
	 
	RCC_AHBPeriphClock_Enable(RCC_AHBPERIPH_GPIOB, ENABLE);	//ʹ��GPIOAʱ��
	RCC_APB2PeriphClock_Enable(RCC_APB2PERIPH_USART1,ENABLE);//ʹ��USART1ʱ��

	GPIO_PinAFConfig(GPIOB,GPIO_PINSOURCE6,GPIO_AF_0);
	GPIO_PinAFConfig(GPIOB,GPIO_PINSOURCE7,GPIO_AF_0);
 //USART1_TX   PA.9 USART1_RX	  PA.10
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_6|GPIO_PIN_7; //PA.9 PA.10
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF;	//�����������
	GPIO_InitStructure.GPIO_OType = GPIO_OTYPE_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PUPD_PULLUP;
	GPIO_Init(GPIOB, &GPIO_InitStructure); //��ʼ��PA9
  
   //USART ��ʼ������

	USART_InitStructure.USART_BRR = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WL = USART_WL_8B;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_STBits = USART_STBITS_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_PARITY_RESET;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HARDWAREFLOWCONTROL_NONE;//��Ӳ������������
	USART_InitStructure.USART_RxorTx = USART_RXORTX_RX | USART_RXORTX_TX;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������
	
	USART_Enable(USART1, ENABLE);  
	USART_INT_Set(USART1, USART_INT_RBNE, ENABLE);//�����ж�
//Usart1 NVIC ����

	NVIC_InitStructure.NVIC_IRQ = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQPreemptPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQEnable = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
	                  //ʹ�ܴ��� 
}

void USART1_IRQHandler(void)                	//����1�жϷ������
	{
	u8 Res;
#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
	OSIntEnter();    
#endif
	if(USART_GetIntBitState(USART1, USART_INT_RBNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		Res = USART_DataReceive(USART1);//(USART1->DR);	//��ȡ���յ�������
		
		if((USART_RX_STA&0x8000)==0)//����δ���
			{
			if(USART_RX_STA&0x4000)//���յ���0x0d
				{
				if(Res!=0x0a)USART_RX_STA=0;//���մ���,���¿�ʼ
				else USART_RX_STA|=0x8000;	//��������� 
				}
			else //��û�յ�0X0D
				{	
				if(Res==0x0d)USART_RX_STA|=0x4000;
				else
					{
					USART_RX_BUF[USART_RX_STA&0X3FFF]=Res ;
					USART_RX_STA++;
					if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
					}		 
				}
			}   		 
     } 
#ifdef OS_TICKS_PER_SEC	 	//���ʱ�ӽ�����������,˵��Ҫʹ��ucosII��.
	OSIntExit();  											 
#endif
} 
#endif	

