
#include "func485.h"
#include "uart3.h"
#include "FuncAPI.h"
#include "DataSave.h"
#include "delay.h"

u8 Cmd_485 = 0x00;
Sys_Para systemset;
u8 Flg_Start_Addr = Flg_Start_Addr_NO;//地址修改开始标志

extern u8 CmdRsvOk;
extern u8 DataLen;
extern u8 Uart485RSV[];

static u8 boardcast_login = 1;

#define	DstAddrOffset				1
#define	DstPortOffset				2
#define	SrcAddrOffset				3
#define	SecPortOffset				4
#define	TypeOffset 					5
#define	LenthOffset 				6
#define	DataOffset					7

u8 Crc8CheckSum(u8 *ptr, u8 length) ;

void Reply485(void)
{
	u8 Sendbuf[MaxRSVSize];
	u8 i;
	u8 n;
	Sendbuf[0] = 0xAA;
	Sendbuf[DstAddrOffset] = Uart485RSV[SrcAddrOffset];
	Sendbuf[DstPortOffset] = Uart485RSV[SecPortOffset];
	Sendbuf[SrcAddrOffset] = Uart485RSV[DstAddrOffset];
	Sendbuf[SecPortOffset] = Uart485RSV[DstPortOffset];
	Sendbuf[TypeOffset]    = Uart485RSV[TypeOffset];
	Sendbuf[LenthOffset]   = Uart485RSV[LenthOffset];
	
	for(i = DataOffset; i<(Uart485RSV[LenthOffset]+DataOffset); i++)
		Sendbuf[i]   = Uart485RSV[i];
	
	Sendbuf[DataLen-1] = Crc8CheckSum(Sendbuf, DataLen-2);
	
	SendDataTo485(Sendbuf, DataLen+1);
	
	printf("SendDataTo485:");
		for(n=0;n<DataLen+1;n++)
			printf("%02X ",Sendbuf[n]);
		printf("\r\n");//MCD
}

/***************************************************************************
函数名称： u8 Crc8CheckSum(u8 *ptr, u8 length) 
函数功能： HOPE协议,CRC8校验
输入参数：
输出参数：
编写日期：2016.5.24
编写人：	赖健平
修改人：  
修改记录：
****************************************************************************/
u8 Crc8CheckSum(u8 *ptr, u8 length) 
{
  u8 i;     
  u8 Crc8=0;
  
  while(length--)
  {
    for(i=0x80; i; i>>=1)
    {
      if((Crc8&0x80)!=0)
      {
        Crc8<<=1;
        Crc8^=0x31;
      }
      else
      {
        Crc8<<=1;
      }
      
      if(*ptr&i)
      {
        Crc8^=0x31;
      } 
    }
    ptr++; 
  }
  return Crc8;
}
/***********************************************************以下为CMD通用模块驱动******************************/
void CMD_Cmd_Auto(MainPro *pPro)
{
	printf("485Cmd： Switch\r\n");
}
void CMD_Cmd_Add(MainPro *pPro)
{
	printf("485Cmd： Add\r\n");
	Cmd_485 = Cmd_Add;
	if(pPro->DestCanle == 0xFF)
	{
		AddStepChVol(0);
		AddStepChVol(1);
		AddStepChVol(2);
		AddStepChVol(3);
	}
	else if(pPro->DestCanle>=1&&pPro->DestCanle<=4)
	{
		AddStepChVol(pPro->DestCanle-1);
	}

	Reply485();//应答给主机
}
void CMD_Cmd_Sub(MainPro *pPro)
{
	printf("485Cmd： Sub\r\n");
	Cmd_485 = Cmd_Sub;
	if(pPro->DestCanle == 0xFF)
	{
		SubStepChVol(0);
		SubStepChVol(1);
		SubStepChVol(2);
		SubStepChVol(3);
	}
	else if(pPro->DestCanle>=1&&pPro->DestCanle<=4)
	{
		SubStepChVol(pPro->DestCanle-1);
	}

	Reply485();//应答给主机
}
void CMD_Cmd_Next(MainPro *pPro)
{
	printf("485Cmd： Next\r\n");
}
void CMD_Cmd_Play(MainPro *pPro)
{
	printf("485Cmd： Play\r\n");
}
void CMD_Cmd_Addr_Start(MainPro *pPro)
{
		//子机不返回，但是将 开始修改地址命令标志位置1 
		Flg_Start_Addr = Flg_Start_Addr_Ok;//开始修改地址标志位置1
		printf("Flg_Addr_Start_Ok");
}

