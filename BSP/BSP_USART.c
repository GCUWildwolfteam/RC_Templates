/**
|-------------------------------- Copyright -----------------------------------|
|                                                                              |
|                     (C) Copyright 2019, Daqo Lee                             |
|                                                                              |
|                          By:GCU The wold of team                             |
|                     https://github.com/GCUWildwolfteam                       |
|------------------------------------------------------------------------------|
|  FileName    : BSP_USART.c                                                
|  Version     : v1.0                                                            
|  Author      : Daqo Lee                                                       
|  Date        : 2019-01-18               
|  Libsupports : STM32F4xx_DFP ( 2.9.0)
|  Description :                                                       
|------------------------------declaration of end------------------------------|
 **/
/*--------------------- I N C L U D E - F I L E S ----------------------------*/
#include "BSP_USART.h" 
	
/*-------------------------- D E F I N E S -----------------------------------*/

uint8_t Usart1Buffer[20];
uint8_t Usart2Buffer[26];
uint8_t Usart3Buffer[26];
uint8_t Usart2SendBuffer[9];

/*-----------L O C A L - F U N C T I O N S - P R O T O T Y P E S--------------*/



/*------------------G L O B A L - F U N C T I O N S --------------------------*/
/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-18 16:32
	* @brief   USART1��ʼ��
	* @param   BaudRate ������
	* @retval  void
	*/
void BSP_USART1_Init(uint32_t BaudRate)
{
	USART_InitTypeDef   USART_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	RCC_AHB1PeriphClockCmd(USART1_TX_GPIO_CLK | USART1_RX_GPIO_CLK,ENABLE);
			/* GPIO��ʼ�� */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		/* ����Tx����  */
	GPIO_InitStructure.GPIO_Pin = USART1_TX_Pin;  
	GPIO_Init(USART1_TX_GPIO_PORT, &GPIO_InitStructure);

	/* ����Rx���� */
	GPIO_InitStructure.GPIO_Pin = USART1_RX_Pin;
	GPIO_Init(USART1_RX_GPIO_PORT, &GPIO_InitStructure);
	
	/* ���� PXx �� USARTx_Tx*/
	GPIO_PinAFConfig(USART1_TX_GPIO_PORT, USART1_TX_PINSOURCE, GPIO_AF_USART1);

	/*  ���� PXx �� USARTx_Rx*/
	GPIO_PinAFConfig(USART1_RX_GPIO_PORT, USART1_RX_PINSOURCE, GPIO_AF_USART1);

	USART_InitStructure.USART_BaudRate           = BaudRate;
	USART_InitStructure.USART_HardwareFlowControl= USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode               = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity             = USART_Parity_No;
	USART_InitStructure.USART_StopBits           = USART_StopBits_1;
	USART_InitStructure.USART_WordLength         = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStructure);
	
	DMA_USART1RxConfig((uint32_t)Usart1Buffer,20);
	
	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
	/* ʹ�ܴ��ڿ����ж� */
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
	USART_Cmd(USART1, ENABLE);
}

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-18 16:32
	* @brief   USART2��ʼ��
	* @param   BaudRate ������
	* @retval  void
	*/
void BSP_USART2_Init(uint32_t BaudRate)
{
	USART_InitTypeDef   USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	RCC_AHB1PeriphClockCmd(USART2_TX_GPIO_CLK | USART2_RX_GPIO_CLK,ENABLE);
			/* GPIO��ʼ�� */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		/* ����Tx����  */
	GPIO_InitStructure.GPIO_Pin = USART2_TX_Pin;  
	GPIO_Init(USART2_TX_GPIO_PORT, &GPIO_InitStructure);
	
	/* ����Rx���� */
	GPIO_InitStructure.GPIO_Pin = USART2_RX_Pin;
	GPIO_Init(USART2_RX_GPIO_PORT, &GPIO_InitStructure);
	
	/* ���� PXx �� USARTx_Tx*/
	GPIO_PinAFConfig(USART2_TX_GPIO_PORT, USART2_TX_PINSOURCE, GPIO_AF_USART2);
	/*  ���� PXx �� USARTx_Rx*/
	GPIO_PinAFConfig(USART2_RX_GPIO_PORT, USART2_RX_PINSOURCE, GPIO_AF_USART2);

	USART_InitStructure.USART_BaudRate           = BaudRate;
	USART_InitStructure.USART_HardwareFlowControl= USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode               = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity             = USART_Parity_No;
	USART_InitStructure.USART_StopBits           = USART_StopBits_1;
	USART_InitStructure.USART_WordLength         = USART_WordLength_8b;
	USART_Init(USART2, &USART_InitStructure);


	DMA_USART2RxConfig((uint32_t)Usart2Buffer,26);
	//DMA_USART2TxConfig((uint32_t)Usart2SendBuffer,9);
	
	USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);
	/* ʹ�ܴ��ڿ����ж� */
//	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);
	USART_Cmd(USART2, ENABLE);
  USART_ClearFlag(USART2, USART_FLAG_TC);  
}

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-18 16:32
	* @brief   USART2��ʼ��
	* @param   BaudRate ������
	* @retval  void
	*/
