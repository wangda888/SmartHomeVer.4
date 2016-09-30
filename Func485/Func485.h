
/*
*********************************************************************************************************
*                                           INCLUDE FILES
*********************************************************************************************************
*/
#ifndef _FUNC485_H_
#define	_FUNC485_H_

#include "sys.h"

#define NULL 0

typedef struct //�ܳ���
{    
		u8 Guide;   		 // ������ 
		u8 Dest;   			 // Ŀ�ĵ�ַ  
		u8 DestCanle;    // Ŀ��ͨ��
		u8 Sour;    		 // Դ��ַ    
		u8 SourCanle;    // Դͨ��
		u8 DivceType;    // �豸����    
		u8 DataLen;      // ���ݳ���    
		u8 Data[255];    // ����    
		u8 Crc8;         // У��
}MainPro;

typedef struct{
	u8 Cmd;
	void (*Func_CmdDeal)(MainPro *pPro);//����һ������ָ�� ��ʽ������˵���� (*������)(����),
}Str_Cmd;

//������Ϣ����
typedef struct //IO����������
{
  u8   softaddr;      //�����ַ
  u8	 MacAdd[7];		 //Ӳ����ַ  
}Sys_Para;

#define  COMM1                  1
#define  COMM2                  2
#define  COMM3                  3

#define  MAIN_485       COMM3

//�豸����
#define Type_Music     0x0F
#define	Type_Amp			 0x20

#define RxBufferSize   0x1

#define  RX       				0
#define  TX       				1

#define  Device_Channal_1   0x01    //M500�豸��ֻ����һ��ͨ����ͨ�����Ϊ 0X01

#if UART3_EN485 //PB4
#define  RS485_CTRL3_PIN_TX		GPIO_Pin_4		  // USART3  485���ͽ��տ���
#define  RS485_CTRL3_PORT			GPIOB
#define  RS485_CTRL3(x)    	  RS485_CTRL3_PORT->ODR = (RS485_CTRL3_PORT->ODR & ~(RS485_CTRL3_PIN_TX)) | (x ? (RS485_CTRL3_PIN_TX) : 0)
#endif


/* ERROR CODES                                        */
#define  COMM_NO_ERR            0                /* Function call was successful                       */
#define  COMM_BAD_CH            1                /* Invalid communications port channel                */
#define  COMM_RX_EMPTY          2                /* Rx buffer is empty, no character available         */
#define  COMM_TX_FULL           3                /* Tx buffer is full, could not deposit character     */
#define  COMM_TX_EMPTY          4                /* If the Tx buffer is empty.                         */
#define  COMM_RX_TIMEOUT        5                /* If a timeout occurred while waiting for a character*/
#define  COMM_TX_TIMEOUT        6                /* If a timeout occurred while waiting to send a char.*/

#define  COMM_PARITY_NONE       0                /* Defines for setting parity                         */
#define  COMM_PARITY_ODD        1
#define  COMM_PARITY_EVEN       2

#define  RX       				0
#define  TX       				1

#define Flg_Start_Addr_Ok     1
#define Flg_Start_Addr_NO     0

//������ַ
#define Host_Addr         0X00
#define Broad_Addr        0XFF

#define Cmd_NULL       		0X00
//���ſ�������
#define Cmd_Auto  				0XBD
#define Cmd_Auto_Bt     	0x03
#define Cmd_Auto_Mp3    	0x01
#define Cmd_Auto_Out    	0x02

#define Cmd_Add   				0xBB
#define Cmd_Sub        	 	0XBC
#define Cmd_Next       		0XBA
#define Cmd_Play       	 	0XB7
#define Cmd_Stop       	 	0XB8
#define Cmd_Prev          0xB9

#define	Cmd_SetVol				0xBE
#define	Cmd_SetChann			0xC2
#define	Cmd_SetChann_Open		0x64
#define	Cmd_SetChann_Close	0x00

//��ַ����
#define Cmd_Addr_Start 		0XDD
#define Cmd_Addr_Change 	0XDE
#define Cmd_Addr_Save     0XDF
#define Cmd_Status_Query  0XB5
#define Cmd_Adrr_Dirt    	0XB6

#define	Cmd_Login					0xEE


//ָ�������б�
void LoadStart(void);
void process485(void);


#endif
