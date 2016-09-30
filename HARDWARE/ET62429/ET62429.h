#ifndef _ET62429_H
#define _ET62429_H


#include "sys.h"


#define ET1_CLK(x)     (x==0)?GPIO_ResetBits(GPIOB, GPIO_PIN_9):GPIO_SetBits(GPIOB, GPIO_PIN_9) //SCL
#define ET1_DAT(x)     (x==0)?GPIO_ResetBits(GPIOB, GPIO_PIN_8):GPIO_SetBits(GPIOB, GPIO_PIN_8) //SDA	 


#define ET2_CLK(x)     (x==0)?GPIO_ResetBits(GPIOB, GPIO_PIN_13):GPIO_SetBits(GPIOB, GPIO_PIN_13) //SCL
#define ET2_DAT(x)     (x==0)?GPIO_ResetBits(GPIOB, GPIO_PIN_12):GPIO_SetBits(GPIOB, GPIO_PIN_12) //SDA	 


#define ET3_CLK(x)     (x==0)?GPIO_ResetBits(GPIOB, GPIO_PIN_1):GPIO_SetBits(GPIOB, GPIO_PIN_1) //SCL
#define ET3_DAT(x)     (x==0)?GPIO_ResetBits(GPIOB, GPIO_PIN_0):GPIO_SetBits(GPIOB, GPIO_PIN_0) //SDA	 


#define ET4_CLK(x)     (x==0)?GPIO_ResetBits(GPIOB, GPIO_PIN_15):GPIO_SetBits(GPIOB, GPIO_PIN_15) //SCL
#define ET4_DAT(x)     (x==0)?GPIO_ResetBits(GPIOB, GPIO_PIN_14):GPIO_SetBits(GPIOB, GPIO_PIN_14) //SDA

//#define ET62429


void ET1_Col(u8 Channel,u8 Volume);
void ET2_Col(u8 Channel,u8 Volume);
void ET3_Col(u8 Channel,u8 Volume);
void ET4_Col(u8 Channel,u8 Volume);


#endif