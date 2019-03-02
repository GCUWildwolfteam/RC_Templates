/**
|-------------------------------- Copyright -----------------------------------|
|                                                                              |
|                     (C) Copyright 2019, Daqo Lee                             |
|                                                                              |
|                          By:GCU The wold of team                             |
|                     https://github.com/GCUWildwolfteam                       |
|------------------------------------------------------------------------------|
|  FileName    : Task_Usart.c                                                
|  Version     : v1.0                                                            
|  Author      : Daqo Lee                                                       
|  Date        : 2019-02-20               
|  Libsupports : STM32F4xx_DFP ( 2.9.0)
|  Description :                                                       
|------------------------------declaration of end------------------------------|
 **/
/*--------------------- I N C L U D E - F I L E S ----------------------------*/
#include "Task_Usart.h"
#include "BSP_USART.h"
#include "DR16.h"
#include "LED.h"
#include "Encoder.h"
#include "Servo.h"
/*-------------------------- D E F I N E S -----------------------------------*/

QueueHandle_t xUsart1RxQueue = NULL;
QueueHandle_t xUsart2RxQueue = NULL;
QueueHandle_t xUsart3RxQueue = NULL;
QueueHandle_t xusartTxQueue = NULL;

static TaskHandle_t xHandleUsart1Receive = NULL;
static TaskHandle_t xHandleUsart2Receive = NULL;
static TaskHandle_t xHandleUsart3Receive = NULL;
static TaskHandle_t xHandleUsartsend     = NULL;

/*-----------L O C A L - F U N C T I O N S - P R O T O T Y P E S--------------*/

static void vTaskUsart1Receive(void *pvParameters);
static void vTaskUsart2Receive(void *pvParameters);
static void vTaskUsart3Receive(void *pvParameters);
static void vTaskUsartSend(void *pvParameters);

/*------------------G L O B A L - F U N C T I O N S --------------------------*/

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-02-20 15:59
	* @brief   USART任务创建函数
	* @param   void
	* @retval  void
	*/
void UsartTaskCreate(void)
{
	xUsart1RxQueue = xQueueCreate(20,20*sizeof(uint8_t));
	xUsart2RxQueue = xQueueCreate(20,20*sizeof(uint8_t));
	xUsart3RxQueue = xQueueCreate(20,20*sizeof(uint8_t));
	xusartTxQueue  = xQueueCreate(20,sizeof(USARTSend_t));

	
	xTaskCreate(vTaskUsart1Receive,             /* 任务函数  */
						  "vTaskUsart1Receive",           /* 任务名    */
						  128,       			                /* 任务栈大小*/
					  	NULL,                           /* 任务参数  */
					  	3,       			                  /* 任务优先级*/
					  	&xHandleUsart1Receive);         /* 任务句柄  */ 
	
	xTaskCreate(vTaskUsart2Receive,            
					  	"vTaskUsart2Receive",          
						  128,       			   
						  NULL,                 
						  3,       			   
					  	&xHandleUsart2Receive);	
	
	xTaskCreate(vTaskUsart3Receive,            
					  	"vTaskUsart3Receive",          
						  128,       			   
						  NULL,                 
						  3,       			   
					  	&xHandleUsart3Receive);

	xTaskCreate(vTaskUsartSend,            
					  	"vTaskUsartSend",          
						  128,       			   
						  NULL,                 
						  3,       			   
					  	&xHandleUsartsend);
}


/*---------------------L O C A L - F U N C T I O N S--------------------------*/

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-02-20 15:59
	* @brief   USART1解析任务
	* @param   void
	* @retval  void
	*/
static void vTaskUsart1Receive(void *pvParameters)
{
  uint8_t usart1RxBuffer[20];
  while(1)
	{
	  xQueueReceive(xUsart1RxQueue, &usart1RxBuffer,portMAX_DELAY);
		DR16.p_DR16getMsg(usart1RxBuffer);
		LED_TOGGLE(LED_G);
	}

}

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-02-20 15:59
	* @brief   USART2解析任务
	* @param   void
	* @retval  void
	*/
static void vTaskUsart2Receive(void *pvParameters)
{
  uint8_t usart2RxBuffer[26];
  while(1)
	{
	  xQueueReceive(xUsart2RxQueue, &usart2RxBuffer,portMAX_DELAY);
		//Posture_getMessage(usart2RxBuffer);
		Dynamixel_getMassage(usart2RxBuffer);
	}

}

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-02-20 15:59
	* @brief   USART3解析任务
	* @param   void
	* @retval  void
	*/
static void vTaskUsart3Receive(void *pvParameters)
{
  uint8_t usart3RxBuffer[20];
  while(1)
	{
	  xQueueReceive(xUsart3RxQueue, &usart3RxBuffer,portMAX_DELAY);

	}

}

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-02-20 15:59
	* @brief   USART发送任务
	* @param   void
	* @retval  void
	*/
static void vTaskUsartSend(void *pvParameters)
{
	USARTSend_t usartSend;
  while(1)
	{
	  xQueueReceive(xusartTxQueue, &usartSend,portMAX_DELAY);
		
    if(usartSend.USART_x==USART_2)
		{

			for(uint8_t i=0;i<usartSend.pUSARTSendBuff[3]+4;i++)
			{
				USART_sendChar(USART2,usartSend.pUSARTSendBuff[i]);
			}
			USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);
      USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);			
		}
		else if(usartSend.USART_x==USART_3)
		{
			for(uint8_t i=0;i<9;i++)
			{
				USART_sendChar(USART3,usartSend.pUSARTSendBuff[i]);
			}			
		}
	}

}

/*------------------------------80 Chars Limit--------------------------------*/
	/**
	* @Data    2019-02-20 15:59
	* @brief   print优化
	* @param   void
	* @retval  void
	*/
void vPrintString(const char *pcString)
{
    taskENTER_CRITICAL();
    {
        printf("%s", pcString);
        fflush(stdout);
    }
    taskEXIT_CRITICAL();
}
/*-----------------------------------FILE OF END------------------------------*/



