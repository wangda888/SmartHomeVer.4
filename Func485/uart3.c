
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
	
	if(USART_GetIntBitState(USART2, USART_INT_RBNE) != RESET)	  //串口接收中断
	{
		Char = (USART_DataReceive(USART2) & 0xFF);  /* Read one byte from the receive data register */
//		printf("%x ", Char);
		if(CmdRsvOk == 0)//在读取完缓存区数据之前，不再处理接收到的数据, 命令处理完毕
		{
			if(RsvStart == 0)//接收到0XAA,并且是数据头
			{
				if(Char == 0xAA)
				{
					RsvStart = 1;//接收到数据头
					Recive_Cnt = 0;
				}
			}
			if(1 == RsvStart)
			{
				Uart485RSV[Recive_Cnt++] = Char;

				//接受个数计数
				if(Recive_Cnt>=MinOneCmdSize)//数据接收个数上限，当接收数据多于15个的数据，默认将数据包认为接收完毕，防止数据长度字符错误，导致程序一直接收
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
		while((USART2->STR&0X40)==0);//循环发送,直到发送完毕   
		USART_DataSend(USART2, (u8)data[i]);
	}
	while((USART2->STR&0X40)==0);//循环发送,直到发送完毕   
	RS485_CTRL3(RX);
}


void Uart485_Init(u32 bound)
{
  //GPIO端口设置
  GPIO_InitPara GPIO_InitStructure;
	USART_InitPara USART_InitStructure;
	NVIC_InitPara NVIC_InitStructure;
	 
	RCC_APB1PeriphClock_Enable(RCC_APB1PERIPH_USART2, ENABLE);
	RCC_AHBPeriphClock_Enable(RCC_AHBPERIPH_GPIOA, ENABLE);	//使能USART1，GPIOA时钟


	GPIO_PinAFConfig(GPIOA,GPIO_PINSOURCE2,GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA,GPIO_PINSOURCE3,GPIO_AF_1);
 //USART2_TX   PA2 USART2_RX	  PA3
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_2|GPIO_PIN_3; //PA.2 PA.3
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_AF;	//复用推挽输出
	GPIO_InitStructure.GPIO_OType = GPIO_OTYPE_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PUPD_PULLUP;
	GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PA9

 
	

  
   //USART 初始化设置
	USART_InitStructure.USART_BRR = bound;//一般设置为9600;
	USART_InitStructure.USART_WL = USART_WL_8B;//字长为8位数据格式
	USART_InitStructure.USART_STBits = USART_STBITS_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_PARITY_RESET;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HARDWAREFLOWCONTROL_NONE;//无硬件数据流控制
	USART_InitStructure.USART_RxorTx = USART_RXORTX_RX | USART_RXORTX_TX;	//收发模式

	USART_Init(USART2, &USART_InitStructure); //初始化串口
	USART_INT_Set(USART2, USART_INT_RBNE, ENABLE);//开启中断
	USART_Enable(USART2, ENABLE);                    //使能串口 
	
	  //Usart3 NVIC 配置
  NVIC_InitStructure.NVIC_IRQ = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQPreemptPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQSubPriority = 2;		//子优先级3
	NVIC_InitStructure.NVIC_IRQEnable = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
	RCC_AHBPeriphClock_Enable(RCC_AHBPERIPH_GPIOB, ENABLE);	 //使能PA端口时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUT; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;		 //IO口速度为50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OTYPE_PP;			//推完输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PUPD_PULLUP;		//上拉
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOB.5
	
	RS485_CTRL3(RX);
}




