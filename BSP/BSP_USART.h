/**
|-------------------------------- Copyright -----------------------------------|
|                                                                              |
|                        (C) Copyright 2019, Daqo Lee,                         |
|                                                                              |
|                            By:GCU The wold of team                           |
|                         https://github.com/GCUWildwolfteam                   |
|------------------------------------------------------------------------------|
|--FileName    : BSP_USART.h                                                
|--Version     : v1.0                                                            
|--Author      : Daqo Lee                                                       
|--Date        : 2019-01-18               
|--Libsupports : STM32F4xx_DFP ( 2.9.0)
|--Description :                                                       
|---------------------------------declaration of end----------------------------|
 **/
#ifndef __BSP_USART_H 
#define __BSP_USART_H 
 
/*--------------------- I N C L U D E - F I L E S ----------------------------*/
#include "BSP_DMA.h"
#include "stdio.h"	

/*-------------------------G L O B A L - T Y P E S----------------------------*/

typedef enum
{
  USART_1=1,
  USART_2=2,
  USART_3=3,
  UART_4 =4,
  UART_5 =5,
  USART_6=6,
  
}USARTx_e;
typedef struct
{
  USARTx_e USART_x;
  uint16_t crc;
  uint8_t pUSARTSendBuff[13];
}USARTSend_t;

/*------------------------G L O B A L - M A C R O S --------------------------*/

/********USART1_Pin_define*************/
#define USART1_TX_GPIO_CLK      RCC_AHB1Periph_GPIOB
#define USART1_TX_GPIO_PORT     GPIOB
#define USART1_TX_Pin          	GPIO_Pin_6
#define USART1_TX_PINSOURCE			GPIO_PinSource6

#define USART1_RX_GPIO_CLK      RCC_AHB1Periph_GPIOB
#define USART1_RX_GPIO_PORT     GPIOB
#define USART1_RX_Pin           GPIO_Pin_7
#define USART1_RX_PINSOURCE			GPIO_PinSource7
/********USART1_Pin_define_END********/

/********USART2_Pin_define************/
#define USART2_TX_GPIO_CLK       RCC_AHB1Periph_GPIOD
#define USART2_TX_GPIO_PORT      GPIOD
#define USART2_TX_Pin          	 GPIO_Pin_5
#define USART2_TX_PINSOURCE			 GPIO_PinSource5

#define USART2_RX_GPIO_CLK       RCC_AHB1Periph_GPIOD
#define USART2_RX_GPIO_PORT      GPIOD
#define USART2_RX_Pin            GPIO_Pin_6
#define USART2_RX_PINSOURCE			 GPIO_PinSource6
/********USART2_Pin_define_END********/

/********USART3_Pin_define************/
#define USART3_TX_GPIO_CLK       RCC_AHB1Periph_GPIOD
#define USART3_TX_GPIO_PORT      GPIOD
#define USART3_TX_Pin          	 GPIO_Pin_8
#define USART3_TX_PINSOURCE			 GPIO_PinSource8

#define USART3_RX_GPIO_CLK       RCC_AHB1Periph_GPIOD
#define USART3_RX_GPIO_PORT      GPIOD
#define USART3_RX_Pin            GPIO_Pin_9
#define USART3_RX_PINSOURCE			 GPIO_PinSource9
/********USART3_Pin_define_END********/

/********UART4_Pin_define*************/
#define UART4_TX_GPIO_CLK         RCC_AHB1Periph_GPIOA
#define UART4_TX_GPIO_PORT        GPIOA
#define UART4_TX_Pin          	 	GPIO_Pin_0
#define UART4_TX_PINSOURCE			  GPIO_PinSource0

#define UART4_RX_GPIO_CLK         RCC_AHB1Periph_GPIOA
#define UART4_RX_GPIO_PORT        GPIOA
#define UART4_RX_Pin           		GPIO_Pin_1
#define UART4_RX_PINSOURCE			  GPIO_PinSource1
/********UART4_Pin_define_END********/
/********USART6_Pin_define***********/
#define USART6_TX_GPIO_CLK        RCC_AHB1Periph_GPIOG
#define USART6_TX_GPIO_PORT       GPIOG
#define USART6_TX_Pin          	 	GPIO_Pin_14
#define USART6_TX_PINSOURCE			  GPIO_PinSource14

#define USART6_RX_GPIO_CLK        RCC_AHB1Periph_GPIOG
#define USART6_RX_GPIO_PORT       GPIOG
#define USART6_RX_Pin           	GPIO_Pin_9
#define USART6_RX_PINSOURCE			  GPIO_PinSource9
/********USART6_Pin_define_END********/

/*----------------------G L O B A L - D E F I N E S---------------------------*/

extern uint8_t Usart1Buffer[20];
extern uint8_t Usart2Buffer[26];
extern uint8_t Usart3Buffer[26];

/*-----------G L O B A L - F U N C T I O N S - P R O T O T Y P E S------------*/

void BSP_USART1_Init(uint32_t BaudRate);
void BSP_USART2_Init(uint32_t BaudRate);
void BSP_USART3_Init(uint32_t BaudRate);
void USART_sendChar(USART_TypeDef* USARTx, char ch);

#endif	// __BSP_USART_H
/*----------------------------------FILE OF END-------------------------------*/





 

