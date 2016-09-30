/**
  ******************************************************************************
  * @file    readme.txt
  * @author  MCU SD 
  * @version V1.0
  * @date    6-Sep-2014 
  * @brief   Description of the Systick_LED demo.
  ******************************************************************************
  */

  @brief
    This demo is based on the GD32130G-START board,in this demo,configure SysTick
  Timer to generate interrupt every 100us.
    When the interrupt occurs,the ISR calls the function TimingDelay_Decrement() to minus
  1,According to the parameter of TimingDelay to delay different time and make LED1 toggle.   

/****************** (C) COPYRIGHT 2014 GIGADEVICE *********END OF FILE*********/