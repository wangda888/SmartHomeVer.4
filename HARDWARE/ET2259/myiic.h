#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"
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

//IO方向设置
#define SDA_IN_3()  {GPIOB->CTLR&=~(3<<(0*2));GPIOB->CTLR|=0<<0*2;}	 
#define SDA_OUT_3() {GPIOB->CTLR&=~(3<<(0*2));GPIOB->CTLR|=1<<0*2;}

//IO操作函数	
#define IIC_SCL_3(x)     (x==0)?GPIO_ResetBits(GPIOB, GPIO_PIN_1):GPIO_SetBits(GPIOB, GPIO_PIN_1) //SCL
#define IIC_SDA_3(x)     (x==0)?GPIO_ResetBits(GPIOB, GPIO_PIN_0):GPIO_SetBits(GPIOB, GPIO_PIN_0) //SDA	 
#define READ_SDA_3  			GPIO_ReadInputBit(GPIOB,GPIO_PIN_0) //输入SDA 

//#define IIC_SCL_3    PBout(1) //SCL
//#define IIC_SDA_3    PBout(0) //SDA	 
//#define READ_SDA_3   PBin(0)  //输入SDA 

//IIC所有操作函数
void IIC_Init_1(void);                //初始化IIC的IO口				 
void IIC_Start_1(void);				//发送IIC开始信号
void IIC_Stop_1(void);	  			//发送IIC停止信号
void IIC_Send_Byte_1(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte_1(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack_1(void); 				//IIC等待ACK信号
void IIC_Ack_1(void);					//IIC发送ACK信号
void IIC_NAck_1(void);				//IIC不发送ACK信号
void IIC_Write_One_Byte_1(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte_1(u8 daddr,u8 addr);	  


//IO方向设置
#define SDA_IN_1()  {GPIOB->CTLR&=~(3<<(8*2));GPIOB->CTLR|=0<<8*2;}	 
#define SDA_OUT_1() {GPIOB->CTLR&=~(3<<(8*2));GPIOB->CTLR|=1<<8*2;}
//#define SDA_IN_2()  {GPIOB->CRH&=0XFFFFFFF0;GPIOB->CRH|=8;}
//#define SDA_OUT_2() {GPIOB->CRH&=0XFFFFFFF0;GPIOB->CRH|=3;}

//IO操作函数	
#define IIC_SCL_1(x)     (x==0)?GPIO_ResetBits(GPIOB, GPIO_PIN_9):GPIO_SetBits(GPIOB, GPIO_PIN_9) //SCL
#define IIC_SDA_1(x)     (x==0)?GPIO_ResetBits(GPIOB, GPIO_PIN_8):GPIO_SetBits(GPIOB, GPIO_PIN_8) //SDA	 
#define READ_SDA_1   			GPIO_ReadInputBit(GPIOB,GPIO_PIN_8)  //输入SDA 

//#define IIC_SCL_1    PBout(9) //SCL
//#define IIC_SDA_1    PBout(8) //SDA	 
//#define READ_SDA_1   PBin(8)  //输入SDA 
//IIC所有操作函数
void IIC_Init_2(void);                //初始化IIC的IO口				 
void IIC_Start_2(void);				//发送IIC开始信号
void IIC_Stop_2(void);	  			//发送IIC停止信号
void IIC_Send_Byte_2(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte_2(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack_2(void); 				//IIC等待ACK信号
void IIC_Ack_2(void);					//IIC发送ACK信号
void IIC_NAck_2(void);				//IIC不发送ACK信号
void IIC_Write_One_Byte_2(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte_2(u8 daddr,u8 addr);	

//IO方向设置
#define SDA_IN_2()  {GPIOB->CTLR&=~(3<<(12*2));GPIOB->CTLR|=0<<12*2;}	 
#define SDA_OUT_2() {GPIOB->CTLR&=~(3<<(12*2));GPIOB->CTLR|=1<<12*2;}
//#define SDA_IN_3()  {GPIOB->CRH&=0XFFF0FFFF;GPIOB->CRH|=8<<16;}
//#define SDA_OUT_3() {GPIOB->CRH&=0XFFF0FFFF;GPIOB->CRH|=3<<16;}

//IO操作函数	
#define IIC_SCL_2(x)     (x==0)?GPIO_ResetBits(GPIOB, GPIO_PIN_13):GPIO_SetBits(GPIOB, GPIO_PIN_13)  //SCL
#define IIC_SDA_2(x)     (x==0)?GPIO_ResetBits(GPIOB, GPIO_PIN_12):GPIO_SetBits(GPIOB, GPIO_PIN_12)  //SDA	 
#define READ_SDA_2   			GPIO_ReadInputBit(GPIOB,GPIO_PIN_12)  //输入SDA 

//#define IIC_SCL_2    PBout(13) //SCL
//#define IIC_SDA_2    PBout(12) //SDA	 
//#define READ_SDA_2   PBin(12)  //输入SDA 
//IIC所有操作函数
void IIC_Init_3(void);                //初始化IIC的IO口				 
void IIC_Start_3(void);				//发送IIC开始信号
void IIC_Stop_3(void);	  			//发送IIC停止信号
void IIC_Send_Byte_3(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte_3(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack_3(void); 				//IIC等待ACK信号
void IIC_Ack_3(void);					//IIC发送ACK信号
void IIC_NAck_3(void);				//IIC不发送ACK信号、
void IIC_Write_One_Byte_3(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte_3(u8 daddr,u8 addr);	

//IO方向设置
#define SDA_IN_4()  {GPIOB->CTLR&=~(3<<(14*2));GPIOB->CTLR|=0<<14*2;}	 
#define SDA_OUT_4() {GPIOB->CTLR&=~(3<<(14*2));GPIOB->CTLR|=1<<14*2;}
//#define SDA_IN_4()  {GPIOB->CRH&=0XF0FFFFFF;GPIOB->CRH|=8<<24;}
//#define SDA_OUT_4() {GPIOB->CRH&=0XF0FFFFFF;GPIOB->CRH|=3<<24;}

//IO操作函数	
#define IIC_SCL_4(x)     (x==0)?GPIO_ResetBits(GPIOB, GPIO_PIN_15):GPIO_SetBits(GPIOB, GPIO_PIN_15) //SCL
#define IIC_SDA_4(x)     (x==0)?GPIO_ResetBits(GPIOB, GPIO_PIN_14):GPIO_SetBits(GPIOB, GPIO_PIN_14) //SDA	 
#define READ_SDA_4   			GPIO_ReadInputBit(GPIOB,GPIO_PIN_14)  //输入SDA 

//#define IIC_SCL_4    PBout(15) //SCL
//#define IIC_SDA_4    PBout(14) //SDA	 
//#define READ_SDA_4   PBin(14)  //输入SDA 
//IIC所有操作函数
void IIC_Init_4(void);                //初始化IIC的IO口				 
void IIC_Start_4(void);				//发送IIC开始信号
void IIC_Stop_4(void);	  			//发送IIC停止信号
void IIC_Send_Byte_4(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte_4(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack_4(void); 				//IIC等待ACK信号
void IIC_Ack_4(void);					//IIC发送ACK信号
void IIC_NAck_4(void);				//IIC不发送ACK信号
void IIC_Write_One_Byte_4(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte_4(u8 daddr,u8 addr);	 
#endif
