void CMD_Cmd_Addr_Change(MainPro *pPro)
{
	u8 n;
	u16 para1 = (u16)(systemset.MacAdd[0]<<8)|systemset.MacAdd[1];
	u16 para2 = (u16)(systemset.MacAdd[2]<<8)|systemset.MacAdd[3];
	if(pPro->Data[0] == Cmd_Addr_Change)//修改地址命令 OXDE
	{
		u8 Sendbuf[MaxRSVSize];

		printf("pProTmp->Data[1]=0x%02X---systemset.MacAdd[0]=0x%02X\r\n",pPro->Data[1],systemset.MacAdd[0]);
		printf("pProTmp->Data[2]=0x%02X---systemset.MacAdd[1]=0x%02X\r\n",pPro->Data[2],systemset.MacAdd[1]);
		printf("pProTmp->Data[3]=0x%02X---systemset.MacAdd[2]=0x%02X\r\n",pPro->Data[3],systemset.MacAdd[2]);
		printf("pProTmp->Data[4]=0x%02X---systemset.MacAdd[3]=0x%02X\r\n",pPro->Data[4],systemset.MacAdd[3]);
		printf("systemset.softaddr=0x%02X\r\n",systemset.softaddr);
		
		Sendbuf[0] = 0xAA;
		Sendbuf[DstAddrOffset] = Uart485RSV[SrcAddrOffset];
		Sendbuf[DstPortOffset] = Uart485RSV[SecPortOffset];
		Sendbuf[SrcAddrOffset] = Uart485RSV[DstAddrOffset];
		Sendbuf[SecPortOffset] = Uart485RSV[DstPortOffset];
		Sendbuf[TypeOffset]    = Uart485RSV[TypeOffset];
		Sendbuf[LenthOffset]   = 5;
		
		Sendbuf[DataOffset+0]   = Cmd_Addr_Change;
		Sendbuf[DataOffset+1]   = systemset.MacAdd[0];		
		Sendbuf[DataOffset+2]   = systemset.MacAdd[1];	
		Sendbuf[DataOffset+3]   = systemset.MacAdd[2];	
		Sendbuf[DataOffset+4]   = systemset.MacAdd[3];	
		
		Sendbuf[12] = Crc8CheckSum(Sendbuf, 11);
		
		SendDataTo485(Sendbuf, 13);
		printf("SendDataTo485:");
		for(n=0;n<13;n++)
			printf("%02X ",Sendbuf[n]);
		printf("\r\n");//MCD
	}
}
void CMD_Cmd_Status_Query(MainPro *pPro)
{
	u8 Sendbuf[MaxRSVSize];
	u8 ch;
	u8 i;
	u8 n;
	
	printf("Cmd_Status_Query\r\n");
	
	ch = Uart485RSV[DstPortOffset];
	if((ch >=1) &&(ch <= 4))
	{
		ch -= 1;
		Sendbuf[0] = 0xAA;
		Sendbuf[DstAddrOffset] = Uart485RSV[SrcAddrOffset];
		Sendbuf[DstPortOffset] = Uart485RSV[SecPortOffset];
		Sendbuf[SrcAddrOffset] = Uart485RSV[DstAddrOffset];
		Sendbuf[SecPortOffset] = Uart485RSV[DstPortOffset];
		Sendbuf[TypeOffset]    = Uart485RSV[TypeOffset];
		
		Sendbuf[LenthOffset]   = 3;

		Sendbuf[DataOffset]    = Uart485RSV[DataOffset];

		Sendbuf[DataOffset+1]  = ChSta[ch];

		Sendbuf[DataOffset+2]  = Volume[ch];
		
		Sendbuf[10] = Crc8CheckSum(Sendbuf, 10);
		
		SendDataTo485(Sendbuf, 11);
		printf("SendDataTo485:");
		for(n=0;n<11;n++)
			printf("%02X ",Sendbuf[n]);
		printf("\r\n");//MCD
	}
	else if(ch == 0xFF)
	{
		Sendbuf[LenthOffset]   = 9;
		
		Sendbuf[DataOffset]    = Uart485RSV[DataOffset];
		for(i =0; i<4; i++)
			Sendbuf[DataOffset+1+i]  = ChSta[i];
		for(i =0; i<4; i++)
		Sendbuf[DataOffset+5+i]  = Volume[i];
		
		Sendbuf[16] = Crc8CheckSum(Sendbuf, 16);
		
		SendDataTo485(Sendbuf, 17);
		
		printf("SendDataTo485:");
		for(n=0;n<17;n++)
			printf("%02X ",Sendbuf[n]);
		printf("\r\n");//MCD
	}
}
void CMD_Cmd_Adrr_Dirt(MainPro *pPro)
{
		printf("CMD_Cmd_Adrr_Dirt\r\n");
		systemset.softaddr = pPro->Data[1];
		S400DataSave();
		Reply485();//应答给主机
	  printf("systemset.softaddr=0x%02X\r\n",systemset.softaddr);
}
void CMD_Cmd_Stop(MainPro *pPro)
{
	printf("485Cmd： Stop\r\n");
}
void CMD_Cmd_Prev(MainPro *pPro)
{
	printf("485Cmd： Prev\r\n");
}

