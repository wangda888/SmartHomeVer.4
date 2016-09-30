
/*
*********************************************************************************************************
*                                           INCLUDE FILES
*********************************************************************************************************
*/
#ifndef _UART3_H_
#define	_UART3_H_
#include "sys.h"
#include "usart.h"	 

#define MaxRSVSize				255+8

#define  RX       				0
#define  TX       				1

#define  RS485_CTRL3_PIN		GPIO_Pin_4		  // USART3  485发送接收控制
#define  RS485_CTRL3_PORT		GPIOB
#define  RS485_CTRL3(x)     (x==0)?GPIO_ResetBits(GPIOB, GPIO_PIN_4):GPIO_SetBits(GPIOB, GPIO_PIN_4)

#define	DstAddrOffset				1
#define	DstPortOffset				2
#define	SrcAddrOffset				3
#define	SecPortOffset				4
#define	TypeOffset 					5
#define	LenthOffset 				6
#define	DataOffset					7

#define MinOneCmdSize	11

void SendDataTo485(u8 *data, u8 datalen);
void Uart485_Init(u32 bound);
#endif

