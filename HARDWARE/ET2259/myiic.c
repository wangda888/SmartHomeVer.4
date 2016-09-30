#include "myiic.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//IIC���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/9
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
 
/////////////////////////////////////////////////////////////////////////////
//////////////////////////////��ʼ��IIC1/////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
void IIC_Init_1(void)
{					     
	GPIO_InitPara GPIO_InitStructure;
	RCC_AHBPeriphClock_Enable(RCC_AHBPERIPH_GPIOB, ENABLE );
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_0|GPIO_PIN_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUT ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;
	GPIO_InitStructure.GPIO_OType = GPIO_OTYPE_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PUPD_PULLUP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_PIN_0|GPIO_PIN_1); 	//PB10,PB11 �����
}
//����IIC��ʼ�ź�
void IIC_Start_1(void)
{
	SDA_OUT_1();     //sda�����
	IIC_SDA_1(1);	  	  
	IIC_SCL_1(1);
	delay_us(4);
 	IIC_SDA_1(0);//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL_1(0);//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop_1(void)
{
	SDA_OUT_1();//sda�����
	IIC_SCL_1(0);
	IIC_SDA_1(0);//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL_1(1); 
	IIC_SDA_1(1);//����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack_1(void)
{
	u8 ucErrTime=0;
	SDA_IN_1();      //SDA����Ϊ����  
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
	IIC_SCL_1(0);//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
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
//������ACKӦ��		    
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
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte_1(u8 txd)
{                        
    u8 t;   
	SDA_OUT_1(); 	    
    IIC_SCL_1(0);//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA_1(1);
		else
			IIC_SDA_1(0);
		txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL_1(1);
		delay_us(2); 
		IIC_SCL_1(0);	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte_1(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN_1();//SDA����Ϊ����
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
        IIC_NAck_1();//����nACK
    else
        IIC_Ack_1(); //����ACK   
    return receive;
}


/////////////////////////////////////////////////////////////////////////////
//////////////////////////////��ʼ��IIC2/////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
void IIC_Init_2(void)
{
	GPIO_InitPara GPIO_InitStructure;
	RCC_AHBPeriphClock_Enable(RCC_AHBPERIPH_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_8 | GPIO_PIN_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUT;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;
	GPIO_InitStructure.GPIO_OType = GPIO_OTYPE_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PUPD_PULLUP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB, GPIO_PIN_8 | GPIO_PIN_9); 	//PB8,PB9 �����	
}
//����IIC��ʼ�ź�
void IIC_Start_2(void)
{
	SDA_OUT_2();     //sda�����
	IIC_SDA_2(1);	  	  
	IIC_SCL_2(1);
	delay_us(4);
 	IIC_SDA_2(0);//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL_2(0);//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop_2(void)
{
	SDA_OUT_2();//sda�����
	IIC_SCL_2(0);
	IIC_SDA_2(0);//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL_2(1); 
	IIC_SDA_2(1);//����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack_2(void)
{
	u8 ucErrTime=0;
	SDA_IN_2();      //SDA����Ϊ����  
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
	IIC_SCL_2(0);//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
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
//������ACKӦ��		    
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
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte_2(u8 txd)
{                        
    u8 t;   
	SDA_OUT_2(); 	    
    IIC_SCL_2(0);//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA_2(1);
		else
			IIC_SDA_2(0);
		txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL_2(1);
		delay_us(2); 
		IIC_SCL_2(0);	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte_2(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN_2();//SDA����Ϊ����
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
        IIC_NAck_2();//����nACK
    else
        IIC_Ack_2(); //����ACK   
    return receive;
}


/////////////////////////////////////////////////////////////////////////////
//////////////////////////////��ʼ��IIC3/////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
void IIC_Init_3(void)
{
	GPIO_InitPara GPIO_InitStructure;
	RCC_AHBPeriphClock_Enable(RCC_AHBPERIPH_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_12 | GPIO_PIN_13;
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUT;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;
	GPIO_InitStructure.GPIO_OType = GPIO_OTYPE_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PUPD_PULLUP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB, GPIO_PIN_12 | GPIO_PIN_13); 	//PB10,PB11 �����
}
//����IIC��ʼ�ź�
void IIC_Start_3(void)
{
	SDA_OUT_3();     //sda�����
	IIC_SDA_3(1);	  	  
	IIC_SCL_3(1);
	delay_us(4);
 	IIC_SDA_3(0);//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL_3(0);//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop_3(void)
{
	SDA_OUT_3();//sda�����
	IIC_SCL_3(0);
	IIC_SDA_3(0);//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL_3(1); 
	IIC_SDA_3(1);//����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack_3(void)
{
	u8 ucErrTime=0;
	SDA_IN_3();      //SDA����Ϊ����  
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
	IIC_SCL_3(0);//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
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
//������ACKӦ��		    
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
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte_3(u8 txd)
{                        
  u8 t;   
	SDA_OUT_3(); 	    
    IIC_SCL_3(0);//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA_3(1);
		else
			IIC_SDA_3(0);
		txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL_3(1);
		delay_us(2); 
		IIC_SCL_3(0);	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte_3(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN_3();//SDA����Ϊ����
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
        IIC_NAck_3();//����nACK
    else
        IIC_Ack_3(); //����ACK   
    return receive;
}



/////////////////////////////////////////////////////////////////////////////
//////////////////////////////��ʼ��IIC4/////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
void IIC_Init_4(void)
{	
	GPIO_InitPara GPIO_InitStructure;
	RCC_AHBPeriphClock_Enable(RCC_AHBPERIPH_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_MODE_OUT;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_SPEED_50MHZ;
	GPIO_InitStructure.GPIO_OType = GPIO_OTYPE_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PUPD_PULLUP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB, GPIO_PIN_14 | GPIO_PIN_15); 	//PB10,PB11 �����
}
//����IIC��ʼ�ź�
void IIC_Start_4(void)
{
	SDA_OUT_4();     //sda�����
	IIC_SDA_4(1);	  	  
	IIC_SCL_4(1);
	delay_us(4);
 	IIC_SDA_4(0);//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL_4(0);//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop_4(void)
{
	SDA_OUT_4();//sda�����
	IIC_SCL_4(0);
	IIC_SDA_4(0);//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL_4(1); 
	IIC_SDA_4(1);//����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack_4(void)
{
	u8 ucErrTime=0;
	SDA_IN_4();      //SDA����Ϊ����  
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
	IIC_SCL_4(0);//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
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
//������ACKӦ��		    
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
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte_4(u8 txd)
{                        
    u8 t;   
	SDA_OUT_4(); 	    
    IIC_SCL_4(0);//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA_4(1);
		else
			IIC_SDA_4(0);
		txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL_4(1);
		delay_us(2); 
		IIC_SCL_4(0);	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte_4(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN_4();//SDA����Ϊ����
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
        IIC_NAck_4();//����nACK
    else
        IIC_Ack_4(); //����ACK   
    return receive;
}






















