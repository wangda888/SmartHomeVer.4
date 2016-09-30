
#include "uart3.h"
#include "func485.h"

u8 CmdRsvOk = 0;
u8 DataLen  = 0;

static u8 Recive_Cnt = 0;
static u8 RsvStart   = 0;
 
u8 Uart485RSV[MaxRSVSize];

void CheckFristTime(void)
{
	u8 datalen = 0;
	if(Uart485RSV[TypeOffset] == Type_Amp)	//check type
	{
		datalen = Uart485RSV[LenthOffset];
		if(Recive_Cnt == (datalen+8))		//data cmd size ok
		{
			CmdRsvOk = 1;
			DataLen  = Recive_Cnt;
		//	SendDataTo485(Uart485RSV, Recive_Cnt);
		}
		else	//should continue receive data
		{
			return;
		}
	}
	//type error or start another receive
	RsvStart = 0;
	Recive_Cnt = 0;
}

void USART2_IRQHandler(void)
{
	u8  Char;
	
	if(USART_GetIntBitState(USART2, USART_INT_RBNE) != RESET)	  //���ڽ����ж�
	{
		Char = (USART_DataReceive(USART2) & 0xFF);  /* Read one byte from the receive data register */
//		printf("%x ", Char);
		if(CmdRsvOk == 0)//�ڶ�ȡ�껺��������֮ǰ�����ٴ�����յ�������, ��������
		{
			if(RsvStart == 0)//���յ�0XAA,����������ͷ
			{
				if(Char == 0xAA)
				{
					RsvStart = 1;//���յ�����ͷ
					Recive_Cnt = 0;
				}
			}
			if(1 == RsvStart)
			{
				Uart485RSV[Recive_Cnt++] = Char;

				//���ܸ�������
				if(Recive_Cnt>=MinOneCmdSize)//���ݽ��ո������ޣ����������ݶ���15�������ݣ�Ĭ�Ͻ����ݰ���Ϊ������ϣ���ֹ���ݳ����ַ����󣬵��³���һֱ����
				{
					CheckFristTime();
				}
			}
		}
		/* Clear the USART1 Receive interrupt */
		USART_ClearIntBitState(USART2, USART_INT_RBNE);
	}
}

void SendDataTo485(u8 *data, u8 datalen)
{
	u8 i;
	
	RS485_CTRL3(TX);
	
	for(i = 0; i<datalen; i++)
	{
		while((USART2->STR&0X40)==0);//ѭ������,ֱ���������   
		USART_DataSend(USART2, (u8)data[i]);
	}
	while((USART2->STR&0X40)==0);//ѭ������,ֱ���������   
	RS485_CTRL3(RX);
}


void Uart485_Init(u32 bound)
{
  //GPIO�˿�����
  GPIO_InitPara GPIO_InitStructure;
	USART_InitPara USART_InitStructure;
	NVIC_InitPara NVIC_InitStructure;
	 
	RCC_APB1PeriphClock_Enable(RCC_APB1PERIPH_USART2, ENABLE);
	RCC_AHBPeriphClock_Enable(RCC_AHBPERIPH_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��


	GPIO_PinAFConfig(GPIOA,GPIO_PINSOURCE2,GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA,GPIO_PINSOURCE3,GPIO_AF_1);
 //USART2_TX   PA2 USART2_RX	  PA3
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_2|GPIO_PIN_3; //PA.2 PA.3
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF;	//�����������
	GPIO_InitStructure.GPIO_OType = GPIO_OTYPE_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PUPD_PULLUP;
	GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��PA9

 
	

  
   //USART ��ʼ������
	USART_InitStructure.USART_BRR = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WL = USART_WL_8B;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_STBits = USART_STBITS_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_PARITY_RESET;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HARDWAREFLOWCONTROL_NONE;//��Ӳ������������
	USART_InitStructure.USART_RxorTx = USART_RXORTX_RX | USART_RXORTX_TX;	//�շ�ģʽ

	USART_Init(USART2, &USART_InitStructure); //��ʼ������
	USART_INT_Set(USART2, USART_INT_RBNE, ENABLE);//�����ж�
	USART_Enable(USART2, ENABLE);                    //ʹ�ܴ��� 
	
	  //Usart3 NVIC ����
  NVIC_InitStructure.NVIC_IRQ = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQPreemptPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQSubPriority = 2;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQEnable = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	RCC_AHBPeriphClock_Enable(RCC_AHBPERIPH_GPIOB, ENABLE);	 //ʹ��PA�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUT; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;		 //IO���ٶ�Ϊ50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OTYPE_PP;			//�������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PUPD_PULLUP;		//����
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5
	
	RS485_CTRL3(RX);
}




