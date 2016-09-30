#ifndef __EC11_H
#define __EC11_H

#include "sys.h"


#define EC11_A  	GPIO_ReadInputBit(GPIOB,GPIO_PIN_3)//��ȡ����EC11_A
#define EC11_B  	GPIO_ReadInputBit(GPIOB,GPIO_PIN_5)//��ȡ����EC11_B
#define EC11_KEY	GPIO_ReadInputBit(GPIOA,GPIO_PIN_0)//��ȡ����EC11_KEY

#define EC11_STAND  0
#define EC11_UP 		1
#define EC11_DOWN		2

#define All 0	//����ȫ������
#define ETVol1 1	//���ƹ���1����
#define ETVol2 2	//���ƹ���2����
#define ETVol3 3	//���ƹ���3����
#define ETVol4 4	//���ƹ���4����


void EC11_Init(void);
u16 EC11_Cor(void);
void EC11KEY_Scan(void);
void EC11_KEYC(void);


#endif
