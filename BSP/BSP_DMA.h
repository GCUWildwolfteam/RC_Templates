/**
|-------------------------------- Copyright -----------------------------------|
|                                                                              |
|                        (C) Copyright 2019, Daqo Lee,                         |
|                                                                              |
|                            By:GCU The wold of team                           |
|                         https://github.com/GCUWildwolfteam                   |
|------------------------------------------------------------------------------|
|--FileName    : BSP_DMA.h                                                
|--Version     : v1.0                                                            
|--Author      : Daqo Lee                                                       
|--Date        : 2019-01-18               
|--Libsupports : STM32F4xx_DFP ( 2.9.0)
|--Description :                                                       
|---------------------------------declaration of end----------------------------|
 **/
#ifndef __BSP_DMA_H 
#define __BSP_DMA_H 
/*--------------------- I N C L U D E - F I L E S ----------------------------*/

#include "stm32f4xx.h"

/*-------------------------G L O B A L - T Y P E S----------------------------*/



/*------------------------G L O B A L - M A C R O S --------------------------*/

/********USART1_DMA_define********/
#define USART1_RX_ADDR					(uint32_t)(&USART1->DR)	/*����1���ݼĴ�����ַ*/
#define USART1_RX_DMA_CHANNEL   DMA_Channel_4	         	/*DMAͨ����*/
#define USART1_RX_DMA_STREAM    DMA2_Stream2		        /*DMA������*/
/********USART1_DMA_define_END********/

/********USART2_DMA_define********/
#define USART2_RX_ADDR						(uint32_t)(&USART2->DR)	//����1���ݼĴ�����ַ
#define USART2_RX_DMA_CHANNEL           	DMA_Channel_4		//DMAͨ����
#define USART2_RX_DMA_STREAM           		DMA1_Stream5		//DMA������

#define USART2_TX_ADDR						(uint32_t)(&USART2->DR)	//����1���ݼĴ�����ַ
#define USART2_TX_DMA_CHANNEL           	DMA_Channel_4		//DMAͨ����
#define USART2_TX_DMA_STREAM           		DMA1_Stream6		//DMA������
/********USART2_DMA_define_END********/

/********USART3_DMA_define********/
#define USART3_RX_ADDR						(uint32_t)(&USART3->DR)	//����1���ݼĴ�����ַ
#define USART3_RX_DMA_CHANNEL           	DMA_Channel_4		//DMAͨ����
#define USART3_RX_DMA_STREAM           		DMA1_Stream1		//DMA������
/********USART3_DMA_define_END********/

/*----------------------G L O B A L - D E F I N E S---------------------------*/



/*-----------G L O B A L - F U N C T I O N S - P R O T O T Y P E S------------*/

void DMA_USART1RxConfig(uint32_t USART1_DMABuff_addr, uint32_t buffsize);
void DMA_USART2RxConfig(uint32_t USART2_DMABuff_addr, uint32_t buffsize);
void DMA_USART3RxConfig(uint32_t USART3_DMABuff_addr, uint32_t buffsize);
void DMA_USART2TxConfig(uint32_t DMABuffAddr, uint32_t buffsize);

#endif	// __BSP_DMA_H
/*----------------------------------FILE OF END-------------------------------*/











 