void BSP_USART2_Half_Init(uint32_t BaudRate)
{
	USART_InitTypeDef   USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	RCC_AHB1PeriphClockCmd(USART2_TX_GPIO_CLK | USART2_RX_GPIO_CLK,ENABLE);
			/* GPIO��ʼ�� */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		/* ����Tx����  */
	GPIO_InitStructure.GPIO_Pin = USART2_TX_Pin;  
	GPIO_Init(USART2_TX_GPIO_PORT, &GPIO_InitStructure);

	/* ���� PXx �� USARTx_Tx*/
	GPIO_PinAFConfig(USART2_TX_GPIO_PORT, USART2_TX_PINSOURCE, GPIO_AF_USART2);

	USART_InitStructure.USART_BaudRate           = BaudRate;
	USART_InitStructure.USART_HardwareFlowControl= USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode               = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity             = USART_Parity_No;
	USART_InitStructure.USART_StopBits           = USART_StopBits_1;
	USART_InitStructure.USART_WordLength         = USART_WordLength_8b;
	USART_Init(USART2, &USART_InitStructure);

//	USART2->CR3&=0<<5;//��SCEN
//	USART2->CR3&=0<<1; //��IREN
//	USART2->CR2&=0<<11;//��CLKEN
//	USART2->CR2&=0<<14; //��LINEN
  

	DMA_USART2RxConfig((uint32_t)Usart2Buffer,26);
	//DMA_USART2TxConfig((uint32_t)Usart2SendBuffer,9);
	
	USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);
	/* ʹ�ܴ��ڿ����ж� */
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);
	USART_Cmd(USART2, ENABLE);
	USART_HalfDuplexCmd( USART2, ENABLE);
  USART_ClearFlag(USART2, USART_FLAG_TC);  
}
void USART_Half_Configuration(void)  
{  
    GPIO_InitTypeDef GPIO_InitStructure;  
    USART_InitTypeDef USART_InitStructure;   

    GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_USART1);  

    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;  
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  
    GPIO_Init(GPIOB, &GPIO_InitStructure);  


    USART_InitStructure.USART_BaudRate = 115200;  
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;  
    USART_InitStructure.USART_StopBits = USART_StopBits_1;  
    USART_InitStructure.USART_Parity = USART_Parity_No;  
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;  
    USART_Init(USART1,&USART_InitStructure);  

    USART_HalfDuplexCmd(USART1, ENABLE);  

    USART_Cmd(USART1,ENABLE);  
    USART_ClearFlag(USART1, USART_FLAG_TC);  
}
/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-18 16:32
	* @brief   USART3��ʼ��
	* @param   BaudRate ������
	* @retval  void
	*/
void BSP_USART3_Init(uint32_t BaudRate)
{
	USART_InitTypeDef   USART_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(USART3_TX_GPIO_CLK | USART3_RX_GPIO_CLK,ENABLE);
			/* GPIO��ʼ�� */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		/* ����Tx����  */
	GPIO_InitStructure.GPIO_Pin = USART3_TX_Pin;  
	GPIO_Init(USART3_TX_GPIO_PORT, &GPIO_InitStructure);

	/* ����Rx���� */
	GPIO_InitStructure.GPIO_Pin = USART3_RX_Pin;
	GPIO_Init(USART3_RX_GPIO_PORT, &GPIO_InitStructure);
	
	/* ���� PXx �� USARTx_Tx*/
	GPIO_PinAFConfig(USART3_TX_GPIO_PORT, USART3_TX_PINSOURCE, GPIO_AF_USART3);

	/*  ���� PXx �� USARTx_Rx*/
	GPIO_PinAFConfig(USART3_RX_GPIO_PORT, USART3_RX_PINSOURCE, GPIO_AF_USART3);
	
	USART_InitStructure.USART_BaudRate           = BaudRate;
	USART_InitStructure.USART_HardwareFlowControl= USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode               = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity             = USART_Parity_No;
	USART_InitStructure.USART_StopBits           = USART_StopBits_1;
	USART_InitStructure.USART_WordLength         = USART_WordLength_8b;
	USART_Init(USART3, &USART_InitStructure);
	
	DMA_USART3RxConfig((uint32_t)Usart3Buffer,26);

	USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE);
	/* ʹ�ܴ��ڿ����ж� */
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);
	USART_Cmd(USART3, ENABLE);
}
/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-01-18 16:32
	* @brief   ���ڷ���һ���ַ�
	* @param   USARTx ���ںţ�ch:Ҫ���͵��ַ�
	* @retval  void
	*/
void USART_sendChar(USART_TypeDef* USARTx, char ch)
{
	/* ����һ���ֽ����ݵ����� */
	USART_SendData(USARTx, (uint8_t) ch);
	/* �ȴ�������� */
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);	
}



#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	
	while((USART2->SR&0X40)==0);//ѭ������,ֱ���������   
	USART2->DR = (u8) ch;      
	return ch;
}
#endif 

/*---------------------L O C A L - F U N C T I O N S--------------------------*/



/*-----------------------------------FILE OF END------------------------------*/