void CMD_Cmd_SetChann(MainPro *pPro)
{
	printf("485Cmd： SetChann\r\n");
	Cmd_485 = Cmd_SetChann;
	
	if(pPro->DestCanle == 0xFF)
	{
		SetChOnOff(0, pPro->Data[1]);
		SetChOnOff(1, pPro->Data[1]);
		SetChOnOff(2, pPro->Data[1]);
		SetChOnOff(3, pPro->Data[1]);
	}
	else if(pPro->DestCanle>=1&&pPro->DestCanle<=4)
	{
		SetChOnOff(pPro->DestCanle-1, pPro->Data[1]);
	}
	
	Reply485();//应答给主机
}

void CMD_Cmd_SetVol(MainPro *pPro)
{
	u8 vol;
	
	printf("485Cmd：SetVol\r\n");
	Cmd_485 = Cmd_SetVol;
	if(pPro->Data[1] > 100)
		return;
	vol = pPro->Data[1];
	if(pPro->DestCanle == 0xFF)
	{
		SetChVol(0, vol);
		SetChVol(1, vol);
		SetChVol(2, vol);
		SetChVol(3, vol);
	}
	else if(pPro->DestCanle>=1&&pPro->DestCanle<=4)
	{
		SetChVol(pPro->DestCanle-1, vol);
	}
	Reply485();//应答给主机
}

void CMD_Cmd_Login(MainPro *pPro)
{
	u8 vol;
	
	printf("485Cmd：Login\r\n");
	Cmd_485 = Cmd_Login;
	
	if((pPro->Dest == systemset.softaddr)&&(pPro->Data[1] == 0x0F)&&(pPro->Data[2] == 0x0F))
	{
		boardcast_login = 0;
	}
}

