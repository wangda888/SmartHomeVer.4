/**
  ******************************************************************************
  * @file    USART/HyperTerminal_Interrupt/gd32f1x0_it.h  
  * @author  MCU SD 
  * @version V1.0.1
  * @date    6-Sep-2014 
  * @brief   Headfile of the Interrupt Service Routines.
  ******************************************************************************
  */ 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GD32F1X0_IT_H
#define __GD32F1X0_IT_H

/* Includes ------------------------------------------------------------------*/
#include "gd32f1x0.h"

/* Exported functions ------------------------------------------------------- */
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);

#endif /* __GD32F1X0_IT_H */

/******************* (C) COPYRIGHT 2014 GIGADEVICE *****END OF FILE****/
