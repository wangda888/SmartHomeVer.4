#ifndef __EC11_H
#define __EC11_H

#include "sys.h"


#define EC11_A  	GPIO_ReadInputBit(GPIOB,GPIO_PIN_3)//读取按键EC11_A
#define EC11_B  	GPIO_ReadInputBit(GPIOB,GPIO_PIN_5)//读取按键EC11_B
#define EC11_KEY	GPIO_ReadInputBit(GPIOA,GPIO_PIN_0)//读取按键EC11_KEY

#define EC11_STAND  0
#define EC11_UP 		1
#define EC11_DOWN		2

#define All 0	//控制全部音量
#define ETVol1 1	//控制功放1音量
#define ETVol2 2	//控制功放2音量
#define ETVol3 3	//控制功放3音量
#define ETVol4 4	//控制功放4音量


void EC11_Init(void);
u16 EC11_Cor(void);
void EC11KEY_Scan(void);
void EC11_KEYC(void);


#endif