//通道1 指令列表
Str_Cmd CMD_Buff_Ch1[]=
{
	{Cmd_Auto,CMD_Cmd_Auto},//切换模式
	{Cmd_Add,CMD_Cmd_Add},//音量add
	{Cmd_Sub,CMD_Cmd_Sub},//音量sub
	{Cmd_Next,CMD_Cmd_Next},//下一曲
	{Cmd_Play,CMD_Cmd_Play},//切换到本地mp3，并且播放/暂停
	{Cmd_Stop,CMD_Cmd_Stop},//暂停
	{Cmd_SetVol,CMD_Cmd_SetVol},//暂停
	{Cmd_Addr_Start,CMD_Cmd_Addr_Start},//地址修改开始命令，接收到后，修改地址标志位置1，子机不作动作
	{Cmd_Addr_Change,CMD_Cmd_Addr_Change},//修改地址命令，子机接收到后，交换源地址，目的地址返回
	{Cmd_Status_Query,CMD_Cmd_Status_Query},//获取子机状态命令
  {Cmd_Adrr_Dirt,CMD_Cmd_Adrr_Dirt},//直接修改地址
	{Cmd_Prev,CMD_Cmd_Prev},//上一曲
	{Cmd_SetChann,CMD_Cmd_SetChann},//设置通道开关
	{Cmd_Login, CMD_Cmd_Login},
	{NULL,	NULL}
};
/***************************************************************************
函数名称：void CMD_Query(MainPro *pPro)
函数功能：CMD指令查询函数，从指令列表中查找到相应的指令，并且执行相应的函数
输入参数：
输出参数：
编写日期：2016.5.24
编写人：	赖健平
修改人：  
修改记录：
****************************************************************************/
void CMD_Query_Ch1(MainPro *pPro)
{
  u8 i = 0;
	printf("0x%x\r\n",pPro->Data[0]);
	for(i=0;CMD_Buff_Ch1[i].Cmd!=0 && CMD_Buff_Ch1[i].Func_CmdDeal != 0;i++)
	{		//查找是什么命令
		if(pPro->Data[0] == CMD_Buff_Ch1[i].Cmd)
		{
			CMD_Buff_Ch1[i].Func_CmdDeal(pPro);
		}
	}
}

/***************************************************************************
函数名称：RecvOneProData(MainPro *pPro,u32 Timeout)
函数功能：从RXbuff中取出一条数据流
输入参数：
输出参数：
编写日期：2016.5.19
编写人：	李俊旗
修改人：  Darcy
修改记录：
****************************************************************************/
//数据接收程序
u8 RecvOneProData(MainPro *pPro)
{
		u8 DataCnt = 0;
	u8 n;
		u16 para1 = (u16)(systemset.MacAdd[0]<<8)|systemset.MacAdd[1];
		u16 para2 = (u16)(systemset.MacAdd[2]<<8)|systemset.MacAdd[3];
		
		if(0 == Crc8CheckSum((u8*)Uart485RSV, DataLen))//校验和正确，处理数据
		{
			
			printf("Uart485RSV:");
		for(n=0;n<DataLen;n++)
			printf("%02X ",Uart485RSV[n]);
		printf("\r\n");//MCD

			
/******************************无论本机还是广播都执行的指令****************************************************************************************/
			if(Flg_Start_Addr == Flg_Start_Addr_Ok) 
			{
				if(pPro->Data[0] == Cmd_Addr_Save)//保存新地址命令 OXDF，并且先验证MAC地址是否跟自身一致
				{
					printf("Get_Cmd_Addr_Save\r\n");
					//打印到接收到的MAC地址				
					if((pPro->Data[1]== systemset.MacAdd[0]) && (pPro->Data[2]== systemset.MacAdd[1]) && (pPro->Data[3]== systemset.MacAdd[2]) && (pPro->Data[4]== systemset.MacAdd[3]))
					{
						printf("MAC OK\r\n");
						systemset.softaddr = pPro->Dest;
						S400DataSave();
						Reply485();
//					SendPro5_2(0x00,systemset.softaddr,Cmd_Addr_Save,pPro->SourCanle,para1,para2);
						printf("systemset.softaddr=0x%02X\r\n",systemset.softaddr);
					}
				}
			}
/**************************本机地址控制指令*****广播地址控制,只能进行改地址，出厂默认本地软件地址为OXFF广播地址****************************************************************************************/
		else if((pPro->Dest == systemset.softaddr)||(pPro->Dest == 0xFF))////目的地址 是广播 地址。
		{
				CMD_Query_Ch1(pPro);//查命令表，执行
		}
	}else	printf("校验和错误\r\n");
}

#define  NumbOfVar    ((uint8_t)0x03)

uint16_t VirtAddVarTab[NumbOfVar] = {0x5555, 0x6666, 0x7777};

u32 EndAddr   = 0x0801FC00;  //要写入Flash的数据的末地址--FLASH结束地址 

union union_temp16
{
    unsigned int 		un_temp16;
    unsigned char   un_temp8[2];		// example 16: 0x0102  8:[0]2 [1]1
}my_unTemp16;

