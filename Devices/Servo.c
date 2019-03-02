/**
|-------------------------------- Copyright -----------------------------------|
|                                                                              |
|                     (C) Copyright 2019, Daqo Lee                             |
|                                                                              |
|                          By:GCU The wold of team                             |
|                     https://github.com/GCUWildwolfteam                       |
|------------------------------------------------------------------------------|
|  FileName    : Servo.c                                                
|  Version     : v1.0                                                            
|  Author      : Daqo Lee                                                       
|  Date        : 2019-01-10               
|  Libsupports : STM32F4xx_DFP ( 2.9.0)
|  Description :                                                       
|------------------------------declaration of end------------------------------|
 **/
/*--------------------- I N C L U D E - F I L E S ----------------------------*/
#include "Servo.h"
#include "BSP_USART.h"
#include "string.h"
#include "Task_Usart.h"
#include "check.h"
 #include <stdio.h>
 #include <stdlib.h>
 #include <stdarg.h>
/*-------------------------- D E F I N E S -----------------------------------*/

DigitalServo_t Dynamixel[8];

/*-----------L O C A L - F U N C T I O N S - P R O T O T Y P E S--------------*/



/*------------------G L O B A L - F U N C T I O N S --------------------------*/


/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-10 14:06
	* @brief   
	* @param   void
	* @retval  void
	*/
void ServoParamInit()
{


}

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-10 14:06
	* @brief   
	* @param   void
	* @retval  void
	*/
void Dynamixel_getMassage(uint8_t *DynamixelBuffer)
{
	 uint16_t crc=0;
	
   for(uint8_t i=0;i<20;i++)
   {
      if(DynamixelBuffer[i] == 0xFF && DynamixelBuffer[i+1]==0xFF)
      {
					for(int j=i;j<(DynamixelBuffer[i+3]+1);j++)/*У���*/
					{
						crc+=DynamixelBuffer[j+2];
					}
					crc=~crc;

					if(DynamixelBuffer[i+7]==crc)
				    Dynamixel[DynamixelBuffer[i+2]].realAngle=DynamixelBuffer[i+5] 
						                                    |(DynamixelBuffer[i+6]<<8);
      }
   }

}

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-10 14:07
	* @brief   
	* @param   void
	* @retval  void
	*/
void Dynamixel2_setMassage(uint8_t ID, uint16_t Length, uint8_t Cmd, uint8_t *Data)
{
	USARTSend_t usartSend;
	
	usartSend.USART_x=USART_2;
	usartSend.pUSARTSendBuff[0]=0xFF;
	usartSend.pUSARTSendBuff[1]=0xFF;
	usartSend.pUSARTSendBuff[2]=0xFD;

	usartSend.pUSARTSendBuff[3]=0x00;
	usartSend.pUSARTSendBuff[4]=ID;
	usartSend.pUSARTSendBuff[5]=Length;
	usartSend.pUSARTSendBuff[6]=Length>>8;
	
	usartSend.pUSARTSendBuff[7]=Cmd;

	memcpy(&usartSend.pUSARTSendBuff[8],Data,Length-3);

	usartSend.crc=update_crc(0,usartSend.pUSARTSendBuff,Length+5);
	usartSend.pUSARTSendBuff[8+Length-3]=usartSend.crc;
	usartSend.pUSARTSendBuff[9+Length-3]=usartSend.crc>>8;
	
	xQueueSend(xusartTxQueue, &usartSend, 20);
   
}

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-10 14:07
	* @brief   DXL1.0Э��򵥴������
  * @param   ID�������ID��Length�����ݳ��ȣ�Cmd ���*Data��Ҫ���͵�����
	* @retval  void
	*/
void Dynamixel1_setMassage(uint8_t ID, uint16_t Length, uint8_t Cmd, uint8_t *Data)
{
	USARTSend_t usartSend;
	uint8_t sendBuff[Length+4];/*�����ڴ�*/
	
	usartSend.USART_x=USART_2;
	usartSend.pUSARTSendBuff=sendBuff;/*��ȡ�ڴ��ַ*/
	
	usartSend.pUSARTSendBuff[0]=0xFF;
	usartSend.pUSARTSendBuff[1]=0xFF;
	usartSend.pUSARTSendBuff[2]=ID;
	usartSend.pUSARTSendBuff[3]=Length;
	usartSend.pUSARTSendBuff[4]=Cmd;
	
  if(Data!=NULL)/*��������ݾͿ���*/
	{
  	memcpy(&usartSend.pUSARTSendBuff[5],Data,Length-2 );
	}
	for(int i=0;i<Length+1;i++)/*У���*/
	{
		usartSend.crc+=usartSend.pUSARTSendBuff[i+2];
	}
	usartSend.pUSARTSendBuff[Length+3]=~usartSend.crc;
	
	xQueueSend(xusartTxQueue, &usartSend, 20);/*�����ݷ��͵�����*/
	
}

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-10 14:07
	* @brief   �������д��Ŀ��Ƕ�
	* @param   ID �����ID Cmd������ Data��Ŀ��Ƕ�
	* @retval  void
	*/
