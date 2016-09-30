#ifndef __ET2259_H
#define __ET2259_H

#include "sys.h"

//#define PE1_ON   PAout(4) //
//#define PE2_ON   PAout(5) //
//#define PE3_ON   PAout(6) //
//#define PE4_ON   PAout(7) //

#define	CH0PIN		GPIO_PIN_5
#define	CH1PIN		GPIO_PIN_6
#define	CH2PIN		GPIO_PIN_4
#define	CH3PIN		GPIO_PIN_7

#define ET2259


void Volume1_Write(u8 Vol);
void Volume2_Write(u8 Vol);
void Volume3_Write(u8 Vol);
void Volume4_Write(u8 Vol);
void	PE_PA_Init(void);
void ChanSwitch(u8 ch, u8 sta);
void	All_InitSet(u8 add,u8 ch,u8 ch1);

#endif