u32 GetLockCode(void)
{
	u16 un;
	u32 sn = 0;
//获取CPU唯一ID  //基地址:0x1FFF F7E8
// CpuID[0]=*(vu32*)(0x1ffff7e8);
// CpuID[1]=*(vu32*)(0x1ffff7ec);
// CpuID[2]=*(vu32*)(0x1ffff7f0);
// //
// Lock_Code=(CpuID[0]>>1)+(CpuID[1]>>2)+(CpuID[2]>>3);
	
	un=(*( u16 *)0x1FFFF7E0);   //闪存容量寄存器
// 	printf(" The Flash size: %d KB\r\n",un);    

// 	printf(" Unique device ID");
	un=(*( u16 *)0x1FFFF7E8);   //c
// 	printf(" U_ID[15:0]: %d\r\n",un);
	sn = un;
	
	un=(*( u16 *)0x1FFFF7EA);
// 	printf(" U_ID[31:16]: %d\r\n",un);
	sn = (sn<<16)+un;
	un=(*( u32 *)0x1FFFF7EC);
// 	printf(" U_ID[63:32]]: %d\r\n",un);  
  sn = sn+un;
	un=(*( u32 *)0x1FFFF7EF);
// 	printf(" U_ID[95:64]: %d\r\n",un);
	sn = sn+un;
// 	printf(" SN]: %d\r\n",sn);
	return sn;
}

void LoadStart(void)
{		
		u32 MacAddr;
		printf("*********************************\r\n");
		systemset.softaddr = 0xFF;
		MacAddr = GetLockCode();
		systemset.MacAdd[0] = (MacAddr>>24)&0xFF;
		systemset.MacAdd[1] = (MacAddr>>16)&0xFF;
		systemset.MacAdd[2] = (MacAddr>> 8)&0xFF;
		systemset.MacAdd[3] = (MacAddr>> 0)&0xFF;
		S400ReadFromFlash();
	  printf("485 Addr: 0x%X\r\n",systemset.softaddr);
		printf("---systemset.MacAdd[0]=0x%02X\r\n",systemset.MacAdd[0]);
		printf("---systemset.MacAdd[1]=0x%02X\r\n",systemset.MacAdd[1]);
		printf("---systemset.MacAdd[2]=0x%02X\r\n",systemset.MacAdd[2]);
		printf("---systemset.MacAdd[3]=0x%02X\r\n",systemset.MacAdd[3]);	
}

void process485(void)
{
	static u32 time_cnt = 0;
	static u8  startsend = 0;
	u8 n;
	
	if(boardcast_login)
	{
		if(!startsend)
		{
			delay_ms(systemset.MacAdd[0]==0?1:systemset.MacAdd[0]);
			delay_ms(systemset.MacAdd[1]==0?1:systemset.MacAdd[1]);
			delay_ms(systemset.MacAdd[2]==0?1:systemset.MacAdd[2]);
			delay_ms(systemset.MacAdd[3]==0?1:systemset.MacAdd[3]);
		}
		else
			delay_ms(100);
		
		if((!startsend)||(time_cnt++ > 50))
		{
			u8 Sendbuf[11] = {0xAA, 0xFF, 0x01, 0x00, 0x00, 0x20, 0x03, 0xEE, 0x00, 0x00, 0x00};
			
			Sendbuf[3] = systemset.softaddr;
			Sendbuf[4] = MaxCh+1;
			Sendbuf[5] = Type_Amp;
			Sendbuf[7] = Cmd_Login;
			
			Sendbuf[10] = Crc8CheckSum(Sendbuf, 10);
			
			SendDataTo485(Sendbuf, 11);
			printf("SendDataTo485:");
			for(n=0;n<11;n++)
			printf("%02X ",Sendbuf[n]);
			printf("\r\n");//MCD
			
			time_cnt = 1;
			startsend = 1;
		}
	}
	
	if(CmdRsvOk)
	{
		MainPro *pPro = (MainPro *)Uart485RSV;
		RecvOneProData(pPro);
		CmdRsvOk = 0;
	}

}