void Dynamixel1_setTargetAngle(uint8_t ID, uint8_t Cmd, uint16_t Data)
{
	USARTSend_t usartSend;
	uint8_t sendBuff[9];
	
	usartSend.USART_x=USART_2;
	usartSend.pUSARTSendBuff=sendBuff;
	
	usartSend.pUSARTSendBuff[0]=0xFF;
	usartSend.pUSARTSendBuff[1]=0xFF;
	usartSend.pUSARTSendBuff[2]=ID;
	usartSend.pUSARTSendBuff[3]=0x05;
	
	usartSend.pUSARTSendBuff[4]=Cmd;

  usartSend.pUSARTSendBuff[5]=0x1E;/*λַ*/
	
	usartSend.pUSARTSendBuff[6]=Data;
	usartSend.pUSARTSendBuff[7]=Data>>8;
	
	for(int i=0;i<6;i++)
	{
		usartSend.crc+=usartSend.pUSARTSendBuff[i+2];
	}
	usartSend.pUSARTSendBuff[8]=~usartSend.crc;
	
	xQueueSend(xusartTxQueue, &usartSend, 20);
   
}

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-10 14:07
	* @brief   ͬ��д����Ŀ��Ƕȣ�������Ŀ���ޡ�(Ŀ��Ƕȳ���Ϊ 2 Byte)
	* @param   Num : ����������������Ƕ����ID��Ŀ��Ƕ�
	*          ... :�����ID��Ŀ��Ƕ�
	* @retval  void
	*/
void Dynamixel1_setSyncTarAng(uint8_t Num,...)
{
	USARTSend_t usartSend;
	/***Length = ((L + 1) * N) + 4,	L:Data Length,N:Number of Dynamixel***/
	uint8_t 		Length=3*Num+4;
	
	uint8_t 		sendBuff[Length+4];
	uint16_t		dataBuff[2*Num];/*�����ڴ棬��Ŷ����Ŀ��Ƕ�*/
	
	va_list args;
	va_start(args, Num);/*argsָ���������б��еĵ�һ����ѡ����Num*/
	
	for(int i=0;i<2*Num;i++)/*��ȡID��Ŀ��Ƕ�*/
	{
		dataBuff[i]=va_arg(args,int);
	}

	usartSend.USART_x=USART_2;
	usartSend.pUSARTSendBuff=sendBuff;
	
	usartSend.pUSARTSendBuff[0]=0xFF;
	usartSend.pUSARTSendBuff[1]=0xFF;
	usartSend.pUSARTSendBuff[2]=0xFE;/*���ж��,�㲥ģʽ*/
	usartSend.pUSARTSendBuff[3]=Length;
	usartSend.pUSARTSendBuff[4]=SYNC_WRITE;/*ͬ��д������*/
  usartSend.pUSARTSendBuff[5]=0x1E;/*λַ*/
	usartSend.pUSARTSendBuff[6]=0x02;/*�������ݳ��ȣ�Ŀ��Ƕȳ���Ϊ 2 Byte*/
	
	for(int i=0;i<Num;i++)/*���ID��Ŀ��Ƕ�*/
	{
		usartSend.pUSARTSendBuff[7+3*i]=dataBuff[2*i];
		usartSend.pUSARTSendBuff[8+3*i]=dataBuff[2*i+1];
		usartSend.pUSARTSendBuff[9+3*i]=dataBuff[2*i+1]>>8;
	}
	
	for(int i=0;i<Length+1;i++)/*У���*/
	{
		usartSend.crc+=usartSend.pUSARTSendBuff[i+2];
	}

	usartSend.pUSARTSendBuff[Length+3]=~usartSend.crc;
	
	xQueueSend(xusartTxQueue, &usartSend, 20);/*�����ݷ��͵�����*/
   
}

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-10 14:07
	* @brief   ͬ��д����Ŀ��Ƕȣ�������Ŀ���ޡ�(Ŀ��Ƕȳ���Ϊ 2 Byte)
  * @param   Addr:λַ��λ��:0x1E���޷�:CW 0x06/CCW 0x08���ٶ�:0x20�����ٶ�:0x49��
	*          Num :���������
	*          ... :�����ID��Ŀ��Ƕ�/�ٶ�/���ٶ�(ȡ����λַAdrr)��
	* @retval  void
	*/
