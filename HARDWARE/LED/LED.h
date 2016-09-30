#ifndef __LED_H
#define __LED_H

#include "sys.h"

#define LED1(x)     (x==0)?GPIO_ResetBits(GPIOA, GPIO_PIN_15):GPIO_SetBits(GPIOA, GPIO_PIN_15)
#define LED2(x)     (x==0)?GPIO_ResetBits(GPIOA, GPIO_PIN_8):GPIO_SetBits(GPIOA, GPIO_PIN_8)
#define LED3(x)     (x==0)?GPIO_ResetBits(GPIOA, GPIO_PIN_11):GPIO_SetBits(GPIOA, GPIO_PIN_11)
#define LED4(x)     (x==0)?GPIO_ResetBits(GPIOA, GPIO_PIN_12):GPIO_SetBits(GPIOA, GPIO_PIN_12)
//#define LED1	PAout(15)
//#define LED2	PAout(8)
//#define LED3	PAout(11)
//#define LED4	PAout(12)

void LED_Init(void);
void LED_ONOFF(u8 led,u8 onoff);
void AUX_Init(void);
#endif
