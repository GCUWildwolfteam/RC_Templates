#include "stm32f4xx_it.h"
#include <stdio.h>
#include "Task_Usart.h"
#include "Task_can.h"
#include "BSP_USART.h"
#include "BSP_CAN.h"
/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  USART1中断服务函数，DR遥控器
  * @param  None
  * @retval None
  */
void USART1_IRQHandler(void)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	
	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)
	{
		/*关闭DMA*/
		DMA_Cmd(USART1_RX_DMA_STREAM, DISABLE);
		/*获取DMAbuff剩余大小，是否匹配*/
		if (DMA_GetCurrDataCounter(USART1_RX_DMA_STREAM) == 2)
		{
			xQueueSendFromISR(xUsart1RxQueue,&Usart1Buffer,&xHigherPriorityTaskWoken);
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
		}
		
		/*打开DMA*/
		DMA_Cmd(USART1_RX_DMA_STREAM, ENABLE);
		/*清除空闲中断标志位*/
		(void)USART1->DR;
		(void)USART1->SR;

	}
}

void USART2_IRQHandler(void)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	
	if(USART_GetITStatus(USART2, USART_IT_IDLE) != RESET)
	{
		/*关闭DMA*/
		DMA_Cmd(USART2_RX_DMA_STREAM, DISABLE);
		/*获取DMAbuff剩余大小，是否匹配*/
		xQueueSendFromISR(xUsart2RxQueue,&Usart2Buffer,&xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
		
		/*打开DMA*/
		DMA_Cmd(USART2_RX_DMA_STREAM, ENABLE);
		/*清除空闲中断标志位*/
		(void)USART2->DR;
		(void)USART2->SR;

	}
}

void USART3_IRQHandler(void)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	
	if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)
	{
		/*关闭DMA*/
		DMA_Cmd(USART3_RX_DMA_STREAM, DISABLE);
		/*获取DMAbuff剩余大小，是否匹配*/
		if (DMA_GetCurrDataCounter(USART3_RX_DMA_STREAM) == 2)
		{
			xQueueSendFromISR(xUsart3RxQueue,&Usart3Buffer,&xHigherPriorityTaskWoken);
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
		}
		
		/*打开DMA*/
		DMA_Cmd(USART3_RX_DMA_STREAM, ENABLE);
		/*清除空闲中断标志位*/
		(void)USART3->DR;
		(void)USART3->SR;

	}
}
/******************************************************************************/
void CAN1_RX0_IRQHandler(void)
{
	CanRxMsg rxMessage;	
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	
	if(CAN_GetITStatus(CAN1, CAN_IT_FMP0))
	{
		CAN_Receive(CAN1, CAN_FIFO0, &rxMessage);
		xQueueSendFromISR(xCan1RxQueue, &rxMessage, &xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
		
  	CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
	}
}



/******************************************************************************/
void CAN2_RX0_IRQHandler(void)
{
	CanRxMsg rxMessage;	
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	if(CAN_GetITStatus(CAN2, CAN_IT_FMP0))
	{
		CAN_Receive(CAN2, CAN_FIFO0, &rxMessage);
		xQueueSendFromISR(xCan2RxQueue, &rxMessage, &xHigherPriorityTaskWoken);
		portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
		
    CAN_ClearITPendingBit(CAN2, CAN_IT_FMP0);
	}
	
}

/******************************************************************************/