void Dynamixel1_setSyncMsg(uint8_t Addr,uint8_t Num,...)
{
	USARTSend_t usartSend;
	/***Length = ((L + 1) * N) + 4,	L:Data Length,N:Number of Dynamixel
	���ٶ�L=1���ٶȺ�λ��L=2*/
	uint8_t Length = Addr==ACC ? 2*Num + 4 : 3*Num + 4;
	uint8_t sendBuff[Length+4];/*�����ڴ棬��ŷ��͵�����*/
	uint16_t dataBuff[2*Num];/*�����ڴ棬��Ŷ��Ŀ������*/
	
	va_list args;
	va_start(args, Num);/*argsָ���������б��еĵ�һ����ѡ����Num*/
	
	for(int i=0;i<2*Num;i++)/*��ȡID��Ŀ������*/
	{
		dataBuff[i]=va_arg(args,int);
	}

	usartSend.USART_x=USART_2;
	usartSend.pUSARTSendBuff=sendBuff;/*��ȡ�ڴ��ַ*/
	
	usartSend.pUSARTSendBuff[0]=0xFF;
	usartSend.pUSARTSendBuff[1]=0xFF;
	usartSend.pUSARTSendBuff[2]=0xFE;/*���ж��*/
	usartSend.pUSARTSendBuff[3]=Length;
	usartSend.pUSARTSendBuff[4]=SYNC_WRITE;/*ͬ��д������*/
  usartSend.pUSARTSendBuff[5]=Addr;/*λַ*/
	
	if(Addr == ACC)
	{
		usartSend.pUSARTSendBuff[6]=0x01;/*�������ݳ��ȣ�Ŀ����ٶȳ���Ϊ 1 Byte*/
		for(int i=0;i<Num;i++)/*���ID��Ŀ����ٶ�*/
		{
			usartSend.pUSARTSendBuff[7+2*i]=dataBuff[2*i];
			usartSend.pUSARTSendBuff[8+2*i]=dataBuff[2*i+1];
		}
	}
	else
	{
		usartSend.pUSARTSendBuff[6]=0x02;/*�������ݳ��ȣ�Ŀ��Ƕ�/�ٶȳ���Ϊ 2 Byte*/
	  for(int i=0;i<Num;i++)/*���ID��Ŀ��Ƕ�/�ٶ�*/
		{
			usartSend.pUSARTSendBuff[7+3*i]=dataBuff[2*i];
			usartSend.pUSARTSendBuff[8+3*i]=dataBuff[2*i+1];
			usartSend.pUSARTSendBuff[9+3*i]=dataBuff[2*i+1]>>8;
		}
	}

	for(int i=0;i<Length+1;i++)/*У���*/
	{
		usartSend.crc+=usartSend.pUSARTSendBuff[i+2];
	}

	usartSend.pUSARTSendBuff[Length+3]=~usartSend.crc;
	
	xQueueSend(xusartTxQueue, &usartSend, 20);/*�����ݷ��͵�����*/
   
}

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-10 14:07
	* @brief   ͬ�����Ŀ��Ƕȣ�������Ŀ���ޡ�(Ŀ��Ƕȳ���Ϊ 2 Byte)
  * @param   Addr:λַ��λ��:0x1E���޷�:CW 0x06/CCW 0x08���ٶ�:0x20�����ٶ�:0x49��
	*          Num :����������������Ƕ����ID��Ŀ��λַ��
	* @retval  void
	*/
void Dynamixel1_setBulkReadMsg(uint8_t Num,...)
{
	USARTSend_t usartSend;
	/***Length = 3 * N + 3,	N:Number of Dynamixel*/
	uint8_t Length = 3*Num+3;
	uint8_t sendBuff[Length+4];/*�����ڴ棬��ŷ��͵�����*/
	uint8_t dataBuff[2*Num];/*�����ڴ棬��Ŷ��Ŀ������*/
	
	va_list args;
	va_start(args, Num);/*argsָ���������б��еĵ�һ����ѡ����Num*/
	
	for(int i=0;i<2*Num;i++)/*��ȡID��Ŀ������*/
	{
		dataBuff[i]=va_arg(args,int);
	}

	usartSend.USART_x=USART_2;
	usartSend.pUSARTSendBuff=sendBuff;/*��ȡ�ڴ��ַ*/
	
	usartSend.pUSARTSendBuff[0]=0xFF;
	usartSend.pUSARTSendBuff[1]=0xFF;
	usartSend.pUSARTSendBuff[2]=0xFE;/*���ж��*/
	usartSend.pUSARTSendBuff[3]=Length;
	usartSend.pUSARTSendBuff[4]=BULK_READ;/*ͬ��д������*/
  usartSend.pUSARTSendBuff[5]=0x00;
	usartSend.pUSARTSendBuff[6]=0x02;

	for(int i=0;i<Num;i++)/*���ID��Ŀ����ٶ�*/
	{
		usartSend.pUSARTSendBuff[7+2*i]=dataBuff[2*i];
		usartSend.pUSARTSendBuff[8+2*i]=dataBuff[2*i+1];
	}

	for(int i=0;i<Length+1;i++)/*У���*/
	{
		usartSend.crc+=usartSend.pUSARTSendBuff[i+2];
	}

	usartSend.pUSARTSendBuff[Length+3]=~usartSend.crc;
	
	xQueueSend(xusartTxQueue, &usartSend, 20);/*�����ݷ��͵�����*/
   
}


/*---------------------L O C A L - F U N C T I O N S--------------------------*/



/*-----------------------------------FILE OF END------------------------------*/





