#include "myiic.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//IIC驱动 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/9
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
 
/////////////////////////////////////////////////////////////////////////////
//////////////////////////////初始化IIC1/////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
void IIC_Init_1(void)
{					     
	GPIO_InitPara GPIO_InitStructure;
	RCC_AHBPeriphClock_Enable(RCC_AHBPERIPH_GPIOB, ENABLE );
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_0|GPIO_PIN_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUT ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;
	GPIO_InitStructure.GPIO_OType = GPIO_OTYPE_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PUPD_PULLUP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_PIN_0|GPIO_PIN_1); 	//PB10,PB11 输出高
}
//产生IIC起始信号
void IIC_Start_1(void)
{
	SDA_OUT_1();     //sda线输出
	IIC_SDA_1(1);	  	  
	IIC_SCL_1(1);
	delay_us(4);
 	IIC_SDA_1(0);//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL_1(0);//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_Stop_1(void)
{
	SDA_OUT_1();//sda线输出
	IIC_SCL_1(0);
	IIC_SDA_1(0);//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL_1(1); 
	IIC_SDA_1(1);//发送I2C总线结束信号
	delay_us(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack_1(void)
{
	u8 ucErrTime=0;
	SDA_IN_1();      //SDA设置为输入  
	IIC_SDA_1(1);delay_us(1);	   
	IIC_SCL_1(1);delay_us(1);	 
	while(READ_SDA_1)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop_1();
			return 1;
		}
	}
	IIC_SCL_1(0);//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void IIC_Ack_1(void)
{
	IIC_SCL_1(0);
	SDA_OUT_1();
	IIC_SDA_1(0);
	delay_us(2);
	IIC_SCL_1(1);
	delay_us(2);
	IIC_SCL_1(0);
}
//不产生ACK应答		    
void IIC_NAck_1(void)
{
	IIC_SCL_1(0);
	SDA_OUT_1();
	IIC_SDA_1(1);
	delay_us(2);
	IIC_SCL_1(1);
	delay_us(2);
	IIC_SCL_1(0);
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte_1(u8 txd)
{                        
    u8 t;   
	SDA_OUT_1(); 	    
    IIC_SCL_1(0);//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA_1(1);
		else
			IIC_SDA_1(0);
		txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL_1(1);
		delay_us(2); 
		IIC_SCL_1(0);	
		delay_us(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte_1(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN_1();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCL_1(0); 
        delay_us(2);
		IIC_SCL_1(1);
        receive<<=1;
        if(READ_SDA_1)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck_1();//发送nACK
    else
        IIC_Ack_1(); //发送ACK   
    return receive;
}


/////////////////////////////////////////////////////////////////////////////
//////////////////////////////初始化IIC2/////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
void IIC_Init_2(void)
{
	GPIO_InitPara GPIO_InitStructure;
	RCC_AHBPeriphClock_Enable(RCC_AHBPERIPH_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_8 | GPIO_PIN_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUT;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;
	GPIO_InitStructure.GPIO_OType = GPIO_OTYPE_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PUPD_PULLUP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB, GPIO_PIN_8 | GPIO_PIN_9); 	//PB8,PB9 输出高	
}
//产生IIC起始信号
void IIC_Start_2(void)
{
	SDA_OUT_2();     //sda线输出
	IIC_SDA_2(1);	  	  
	IIC_SCL_2(1);
	delay_us(4);
 	IIC_SDA_2(0);//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL_2(0);//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_Stop_2(void)
{
	SDA_OUT_2();//sda线输出
	IIC_SCL_2(0);
	IIC_SDA_2(0);//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL_2(1); 
	IIC_SDA_2(1);//发送I2C总线结束信号
	delay_us(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack_2(void)
{
	u8 ucErrTime=0;
	SDA_IN_2();      //SDA设置为输入  
	IIC_SDA_2(1);delay_us(1);	   
	IIC_SCL_2(1);delay_us(1);	 
	while(READ_SDA_2)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop_2();
			return 1;
		}
	}
	IIC_SCL_2(0);//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void IIC_Ack_2(void)
{
	IIC_SCL_2(0);
	SDA_OUT_2();
	IIC_SDA_2(0);
	delay_us(2);
	IIC_SCL_2(1);
	delay_us(2);
	IIC_SCL_2(0);
}
//不产生ACK应答		    
void IIC_NAck_2(void)
{
	IIC_SCL_2(0);
	SDA_OUT_2();
	IIC_SDA_2(1);
	delay_us(2);
	IIC_SCL_2(1);
	delay_us(2);
	IIC_SCL_2(0);
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte_2(u8 txd)
{                        
    u8 t;   
	SDA_OUT_2(); 	    
    IIC_SCL_2(0);//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA_2(1);
		else
			IIC_SDA_2(0);
		txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL_2(1);
		delay_us(2); 
		IIC_SCL_2(0);	
		delay_us(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte_2(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN_2();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCL_2(0); 
        delay_us(2);
		IIC_SCL_2(1);
        receive<<=1;
        if(READ_SDA_2)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck_2();//发送nACK
    else
        IIC_Ack_2(); //发送ACK   
    return receive;
}


/////////////////////////////////////////////////////////////////////////////
//////////////////////////////初始化IIC3/////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
void IIC_Init_3(void)
{
	GPIO_InitPara GPIO_InitStructure;
	RCC_AHBPeriphClock_Enable(RCC_AHBPERIPH_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_12 | GPIO_PIN_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUT;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;
	GPIO_InitStructure.GPIO_OType = GPIO_OTYPE_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PUPD_PULLUP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB, GPIO_PIN_12 | GPIO_PIN_13); 	//PB10,PB11 输出高
}
//产生IIC起始信号
void IIC_Start_3(void)
{
	SDA_OUT_3();     //sda线输出
	IIC_SDA_3(1);	  	  
	IIC_SCL_3(1);
	delay_us(4);
 	IIC_SDA_3(0);//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL_3(0);//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_Stop_3(void)
{
	SDA_OUT_3();//sda线输出
	IIC_SCL_3(0);
	IIC_SDA_3(0);//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL_3(1); 
	IIC_SDA_3(1);//发送I2C总线结束信号
	delay_us(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack_3(void)
{
	u8 ucErrTime=0;
	SDA_IN_3();      //SDA设置为输入  
	IIC_SDA_3(1);delay_us(1);	   
	IIC_SCL_3(1);delay_us(1);	 
	while(READ_SDA_3)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop_3();
			return 1;
		}
	}
	IIC_SCL_3(0);//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void IIC_Ack_3(void)
{
	IIC_SCL_3(0);
	SDA_OUT_3();
	IIC_SDA_3(0);
	delay_us(2);
	IIC_SCL_3(1);
	delay_us(2);
	IIC_SCL_3(1);
}
//不产生ACK应答		    
void IIC_NAck_3(void)
{
	IIC_SCL_3(0);
	SDA_OUT_3();
	IIC_SDA_3(1);
	delay_us(2);
	IIC_SCL_3(1);
	delay_us(2);
	IIC_SCL_3(0);
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte_3(u8 txd)
{                        
  u8 t;   
	SDA_OUT_3(); 	    
    IIC_SCL_3(0);//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA_3(1);
		else
			IIC_SDA_3(0);
		txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL_3(1);
		delay_us(2); 
		IIC_SCL_3(0);	
		delay_us(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte_3(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN_3();//SDA设置为输入
   for(i=0;i<8;i++ )
	{
    IIC_SCL_3(0); 
    delay_us(2);
		IIC_SCL_3(1);
    receive<<=1;
    if(READ_SDA_3)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck_3();//发送nACK
    else
        IIC_Ack_3(); //发送ACK   
    return receive;
}



/////////////////////////////////////////////////////////////////////////////
//////////////////////////////初始化IIC4/////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
void IIC_Init_4(void)
{	
	GPIO_InitPara GPIO_InitStructure;
	RCC_AHBPeriphClock_Enable(RCC_AHBPERIPH_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUT;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;
	GPIO_InitStructure.GPIO_OType = GPIO_OTYPE_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PUPD_PULLUP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB, GPIO_PIN_14 | GPIO_PIN_15); 	//PB10,PB11 输出高
}
//产生IIC起始信号
void IIC_Start_4(void)
{
	SDA_OUT_4();     //sda线输出
	IIC_SDA_4(1);	  	  
	IIC_SCL_4(1);
	delay_us(4);
 	IIC_SDA_4(0);//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL_4(0);//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_Stop_4(void)
{
	SDA_OUT_4();//sda线输出
	IIC_SCL_4(0);
	IIC_SDA_4(0);//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL_4(1); 
	IIC_SDA_4(1);//发送I2C总线结束信号
	delay_us(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack_4(void)
{
	u8 ucErrTime=0;
	SDA_IN_4();      //SDA设置为输入  
	IIC_SDA_4(1);delay_us(1);	   
	IIC_SCL_4(1);delay_us(1);	 
	while(READ_SDA_4)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop_4();
			return 1;
		}
	}
	IIC_SCL_4(0);//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void IIC_Ack_4(void)
{
	IIC_SCL_4(0);
	SDA_OUT_4();
	IIC_SDA_4(0);
	delay_us(2);
	IIC_SCL_4(1);
	delay_us(2);
	IIC_SCL_4(0);
}
//不产生ACK应答		    
void IIC_NAck_4(void)
{
	IIC_SCL_4(0);
	SDA_OUT_4();
	IIC_SDA_4(1);
	delay_us(2);
	IIC_SCL_4(1);
	delay_us(2);
	IIC_SCL_4(0);
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte_4(u8 txd)
{                        
    u8 t;   
	SDA_OUT_4(); 	    
    IIC_SCL_4(0);//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA_4(1);
		else
			IIC_SDA_4(0);
		txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL_4(1);
		delay_us(2); 
		IIC_SCL_4(0);	
		delay_us(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte_4(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN_4();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCL_4(0); 
        delay_us(2);
		IIC_SCL_4(1);
        receive<<=1;
        if(READ_SDA_4)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck_4();//发送nACK
    else
        IIC_Ack_4(); //发送ACK   
    return receive;
}






















